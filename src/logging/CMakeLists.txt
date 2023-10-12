add_library(Loggable Loggable.cpp)
target_link_libraries(
    Loggable PRIVATE
    Qt::Widgets
    cpr::cpr
    LoggerProxy
    LoggerRegistry
)

add_library(Logger Logger.cpp)
target_link_libraries(
    Logger PRIVATE
    Qt::Widgets
    cpr::cpr
    Helpers
    LoggerRegistry
    Settings
)

add_library(LoggerProxy LoggerProxy.cpp)
target_link_libraries(
    LoggerProxy PRIVATE
    Qt::Widgets
    cpr::cpr
)

add_library(LoggerRegistry LoggerRegistry.cpp)
target_link_libraries(
    LoggerRegistry PRIVATE
    Qt::Widgets
    Loggable
    Logger
    LoggerProxy
)