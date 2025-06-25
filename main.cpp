#include <QGuiApplication>
#include <QtQml/QQmlApplicationEngine>
#include <QtQml/QQmlContext>

#include "TaskManager.h"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    TaskManager taskManager;
    engine.rootContext()->setContextProperty("taskManager", &taskManager);

    const QUrl url(u"qrc:/qml/Main.qml"_qs);
    engine.load(url);

    return app.exec();
}
