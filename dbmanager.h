#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariantList>

class DbManager : public QObject
{
    Q_OBJECT

public:
    static DbManager& instance();

    // 连接到 MySQL 数据库
    bool connectToMySQL(const QString &host, int port, const QString &dbName, const QString &username, const QString &password);
    
    // 关闭当前连接
    void closeConnection();

    // 检查数据库是否已连接
    bool isConnected() const;

    // 获取最后的连接/执行错误信息
    QString getLastErrorText() const { return m_lastErrorText; }

    // 执行不需要返回结果的 SQL 语句 (参数化绑定，防注入，如 INSERT, UPDATE, DELETE)
    bool executeQuery(const QString &queryStr, const QVariantList &params = QVariantList());

    // 执行带参数的查询，返回 QSqlQuery
    QSqlQuery selectQuery(const QString &queryStr, const QVariantList &params = QVariantList());

    // 事务控制
    bool beginTransaction();
    bool commitTransaction();
    bool rollbackTransaction();

    // 调用存储过程获取用户消费总额
    double getUserTotalConsumption(int userId);

    // 调用自定义函数获取分类下商品数量
    int getCategoryActiveGoodsCount(int categoryId);

    // 获取当前登录用户 ID 和信息
    int getCurrentUserId() const { return m_currentUserId; }
    QString getCurrentUsername() const { return m_currentUsername; }
    QString getCurrentUserNickname() const { return m_currentUserNickname; }
    QString getCurrentUserRole() const { return m_currentUserRole; }
    
    void setCurrentUser(int id, const QString &username, const QString &nickname, const QString &role) {
        m_currentUserId = id;
        m_currentUsername = username;
        m_currentUserNickname = nickname;
        m_currentUserRole = role;
    }
    
    void clearCurrentUser() {
        m_currentUserId = -1;
        m_currentUsername.clear();
        m_currentUserNickname.clear();
        m_currentUserRole.clear();
    }

    // 哈希加密密码 (加盐 SHA256)
    static QString hashPassword(const QString &password);

private:
    DbManager(QObject *parent = nullptr);
    ~DbManager() override;

    DbManager(const DbManager&) = delete;
    DbManager& operator=(const DbManager&) = delete;

    QString m_connectionName;
    int m_currentUserId;
    QString m_currentUsername;
    QString m_currentUserNickname;
    QString m_currentUserRole;
    QString m_lastErrorText;
};

#endif // DBMANAGER_H
