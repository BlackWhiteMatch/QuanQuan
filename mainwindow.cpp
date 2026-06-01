#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dbmanager.h"
#include <QMessageBox>
#include "applemsgbox.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDateTime>
#include <QRandomGenerator>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QTableWidgetItem>
#include <QPainter>
#include <QPainterPath>
#include <QGraphicsDropShadowEffect>
#include <QStyledItemDelegate>

// ==========================================================
// 1. GoodsCardWidget - 闲置商品 Apple 风格白底圆角卡片渲染类
// ==========================================================
GoodsCardWidget::GoodsCardWidget(int goodsId, const QString &title, double price, const QString &desc, 
                                 const QString &category, const QString &seller, int status, 
                                 bool isFav, bool isOwn, QWidget *parent)
    : QWidget(parent)
    , m_goodsId(goodsId)
    , m_isFav(isFav)
{
    // 必须开启此属性，否则直接继承自 QWidget 的自定义类不会绘制 QSS 的 background 和 border！
    setAttribute(Qt::WA_StyledBackground, true);
    
    // 设置对象名以匹配 style.qss 中 goodsCard 的样式
    setObjectName("goodsCard");
    setStyleSheet(
        "QWidget#goodsCard {"
        "   background-color: #FFFFFF;"
        "   border: 1px solid #E5E5EA;"
        "   border-radius: 14px;"
        "}"
        "QWidget#goodsCard:hover {"
        "   border: 1px solid #D1D1D6;"
        "   background-color: #FAFAFC;"
        "}"
    );
    
    // 固定卡片高度，防止被网格布局无限拉伸
    setFixedHeight(190);
    
    // 添加高级阴影效果，让卡片悬浮于背景之上，明显区分于页面底色
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setBlurRadius(20);
    shadow->setColor(QColor(0, 0, 0, 15)); // 极其微弱的 Apple 风格柔和黑影 (约 6% 的不透明度)
    shadow->setOffset(0, 4);
    setGraphicsEffect(shadow);
    
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(15, 15, 15, 15);
    layout->setSpacing(8);
    
    // 头部: 标签与状态
    QHBoxLayout *headerLayout = new QHBoxLayout();
    headerLayout->setContentsMargins(0, 0, 0, 0);
    
    QLabel *lblTag = new QLabel(category, this);
    lblTag->setStyleSheet("background-color: #E5F1FF; color: #007AFF; font-size: 11px; font-weight: bold; border-radius: 6px; padding: 3px 8px; border: none;");
    headerLayout->addWidget(lblTag);
    
    headerLayout->addSpacerItem(new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
    
    QLabel *lblStatus = new QLabel(this);
    if (status == 1) {
        lblStatus->setText("在售");
        lblStatus->setStyleSheet("background-color: #E5F8ED; color: #34C759; font-size: 11px; font-weight: bold; border-radius: 6px; padding: 3px 8px; border: none;");
    } else if (status == 0) {
        lblStatus->setText("已售");
        lblStatus->setStyleSheet("background-color: #F2F2F7; color: #86868B; font-size: 11px; font-weight: bold; border-radius: 6px; padding: 3px 8px; border: none;");
    } else {
        lblStatus->setText("下架");
        lblStatus->setStyleSheet("background-color: #FFEAEA; color: #FF3B30; font-size: 11px; font-weight: bold; border-radius: 6px; padding: 3px 8px; border: none;");
    }
    headerLayout->addWidget(lblStatus);
    layout->addLayout(headerLayout);
    
    // 标题
    QLabel *lblTitle = new QLabel(title, this);
    lblTitle->setStyleSheet("font-size: 15px; font-weight: bold; color: #1D1D1F; background: transparent; border: none;");
    lblTitle->setWordWrap(true);
    layout->addWidget(lblTitle);
    
    // 描述 (限高截断)
    QLabel *lblDesc = new QLabel(desc, this);
    lblDesc->setStyleSheet("color: #86868B; font-size: 12px; background: transparent; border: none;");
    lblDesc->setWordWrap(true);
    lblDesc->setMaximumHeight(40);
    layout->addWidget(lblDesc);
    
    layout->addSpacerItem(new QSpacerItem(10, 10, QSizePolicy::Minimum, QSizePolicy::Expanding));
    
    // 价格与卖家
    QHBoxLayout *priceLayout = new QHBoxLayout();
    priceLayout->setContentsMargins(0, 0, 0, 0);
    
    QLabel *lblPrice = new QLabel(QString("￥%1").arg(QString::number(price, 'f', 2)), this);
    lblPrice->setStyleSheet("font-size: 18px; font-weight: bold; color: #FF9500; background: transparent; border: none;");
    priceLayout->addWidget(lblPrice);
    
    priceLayout->addSpacerItem(new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
    
    QLabel *lblSeller = new QLabel(QString("👤 %1").arg(seller), this);
    lblSeller->setStyleSheet("color: #86868B; font-size: 11px; background: transparent; border: none;");
    priceLayout->addWidget(lblSeller);
    layout->addLayout(priceLayout);
    
    // 按钮布局
    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->setContentsMargins(0, 5, 0, 0);
    btnLayout->setSpacing(8);
    
    if (isOwn) {
        // 不显示任何多余标签

    } else {
        QPushButton *btnBuy = new QPushButton("🛒 立即购买", this);
        btnBuy->setObjectName("primaryButton");
        btnBuy->setStyleSheet("height: 28px; font-size: 12px; border-radius: 6px; padding: 4px 10px;");
        if (status != 1) {
            btnBuy->setEnabled(false);
            btnBuy->setText("已售罄");
            btnBuy->setStyleSheet("background-color: #E5E5EA; color: #86868B; height: 28px; font-size: 12px; border-radius: 6px;");
        }
        
        QPushButton *btnFav = new QPushButton(this);
        btnFav->setCheckable(true);
        btnFav->setChecked(isFav);
        
        auto updateFavStyle = [btnFav](bool checked) {
            if (checked) {
                btnFav->setText("★ 已收藏");
                btnFav->setStyleSheet("background-color: #FFF2CC; color: #FF9500; border: 1px solid #FFE0B2; height: 28px; font-size: 12px; border-radius: 6px; padding: 4px 10px; font-weight: bold;");
            } else {
                btnFav->setText("☆ 收藏");
                btnFav->setStyleSheet("background-color: #FFFFFF; color: #86868B; border: 1px solid #D1D1D6; height: 28px; font-size: 12px; border-radius: 6px; padding: 4px 10px;");
            }
        };
        updateFavStyle(isFav);
        
        connect(btnBuy, &QPushButton::clicked, this, [this]() {
            emit buyClicked(m_goodsId);
        });
        
        connect(btnFav, &QPushButton::clicked, this, [this, btnFav, updateFavStyle]() {
            m_isFav = !m_isFav;
            btnFav->setChecked(m_isFav);
            updateFavStyle(m_isFav);
            emit favClicked(m_goodsId, m_isFav);
        });
        
        btnLayout->addWidget(btnBuy);
        btnLayout->addWidget(btnFav);
    }
    layout->addLayout(btnLayout);
}

// ==========================================================
// 2. MainWindow - 圈圈交易主控仪表盘逻辑
// ==========================================================
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    // 给所有下拉菜单加上 QStyledItemDelegate，强制接管底层渲染，让 QSS 中的项悬浮完美生效
    auto setupComboBox = [](QComboBox *cb) {
        cb->setItemDelegate(new QStyledItemDelegate(cb));
    };
    setupComboBox(ui->comboCategoryFilter);
    setupComboBox(ui->comboSellCategory);
    setupComboBox(ui->comboStatsCategory);
    
    // 生成圆角 Logo 给侧边栏
    QPixmap src(":/quanquan.png");
    if (!src.isNull()) {
        int logoSize = 140;
        QPixmap target(logoSize, logoSize);
        target.fill(Qt::transparent);
        QPainter painter(&target);
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
        QPainterPath path;
        path.addRoundedRect(0, 0, logoSize, logoSize, 30, 30);
        painter.setClipPath(path);
        
        QPixmap scaledSrc = src.scaled(logoSize, logoSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        int x = (logoSize - scaledSrc.width()) / 2;
        int y = (logoSize - scaledSrc.height()) / 2;
        painter.drawPixmap(x, y, scaledSrc);
        
        ui->sidebarTitle->setPixmap(target);
    }
    
    // 初始化侧边栏导航与按钮组绑定
    initNavigation();
    
    // 监听各种组件发出的槽信号
    connect(ui->btnRefreshMarket, &QPushButton::clicked, this, &MainWindow::onRefreshMarket);
    
    // 信号重载机制保证 Qt6 兼容性良好
    connect(ui->comboCategoryFilter, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::onCategoryFilterChanged);
    connect(ui->editSearch, &QLineEdit::textChanged, this, &MainWindow::onSearchTextChanged);
    connect(ui->btnPublish, &QPushButton::clicked, this, &MainWindow::onPublishClicked);
    connect(ui->btnRecharge, &QPushButton::clicked, this, &MainWindow::onRechargeClicked);
    connect(ui->comboStatsCategory, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::onStatsCategoryChanged);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initNavigation()
{
    m_navGroup = new QButtonGroup(this);
    m_navGroup->addButton(ui->btnNavMarket, 0);
    m_navGroup->addButton(ui->btnNavSell, 1);
    m_navGroup->addButton(ui->btnNavOrders, 2);
    m_navGroup->addButton(ui->btnNavFavorites, 3);
    m_navGroup->addButton(ui->btnNavProfile, 4);
    
    // 默认排他选中
    m_navGroup->setExclusive(true);
    
    // 监听切换
    connect(m_navGroup, &QButtonGroup::idClicked, this, &MainWindow::onNavButtonClicked);
    connect(ui->btnNavLogout, &QPushButton::clicked, this, &MainWindow::onLogoutClicked);
}

void MainWindow::refreshAllData()
{
    // 加载缓存商品分类
    loadCategories();
    
    // 刷新各个页面
    loadMarket();
    loadOrders();
    loadFavorites();
    loadProfile();
}

void MainWindow::onNavButtonClicked(int index)
{
    if (index >= 0 && index < ui->stackedWidget->count()) {
        ui->stackedWidget->setCurrentIndex(index);
        
        // 针对不同界面打开时执行特定重载加载
        if (index == 0) {
            loadMarket();
        } else if (index == 1) {
            // 用户准备发布商品时，强制重新拉取一次数据库最新分类
            loadCategories();
        } else if (index == 2) {
            loadOrders();
        } else if (index == 3) {
            loadFavorites();
        } else if (index == 4) {
            loadCategories();
            loadProfile();
        }
    }
}

void MainWindow::onLogoutClicked()
{
    QMessageBox::StandardButton reply = AppleMsgBox::question(this, "退出确认", 
        "您确认要退出登录圈圈校园二手交易平台吗？", QMessageBox::Yes | QMessageBox::No);
        
    if (reply == QMessageBox::Yes) {
        DbManager::instance().clearCurrentUser();
        emit logoutRequested();
    }
}

void MainWindow::loadCategories()
{
    DbManager &db = DbManager::instance();
    QSqlQuery q = db.selectQuery("SELECT id, name FROM categories ORDER BY id ASC");
    
    // 暂时阻塞信号，避免初始化添加条目触发连带的 `currentIndexChanged` 检索
    ui->comboCategoryFilter->blockSignals(true);
    ui->comboSellCategory->blockSignals(true);
    ui->comboStatsCategory->blockSignals(true);
    
    ui->comboCategoryFilter->clear();
    ui->comboSellCategory->clear();
    ui->comboStatsCategory->clear();
    
    ui->comboCategoryFilter->addItem("全部商品", 0);
    
    m_categoryMap.clear();
    
    while (q.next()) {
        int id = q.value("id").toInt();
        QString name = q.value("name").toString();
        
        m_categoryMap[id] = name;
        
        ui->comboCategoryFilter->addItem(name, id);
        ui->comboSellCategory->addItem(name, id);
        ui->comboStatsCategory->addItem(name, id);
    }
    
    ui->comboCategoryFilter->blockSignals(false);
    ui->comboSellCategory->blockSignals(false);
    ui->comboStatsCategory->blockSignals(false);
}

void MainWindow::loadMarket()
{
    // 安全移除原先在网格布局中的所有卡片小部件
    QLayoutItem *child;
    while ((child = ui->gridLayoutMarket->takeAt(0)) != nullptr) {
        if (child->widget()) {
            child->widget()->deleteLater();
        }
        delete child;
    }
    
    DbManager &db = DbManager::instance();
    int currentUserId = db.getCurrentUserId();
    
    int catFilter = ui->comboCategoryFilter->currentData().toInt();
    QString searchText = ui->editSearch->text().trimmed();
    
    // 多表 JOIN 级联查询：带出分类名称、卖家昵称，同时查询该用户是否已收藏该商品
    QString sql = 
        "SELECT g.id, g.title, g.description, g.price, g.status, g.category_id, g.seller_id, "
        "       c.name AS category_name, u.nickname AS seller_name, "
        "       (SELECT COUNT(*) FROM favorites f WHERE f.user_id = ? AND f.goods_id = g.id) AS is_fav "
        "FROM goods g "
        "JOIN categories c ON g.category_id = c.id "
        "JOIN users u ON g.seller_id = u.id "
        "WHERE g.status = 1 "; // 默认只在市场中渲染“在售”商品
    
    QVariantList params;
    params << currentUserId;
    
    if (catFilter > 0) {
        sql += " AND g.category_id = ? ";
        params << catFilter;
    }
    
    if (!searchText.isEmpty()) {
        sql += " AND (g.title LIKE ? OR g.description LIKE ?) ";
        params << "%" + searchText + "%" << "%" + searchText + "%";
    }
    
    sql += " ORDER BY g.created_at DESC";
    
    QSqlQuery query = db.selectQuery(sql, params);
    
    int row = 0;
    int col = 0;
    const int maxCols = 3; // 精准3列流式自适应网格排列
    
    while (query.next()) {
        int id = query.value("id").toInt();
        QString title = query.value("title").toString();
        double price = query.value("price").toDouble();
        QString desc = query.value("description").toString();
        QString category = query.value("category_name").toString();
        QString seller = query.value("seller_name").toString();
        int status = query.value("status").toInt();
        bool isFav = query.value("is_fav").toInt() > 0;
        int sellerId = query.value("seller_id").toInt();
        bool isOwn = (sellerId == currentUserId);
        
        GoodsCardWidget *card = new GoodsCardWidget(id, title, price, desc, category, seller, status, isFav, isOwn, this);
        
        connect(card, &GoodsCardWidget::buyClicked, this, &MainWindow::onBuyGoods);
        connect(card, &GoodsCardWidget::favClicked, this, &MainWindow::onFavoriteGoods);
        
        ui->gridLayoutMarket->addWidget(card, row, col);
        
        col++;
        if (col >= maxCols) {
            col = 0;
            row++;
        }
    }
    
    if (row == 0 && col == 0) {
        QLabel *lblEmpty = new QLabel("🛍️ 暂时没有满足条件的宝贝商品在售中，快去发布第一件闲置吧！", this);
        lblEmpty->setAlignment(Qt::AlignCenter);
        lblEmpty->setStyleSheet("color: #86868B; font-size: 14px; font-weight: 500; margin-top: 100px;");
        ui->gridLayoutMarket->addWidget(lblEmpty, 0, 0, 1, 3);
    }
    
    // 强制推顶对齐，避免单行卡片被垂直居中或拉伸
    ui->gridLayoutMarket->addItem(new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding), row + 1, 0, 1, maxCols);
}

void MainWindow::loadFavorites()
{
    QLayoutItem *child;
    while ((child = ui->gridLayoutFav->takeAt(0)) != nullptr) {
        if (child->widget()) {
            child->widget()->deleteLater();
        }
        delete child;
    }
    
    DbManager &db = DbManager::instance();
    int currentUserId = db.getCurrentUserId();
    
    QString sql = 
        "SELECT g.id, g.title, g.description, g.price, g.status, g.category_id, g.seller_id, "
        "       c.name AS category_name, u.nickname AS seller_name "
        "FROM favorites f "
        "JOIN goods g ON f.goods_id = g.id "
        "JOIN categories c ON g.category_id = c.id "
        "JOIN users u ON g.seller_id = u.id "
        "WHERE f.user_id = ? "
        "ORDER BY f.created_at DESC";
    
    QSqlQuery query = db.selectQuery(sql, QVariantList() << currentUserId);
    
    int row = 0;
    int col = 0;
    const int maxCols = 3;
    
    while (query.next()) {
        int id = query.value("id").toInt();
        QString title = query.value("title").toString();
        double price = query.value("price").toDouble();
        QString desc = query.value("description").toString();
        QString category = query.value("category_name").toString();
        QString seller = query.value("seller_name").toString();
        int status = query.value("status").toInt();
        int sellerId = query.value("seller_id").toInt();
        bool isOwn = (sellerId == currentUserId);
        
        // 收藏列表中渲染的商品, 其 isFav 必须标记为 true
        GoodsCardWidget *card = new GoodsCardWidget(id, title, price, desc, category, seller, status, true, isOwn, this);
        
        connect(card, &GoodsCardWidget::buyClicked, this, &MainWindow::onBuyGoods);
        connect(card, &GoodsCardWidget::favClicked, this, &MainWindow::onFavoriteGoods);
        
        ui->gridLayoutFav->addWidget(card, row, col);
        
        col++;
        if (col >= maxCols) {
            col = 0;
            row++;
        }
    }
    
    if (row == 0 && col == 0) {
        QLabel *lblEmpty = new QLabel("⭐ 收藏夹空空如也，快去市场寻找心仪宝贝吧！", this);
        lblEmpty->setAlignment(Qt::AlignCenter);
        lblEmpty->setStyleSheet("color: #86868B; font-size: 14px; font-weight: 500; margin-top: 100px;");
        ui->gridLayoutFav->addWidget(lblEmpty, 0, 0, 1, 3);
    }
    
    // 强制推顶对齐
    ui->gridLayoutFav->addItem(new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding), row + 1, 0, 1, maxCols);
}

void MainWindow::loadOrders()
{
    DbManager &db = DbManager::instance();
    int currentUserId = db.getCurrentUserId();
    
    // --- 1. 我买入的宝贝 ---
    ui->tableBought->clear();
    ui->tableBought->setColumnCount(6);
    ui->tableBought->setHorizontalHeaderLabels(QStringList() << "订单号" << "宝贝名称" << "卖家" << "成交价" << "订单状态" << "交易时间");
    ui->tableBought->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableBought->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableBought->verticalHeader()->setVisible(false);
    
    QString sqlBought = 
        "SELECT o.order_no, o.price, o.status, o.created_at, g.title, u.nickname AS seller_name "
        "FROM orders o "
        "JOIN goods g ON o.goods_id = g.id "
        "JOIN users u ON g.seller_id = u.id "
        "WHERE o.buyer_id = ? "
        "ORDER BY o.created_at DESC";
    
    QSqlQuery qBought = db.selectQuery(sqlBought, QVariantList() << currentUserId);
    int rowB = 0;
    ui->tableBought->setRowCount(0);
    
    while (qBought.next()) {
        ui->tableBought->insertRow(rowB);
        
        ui->tableBought->setItem(rowB, 0, new QTableWidgetItem(qBought.value("order_no").toString()));
        ui->tableBought->setItem(rowB, 1, new QTableWidgetItem(qBought.value("title").toString()));
        ui->tableBought->setItem(rowB, 2, new QTableWidgetItem(qBought.value("seller_name").toString()));
        ui->tableBought->setItem(rowB, 3, new QTableWidgetItem(QString("￥%1").arg(QString::number(qBought.value("price").toDouble(), 'f', 2))));
        
        int status = qBought.value("status").toInt();
        QString statusStr = "未知";
        if (status == 0) statusStr = "未支付";
        else if (status == 1) statusStr = "已支付";
        else if (status == 2) statusStr = "已取消";
        QTableWidgetItem *itemStatus = new QTableWidgetItem(statusStr);
        if (status == 1) itemStatus->setForeground(QBrush(QColor("#34C759")));
        else if (status == 0) itemStatus->setForeground(QBrush(QColor("#FF9500")));
        else itemStatus->setForeground(QBrush(QColor("#FF3B30")));
        
        ui->tableBought->setItem(rowB, 4, itemStatus);
        ui->tableBought->setItem(rowB, 5, new QTableWidgetItem(qBought.value("created_at").toDateTime().toString("yyyy-MM-dd HH:mm:ss")));
        
        rowB++;
    }
    
    // --- 2. 我卖出的宝贝 ---
    ui->tableSold->clear();
    ui->tableSold->setColumnCount(6);
    ui->tableSold->setHorizontalHeaderLabels(QStringList() << "订单号" << "宝贝名称" << "买家" << "成交价" << "交易状态" << "交易时间");
    ui->tableSold->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableSold->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableSold->verticalHeader()->setVisible(false);
    
    QString sqlSold = 
        "SELECT o.order_no, o.price, o.status, o.created_at, g.title, u.nickname AS buyer_name "
        "FROM orders o "
        "JOIN goods g ON o.goods_id = g.id "
        "JOIN users u ON o.buyer_id = u.id "
        "WHERE g.seller_id = ? "
        "ORDER BY o.created_at DESC";
        
    QSqlQuery qSold = db.selectQuery(sqlSold, QVariantList() << currentUserId);
    int rowS = 0;
    ui->tableSold->setRowCount(0);
    
    while (qSold.next()) {
        ui->tableSold->insertRow(rowS);
        
        ui->tableSold->setItem(rowS, 0, new QTableWidgetItem(qSold.value("order_no").toString()));
        ui->tableSold->setItem(rowS, 1, new QTableWidgetItem(qSold.value("title").toString()));
        ui->tableSold->setItem(rowS, 2, new QTableWidgetItem(qSold.value("buyer_name").toString()));
        ui->tableSold->setItem(rowS, 3, new QTableWidgetItem(QString("￥%1").arg(QString::number(qSold.value("price").toDouble(), 'f', 2))));
        
        int status = qSold.value("status").toInt();
        QString statusStr = "未知";
        if (status == 0) statusStr = "未支付";
        else if (status == 1) statusStr = "已支付";
        else if (status == 2) statusStr = "已取消";
        QTableWidgetItem *itemStatus = new QTableWidgetItem(statusStr);
        if (status == 1) itemStatus->setForeground(QBrush(QColor("#34C759")));
        else if (status == 0) itemStatus->setForeground(QBrush(QColor("#FF9500")));
        else itemStatus->setForeground(QBrush(QColor("#FF3B30")));
        
        ui->tableSold->setItem(rowS, 4, itemStatus);
        ui->tableSold->setItem(rowS, 5, new QTableWidgetItem(qSold.value("created_at").toDateTime().toString("yyyy-MM-dd HH:mm:ss")));
        
        rowS++;
    }
}

void MainWindow::loadProfile()
{
    DbManager &db = DbManager::instance();
    int currentUserId = db.getCurrentUserId();
    
    // 1. 查询基本资料与余额，同时利用子查询一次性查出在售宝贝数量 (减少网络请求次数)
    QString sql = "SELECT u.username, u.nickname, u.phone, u.email, u.balance, u.role, "
                  "(SELECT COUNT(*) FROM goods g WHERE g.seller_id = u.id AND g.status = 1) AS listed_count "
                  "FROM users u WHERE u.id = ?";
    QSqlQuery qUser = db.selectQuery(sql, QVariantList() << currentUserId);
    
    int totalListed = 0;
    
    if (qUser.next()) {
        ui->lblUsernameVal->setText("👤 用户名:  " + qUser.value("username").toString());
        ui->lblNicknameVal->setText("🏷️ 昵称:  " + qUser.value("nickname").toString());
        ui->lblPhoneVal->setText("📞 联系方式:  " + (qUser.value("phone").toString().isEmpty() ? "未填写" : qUser.value("phone").toString()));
        ui->lblEmailVal->setText("✉️ 常用邮箱:  " + (qUser.value("email").toString().isEmpty() ? "未填写" : qUser.value("email").toString()));
        
        QString roleStr = qUser.value("role").toString() == "admin" ? "🛡️ 平台管理员" : "👤 认证普通用户";
        ui->lblRoleVal->setText("🎫 账号身份:  " + roleStr);
        
        double balance = qUser.value("balance").toDouble();
        ui->lblBalanceValue->setText(QString("￥%1").arg(QString::number(balance, 'f', 2)));
        
        totalListed = qUser.value("listed_count").toInt();
    }
    
    // 2. 调用存储过程 CalculateUserTotalConsumption 计算成交消费总额
    double totalConsumption = db.getUserTotalConsumption(currentUserId);
    ui->lblTotalConsumption->setText(QString("🛒 累计成交消费总额：￥%1")
                                     .arg(QString::number(totalConsumption, 'f', 2)));
                                     
    // 3. 更新界面显示的在售数量
    ui->lblTotalListed->setText(QString("📤 您当前发布且处于“在售”状态的二手商品数量：%1 件").arg(totalListed));
    
    // 4. 更新数据库自定义函数所查询的分类在售数量
    onStatsCategoryChanged(ui->comboStatsCategory->currentIndex());
}

void MainWindow::onRefreshMarket()
{
    loadCategories();
    loadMarket();
}

void MainWindow::onCategoryFilterChanged(int index)
{
    Q_UNUSED(index);
    loadMarket();
}

void MainWindow::onSearchTextChanged(const QString &text)
{
    Q_UNUSED(text);
    loadMarket();
}

void MainWindow::onPublishClicked()
{
    QString title = ui->editSellTitle->text().trimmed();
    double price = ui->spinSellPrice->value();
    int categoryId = ui->comboSellCategory->currentData().toInt();
    QString desc = ui->editSellDesc->toPlainText().trimmed();
    
    if (title.isEmpty()) {
        AppleMsgBox::warning(this, "发布失败", "请输入商品名称！");
        return;
    }
    if (price <= 0.00) {
        AppleMsgBox::warning(this, "发布失败", "商品转让价格必须大于 0！");
        return;
    }
    if (categoryId <= 0) {
        AppleMsgBox::warning(this, "发布失败", "请选择正确的商品分类！");
        return;
    }
    
    DbManager &db = DbManager::instance();
    int sellerId = db.getCurrentUserId();
    
    bool ok = db.executeQuery(
        "INSERT INTO goods (title, description, price, status, category_id, seller_id, image_url) VALUES (?, ?, ?, 1, ?, ?, '')",
        QVariantList() << title << desc << price << categoryId << sellerId
    );
    
    if (ok) {
        AppleMsgBox::information(this, "发布成功", QString("您的宝贝「%1」已成功发布到市场！").arg(title));
        
        // 重置发布输入字段
        ui->editSellTitle->clear();
        ui->spinSellPrice->setValue(0.00);
        ui->editSellDesc->clear();
        
        // 触发自动跳转回市场主页，并刷新数据
        ui->btnNavMarket->click();
    } else {
        AppleMsgBox::critical(this, "发布失败", "发布商品数据未写入成功，请检查数据库链路！");
    }
}

void MainWindow::onBuyGoods(int goodsId)
{
    DbManager &db = DbManager::instance();
    int buyerId = db.getCurrentUserId();
    
    // 1. 查询该商品的最新信息，核实状态
    QSqlQuery qGoods = db.selectQuery("SELECT title, price, seller_id, status FROM goods WHERE id = ?", QVariantList() << goodsId);
    if (!qGoods.next()) {
        AppleMsgBox::warning(this, "购买失败", "该闲置商品不存在！");
        return;
    }
    
    QString title = qGoods.value("title").toString();
    double price = qGoods.value("price").toDouble();
    int sellerId = qGoods.value("seller_id").toInt();
    int status = qGoods.value("status").toInt();
    
    if (status != 1) {
        AppleMsgBox::warning(this, "购买失败", "该闲置宝贝已被售出或下架！");
        return;
    }
    
    if (sellerId == buyerId) {
        AppleMsgBox::warning(this, "购买失败", "您不能购买自己发布的宝贝商品！");
        return;
    }
    
    QMessageBox::StandardButton reply = AppleMsgBox::question(this, "确认交易", 
        QString("您确认要以 ￥%1 的转让价购买「%2」吗？\n交易成功后，余额将自动扣除并打给卖家。").arg(price).arg(title),
        QMessageBox::Yes | QMessageBox::No);
        
    if (reply != QMessageBox::Yes) {
        return;
    }
    
    // ==========================================
    // 事务控制 & 触发器安全审查联动
    // ==========================================
    db.beginTransaction();
    
    QString orderNo = generateOrderNo();
    
    // A. 先生成订单（未支付状态）
    bool orderOk = db.executeQuery(
        "INSERT INTO orders (order_no, buyer_id, goods_id, price, status) VALUES (?, ?, ?, ?, 0)",
        QVariantList() << orderNo << buyerId << goodsId << price
    );
    
    if (!orderOk) {
        db.rollbackTransaction();
        AppleMsgBox::critical(this, "交易失败", "后台创建待支付订单失败，请检查数据库配置！");
        return;
    }
    
    // B. 将订单更新为“已支付”状态
    // 此处将直接触发 BEFORE UPDATE 触发器 `trg_order_before_pay` 进行买家账户扣减余额以及卖家账户加账。
    // 如果余额不足，该触发器会抛出 SIGNAL 异常，此时 query.exec() 执行失败，触发回滚。
    // 扣减成功后，AFTER UPDATE 触发器 `trg_order_paid_update_goods` 会将该商品状态自动更新为 0 (已售)。
    QSqlQuery payQuery = db.selectQuery("UPDATE orders SET status = 1 WHERE order_no = ?", QVariantList() << orderNo);
    
    if (payQuery.lastError().isValid()) {
        db.rollbackTransaction();
        
        QString errText = payQuery.lastError().text();
        QString decodedErr = QString::fromUtf8(errText.toLatin1()); // Fix for Qt MySQL driver UTF-8 garbling
        QString nativeErr = payQuery.lastError().nativeErrorCode();
        QString errMsg = "交易失败：底层事务遇到未知错误！";
        
        if (errText.contains("余额不足") || decodedErr.contains("余额不足") || nativeErr == "1644") {
            errMsg = "交易失败！您的钱包余额不足，请前往“个人中心”充值余额后重试！";
        } else {
            errMsg = QString("交易被中断：%1").arg(decodedErr.isEmpty() || decodedErr == errText ? errText : decodedErr);
        }
        
        AppleMsgBox::critical(this, "扣款失败", errMsg);
        return;
    }
    
    // C. 提交事务，写入数据库
    bool commitOk = db.commitTransaction();
    if (!commitOk) {
        db.rollbackTransaction();
        AppleMsgBox::critical(this, "交易失败", "提交数据库事务失败，数据已被回滚！");
        return;
    }
    
    AppleMsgBox::information(this, "交易成功", 
        QString("恭喜您，购买商品「%1」成功！\n"
                "订单号为：%2\n"
                "资金已全额存入卖家钱包中。").arg(title).arg(orderNo));
                
    // 重新拉取同步所有页面数据
    refreshAllData();
}

void MainWindow::onFavoriteGoods(int goodsId, bool toFav)
{
    DbManager &db = DbManager::instance();
    int userId = db.getCurrentUserId();
    
    if (toFav) {
        db.executeQuery("INSERT IGNORE INTO favorites (user_id, goods_id) VALUES (?, ?)", QVariantList() << userId << goodsId);
    } else {
        db.executeQuery("DELETE FROM favorites WHERE user_id = ? AND goods_id = ?", QVariantList() << userId << goodsId);
    }
    
    // 静默载入最新的收藏
    loadFavorites();
}

void MainWindow::onRechargeClicked()
{
    double amount = ui->spinRecharge->value();
    if (amount <= 0.00) {
        AppleMsgBox::warning(this, "充值失败", "请输入大于 0 的充值金额！");
        return;
    }
    
    DbManager &db = DbManager::instance();
    int userId = db.getCurrentUserId();
    
    bool ok = db.executeQuery("UPDATE users SET balance = balance + ? WHERE id = ?", QVariantList() << amount << userId);
    if (ok) {
        AppleMsgBox::information(this, "充值成功", QString("恭喜！成功充值 ￥%1 元，您的余额已到账！").arg(amount));
        loadProfile(); // 更新主页面板
    } else {
        AppleMsgBox::critical(this, "充值失败", "钱包充值失败，请确认数据库服务已连通！");
    }
}

void MainWindow::onStatsCategoryChanged(int index)
{
    if (index < 0) return;
    
    int categoryId = ui->comboStatsCategory->itemData(index).toInt();
    
    DbManager &db = DbManager::instance();
    
    // 调用自定义函数 CountActiveProductsInCategory 计算当前品类下有多少商品正在全站出售中
    int count = db.getCategoryActiveGoodsCount(categoryId);
    
    QString catName = ui->comboStatsCategory->itemText(index);
    ui->lblStatsActiveGoods->setText(QString("👉 品类【%1】全站当前“在售”闲置数量：%2 件").arg(catName).arg(count));
}

QString MainWindow::generateOrderNo()
{
    // 生成：ORDER + 当前年月日时分秒 + 4位极高离散随机数
    QString timestamp = QDateTime::currentDateTime().toString("yyyyMMddHHmmss");
    int randomPart = QRandomGenerator::global()->bounded(1000, 9999);
    return QString("ORDER%1%2").arg(timestamp).arg(randomPart);
}

// 覃金焱：优化了发布表单与交易订单的异常处理

// 韦宇隆：增强了钱包并发安全性与看板统计逻辑

// 覃金焱：排查并修复了多表联查时的潜在锁表风险

// 苏将伟：引入了商品搜索的模糊匹配机制

// 覃金焱：优化了发布表单与交易订单的异常处理
