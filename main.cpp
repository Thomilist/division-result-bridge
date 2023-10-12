#include <QApplication>
#include <QCoreApplication>
#include <QObject>

#include "src/utils/ForwardDeclarations.hpp"

#include "src/utils/Helpers.hpp"
#include "src/MainWindow.hpp"
#include "src/version/Version.hpp"

#ifdef _WIN32
extern Q_CORE_EXPORT int qt_ntfs_permission_lookup;
#endif

int main(int argc, char* argv[])
{
    #ifdef _WIN32
    ++qt_ntfs_permission_lookup;
    #endif
    
    QApplication application{argc, argv};

    divi::Version version{divi::Helpers::projectVersion()};

    QCoreApplication::setOrganizationName(divi::Helpers::authorUsername());
    QCoreApplication::setApplicationName(divi::Helpers::projectName());
    QCoreApplication::setApplicationVersion(version.getCurrentVersion());

    divi::MainWindow main_window{&version};

    QObject::connect(&application, &QApplication::lastWindowClosed, &application, &QApplication::quit);

    const int status = application.exec();

    #ifdef _WIN32
    --qt_ntfs_permission_lookup;
    #endif
    
    return status;
}