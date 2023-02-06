#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "backend.h"

// /home/revgato/Qt5.12.12/5.12.12/gcc_64/bin/qmake

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    if(argc != 3){
        printf("Usage: %s <ip> <port>\n", argv[0]);
        return 0;
    }
    strcpy(Backend::server_ip, argv[1]);
    Backend::server_port = atoi(argv[2]);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    qmlRegisterType<Backend>("Backend", 1, 0, "Backend");
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
