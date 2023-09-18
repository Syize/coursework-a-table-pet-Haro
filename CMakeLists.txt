cmake_minimum_required(VERSION 3.5)

project(haro VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS src/include)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt5 REQUIRED COMPONENTS Widgets LinguistTools Multimedia MultimediaWidgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools Multimedia MultimediaWidgets)

# other library
set(EXTERNAL_LIBS "")

include_directories(AFTER src/include)

set(PROJECT_SOURCES
        main.cpp
)

file(GLOB_RECURSE INCLUDE_SOURCES "src/*.cpp")
file(GLOB_RECURSE UI_SOURCES "src/include/*.h")
file(GLOB_RECURSE QRC_SOURCES "*.qrc")

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_resources(QRC_FILES ${QRC_SOURCES})
    qt_add_executable(haro
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ${INCLUDE_SOURCES}
        ${UI_SOURCES}
        ${QRC_FILES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET test-Python APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(haro SHARED
            ${PROJECT_SOURCES}
            ${INCLUDE_SOURCES}
            ${UI_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
    qt5_add_resources(QRC_FILES ${QRC_SOURCES})
        add_executable(haro
            ${PROJECT_SOURCES}
            ${INCLUDE_SOURCES}
            ${UI_SOURCES}
            ${QRC_FILES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(haro PRIVATE Qt${QT_VERSION_MAJOR}::Widgets ${EXTERNAL_LIBS} Qt${QT_VERSION_MAJOR}::Multimedia Qt${QT_VERSION_MAJOR}::MultimediaWidgets)

set_target_properties(haro PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS haro
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(haro)
endif()
