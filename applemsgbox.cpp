#include "applemsgbox.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QGraphicsDropShadowEffect>
#include <QPainter>
#include <QEventLoop>
#include <QFrame>
#include <QEvent>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QWheelEvent>
#include <QPointer>

class AppleMsgBoxOverlay : public QWidget {
public:
    AppleMsgBoxOverlay(QWidget *parent) : QWidget(parent) {
        if (parent) {
            parent->installEventFilter(this);
            resize(parent->size());
        }
        setObjectName("appleOverlay");
        setStyleSheet("QWidget#appleOverlay { background-color: rgba(0, 0, 0, 60); }");
        setFocusPolicy(Qt::StrongFocus);
        setFocus(); // grab focus to block keyboard events from other widgets
    }
    
protected:
    bool eventFilter(QObject *obj, QEvent *event) override {
        if (obj == parentWidget() && event->type() == QEvent::Resize) {
            resize(parentWidget()->size());
            if (children().count() > 0) {
                QWidget *box = nullptr;
                for (QObject *child : children()) {
                    if (child->isWidgetType()) {
                        box = qobject_cast<QWidget*>(child);
                        break;
                    }
                }
                if (box) {
                    box->move((width() - box->width()) / 2, (height() - box->height()) / 2);
                }
            }
        }
        return QWidget::eventFilter(obj, event);
    }
    
    void mousePressEvent(QMouseEvent *event) override { event->accept(); }
    void mouseReleaseEvent(QMouseEvent *event) override { event->accept(); }
    void mouseDoubleClickEvent(QMouseEvent *event) override { event->accept(); }
    void mouseMoveEvent(QMouseEvent *event) override { event->accept(); }
    void keyPressEvent(QKeyEvent *event) override { event->accept(); }
    void keyReleaseEvent(QKeyEvent *event) override { event->accept(); }
    void wheelEvent(QWheelEvent *event) override { event->accept(); }
};

AppleMsgBox::AppleMsgBox(QWidget *parent, const QString &title, const QString &text, int buttons)
    : QWidget(parent), m_clickedButton(QMessageBox::NoButton)
{
    setMinimumWidth(300);
    setMaximumWidth(300);
    
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(15, 15, 15, 15);
    mainLayout->setSpacing(0);
    
    QWidget *container = new QWidget(this);
    container->setObjectName("appleContainer");
    container->setStyleSheet(
        "QWidget#appleContainer {"
        "  background-color: rgba(255, 255, 255, 245);"
        "  border-radius: 14px;"
        "}"
    );
    
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setBlurRadius(20);
    shadow->setColor(QColor(0, 0, 0, 60));
    shadow->setOffset(0, 4);
    container->setGraphicsEffect(shadow);
    
    QVBoxLayout *vLayout = new QVBoxLayout(container);
    vLayout->setContentsMargins(0, 0, 0, 0);
    vLayout->setSpacing(0);
    
    QVBoxLayout *contentLayout = new QVBoxLayout();
    contentLayout->setContentsMargins(20, 24, 20, 20);
    contentLayout->setSpacing(10);
    
    if (!title.isEmpty()) {
        QLabel *titleLabel = new QLabel(title, container);
        titleLabel->setAlignment(Qt::AlignCenter);
        titleLabel->setStyleSheet("background-color: transparent; font-weight: bold; font-size: 17px; color: #000000; font-family: -apple-system, 'SF Pro Display', 'Microsoft YaHei';");
        contentLayout->addWidget(titleLabel);
    }
    
    if (!text.isEmpty()) {
        QLabel *textLabel = new QLabel(text, container);
        textLabel->setAlignment(Qt::AlignCenter);
        textLabel->setWordWrap(true);
        textLabel->setStyleSheet("background-color: transparent; font-size: 14px; color: #333333; font-family: -apple-system, 'SF Pro Text', 'Microsoft YaHei'; line-height: 1.5;");
        contentLayout->addWidget(textLabel);
    }
    
    vLayout->addLayout(contentLayout);
    
    QFrame *hLine = new QFrame(container);
    hLine->setFrameShape(QFrame::HLine);
    hLine->setStyleSheet("background-color: rgba(60, 60, 67, 0.29); min-height: 1px; max-height: 1px; margin: 0px; padding: 0px; border: none;");
    vLayout->addWidget(hLine);
    
    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->setContentsMargins(0, 0, 0, 0);
    hLayout->setSpacing(0);
    
    QString btnStyleRight = 
        "QPushButton {"
        "  background: transparent;"
        "  color: #007aff;"
        "  font-weight: bold;"
        "  font-size: 17px;"
        "  border: none;"
        "  min-height: 44px;"
        "  max-height: 44px;"
        "}"
        "QPushButton:pressed {"
        "  background: rgba(0, 0, 0, 10);"
        "  border-bottom-right-radius: 14px;"
        "}";
        
    QString btnStyleLeft = 
        "QPushButton {"
        "  background: transparent;"
        "  color: #007aff;"
        "  font-size: 17px;"
        "  border: none;"
        "  min-height: 44px;"
        "  max-height: 44px;"
        "}"
        "QPushButton:pressed {"
        "  background: rgba(0, 0, 0, 10);"
        "  border-bottom-left-radius: 14px;"
        "}";
        
    QString btnStyleSingle = 
        "QPushButton {"
        "  background: transparent;"
        "  color: #007aff;"
        "  font-weight: bold;"
        "  font-size: 17px;"
        "  border: none;"
        "  min-height: 44px;"
        "  max-height: 44px;"
        "}"
        "QPushButton:pressed {"
        "  background: rgba(0, 0, 0, 10);"
        "  border-bottom-left-radius: 14px;"
        "  border-bottom-right-radius: 14px;"
        "}";
    
    if ((buttons & QMessageBox::Yes) && (buttons & QMessageBox::No)) {
        QPushButton *btnNo = new QPushButton("取消", container);
        btnNo->setStyleSheet(btnStyleLeft);
        btnNo->setCursor(Qt::PointingHandCursor);
        connect(btnNo, &QPushButton::clicked, this, [this]() {
            m_clickedButton = QMessageBox::No;
            emit finished();
        });
        hLayout->addWidget(btnNo);
        
        QFrame *vLine = new QFrame(container);
        vLine->setFrameShape(QFrame::VLine);
        vLine->setStyleSheet("background-color: rgba(60, 60, 67, 0.29); min-width: 1px; max-width: 1px; margin: 0px; padding: 0px; border: none;");
        hLayout->addWidget(vLine);
        
        QPushButton *btnYes = new QPushButton("确认", container);
        btnYes->setStyleSheet(btnStyleRight);
        btnYes->setCursor(Qt::PointingHandCursor);
        connect(btnYes, &QPushButton::clicked, this, [this]() {
            m_clickedButton = QMessageBox::Yes;
            emit finished();
        });
        hLayout->addWidget(btnYes);
    } else {
        QPushButton *btnOk = new QPushButton("确定", container);
        btnOk->setStyleSheet(btnStyleSingle);
        btnOk->setCursor(Qt::PointingHandCursor);
        connect(btnOk, &QPushButton::clicked, this, [this]() {
            m_clickedButton = QMessageBox::Ok;
            emit finished();
        });
        hLayout->addWidget(btnOk);
    }
    
    vLayout->addLayout(hLayout);
    mainLayout->addWidget(container);
}

static QMessageBox::StandardButton executeOverlayMsgBox(QWidget *parent, const QString &title, const QString &text, int buttons) {
    QWidget *topLevel = parent ? parent->window() : nullptr;
    
    if (!topLevel) {
        QMessageBox msgBox(parent);
        msgBox.setWindowTitle(title);
        msgBox.setText(text);
        if ((buttons & QMessageBox::Yes) && (buttons & QMessageBox::No)) {
            msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        } else {
            msgBox.setStandardButtons(QMessageBox::Ok);
        }
        return (QMessageBox::StandardButton)msgBox.exec();
    }
    
    AppleMsgBoxOverlay *overlay = new AppleMsgBoxOverlay(topLevel);
    AppleMsgBox *box = new AppleMsgBox(overlay, title, text, buttons);
    
    overlay->show();
    overlay->raise();
    box->move((overlay->width() - box->width()) / 2, (overlay->height() - box->height()) / 2);
    box->show();
    
    QEventLoop loop;
    QPointer<AppleMsgBox> boxPtr(box);
    QObject::connect(box, &AppleMsgBox::finished, &loop, &QEventLoop::quit);
    QObject::connect(topLevel, &QObject::destroyed, &loop, &QEventLoop::quit);
    loop.exec();
    
    QMessageBox::StandardButton result = QMessageBox::Cancel;
    if (boxPtr) {
        result = boxPtr->getClickedButton();
        overlay->deleteLater();
    }
    
    return result;
}

QMessageBox::StandardButton AppleMsgBox::information(QWidget *parent, const QString &title, const QString &text) {
    return executeOverlayMsgBox(parent, title, text, QMessageBox::Ok);
}

QMessageBox::StandardButton AppleMsgBox::warning(QWidget *parent, const QString &title, const QString &text) {
    return executeOverlayMsgBox(parent, title, text, QMessageBox::Ok);
}

QMessageBox::StandardButton AppleMsgBox::critical(QWidget *parent, const QString &title, const QString &text) {
    return executeOverlayMsgBox(parent, title, text, QMessageBox::Ok);
}

QMessageBox::StandardButton AppleMsgBox::question(QWidget *parent, const QString &title, const QString &text, int buttons) {
    return executeOverlayMsgBox(parent, title, text, buttons);
}
