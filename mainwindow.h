#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QButtonGroup>
#include <QVariantList>
#include <QSqlQuery>

namespace Ui {
class MainWindow;
}

// ----------------------------------------------------
// 1. 商品白底圆角 Apple 风格卡片控件
// ----------------------------------------------------
class GoodsCardWidget : public QWidget
{
    Q_OBJECT
public:
    GoodsCardWidget(int goodsId, const QString &title, double price, const QString &desc, 
                    const QString &category, const QString &seller, int status, 
                    bool isFav, bool isOwn, QWidget *parent = nullptr);

signals:
    void buyClicked(int id);
    void favClicked(int id, bool toFav);

private:
    int m_goodsId;
    bool m_isFav;
};

// ----------------------------------------------------
// 2. 主控制仪表盘窗体
// ----------------------------------------------------
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

    // 当登录成功后，更新当前用户身份并加载所有数据
    void refreshAllData();

signals:
    void logoutRequested(); // 请求返回登录窗口

private slots:
    // 侧边栏导航槽
    void onNavButtonClicked(int index);
    void onLogoutClicked();

    // 市场选项卡槽
    void onRefreshMarket();
    void onCategoryFilterChanged(int index);
    void onSearchTextChanged(const QString &text);

    // 发布商品槽
    void onPublishClicked();

    // 交易与收藏核心业务槽
    void onBuyGoods(int goodsId);
    void onFavoriteGoods(int goodsId, bool toFav);

    // 个人中心钱包与统计槽
    void onRechargeClicked();
    void onStatsCategoryChanged(int index);

private:
    Ui::MainWindow *ui;
    QButtonGroup *m_navGroup;
    
    // 分类缓存：分类ID -> 分类名称
    QMap<int, QString> m_categoryMap;

    void initNavigation();
    void loadCategories();
    
    // 页面刷新加载子程序
    void loadMarket();
    void loadOrders();
    void loadFavorites();
    void loadProfile();
    
    // 辅助工具方法
    QString generateOrderNo();
};

#endif // MAINWINDOW_H
