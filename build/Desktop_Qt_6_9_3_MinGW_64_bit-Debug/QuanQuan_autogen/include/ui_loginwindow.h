/********************************************************************************
** Form generated from reading UI file 'loginwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINWINDOW_H
#define UI_LOGINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginWindow
{
public:
    QVBoxLayout *verticalLayout;
    QStackedWidget *stackedWidget;
    QWidget *pageAuth;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *logoLayout;
    QSpacerItem *logoSpacerLeft;
    QLabel *labelImageIcon;
    QSpacerItem *logoSpacerRight;
    QLineEdit *editUsername;
    QLineEdit *editPassword;
    QLineEdit *editNickname;
    QLineEdit *editPhone;
    QLineEdit *editEmail;
    QPushButton *btnSubmit;
    QPushButton *btnToggleMode;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *LoginWindow)
    {
        if (LoginWindow->objectName().isEmpty())
            LoginWindow->setObjectName("LoginWindow");
        LoginWindow->resize(500, 600);
        verticalLayout = new QVBoxLayout(LoginWindow);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        stackedWidget = new QStackedWidget(LoginWindow);
        stackedWidget->setObjectName("stackedWidget");
        pageAuth = new QWidget();
        pageAuth->setObjectName("pageAuth");
        verticalLayout_2 = new QVBoxLayout(pageAuth);
        verticalLayout_2->setSpacing(15);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(40, 40, 40, 40);
        verticalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_3);

        logoLayout = new QHBoxLayout();
        logoLayout->setObjectName("logoLayout");
        logoSpacerLeft = new QSpacerItem(0, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        logoLayout->addItem(logoSpacerLeft);

        labelImageIcon = new QLabel(pageAuth);
        labelImageIcon->setObjectName("labelImageIcon");
        labelImageIcon->setMinimumSize(QSize(140, 140));
        labelImageIcon->setMaximumSize(QSize(140, 140));
        labelImageIcon->setPixmap(QPixmap(QString::fromUtf8(":/quanquan.png")));
        labelImageIcon->setScaledContents(true);

        logoLayout->addWidget(labelImageIcon);

        logoSpacerRight = new QSpacerItem(0, 0, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        logoLayout->addItem(logoSpacerRight);


        verticalLayout_2->addLayout(logoLayout);

        editUsername = new QLineEdit(pageAuth);
        editUsername->setObjectName("editUsername");

        verticalLayout_2->addWidget(editUsername);

        editPassword = new QLineEdit(pageAuth);
        editPassword->setObjectName("editPassword");
        editPassword->setEchoMode(QLineEdit::Password);

        verticalLayout_2->addWidget(editPassword);

        editNickname = new QLineEdit(pageAuth);
        editNickname->setObjectName("editNickname");

        verticalLayout_2->addWidget(editNickname);

        editPhone = new QLineEdit(pageAuth);
        editPhone->setObjectName("editPhone");

        verticalLayout_2->addWidget(editPhone);

        editEmail = new QLineEdit(pageAuth);
        editEmail->setObjectName("editEmail");

        verticalLayout_2->addWidget(editEmail);

        btnSubmit = new QPushButton(pageAuth);
        btnSubmit->setObjectName("btnSubmit");

        verticalLayout_2->addWidget(btnSubmit);

        btnToggleMode = new QPushButton(pageAuth);
        btnToggleMode->setObjectName("btnToggleMode");
        btnToggleMode->setStyleSheet(QString::fromUtf8("background: transparent; border: none; color: #007AFF; text-decoration: none; font-weight: 500;"));

        verticalLayout_2->addWidget(btnToggleMode);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        stackedWidget->addWidget(pageAuth);

        verticalLayout->addWidget(stackedWidget);


        retranslateUi(LoginWindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(LoginWindow);
    } // setupUi

    void retranslateUi(QWidget *LoginWindow)
    {
        LoginWindow->setWindowTitle(QCoreApplication::translate("LoginWindow", "\345\234\210\345\234\210 - \346\240\241\345\233\255\344\272\214\346\211\213\344\272\244\346\230\223\345\271\263\345\217\260", nullptr));
        editUsername->setPlaceholderText(QCoreApplication::translate("LoginWindow", "\347\224\250\346\210\267\345\220\215", nullptr));
        editPassword->setPlaceholderText(QCoreApplication::translate("LoginWindow", "\345\257\206\347\240\201", nullptr));
        editNickname->setPlaceholderText(QCoreApplication::translate("LoginWindow", "\346\230\265\347\247\260 (\345\246\202: \350\213\271\346\236\234\345\255\246\345\247\220)", nullptr));
        editPhone->setPlaceholderText(QCoreApplication::translate("LoginWindow", "\350\201\224\347\263\273\347\224\265\350\257\235", nullptr));
        editEmail->setPlaceholderText(QCoreApplication::translate("LoginWindow", "\347\224\265\345\255\220\351\202\256\347\256\261", nullptr));
        btnSubmit->setText(QCoreApplication::translate("LoginWindow", "\347\253\213\345\215\263\347\231\273\345\275\225", nullptr));
        btnSubmit->setProperty("objectName", QVariant(QCoreApplication::translate("LoginWindow", "primaryButton", nullptr)));
        btnToggleMode->setText(QCoreApplication::translate("LoginWindow", "\346\262\241\346\234\211\350\264\246\345\217\267\357\274\237\347\253\213\345\215\263\346\263\250\345\206\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginWindow: public Ui_LoginWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINWINDOW_H
