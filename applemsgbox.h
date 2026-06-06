#ifndef APPLEMSGBOX_H
#define APPLEMSGBOX_H

#include <QWidget>
#include <QString>
#include <QMessageBox>

class AppleMsgBox : public QWidget
{
    Q_OBJECT
public:
    explicit AppleMsgBox(QWidget *parent, const QString &title, const QString &text, int buttons);
    
    static QMessageBox::StandardButton information(QWidget *parent, const QString &title, const QString &text);
    static QMessageBox::StandardButton warning(QWidget *parent, const QString &title, const QString &text);
    static QMessageBox::StandardButton critical(QWidget *parent, const QString &title, const QString &text);
    static QMessageBox::StandardButton question(QWidget *parent, const QString &title, const QString &text, int buttons = QMessageBox::Yes | QMessageBox::No);
    
    QMessageBox::StandardButton getClickedButton() const { return m_clickedButton; }

signals:
    void finished();

private:
    QMessageBox::StandardButton m_clickedButton;
};

#endif // APPLEMSGBOX_H
