/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QFrame *sidebarFrame;
    QVBoxLayout *verticalLayoutSidebar;
    QHBoxLayout *logoSidebarLayout;
    QSpacerItem *logoSidebarSpacerLeft;
    QLabel *sidebarTitle;
    QSpacerItem *logoSidebarSpacerRight;
    QSpacerItem *verticalSpacerLogo;
    QPushButton *btnNavMarket;
    QPushButton *btnNavSell;
    QPushButton *btnNavOrders;
    QPushButton *btnNavFavorites;
    QPushButton *btnNavProfile;
    QSpacerItem *verticalSpacerSidebar;
    QPushButton *btnNavLogout;
    QStackedWidget *stackedWidget;
    QWidget *pageMarket;
    QVBoxLayout *verticalLayoutMarket;
    QHBoxLayout *horizontalLayoutMarketHeader;
    QLabel *lblMarketTitle;
    QSpacerItem *horizontalSpacerMarket;
    QLineEdit *editSearch;
    QComboBox *comboCategoryFilter;
    QPushButton *btnRefreshMarket;
    QScrollArea *scrollAreaMarket;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayoutMarket;
    QWidget *pageSell;
    QVBoxLayout *verticalLayoutSell;
    QLabel *lblSellTitle;
    QLabel *lblSellSub;
    QFormLayout *formLayoutSell;
    QLabel *lblSellName;
    QLineEdit *editSellTitle;
    QLabel *lblSellPrice;
    QDoubleSpinBox *spinSellPrice;
    QLabel *lblSellCategory;
    QComboBox *comboSellCategory;
    QLabel *lblSellDesc;
    QTextEdit *editSellDesc;
    QSpacerItem *verticalSpacerSell;
    QPushButton *btnPublish;
    QWidget *pageOrders;
    QVBoxLayout *verticalLayoutOrders;
    QLabel *lblOrdersTitle;
    QTabWidget *tabOrders;
    QWidget *tabBought;
    QVBoxLayout *verticalLayoutTabBought;
    QTableWidget *tableBought;
    QWidget *tabSold;
    QVBoxLayout *verticalLayoutTabSold;
    QTableWidget *tableSold;
    QWidget *pageFavorites;
    QVBoxLayout *verticalLayoutFav;
    QLabel *lblFavTitle;
    QScrollArea *scrollAreaFav;
    QWidget *scrollAreaFavContents;
    QGridLayout *gridLayoutFav;
    QWidget *pageProfile;
    QVBoxLayout *verticalLayoutProfile;
    QLabel *lblProfileTitle;
    QHBoxLayout *horizontalLayoutProfileTop;
    QFrame *frameProfile;
    QVBoxLayout *verticalLayoutFrameProfile;
    QLabel *label_11;
    QLabel *lblUsernameVal;
    QLabel *lblNicknameVal;
    QLabel *lblPhoneVal;
    QLabel *lblEmailVal;
    QLabel *lblRoleVal;
    QFrame *frameWallet;
    QVBoxLayout *verticalLayoutFrameWallet;
    QLabel *label_13;
    QLabel *lblBalanceValue;
    QSpacerItem *verticalSpacerWallet;
    QHBoxLayout *horizontalLayoutRecharge;
    QDoubleSpinBox *spinRecharge;
    QPushButton *btnRecharge;
    QFrame *frameStats;
    QVBoxLayout *verticalLayoutFrameStats;
    QLabel *label_15;
    QLabel *lblTotalConsumption;
    QLabel *lblTotalListed;
    QHBoxLayout *horizontalLayoutStatsFunc;
    QLabel *lblFuncIntro;
    QComboBox *comboStatsCategory;
    QSpacerItem *horizontalSpacerStats;
    QLabel *lblStatsActiveGoods;
    QSpacerItem *verticalSpacerProfile;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1100, 750);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        sidebarFrame = new QFrame(centralwidget);
        sidebarFrame->setObjectName("sidebarFrame");
        sidebarFrame->setMinimumSize(QSize(220, 0));
        sidebarFrame->setMaximumSize(QSize(220, 16777215));
        sidebarFrame->setFrameShape(QFrame::StyledPanel);
        sidebarFrame->setFrameShadow(QFrame::Raised);
        verticalLayoutSidebar = new QVBoxLayout(sidebarFrame);
        verticalLayoutSidebar->setSpacing(6);
        verticalLayoutSidebar->setObjectName("verticalLayoutSidebar");
        verticalLayoutSidebar->setContentsMargins(15, 25, 15, 25);
        logoSidebarLayout = new QHBoxLayout();
        logoSidebarLayout->setObjectName("logoSidebarLayout");
        logoSidebarSpacerLeft = new QSpacerItem(0, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        logoSidebarLayout->addItem(logoSidebarSpacerLeft);

        sidebarTitle = new QLabel(sidebarFrame);
        sidebarTitle->setObjectName("sidebarTitle");
        sidebarTitle->setMinimumSize(QSize(140, 140));
        sidebarTitle->setMaximumSize(QSize(140, 140));

        logoSidebarLayout->addWidget(sidebarTitle);

        logoSidebarSpacerRight = new QSpacerItem(0, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        logoSidebarLayout->addItem(logoSidebarSpacerRight);


        verticalLayoutSidebar->addLayout(logoSidebarLayout);

        verticalSpacerLogo = new QSpacerItem(20, 15, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayoutSidebar->addItem(verticalSpacerLogo);

        btnNavMarket = new QPushButton(sidebarFrame);
        btnNavMarket->setObjectName("btnNavMarket");
        btnNavMarket->setCheckable(true);
        btnNavMarket->setChecked(true);

        verticalLayoutSidebar->addWidget(btnNavMarket);

        btnNavSell = new QPushButton(sidebarFrame);
        btnNavSell->setObjectName("btnNavSell");
        btnNavSell->setCheckable(true);

        verticalLayoutSidebar->addWidget(btnNavSell);

        btnNavOrders = new QPushButton(sidebarFrame);
        btnNavOrders->setObjectName("btnNavOrders");
        btnNavOrders->setCheckable(true);

        verticalLayoutSidebar->addWidget(btnNavOrders);

        btnNavFavorites = new QPushButton(sidebarFrame);
        btnNavFavorites->setObjectName("btnNavFavorites");
        btnNavFavorites->setCheckable(true);

        verticalLayoutSidebar->addWidget(btnNavFavorites);

        btnNavProfile = new QPushButton(sidebarFrame);
        btnNavProfile->setObjectName("btnNavProfile");
        btnNavProfile->setCheckable(true);

        verticalLayoutSidebar->addWidget(btnNavProfile);

        verticalSpacerSidebar = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayoutSidebar->addItem(verticalSpacerSidebar);

        btnNavLogout = new QPushButton(sidebarFrame);
        btnNavLogout->setObjectName("btnNavLogout");

        verticalLayoutSidebar->addWidget(btnNavLogout);


        horizontalLayout->addWidget(sidebarFrame);

        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        pageMarket = new QWidget();
        pageMarket->setObjectName("pageMarket");
        verticalLayoutMarket = new QVBoxLayout(pageMarket);
        verticalLayoutMarket->setSpacing(15);
        verticalLayoutMarket->setObjectName("verticalLayoutMarket");
        verticalLayoutMarket->setContentsMargins(30, 30, 30, 30);
        horizontalLayoutMarketHeader = new QHBoxLayout();
        horizontalLayoutMarketHeader->setObjectName("horizontalLayoutMarketHeader");
        lblMarketTitle = new QLabel(pageMarket);
        lblMarketTitle->setObjectName("lblMarketTitle");

        horizontalLayoutMarketHeader->addWidget(lblMarketTitle);

        horizontalSpacerMarket = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayoutMarketHeader->addItem(horizontalSpacerMarket);

        editSearch = new QLineEdit(pageMarket);
        editSearch->setObjectName("editSearch");
        editSearch->setMinimumSize(QSize(220, 0));

        horizontalLayoutMarketHeader->addWidget(editSearch);

        comboCategoryFilter = new QComboBox(pageMarket);
        comboCategoryFilter->setObjectName("comboCategoryFilter");
        comboCategoryFilter->setMinimumSize(QSize(130, 0));

        horizontalLayoutMarketHeader->addWidget(comboCategoryFilter);

        btnRefreshMarket = new QPushButton(pageMarket);
        btnRefreshMarket->setObjectName("btnRefreshMarket");

        horizontalLayoutMarketHeader->addWidget(btnRefreshMarket);


        verticalLayoutMarket->addLayout(horizontalLayoutMarketHeader);

        scrollAreaMarket = new QScrollArea(pageMarket);
        scrollAreaMarket->setObjectName("scrollAreaMarket");
        scrollAreaMarket->setWidgetResizable(true);
        scrollAreaMarket->setFrameShape(QFrame::NoFrame);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 820, 600));
        gridLayoutMarket = new QGridLayout(scrollAreaWidgetContents);
        gridLayoutMarket->setSpacing(15);
        gridLayoutMarket->setObjectName("gridLayoutMarket");
        gridLayoutMarket->setContentsMargins(0, 0, 0, 0);
        scrollAreaMarket->setWidget(scrollAreaWidgetContents);

        verticalLayoutMarket->addWidget(scrollAreaMarket);

        stackedWidget->addWidget(pageMarket);
        pageSell = new QWidget();
        pageSell->setObjectName("pageSell");
        verticalLayoutSell = new QVBoxLayout(pageSell);
        verticalLayoutSell->setSpacing(20);
        verticalLayoutSell->setObjectName("verticalLayoutSell");
        verticalLayoutSell->setContentsMargins(40, 45, 40, 45);
        lblSellTitle = new QLabel(pageSell);
        lblSellTitle->setObjectName("lblSellTitle");

        verticalLayoutSell->addWidget(lblSellTitle);

        lblSellSub = new QLabel(pageSell);
        lblSellSub->setObjectName("lblSellSub");

        verticalLayoutSell->addWidget(lblSellSub);

        formLayoutSell = new QFormLayout();
        formLayoutSell->setObjectName("formLayoutSell");
        formLayoutSell->setHorizontalSpacing(20);
        formLayoutSell->setVerticalSpacing(15);
        lblSellName = new QLabel(pageSell);
        lblSellName->setObjectName("lblSellName");
        lblSellName->setStyleSheet(QString::fromUtf8("font-weight: bold;"));

        formLayoutSell->setWidget(0, QFormLayout::ItemRole::LabelRole, lblSellName);

        editSellTitle = new QLineEdit(pageSell);
        editSellTitle->setObjectName("editSellTitle");

        formLayoutSell->setWidget(0, QFormLayout::ItemRole::FieldRole, editSellTitle);

        lblSellPrice = new QLabel(pageSell);
        lblSellPrice->setObjectName("lblSellPrice");
        lblSellPrice->setStyleSheet(QString::fromUtf8("font-weight: bold;"));

        formLayoutSell->setWidget(1, QFormLayout::ItemRole::LabelRole, lblSellPrice);

        spinSellPrice = new QDoubleSpinBox(pageSell);
        spinSellPrice->setObjectName("spinSellPrice");
        spinSellPrice->setMaximum(99999.000000000000000);
        spinSellPrice->setSingleStep(10.000000000000000);

        formLayoutSell->setWidget(1, QFormLayout::ItemRole::FieldRole, spinSellPrice);

        lblSellCategory = new QLabel(pageSell);
        lblSellCategory->setObjectName("lblSellCategory");
        lblSellCategory->setStyleSheet(QString::fromUtf8("font-weight: bold;"));

        formLayoutSell->setWidget(2, QFormLayout::ItemRole::LabelRole, lblSellCategory);

        comboSellCategory = new QComboBox(pageSell);
        comboSellCategory->setObjectName("comboSellCategory");

        formLayoutSell->setWidget(2, QFormLayout::ItemRole::FieldRole, comboSellCategory);

        lblSellDesc = new QLabel(pageSell);
        lblSellDesc->setObjectName("lblSellDesc");
        lblSellDesc->setStyleSheet(QString::fromUtf8("font-weight: bold;"));

        formLayoutSell->setWidget(3, QFormLayout::ItemRole::LabelRole, lblSellDesc);

        editSellDesc = new QTextEdit(pageSell);
        editSellDesc->setObjectName("editSellDesc");

        formLayoutSell->setWidget(3, QFormLayout::ItemRole::FieldRole, editSellDesc);


        verticalLayoutSell->addLayout(formLayoutSell);

        verticalSpacerSell = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayoutSell->addItem(verticalSpacerSell);

        btnPublish = new QPushButton(pageSell);
        btnPublish->setObjectName("btnPublish");
        btnPublish->setMinimumSize(QSize(0, 40));

        verticalLayoutSell->addWidget(btnPublish);

        stackedWidget->addWidget(pageSell);
        pageOrders = new QWidget();
        pageOrders->setObjectName("pageOrders");
        verticalLayoutOrders = new QVBoxLayout(pageOrders);
        verticalLayoutOrders->setSpacing(15);
        verticalLayoutOrders->setObjectName("verticalLayoutOrders");
        verticalLayoutOrders->setContentsMargins(30, 30, 30, 30);
        lblOrdersTitle = new QLabel(pageOrders);
        lblOrdersTitle->setObjectName("lblOrdersTitle");

        verticalLayoutOrders->addWidget(lblOrdersTitle);

        tabOrders = new QTabWidget(pageOrders);
        tabOrders->setObjectName("tabOrders");
        tabBought = new QWidget();
        tabBought->setObjectName("tabBought");
        verticalLayoutTabBought = new QVBoxLayout(tabBought);
        verticalLayoutTabBought->setObjectName("verticalLayoutTabBought");
        verticalLayoutTabBought->setContentsMargins(10, 15, 10, 10);
        tableBought = new QTableWidget(tabBought);
        tableBought->setObjectName("tableBought");

        verticalLayoutTabBought->addWidget(tableBought);

        tabOrders->addTab(tabBought, QString());
        tabSold = new QWidget();
        tabSold->setObjectName("tabSold");
        verticalLayoutTabSold = new QVBoxLayout(tabSold);
        verticalLayoutTabSold->setObjectName("verticalLayoutTabSold");
        verticalLayoutTabSold->setContentsMargins(10, 15, 10, 10);
        tableSold = new QTableWidget(tabSold);
        tableSold->setObjectName("tableSold");

        verticalLayoutTabSold->addWidget(tableSold);

        tabOrders->addTab(tabSold, QString());

        verticalLayoutOrders->addWidget(tabOrders);

        stackedWidget->addWidget(pageOrders);
        pageFavorites = new QWidget();
        pageFavorites->setObjectName("pageFavorites");
        verticalLayoutFav = new QVBoxLayout(pageFavorites);
        verticalLayoutFav->setSpacing(15);
        verticalLayoutFav->setObjectName("verticalLayoutFav");
        verticalLayoutFav->setContentsMargins(30, 30, 30, 30);
        lblFavTitle = new QLabel(pageFavorites);
        lblFavTitle->setObjectName("lblFavTitle");

        verticalLayoutFav->addWidget(lblFavTitle);

        scrollAreaFav = new QScrollArea(pageFavorites);
        scrollAreaFav->setObjectName("scrollAreaFav");
        scrollAreaFav->setWidgetResizable(true);
        scrollAreaFav->setFrameShape(QFrame::NoFrame);
        scrollAreaFavContents = new QWidget();
        scrollAreaFavContents->setObjectName("scrollAreaFavContents");
        gridLayoutFav = new QGridLayout(scrollAreaFavContents);
        gridLayoutFav->setSpacing(15);
        gridLayoutFav->setObjectName("gridLayoutFav");
        gridLayoutFav->setContentsMargins(0, 0, 0, 0);
        scrollAreaFav->setWidget(scrollAreaFavContents);

        verticalLayoutFav->addWidget(scrollAreaFav);

        stackedWidget->addWidget(pageFavorites);
        pageProfile = new QWidget();
        pageProfile->setObjectName("pageProfile");
        verticalLayoutProfile = new QVBoxLayout(pageProfile);
        verticalLayoutProfile->setSpacing(20);
        verticalLayoutProfile->setObjectName("verticalLayoutProfile");
        verticalLayoutProfile->setContentsMargins(30, 30, 30, 30);
        lblProfileTitle = new QLabel(pageProfile);
        lblProfileTitle->setObjectName("lblProfileTitle");

        verticalLayoutProfile->addWidget(lblProfileTitle);

        horizontalLayoutProfileTop = new QHBoxLayout();
        horizontalLayoutProfileTop->setSpacing(20);
        horizontalLayoutProfileTop->setObjectName("horizontalLayoutProfileTop");
        frameProfile = new QFrame(pageProfile);
        frameProfile->setObjectName("frameProfile");
        frameProfile->setFrameShape(QFrame::StyledPanel);
        verticalLayoutFrameProfile = new QVBoxLayout(frameProfile);
        verticalLayoutFrameProfile->setSpacing(12);
        verticalLayoutFrameProfile->setObjectName("verticalLayoutFrameProfile");
        verticalLayoutFrameProfile->setContentsMargins(20, 20, 20, 20);
        label_11 = new QLabel(frameProfile);
        label_11->setObjectName("label_11");

        verticalLayoutFrameProfile->addWidget(label_11);

        lblUsernameVal = new QLabel(frameProfile);
        lblUsernameVal->setObjectName("lblUsernameVal");

        verticalLayoutFrameProfile->addWidget(lblUsernameVal);

        lblNicknameVal = new QLabel(frameProfile);
        lblNicknameVal->setObjectName("lblNicknameVal");

        verticalLayoutFrameProfile->addWidget(lblNicknameVal);

        lblPhoneVal = new QLabel(frameProfile);
        lblPhoneVal->setObjectName("lblPhoneVal");

        verticalLayoutFrameProfile->addWidget(lblPhoneVal);

        lblEmailVal = new QLabel(frameProfile);
        lblEmailVal->setObjectName("lblEmailVal");

        verticalLayoutFrameProfile->addWidget(lblEmailVal);

        lblRoleVal = new QLabel(frameProfile);
        lblRoleVal->setObjectName("lblRoleVal");

        verticalLayoutFrameProfile->addWidget(lblRoleVal);


        horizontalLayoutProfileTop->addWidget(frameProfile);

        frameWallet = new QFrame(pageProfile);
        frameWallet->setObjectName("frameWallet");
        frameWallet->setFrameShape(QFrame::StyledPanel);
        verticalLayoutFrameWallet = new QVBoxLayout(frameWallet);
        verticalLayoutFrameWallet->setSpacing(12);
        verticalLayoutFrameWallet->setObjectName("verticalLayoutFrameWallet");
        verticalLayoutFrameWallet->setContentsMargins(20, 20, 20, 20);
        label_13 = new QLabel(frameWallet);
        label_13->setObjectName("label_13");

        verticalLayoutFrameWallet->addWidget(label_13);

        lblBalanceValue = new QLabel(frameWallet);
        lblBalanceValue->setObjectName("lblBalanceValue");
        lblBalanceValue->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayoutFrameWallet->addWidget(lblBalanceValue);

        verticalSpacerWallet = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayoutFrameWallet->addItem(verticalSpacerWallet);

        horizontalLayoutRecharge = new QHBoxLayout();
        horizontalLayoutRecharge->setObjectName("horizontalLayoutRecharge");
        spinRecharge = new QDoubleSpinBox(frameWallet);
        spinRecharge->setObjectName("spinRecharge");
        spinRecharge->setMinimum(10.000000000000000);
        spinRecharge->setMaximum(99999.000000000000000);
        spinRecharge->setSingleStep(100.000000000000000);
        spinRecharge->setValue(100.000000000000000);

        horizontalLayoutRecharge->addWidget(spinRecharge);

        btnRecharge = new QPushButton(frameWallet);
        btnRecharge->setObjectName("btnRecharge");

        horizontalLayoutRecharge->addWidget(btnRecharge);


        verticalLayoutFrameWallet->addLayout(horizontalLayoutRecharge);


        horizontalLayoutProfileTop->addWidget(frameWallet);


        verticalLayoutProfile->addLayout(horizontalLayoutProfileTop);

        frameStats = new QFrame(pageProfile);
        frameStats->setObjectName("frameStats");
        frameStats->setFrameShape(QFrame::StyledPanel);
        verticalLayoutFrameStats = new QVBoxLayout(frameStats);
        verticalLayoutFrameStats->setSpacing(12);
        verticalLayoutFrameStats->setObjectName("verticalLayoutFrameStats");
        verticalLayoutFrameStats->setContentsMargins(20, 20, 20, 20);
        label_15 = new QLabel(frameStats);
        label_15->setObjectName("label_15");

        verticalLayoutFrameStats->addWidget(label_15);

        lblTotalConsumption = new QLabel(frameStats);
        lblTotalConsumption->setObjectName("lblTotalConsumption");

        verticalLayoutFrameStats->addWidget(lblTotalConsumption);

        lblTotalListed = new QLabel(frameStats);
        lblTotalListed->setObjectName("lblTotalListed");

        verticalLayoutFrameStats->addWidget(lblTotalListed);

        horizontalLayoutStatsFunc = new QHBoxLayout();
        horizontalLayoutStatsFunc->setObjectName("horizontalLayoutStatsFunc");
        lblFuncIntro = new QLabel(frameStats);
        lblFuncIntro->setObjectName("lblFuncIntro");

        horizontalLayoutStatsFunc->addWidget(lblFuncIntro);

        comboStatsCategory = new QComboBox(frameStats);
        comboStatsCategory->setObjectName("comboStatsCategory");
        comboStatsCategory->setMinimumSize(QSize(150, 0));

        horizontalLayoutStatsFunc->addWidget(comboStatsCategory);

        horizontalSpacerStats = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayoutStatsFunc->addItem(horizontalSpacerStats);


        verticalLayoutFrameStats->addLayout(horizontalLayoutStatsFunc);

        lblStatsActiveGoods = new QLabel(frameStats);
        lblStatsActiveGoods->setObjectName("lblStatsActiveGoods");
        lblStatsActiveGoods->setStyleSheet(QString::fromUtf8("font-weight: bold; color: #007AFF;"));

        verticalLayoutFrameStats->addWidget(lblStatsActiveGoods);


        verticalLayoutProfile->addWidget(frameStats);

        verticalSpacerProfile = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayoutProfile->addItem(verticalSpacerProfile);

        stackedWidget->addWidget(pageProfile);

        horizontalLayout->addWidget(stackedWidget);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\345\234\210\345\234\210 - \346\240\241\345\233\255\344\272\214\346\211\213\344\272\244\346\230\223\345\271\263\345\217\260", nullptr));
        sidebarTitle->setText(QString());
        btnNavMarket->setText(QCoreApplication::translate("MainWindow", "\360\237\233\215\357\270\217 \344\272\214\346\211\213\345\270\202\345\234\272", nullptr));
        btnNavSell->setText(QCoreApplication::translate("MainWindow", "\360\237\223\244 \345\217\221\345\270\203\351\227\262\347\275\256", nullptr));
        btnNavOrders->setText(QCoreApplication::translate("MainWindow", "\360\237\223\235 \346\210\221\347\232\204\350\256\242\345\215\225", nullptr));
        btnNavFavorites->setText(QCoreApplication::translate("MainWindow", "\342\255\220 \346\210\221\347\232\204\346\224\266\350\227\217", nullptr));
        btnNavProfile->setText(QCoreApplication::translate("MainWindow", "\360\237\221\244 \344\270\252\344\272\272\344\270\255\345\277\203", nullptr));
        btnNavLogout->setText(QCoreApplication::translate("MainWindow", "\360\237\232\252 \351\200\200\345\207\272\347\231\273\345\275\225", nullptr));
        lblMarketTitle->setText(QCoreApplication::translate("MainWindow", "\344\272\214\346\211\213\345\270\202\345\234\272", nullptr));
        lblMarketTitle->setProperty("objectName", QVariant(QCoreApplication::translate("MainWindow", "titleLabel", nullptr)));
        editSearch->setPlaceholderText(QCoreApplication::translate("MainWindow", "\346\220\234\347\264\242\346\204\237\345\205\264\350\266\243\347\232\204\351\227\262\347\275\256\345\225\206\345\223\201...", nullptr));
        btnRefreshMarket->setText(QCoreApplication::translate("MainWindow", "\345\210\267\346\226\260", nullptr));
        lblSellTitle->setText(QCoreApplication::translate("MainWindow", "\345\217\221\345\270\203\345\256\235\350\264\235", nullptr));
        lblSellTitle->setProperty("objectName", QVariant(QCoreApplication::translate("MainWindow", "titleLabel", nullptr)));
        lblSellSub->setText(QCoreApplication::translate("MainWindow", "\345\256\214\345\226\204\345\225\206\345\223\201\350\257\246\347\273\206\344\277\241\346\201\257\357\274\214\350\256\251\344\271\260\345\256\266\344\270\200\347\234\274\347\233\270\344\270\255", nullptr));
        lblSellSub->setProperty("objectName", QVariant(QCoreApplication::translate("MainWindow", "tipLabel", nullptr)));
        lblSellName->setText(QCoreApplication::translate("MainWindow", "\345\225\206\345\223\201\345\220\215\347\247\260", nullptr));
        editSellTitle->setPlaceholderText(QCoreApplication::translate("MainWindow", "\344\276\213\345\246\202\357\274\232C++ Primer \347\254\2546\347\211\210\357\274\214iPad Air 5 \347\255\211...", nullptr));
        lblSellPrice->setText(QCoreApplication::translate("MainWindow", "\350\275\254\350\256\251\344\273\267\346\240\274 (\345\205\203)", nullptr));
        lblSellCategory->setText(QCoreApplication::translate("MainWindow", "\345\225\206\345\223\201\345\210\206\347\261\273", nullptr));
        lblSellDesc->setText(QCoreApplication::translate("MainWindow", "\350\257\246\346\203\205\346\217\217\350\277\260", nullptr));
        editSellDesc->setPlaceholderText(QCoreApplication::translate("MainWindow", "\350\257\246\347\273\206\346\217\217\350\277\260\345\225\206\345\223\201\347\232\204\346\210\220\350\211\262\343\200\201\350\264\255\344\271\260\346\270\240\351\201\223\343\200\201\344\272\244\346\230\223\346\226\271\345\274\217\357\274\210\345\246\202\351\243\237\345\240\202\351\235\242\344\272\244\343\200\201\345\256\277\350\210\215\346\245\274\350\207\252\346\217\220\347\255\211\357\274\211...", nullptr));
        btnPublish->setText(QCoreApplication::translate("MainWindow", "\360\237\232\200 \347\241\256\350\256\244\345\217\221\345\270\203\345\225\206\345\223\201", nullptr));
        btnPublish->setProperty("objectName", QVariant(QCoreApplication::translate("MainWindow", "primaryButton", nullptr)));
        lblOrdersTitle->setText(QCoreApplication::translate("MainWindow", "\346\210\221\347\232\204\344\272\244\346\230\223\350\256\242\345\215\225", nullptr));
        lblOrdersTitle->setProperty("objectName", QVariant(QCoreApplication::translate("MainWindow", "titleLabel", nullptr)));
        tabOrders->setTabText(tabOrders->indexOf(tabBought), QCoreApplication::translate("MainWindow", "\360\237\233\222 \346\210\221\344\271\260\345\205\245\347\232\204\345\256\235\350\264\235", nullptr));
        tabOrders->setTabText(tabOrders->indexOf(tabSold), QCoreApplication::translate("MainWindow", "\360\237\222\260 \346\210\221\345\224\256\345\207\272\347\232\204\345\256\235\350\264\235", nullptr));
        lblFavTitle->setText(QCoreApplication::translate("MainWindow", "\345\277\203\346\204\277\346\224\266\350\227\217\345\215\225", nullptr));
        lblFavTitle->setProperty("objectName", QVariant(QCoreApplication::translate("MainWindow", "titleLabel", nullptr)));
        lblProfileTitle->setText(QCoreApplication::translate("MainWindow", "\344\270\252\344\272\272\344\270\255\345\277\203", nullptr));
        lblProfileTitle->setProperty("objectName", QVariant(QCoreApplication::translate("MainWindow", "titleLabel", nullptr)));
        label_11->setText(QCoreApplication::translate("MainWindow", "\360\237\221\244 \345\237\272\346\234\254\350\265\204\346\226\231", nullptr));
        lblUsernameVal->setText(QCoreApplication::translate("MainWindow", "\347\224\250\346\210\267\345\220\215: \345\212\240\350\275\275\344\270\255...", nullptr));
        lblNicknameVal->setText(QCoreApplication::translate("MainWindow", "\346\230\265\347\247\260: \345\212\240\350\275\275\344\270\255...", nullptr));
        lblPhoneVal->setText(QCoreApplication::translate("MainWindow", "\350\201\224\347\263\273\346\226\271\345\274\217: \345\212\240\350\275\275\344\270\255...", nullptr));
        lblEmailVal->setText(QCoreApplication::translate("MainWindow", "\345\270\270\347\224\250\351\202\256\347\256\261: \345\212\240\350\275\275\344\270\255...", nullptr));
        lblRoleVal->setText(QCoreApplication::translate("MainWindow", "\350\264\246\345\217\267\350\272\253\344\273\275: \345\212\240\350\275\275\344\270\255...", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "\360\237\222\263 \346\210\221\347\232\204\351\222\261\345\214\205\344\275\231\351\242\235", nullptr));
        lblBalanceValue->setText(QCoreApplication::translate("MainWindow", "\357\277\2451000.00", nullptr));
        btnRecharge->setText(QCoreApplication::translate("MainWindow", "\360\237\222\260 \345\205\205\345\200\274\344\275\231\351\242\235", nullptr));
        btnRecharge->setProperty("objectName", QVariant(QCoreApplication::translate("MainWindow", "primaryButton", nullptr)));
        label_15->setText(QCoreApplication::translate("MainWindow", "\360\237\223\212 \346\225\260\346\215\256\345\272\223\347\274\226\347\250\213 \302\267 \351\253\230\347\272\247\344\270\232\345\212\241\347\273\237\350\256\241", nullptr));
        lblTotalConsumption->setText(QCoreApplication::translate("MainWindow", "\360\237\233\222 \347\264\257\350\256\241\346\210\220\344\272\244\346\266\210\350\264\271\346\200\273\351\242\235\357\274\232\357\277\2450.00", nullptr));
        lblTotalListed->setText(QCoreApplication::translate("MainWindow", "\360\237\223\244 \346\202\250\345\275\223\345\211\215\345\217\221\345\270\203\344\270\224\345\244\204\344\272\216\342\200\234\345\234\250\345\224\256\342\200\235\347\212\266\346\200\201\347\232\204\344\272\214\346\211\213\345\225\206\345\223\201\346\225\260\351\207\217\357\274\2320 \344\273\266", nullptr));
        lblFuncIntro->setText(QCoreApplication::translate("MainWindow", "\360\237\224\215 \345\256\236\346\227\266\346\243\200\347\264\242\347\211\271\345\256\232\345\210\206\347\261\273\347\232\204\345\234\250\345\224\256\351\227\262\347\275\256\346\200\273\346\225\260\357\274\232", nullptr));
        lblStatsActiveGoods->setText(QCoreApplication::translate("MainWindow", "\360\237\221\211 \350\257\245\345\210\206\347\261\273\345\205\250\347\253\231\345\275\223\345\211\215\342\200\234\345\234\250\345\224\256\342\200\235\351\227\262\347\275\256\346\225\260\351\207\217\357\274\2320 \344\273\266", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
