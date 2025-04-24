cmake_minimum_required(VERSION 3.16)  # Qt 6 requires CMake 3.16+
project(main CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_COMPILER "g++")  # Ensure this matches your Qt kit (e.g., MinGW)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)

find_package(Qt6 COMPONENTS 
    Core
    Widgets
    REQUIRED
    Charts
)

qt_add_resources(RESOURCE_FILES
    "styles/styles.qrc"
)

set(CMAKE_AUTOMOC ON)

include_directories(
    ${CMAKE_SOURCE_DIR}/include/SQLite3
    ${CMAKE_SOURCE_DIR}/src/Functions
    ${CMAKE_SOURCE_DIR}/src/Classes
    ${CMAKE_SOURCE_DIR}/src/Widgets/ItemCard
    ${CMAKE_SOURCE_DIR}/src/Widgets/WindowCard
    ${CMAKE_SOURCE_DIR}/src/Interfaces
    ${CMAKE_SOURCE_DIR}/src/Database/Items
)

file(GLOB SRC_FILES 
    ${CMAKE_SOURCE_DIR}/src/*.cpp 
    ${CMAKE_SOURCE_DIR}/include/SQLite3/*.c
    ${CMAKE_SOURCE_DIR}/src/Functions/*.cpp
    ${CMAKE_SOURCE_DIR}/src/Classes/*.cpp
    ${CMAKE_SOURCE_DIR}/src/Widgets/WindowCard/*.cpp
    ${CMAKE_SOURCE_DIR}/src/Widgets/ItemCard/*.cpp
    ${CMAKE_SOURCE_DIR}/src/Interfaces/*.cpp
)

# Copy images to build directory
file(COPY ${CMAKE_SOURCE_DIR}/src/Database/Items DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/src/Database)

add_executable(${PROJECT_NAME} 
    ${SRC_FILES}
    ${RESOURCE_FILES}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    pthread
    sqlite3
    Qt6::Core
    Qt6::Widgets
)
