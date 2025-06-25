#ifndef TASK_H
#define TASK_H

#include <QObject>
#include <QTime>

class Task : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QTime startTime READ startTime WRITE setStartTime NOTIFY startTimeChanged)
    Q_PROPERTY(QTime endTime READ endTime WRITE setEndTime NOTIFY endTimeChanged)

public:
    explicit Task(QObject *parent = nullptr);
    Task(const QString &name, const QTime &start, const QTime &end, QObject *parent = nullptr);

    QString name() const;
    void setName(const QString &name);

    QTime startTime() const;
    void setStartTime(const QTime &time);

    QTime endTime() const;
    void setEndTime(const QTime &time);

signals:
    void nameChanged();
    void startTimeChanged();
    void endTimeChanged();

private:
    QString m_name;
    QTime m_startTime;
    QTime m_endTime;
};

#endif // TASK_H
