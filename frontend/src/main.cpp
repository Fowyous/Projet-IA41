#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QGuiApplication::setOrganizationName("RasendeRoboter");
    QGuiApplication::setApplicationName("RasendeRoboter");

    // Style "Basic" : le même rendu partout, entièrement personnalisable par nos couleurs
    QQuickStyle::setStyle("Basic");

    QQmlApplicationEngine engine;
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
                     &app, []() { QCoreApplication::exit(-1); },
                     Qt::QueuedConnection);
    engine.loadFromModule("RasendeRoboter", "Main");
    return app.exec();
}
