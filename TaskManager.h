#include <QObject>
#include <QList>
#include <QTimer>
#include <QtQml/QQmlListProperty>
#include <QTime>
#include "Task.h"

class TaskManager : public QObject {
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<Task> tasks READ tasks NOTIFY tasksChanged)

public:
    explicit TaskManager(QObject *parent = nullptr);

    QQmlListProperty<Task> tasks();
    Q_INVOKABLE void addTask(const QString &name, const QTime &start, const QTime &end);

signals:
    void tasksChanged();
    void taskStartingSoon(const QString &taskName);

private:
    QList<Task*> m_tasks;
    QTimer m_checkTimer;

    void checkTasks();

    static qsizetype taskCount(QQmlListProperty<Task>* list);
    static Task* taskAt(QQmlListProperty<Task>* list, qsizetype index);
    static void clearTasks(QQmlListProperty<Task>* list);
    static void appendTask(QQmlListProperty<Task>* list, Task* task); // وظيفة لإضافة المهام
};
