#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow() override;

signals:
    void loginSuccess();

private slots:
    void onLoginClicked();
    void onRegisterClicked();
    void onToggleModeClicked(); // 切换登录/注册表单

private:
    Ui::LoginWindow *ui;
    bool m_isRegisterMode;
    
    void updateUiMode();
    bool tryConnectDatabase(); // 直接连接程序中硬编码的数据库
};

#endif // LOGINWINDOW_H
