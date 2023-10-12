add_subdirectory(comp-create-wizard)
add_subdirectory(logging)
add_subdirectory(utils)
add_subdirectory(version)
add_subdirectory(workers)

add_library(AboutDialog AboutDialog.cpp)
target_link_libraries(
    AboutDialog PRIVATE
    Qt::Widgets
    cpr::cpr
    pugixml::pugixml
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

add_library(ConfigValidator ConfigValidator.cpp)
target_link_libraries(
    ConfigValidator PRIVATE
    Qt::Widgets
    Division
    Helpers
    Loggable
    Settings
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
    Helpers
)

add_library(DivisionTableModel DivisionTableModel.cpp)
target_link_libraries(
    DivisionTableModel PRIVATE
    Qt::Widgets
    Settings
)

add_library(MainWindow MainWindow.cpp)
target_link_libraries(
    MainWindow PRIVATE
    Qt::Widgets
    AboutDialog
    CompetitionCreationWizard
    ConfigValidator
    Division
    DivisionEditor
    DivisionTableModel
    Helpers
    Loggable
    Logger
    LoggerProxy
    Coordinator
    PersistentSettings
    UpdateDialog
    Version
    VersionNotifier
)

add_library(PersistentSettings PersistentSettings.cpp)
target_link_libraries(
    PersistentSettings PRIVATE
    Qt::Widgets
    Division
    Settings
)

add_library(Settings Settings.cpp)
target_link_libraries(
    Settings PRIVATE
    Qt::Widgets
    Competition
    Division
)