#include <QApplication>
#include <QFile>
#include <QDebug>
#include "loginwindow.h"
#include "dbmanager.h"
#include "mainwindow.h"

#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    // 设置全局应用图标
    a.setWindowIcon(QIcon(":/quanquan.png"));

    // 1. 全局加载并应用精美的 QSS 样式表
    QFile styleFile(":/style.qss");
    if (styleFile.open(QFile::ReadOnly | QFile::Text)) {
        QString styleSheet = QLatin1String(styleFile.readAll());
        a.setStyleSheet(styleSheet);
        qDebug() << "Successfully applied global QSS stylesheet from embedded resources.";
    } else {
        qWarning() << "Failed to open global style.qss from resource system!";
    }
    
    // 启用跨平台的 Fusion 风格，去除 Windows 原生控件的 3D 边框，让下拉框等控件看起来更纯粹扁平
    a.setStyle("Fusion");

    // 2. 实例化登录与主控仪表盘窗口
    LoginWindow loginWin;
    MainWindow mainWin;

    // 设置窗口固定/最小尺寸，防止拉伸变形和挤压
    loginWin.setFixedSize(400, 650);
    mainWin.setMinimumSize(1100, 750);

    // 3. 槽函数关联：处理从登录界面到主界面的完美跳转
    QObject::connect(&loginWin, &LoginWindow::loginSuccess, [&]() {
        loginWin.hide();
        
        // 刷新主窗口的全部内容（商品流、分类、个人钱包、存储过程/自定义函数等数据）
        mainWin.refreshAllData();
        mainWin.show();
    });

    // 4. 槽函数关联：处理从主界面点击“退出登录”返回登录界面
    QObject::connect(&mainWin, &MainWindow::logoutRequested, [&]() {
        mainWin.hide();
        loginWin.show();
    });

    // 5. 首次展现登录窗体
    loginWin.show();

    int ret = QApplication::exec();
    
    // 在 QApplication 销毁前手动关闭并移除数据库连接，以消除 "requires a QCoreApplication" 的退出警告
    DbManager::instance().closeConnection();
    
    return ret;
}
