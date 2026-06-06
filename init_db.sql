-- ==========================================
-- 校园二手交易平台（圈圈 - QuanQuan）数据库初始化脚本
-- 适用数据库：MySQL 8.0+ / openGauss
-- 包含：5大强实体表、完整性约束、触发器、存储过程、函数及测试数据
-- ==========================================

CREATE DATABASE IF NOT EXISTS quanquan_db DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci;
USE quanquan_db;

-- ------------------------------------------
-- 1. 删除旧表（按照外键依赖的反向顺序）
-- ------------------------------------------
DROP TABLE IF EXISTS favorites;
DROP TABLE IF EXISTS orders;
DROP TABLE IF EXISTS goods;
DROP TABLE IF EXISTS users;
DROP TABLE IF EXISTS categories;

-- ------------------------------------------
-- 2. 创建实体表
-- ------------------------------------------

-- 2.1 商品分类表（Category）
CREATE TABLE categories (
    id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(50) NOT NULL UNIQUE COMMENT '分类名称',
    description VARCHAR(255) COMMENT '分类描述'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COMMENT='商品分类表';

-- 2.2 用户表（User）
CREATE TABLE users (
    id INT AUTO_INCREMENT PRIMARY KEY,
    username VARCHAR(50) NOT NULL UNIQUE COMMENT '登录用户名',
    password VARCHAR(64) NOT NULL COMMENT '密码哈希值(SHA256)',
    nickname VARCHAR(50) NOT NULL COMMENT '用户昵称',
    balance DECIMAL(10, 2) NOT NULL DEFAULT 1000.00 CHECK (balance >= 0) COMMENT '账户余额(不能小于0)',
    phone VARCHAR(20) COMMENT '联系电话',
    email VARCHAR(100) COMMENT '电子邮箱',
    role VARCHAR(10) NOT NULL DEFAULT 'user' CHECK (role IN ('user', 'admin')) COMMENT '角色: user/admin',
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP COMMENT '注册时间'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COMMENT='用户表';

-- 2.3 商品表（Goods）
CREATE TABLE goods (
    id INT AUTO_INCREMENT PRIMARY KEY,
    title VARCHAR(100) NOT NULL COMMENT '商品标题',
    description TEXT COMMENT '商品详情描述',
    price DECIMAL(10, 2) NOT NULL CHECK (price >= 0) COMMENT '在售单价',
    status INT NOT NULL DEFAULT 1 CHECK (status IN (0, 1, 2)) COMMENT '商品状态: 1-在售, 0-已售, 2-下架',
    category_id INT NOT NULL COMMENT '分类ID外键',
    seller_id INT NOT NULL COMMENT '卖家用户ID外键',
    image_url VARCHAR(255) COMMENT '商品图片链接',
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP COMMENT '发布时间',
    FOREIGN KEY (category_id) REFERENCES categories(id) ON DELETE CASCADE,
    FOREIGN KEY (seller_id) REFERENCES users(id) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COMMENT='二手商品表';

-- 2.4 订单表（Orders）
CREATE TABLE orders (
    id INT AUTO_INCREMENT PRIMARY KEY,
    order_no VARCHAR(50) NOT NULL UNIQUE COMMENT '订单号(唯一编号)',
    buyer_id INT NOT NULL COMMENT '买家ID外键',
    goods_id INT NOT NULL COMMENT '商品ID外键',
    price DECIMAL(10, 2) NOT NULL CHECK (price >= 0) COMMENT '成交价格',
    status INT NOT NULL DEFAULT 0 CHECK (status IN (0, 1, 2)) COMMENT '订单状态: 0-未支付, 1-已支付, 2-已取消',
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP COMMENT '订单创建时间',
    FOREIGN KEY (buyer_id) REFERENCES users(id) ON DELETE CASCADE,
    FOREIGN KEY (goods_id) REFERENCES goods(id) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COMMENT='交易订单表';

-- 2.5 收藏夹表（Favorites）
CREATE TABLE favorites (
    id INT AUTO_INCREMENT PRIMARY KEY,
    user_id INT NOT NULL COMMENT '用户ID外键',
    goods_id INT NOT NULL COMMENT '商品ID外键',
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP COMMENT '收藏时间',
    FOREIGN KEY (user_id) REFERENCES users(id) ON DELETE CASCADE,
    FOREIGN KEY (goods_id) REFERENCES goods(id) ON DELETE CASCADE,
    UNIQUE KEY uq_user_goods (user_id, goods_id) COMMENT '禁止重复收藏同一商品'
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COMMENT='收藏夹关联表';


-- ------------------------------------------
-- 3. 创建索引（提升搜索与多表连接性能）
-- ------------------------------------------
CREATE INDEX idx_goods_title ON goods(title);
CREATE INDEX idx_goods_status ON goods(status);
CREATE INDEX idx_orders_no ON orders(order_no);
CREATE INDEX idx_favorites_user ON favorites(user_id);


-- ------------------------------------------
-- 4. 高级数据库编程：触发器 (Triggers)
-- ------------------------------------------

-- 触发器 1：订单支付联动商品状态更新 (订单支付成功后，商品状态自动变为 0:已售)
DELIMITER //
CREATE TRIGGER trg_order_paid_update_goods
AFTER UPDATE ON orders
FOR EACH ROW
BEGIN
    -- 状态从非已支付更新为已支付(1)
    IF NEW.status = 1 AND OLD.status <> 1 THEN
        UPDATE goods SET status = 0 WHERE id = NEW.goods_id;
    END IF;
END //
DELIMITER ;


-- 触发器 2：下订单/支付前自动检查并扣减余额
-- 当订单状态变更为已支付时，从买家账户扣减余额，并自动增加到卖家账户。
-- 若买家余额不足，则抛出 SQLSTATE '45000' 错误，阻止该事务并回滚。
DELIMITER //
CREATE TRIGGER trg_order_before_pay
BEFORE UPDATE ON orders
FOR EACH ROW
BEGIN
    DECLARE buyer_balance DECIMAL(10, 2);
    DECLARE seller_user_id INT;
    
    IF NEW.status = 1 AND OLD.status <> 1 THEN
        -- 获取买家余额
        SELECT balance INTO buyer_balance FROM users WHERE id = NEW.buyer_id;
        
        -- 获取商品卖家ID
        SELECT seller_id INTO seller_user_id FROM goods WHERE id = NEW.goods_id;
        
        -- 余额校验
        IF buyer_balance < NEW.price THEN
            SIGNAL SQLSTATE '45000'
            SET MESSAGE_TEXT = '支付失败：账户余额不足，请先充值！';
        ELSE
            -- 扣减买家余额
            UPDATE users SET balance = balance - NEW.price WHERE id = NEW.buyer_id;
            -- 增加卖家余额
            UPDATE users SET balance = balance + NEW.price WHERE id = seller_user_id;
        END IF;
    END IF;
END //
DELIMITER ;


-- ------------------------------------------
-- 5. 高级数据库编程：存储过程 (Stored Procedures)
-- ------------------------------------------

-- 存储过程：按用户ID统计其已支付订单的消费总额
DELIMITER //
CREATE PROCEDURE CalculateUserTotalConsumption(
    IN p_user_id INT,
    OUT p_total_consumption DECIMAL(10, 2)
)
BEGIN
    SELECT COALESCE(SUM(price), 0.00) INTO p_total_consumption
    FROM orders
    WHERE buyer_id = p_user_id AND status = 1;
END //
DELIMITER ;


-- ------------------------------------------
-- 6. 高级数据库编程：自定义函数 (Functions)
-- ------------------------------------------

-- 自定义函数：统计某个分类下当前“在售”的商品总数
DELIMITER //
CREATE FUNCTION CountActiveProductsInCategory(
    p_category_id INT
) 
RETURNS INT
DETERMINISTIC
BEGIN
    DECLARE v_count INT;
    SELECT COUNT(*) INTO v_count
    FROM goods
    WHERE category_id = p_category_id AND status = 1;
    RETURN v_count;
END //
DELIMITER ;


-- ------------------------------------------
-- 7. 导入初始测试数据 (5个分类, 4个用户, 10个商品, 并带有收藏和订单关系)
-- ------------------------------------------

-- 7.1 导入分类数据
INSERT INTO categories (name, description) VALUES
('图书教材', '各类二手课本、课外书、专业教材及考研资料'),
('数码产品', '二手手机、笔记本电脑、平板电脑、耳机等数码配件'),
('运动户外', '自行车、篮球、网球拍、健身器材等运动装备'),
('生活用品', '宿舍台灯、小冰箱、风扇、收纳盒等日常百货'),
('票务卡券', '讲座门票、音乐会门票、健身卡、代金券转让');

-- 7.2 导入初始用户数据（密码均为 123456 的 SHA256 哈希值）
-- 123456 的 SHA256: 8d969eef6ecad3c29a3a629280e686cf0c3f5d5a86aff3ca12020c923adc6c92
INSERT INTO users (username, password, nickname, balance, phone, email, role) VALUES
('alice', '8d969eef6ecad3c29a3a629280e686cf0c3f5d5a86aff3ca12020c923adc6c92', '爱丽丝学姐', 1500.00, '13800138001', 'alice@edu.cn', 'user'),
('bob', '8d969eef6ecad3c29a3a629280e686cf0c3f5d5a86aff3ca12020c923adc6c92', '极客鲍勃', 280.50, '13911112222', 'bob@edu.cn', 'user'),
('charlie', '8d969eef6ecad3c29a3a629280e686cf0c3f5d5a86aff3ca12020c923adc6c92', '查理运动狂', 50.00, '13566667777', 'charlie@edu.cn', 'user'),
('admin', '8d969eef6ecad3c29a3a629280e686cf0c3f5d5a86aff3ca12020c923adc6c92', '平台管理员', 99999.00, '13300000000', 'admin@edu.cn', 'admin');

-- 7.3 导入初始商品数据
-- status: 1 - 在售, 0 - 已售, 2 - 下架
INSERT INTO goods (title, description, price, status, category_id, seller_id, image_url) VALUES
('C++ Primer Plus 第6版 中文版', '9.5成新，考研复习买的，里面有少许铅笔划痕，不影响阅读。附送课后习题答案！', 35.00, 1, 1, 1, ''),
('高等数学同济第七版(上下册)', '期末考完低价转让，期末高分飘过，附送考前重点整理笔记！', 15.00, 1, 1, 1, ''),
('iPad Air 5 64G 灰色', '国行在保，自用极度爱惜，全机无磕碰，屏幕完美，带类纸膜和保护壳。仅限学校食堂面交！', 3200.00, 1, 2, 2, ''),
('HHKB Classic 机械键盘', '静电容键盘，静音红轴手感，码农神器。用了半年，键帽无打油，包装盒齐全。', 1200.00, 1, 2, 2, ''),
('捷安特公路自行车 8成新', '适合校内通勤或者周末骑行，变速器灵敏，刹车安全，前轮刚换的内外胎。附送车锁与雨蓬。', 350.00, 1, 3, 3, ''),
('威尔胜威尔逊经典篮球', '正品Wilson 7号标准球，水泥地打过几次，气密性极好，耐磨吸汗。', 80.00, 1, 3, 3, ''),
('宿舍多功能寝室小电锅', '煮面、蒸蛋、小火锅神器，两档火力，不粘锅内胆。毕业带不走，低价出。', 25.00, 1, 4, 1, ''),
('九阳静音家用吹风机', '大风力，带冷热风调节和负离子护发。适合宿舍限电使用，功率在安全范围内。', 30.00, 1, 4, 2, ''),
('草莓音乐节单日门票一张', '周末草莓音乐节，因临时有实验课冲突去不了，痛心割爱转让，可现场或电子票转。', 180.00, 1, 5, 3, ''),
('校园健身房月卡一张', '校园健身房月卡，还剩20天，因腿部拉伤无法去运动，诚意低价转让。', 50.00, 1, 5, 1, '');

-- 7.4 导入初始收藏夹数据
INSERT INTO favorites (user_id, goods_id) VALUES
(1, 3), -- Alice 收藏了 iPad
(1, 4), -- Alice 收藏了 键盘
(2, 1), -- Bob 收藏了 C++ Primer
(2, 5); -- Bob 收藏了 自行车

-- 7.5 导入初始订单数据 (创建一笔已成交订单和一笔待支付订单)
-- 订单1：Bob 向 Alice 买了小电锅，已支付 (已完成)
INSERT INTO orders (order_no, buyer_id, goods_id, price, status) VALUES
('ORDER202605200001', 2, 7, 25.00, 1);
-- 触发器 1 应该会将该商品更新为已售
UPDATE goods SET status = 0 WHERE id = 7;

-- 订单2：Alice 向 Charlie 买了篮球，未支付 (待支付)
INSERT INTO orders (order_no, buyer_id, goods_id, price, status) VALUES
('ORDER202605200002', 1, 6, 80.00, 0);
