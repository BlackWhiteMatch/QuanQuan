#include "dbmanager.h"
#include <QDebug>
#include <QCryptographicHash>

DbManager::DbManager(QObject *parent)
    : QObject(parent)
    , m_currentUserId(-1)
{
    m_connectionName = "QuanQuanConnection";
}

DbManager::~DbManager()
{
    closeConnection();
}

DbManager& DbManager::instance()
{
    static DbManager inst;
    return inst;
}

bool DbManager::connectToMySQL(const QString &host, int port, const QString &dbName, const QString &username, const QString &password)
{
    closeConnection();

    m_lastErrorText.clear();

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL", m_connectionName);
    db.setHostName(host);
    db.setPort(port);
    db.setDatabaseName(dbName);
    db.setUserName(username);
    db.setPassword(password);

    if (!db.open()) {
        m_lastErrorText = db.lastError().text();
        qWarning() << "Failed to open MySQL database:" << m_lastErrorText;
        return false;
    }

    qDebug() << "Successfully connected to MySQL database!";
    return true;
}

#include <QCoreApplication>

void DbManager::closeConnection()
{
    if (!QCoreApplication::instance()) return;

    if (QSqlDatabase::contains(m_connectionName)) {
        QSqlDatabase db = QSqlDatabase::database(m_connectionName);
        if (db.isOpen()) {
            db.close();
        }
    }
    QSqlDatabase::removeDatabase(m_connectionName);
}

bool DbManager::isConnected() const
{
    if (!QSqlDatabase::contains(m_connectionName)) return false;
    return QSqlDatabase::database(m_connectionName).isOpen();
}

bool DbManager::executeQuery(const QString &queryStr, const QVariantList &params)
{
    if (!isConnected()) {
        qWarning() << "Database not connected!";
        return false;
    }

    QSqlDatabase db = QSqlDatabase::database(m_connectionName);
    QSqlQuery query(db);
    query.prepare(queryStr);

    for (int i = 0; i < params.size(); ++i) {
        query.bindValue(i, params[i]);
    }

    if (!query.exec()) {
        qWarning() << "Execute query failed:" << query.lastError().text() << "\nSQL:" << queryStr;
        return false;
    }
    return true;
}

QSqlQuery DbManager::selectQuery(const QString &queryStr, const QVariantList &params)
{
    if (!isConnected()) {
        qWarning() << "Database not connected!";
        return QSqlQuery();
    }

    QSqlDatabase db = QSqlDatabase::database(m_connectionName);
    QSqlQuery query(db);
    query.prepare(queryStr);

    for (int i = 0; i < params.size(); ++i) {
        query.bindValue(i, params[i]);
    }

    if (!query.exec()) {
        QString errText = query.lastError().text();
        QString decodedErr = QString::fromUtf8(errText.toLatin1());
        qWarning() << "Select query failed:" << (decodedErr.isEmpty() ? errText : decodedErr);
        qWarning() << "SQL:" << queryStr;
    }
    return query;
}

bool DbManager::beginTransaction()
{
    if (!isConnected()) return false;
    return QSqlDatabase::database(m_connectionName).transaction();
}

bool DbManager::commitTransaction()
{
    if (!isConnected()) return false;
    return QSqlDatabase::database(m_connectionName).commit();
}

bool DbManager::rollbackTransaction()
{
    if (!isConnected()) return false;
    return QSqlDatabase::database(m_connectionName).rollback();
}

double DbManager::getUserTotalConsumption(int userId)
{
    if (!isConnected()) return 0.00;
    
    QSqlDatabase db = QSqlDatabase::database(m_connectionName);
    QSqlQuery query(db);
    
    // 调用存储过程 CalculateUserTotalConsumption
    query.prepare("CALL CalculateUserTotalConsumption(?, ?)");
    query.bindValue(0, userId);
    query.bindValue(1, 0.00, QSql::Out); // 绑定输出参数

    if (!query.exec()) {
        qWarning() << "Call stored procedure failed:" << query.lastError().text();
        return 0.00;
    }
    
    return query.boundValue(1).toDouble();
}

int DbManager::getCategoryActiveGoodsCount(int categoryId)
{
    if (!isConnected()) return 0;
    
    // 调用自定义函数 CountActiveProductsInCategory
    QSqlQuery q = selectQuery("SELECT CountActiveProductsInCategory(?)", QVariantList() << categoryId);
    if (q.next()) {
        return q.value(0).toInt();
    }
    return 0;
}

QString DbManager::hashPassword(const QString &password)
{
    // 加盐哈希加密 (加盐 SHA-256)，提升防破解安全性
    QString salt = "QuanQuanSaltKey2026";
    QByteArray saltedPass = (password + salt).toUtf8();
    QByteArray hash = QCryptographicHash::hash(saltedPass, QCryptographicHash::Sha256);
    return QString(hash.toHex());
}
