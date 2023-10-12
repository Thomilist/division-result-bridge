add_library(Helpers Helpers.cpp)
target_link_libraries(
    Helpers PRIVATE
    Qt::Widgets
    Division
)