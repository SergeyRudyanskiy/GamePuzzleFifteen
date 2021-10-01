#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "gameboard.h"

int main(int argc, char *argv[]) {
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    GameBoard model;
    qmlRegisterType<GameBoard>("GamePuzzleFifteen", 1, 0, "GameBordModel");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));

    auto lambda_checker_validity = [url](QObject *obj, const QUrl &objUrl) { if (!obj && url == objUrl) QCoreApplication::exit(-1); };

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated, &app, lambda_checker_validity , Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
