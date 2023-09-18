#include <QApplication>
#include <QCoreApplication>
#include <QObject>

#include "src/ForwardDeclarations.hpp"

#include "src/Helpers.hpp"
#include "src/MainWindow.hpp"
#include "src/Version.hpp"

int main(int argc, char* argv[])
{
    QApplication application{argc, argv};

    divi::Version version{divi::Helpers::projectVersion()};

    QCoreApplication::setOrganizationName(divi::Helpers::authorUsername());
    QCoreApplication::setApplicationName(divi::Helpers::projectName());
    QCoreApplication::setApplicationVersion(version.getCurrentVersion());

    divi::MainWindow main_window{&version};

    QObject::connect(&application, &QApplication::lastWindowClosed, &application, &QApplication::quit);

    return application.exec();
}