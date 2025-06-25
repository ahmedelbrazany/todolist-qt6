#include "TaskManager.h"
#include <QDateTime>
#include <QDebug>

TaskManager::TaskManager(QObject *parent)
    : QObject(parent)
{
    // ضبط التايمر ليفحص المهام كل دقيقة
    m_checkTimer.setInterval(60000); // 60 ثانية
    connect(&m_checkTimer, &QTimer::timeout, this, &TaskManager::checkTasks);
    m_checkTimer.start();
}
QQmlListProperty<Task> TaskManager::tasks()
{
    return QQmlListProperty<Task>(this, &m_tasks,
                                  appendTask, taskCount, taskAt, clearTasks);
}

void TaskManager::appendTask(QQmlListProperty<Task>* list, Task* task)
{
    auto tasks = static_cast<QList<Task*>*>(list->data);
    tasks->append(task);
}

qsizetype TaskManager::taskCount(QQmlListProperty<Task>* list)
{
    auto tasks = static_cast<QList<Task*>*>(list->data);
    return tasks->size();
}

Task* TaskManager::taskAt(QQmlListProperty<Task>* list, qsizetype index)
{
    auto tasks = static_cast<QList<Task*>*>(list->data);
    return tasks->at(index);
}

void TaskManager::clearTasks(QQmlListProperty<Task>* list)
{
    auto tasks = static_cast<QList<Task*>*>(list->data);
    qDeleteAll(*tasks);
    tasks->clear();
}

void TaskManager::addTask(const QString &name, const QTime &start, const QTime &end)
{
    Task *task = new Task(name, start, end, this);
    m_tasks.append(task);
    emit tasksChanged();
}

void TaskManager::checkTasks()
{
    QTime now = QTime::currentTime();

    for (Task* task : std::as_const(m_tasks)) {
        int diff = now.secsTo(task->startTime());

        if (diff > 0 && diff <= 300) { // 5 دقائق أو أقل
            emit taskStartingSoon(task->name());
            qDebug() << "Task starting soon:" << task->name();
        }
    }
}
