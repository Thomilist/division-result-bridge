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
    Version
)