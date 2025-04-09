cmake_minimum_required(VERSION 3.16)

project(Puzzle VERSION 1.0 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(SOURCE_DIR src)
set(INCLUDE_DIR include)

file(GLOB_RECURSE SOURCES "${SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE HEADERS "${INCLUDE_DIR}/*.h")

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} PRIVATE Qt::Core Qt::Widgets)

target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIR})
