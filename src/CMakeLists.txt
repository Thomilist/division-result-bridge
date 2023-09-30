add_library(AboutDialog AboutDialog.cpp)
target_link_libraries(
    AboutDialog PRIVATE
    Qt::Widgets
    Helpers
    Version
)
add_custom_target(
    AlwaysRebuildAboutDialog
    ALL
    COMMAND
    ${CMAKE_COMMAND} -E touch_nocreate ${CMAKE_SOURCE_DIR}/src/AboutDialog.cpp
)
add_dependencies(
    AboutDialog
    AlwaysRebuildAboutDialog
)

add_library(Competition Competition.cpp)
target_link_libraries(
    Competition PRIVATE
    Qt::Widgets
    Helpers
)

add_library(CompetitionCreatedDialog CompetitionCreatedDialog.cpp)
target_link_libraries(
    CompetitionCreatedDialog PRIVATE
    Qt::Widgets
    Competition
)

add_library(ConfigValidator ConfigValidator.cpp)
target_link_libraries(
    ConfigValidator PRIVATE
    Qt::Widgets
    Helpers
    Loggable
    Logger
    Settings
)

add_library(Coordinator Coordinator.cpp)
target_link_libraries(
    Coordinator PRIVATE
    Qt::Widgets
    cpr::cpr
    Competition
    Division
    Helpers
    Loggable
    Logger
    MeosInterface
    ResultPackage
    Settings
    WebserverInterface
)

add_library(CreateCompetitionDialog CreateCompetitionDialog.cpp)
target_link_libraries(
    CreateCompetitionDialog PRIVATE
    Qt::Widgets
    Helpers
)

add_library(Division Division.cpp)
target_link_libraries(
    Division PRIVATE
    Qt::Widgets
)

add_library(DivisionEditor DivisionEditor.cpp)
target_link_libraries(
    DivisionEditor PRIVATE
    Qt::Widgets
    Division
)

add_library(DivisionTableModel DivisionTableModel.cpp)
target_link_libraries(
    DivisionTableModel PRIVATE
    Qt::Widgets
    Settings
)

add_library(Helpers Helpers.cpp)
target_link_libraries(
    Helpers PRIVATE
    Qt::Widgets
    Division
)

add_library(Loggable Loggable.cpp)
target_link_libraries(
    Loggable PRIVATE
    Qt::Widgets
    cpr::cpr
    Logger
    LoggerProxy
)

add_library(Logger Logger.cpp)
target_link_libraries(
    Logger PRIVATE
    Qt::Widgets
    cpr::cpr
    Helpers
)

add_library(LoggerProxy LoggerProxy.cpp)
target_link_libraries(
    LoggerProxy PRIVATE
    Qt::Widgets
    cpr::cpr
    Logger
)

add_library(MainWindow MainWindow.cpp)
target_link_libraries(
    MainWindow PRIVATE
    Qt::Widgets
    AboutDialog
    CompetitionCreatedDialog
    ConfigValidator
    CreateCompetitionDialog
    Division
    DivisionEditor
    DivisionTableModel
    Helpers
    Logger
    Loggable
    MeosInterface
    Coordinator
    PersistentSettings
    UpdateDialog
    Version
    VersionNotifier
)

add_library(MeosInterface MeosInterface.cpp)
target_link_libraries(
    MeosInterface PRIVATE
    Qt::Widgets
    cpr::cpr
    pugixml::pugixml
    Competition
    Helpers
    Loggable
    Logger
    Settings
)

add_library(PersistentSettings PersistentSettings.cpp)
target_link_libraries(
    PersistentSettings PRIVATE
    Qt::Widgets
    Division
    Settings
)

add_library(ResultPackage ResultPackage.cpp)
target_link_libraries(
    ResultPackage PRIVATE
    Qt::Widgets
)

add_library(Settings Settings.cpp)
target_link_libraries(
    Settings PRIVATE
    Qt::Widgets
    Competition
    Division
)

add_library(UpdateDialog UpdateDialog.cpp)
target_link_libraries(
    UpdateDialog PRIVATE
    Qt::Widgets
    Helpers
    Version
)

add_library(Version Version.cpp)
target_link_libraries(
    Version PRIVATE
    Qt::Widgets
    cpr::cpr
    nlohmann_json::nlohmann_json
    Helpers
)

add_library(VersionNotifier VersionNotifier.cpp)
target_link_libraries(
    VersionNotifier PRIVATE
    Qt::Widgets
    Helpers
    Loggable
    Logger
    Version
)

add_library(WebserverInterface WebserverInterface.cpp)
target_link_libraries(
    WebserverInterface PRIVATE
    Qt::Widgets
    cpr::cpr
    Competition
    Division
    Helpers
    Loggable
    Logger
    ResultPackage
    Settings
)