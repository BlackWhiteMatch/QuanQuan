#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "dbmanager.h"
#include <QMessageBox>
#include "applemsgbox.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QCryptographicHash>
#include <QPainter>
#include <QPainterPath>
#include <QAction>
// 数据库硬编码配置
const QString DB_HOST = "62.234.97.253";
const int     DB_PORT = 3306;
const QString DB_NAME = "quanquan_db";
const QString DB_USER = "XJ";
const QString DB_PASS = "@XJ1234567890";

LoginWindow::LoginWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginWindow)
    , m_isRegisterMode(false)
{
    ui->setupUi(this);
    
    // 密码框小眼睛切换功能 (同时适用于登录和注册)
    QAction *eyeAction = ui->editPassword->addAction(QIcon(), QLineEdit::TrailingPosition);
    auto updateEyeIcon = [this, eyeAction]() {
        QPixmap pixmap(24, 24);
        pixmap.fill(Qt::transparent);
        QPainter painter(&pixmap);
        QFont f = painter.font();
        f.setPointSize(10);
        painter.setFont(f);
        QString emoji = (ui->editPassword->echoMode() == QLineEdit::Password) ? "🙈" : "👁️";
        painter.drawText(pixmap.rect(), Qt::AlignCenter, emoji);
        eyeAction->setIcon(QIcon(pixmap));
    };
    updateEyeIcon();
    connect(eyeAction, &QAction::triggered, this, [this, updateEyeIcon]() {
        ui->editPassword->setEchoMode(
            ui->editPassword->echoMode() == QLineEdit::Password ? QLineEdit::Normal : QLineEdit::Password
        );
        updateEyeIcon();
    });
    
    // 生成圆角 Logo
    QPixmap src(":/quanquan.png");
    if (!src.isNull()) {
        int logoSize = 140;
        QPixmap target(logoSize, logoSize);
        target.fill(Qt::transparent);
        QPainter painter(&target);
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
        QPainterPath path;
        path.addRoundedRect(0, 0, logoSize, logoSize, 30, 30); // Apple 圆角大小
        painter.setClipPath(path);
        
        QPixmap scaledSrc = src.scaled(logoSize, logoSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        int x = (logoSize - scaledSrc.width()) / 2;
        int y = (logoSize - scaledSrc.height()) / 2;
        painter.drawPixmap(x, y, scaledSrc);
        
        ui->labelImageIcon->setPixmap(target);
    }
    
    // 绑定信号槽
    connect(ui->btnSubmit, &QPushButton::clicked, this, [this]() {
        if (m_isRegisterMode) {
            onRegisterClicked();
        } else {
            onLoginClicked();
        }
    });
    connect(ui->btnToggleMode, &QPushButton::clicked, this, &LoginWindow::onToggleModeClicked);
    
    // 初始化 UI 模式为登录模式
    updateUiMode();
    
    // 尝试连接数据库
    tryConnectDatabase();
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

bool LoginWindow::tryConnectDatabase()
{
    DbManager &db = DbManager::instance();
    if (db.isConnected()) {
        return true;
    }
    
    bool ok = db.connectToMySQL(DB_HOST, DB_PORT, DB_NAME, DB_USER, DB_PASS);
    if (!ok) {
        AppleMsgBox::critical(this, "连接失败", 
            QString("无法打开本地 MySQL 数据库！\n\n"
                    "主机: %1\n端口: %2\n数据库: %3\n用户名: %4\n\n"
                    "错误详情:\n%5\n\n"
                    "请确保 MySQL 服务已启动且创建了数据库表。")
            .arg(DB_HOST).arg(DB_PORT).arg(DB_NAME).arg(DB_USER).arg(db.getLastErrorText()));
        return false;
    }
    
    return true;
}

void LoginWindow::updateUiMode()
{
    if (m_isRegisterMode) {
        // 注册模式：显示昵称、电话、邮箱
        ui->editNickname->setVisible(true);
        ui->editPhone->setVisible(true);
        ui->editEmail->setVisible(true);
        
        ui->btnSubmit->setText("立即注册并登录");
        ui->btnToggleMode->setText("已有账号？返回登录");
    } else {
        // 登录模式：隐藏注册专用的字段
        ui->editNickname->setVisible(false);
        ui->editPhone->setVisible(false);
        ui->editEmail->setVisible(false);
        
        ui->btnSubmit->setText("安全登录");
        ui->btnToggleMode->setText("没有账号？立即注册");
    }
    
    // 清空输入
    ui->editPassword->clear();
}

void LoginWindow::onToggleModeClicked()
{
    m_isRegisterMode = !m_isRegisterMode;
    updateUiMode();
}

void LoginWindow::onLoginClicked()
{
    if (!tryConnectDatabase()) return;
    
    QString username = ui->editUsername->text().trimmed();
    QString password = ui->editPassword->text();
    
    if (username.isEmpty() || password.isEmpty()) {
        AppleMsgBox::warning(this, "登录失败", "请输入用户名和密码！");
        return;
    }
    
    // 计算两种哈希值：加盐哈希（新注册用户）与普通 SHA-256 哈希（内置测试数据）
    QString saltedHash = DbManager::hashPassword(password);
    
    // 普通 SHA-256
    QByteArray plainBytes = password.toUtf8();
    QByteArray plainHash = QCryptographicHash::hash(plainBytes, QCryptographicHash::Sha256);
    QString plainHashStr = QString(plainHash.toHex());
    
    // 查询数据库
    DbManager &db = DbManager::instance();
    QSqlQuery query = db.selectQuery(
        "SELECT id, username, nickname, role, password FROM users WHERE username = ?",
        QVariantList() << username
    );
    
    if (query.next()) {
        QString dbPassword = query.value("password").toString();
        int userId = query.value("id").toInt();
        QString nickname = query.value("nickname").toString();
        QString role = query.value("role").toString();
        
        // 匹配任意一种哈希即可
        if (dbPassword == saltedHash || dbPassword == plainHashStr) {
            db.setCurrentUser(userId, username, nickname, role);
            emit loginSuccess();
        } else {
            AppleMsgBox::warning(this, "登录失败", "用户名或密码错误！");
        }
    } else {
        AppleMsgBox::warning(this, "登录失败", "用户名不存在！");
    }
}

#include <QRegularExpression>

void LoginWindow::onRegisterClicked()
{
    if (!tryConnectDatabase()) return;
    
    QString username = ui->editUsername->text().trimmed();
    QString password = ui->editPassword->text();
    QString nickname = ui->editNickname->text().trimmed();
    QString phone = ui->editPhone->text().trimmed();
    QString email = ui->editEmail->text().trimmed();
    
    if (username.isEmpty() || password.isEmpty() || nickname.isEmpty() || phone.isEmpty() || email.isEmpty()) {
        AppleMsgBox::warning(this, "注册失败", "所有字段（包含电话和邮箱）均不能为空！");
        return;
    }
    
    // 使用正则表达式严格校验手机号格式 (中国大陆11位手机号)
    QRegularExpression phoneRegex("^1[3-9]\\d{9}$");
    if (!phoneRegex.match(phone).hasMatch()) {
        AppleMsgBox::warning(this, "注册失败", "手机号格式不正确！请输入有效的 11 位手机号码。");
        return;
    }
    
    // 使用正则表达式严格校验电子邮箱格式
    QRegularExpression emailRegex("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
    if (!emailRegex.match(email).hasMatch()) {
        AppleMsgBox::warning(this, "注册失败", "电子邮箱格式不正确！请检查。");
        return;
    }
    
    DbManager &db = DbManager::instance();
    
    // 检查用户名是否已存在
    QSqlQuery checkQuery = db.selectQuery("SELECT id FROM users WHERE username = ?", QVariantList() << username);
    if (checkQuery.next()) {
        AppleMsgBox::warning(this, "注册失败", "用户名已被注册！");
        return;
    }
    
    // 加密密码
    QString encryptedPassword = DbManager::hashPassword(password);
    
    // 插入新用户记录 (余额默认为 1000.00，在表设计中已定义)
    bool success = db.executeQuery(
        "INSERT INTO users (username, password, nickname, phone, email, balance, role) VALUES (?, ?, ?, ?, ?, 1000.00, 'user')",
        QVariantList() << username << encryptedPassword << nickname << phone << email
    );
    
    if (success) {
        // 注册成功，获取新插入用户的ID并登录
        QSqlQuery loginQuery = db.selectQuery("SELECT id, role FROM users WHERE username = ?", QVariantList() << username);
        if (loginQuery.next()) {
            int userId = loginQuery.value("id").toInt();
            QString role = loginQuery.value("role").toString();
            
            db.setCurrentUser(userId, username, nickname, role);
            emit loginSuccess();
        }
    } else {
        AppleMsgBox::warning(this, "注册失败", "注册失败，请检查数据库状态！");
    }
}
