cmake_minimum_required(VERSION 3.14)

project(Nicone LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core LinguistTools REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core LinguistTools REQUIRED)

set(TS_FILES Nicone_en_150.ts)

add_executable(Nicone
  main.cpp
  read_nicolete_file.cpp
  ${TS_FILES}
)


add_subdirectory(../../EDFlib-AK/edflib/ ${CMAKE_CURRENT_BINARY_DIR}/build-edflib-Desktop_Qt_5_6_3_MSVC2013_32bit-Release)


set_target_properties(Nicone PROPERTIES
    AUTOMOC ON
)

target_link_libraries(Nicone PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    edflib
)

if(COMMAND qt_create_translation)
    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()
