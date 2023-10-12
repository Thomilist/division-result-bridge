add_library(Coordinator Coordinator.cpp)
target_link_libraries(
    Coordinator PRIVATE
    Qt::Widgets
    cpr::cpr
    Competition
    DivisionInterface
    Helpers
    Loggable
    MeosInterface
    ResultPackage
    Settings
    WebserverInterface
)

add_library(DivisionInterface DivisionInterface.cpp)
target_link_libraries(
    DivisionInterface PRIVATE
    Qt::Widgets
    cpr::cpr
    Division
    Helpers
    Loggable
    Settings
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
    Settings
)

add_library(ResultPackage ResultPackage.cpp)
target_link_libraries(
    ResultPackage PRIVATE
    Qt::Widgets
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
    ResultPackage
    Settings
)