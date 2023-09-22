cmake_minimum_required(VERSION 3.27.4)
project(division-result-bridge VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_compile_options(
    -Wall
    -Wextra
    -pedantic
    -Werror
)

if(MINGW)
    set(CMAKE_CXX_FLAGS "-mwindows")    
    set(APP_ICON_RESOURCE_WINDOWS "${CMAKE_CURRENT_SOURCE_DIR}/resources/icon/icon.rc")
    add_executable(
        ${PROJECT_NAME}
        main.cpp
        resources/resources.qrc
        ${APP_ICON_RESOURCE_WINDOWS}
    )
else()
    add_executable(
        ${PROJECT_NAME}
        main.cpp
        resources/resources.qrc
    )
endif()

find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(nlohmann_json REQUIRED)
set(CPR_USE_SYSTEM_CURL ON)
find_package(cpr REQUIRED)
find_package(pugixml REQUIRED)

add_subdirectory(src)
target_link_libraries(
    division-result-bridge PRIVATE
    Qt::Widgets
    Helpers
    MainWindow
    Version
)