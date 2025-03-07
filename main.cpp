#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "notemodel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    NoteModel noteModel;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.rootContext()->setContextProperty("_noteModel", &noteModel);
    engine.loadFromModule("Thunder_Note_Client", "Main");

    return app.exec();
}
