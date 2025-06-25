#include "Task.h"

Task::Task(QObject *parent) : QObject(parent) {}
Task::Task(const QString &name, const QTime &start, const QTime &end, QObject *parent)
    : QObject(parent), m_name(name), m_startTime(start), m_endTime(end) {}

QString Task::name() const { return m_name; }
void Task::setName(const QString &name) { m_name = name; emit nameChanged(); }

QTime Task::startTime() const { return m_startTime; }
void Task::setStartTime(const QTime &time) { m_startTime = time; emit startTimeChanged(); }

QTime Task::endTime() const { return m_endTime; }
void Task::setEndTime(const QTime &time) { m_endTime = time; emit endTimeChanged(); }
