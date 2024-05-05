cmake_minimum_required(VERSION 3.5)

project(robots VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(AUTOGEN_BUILD_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        src/main.cpp
        src/room.h src/room.cpp
        src/robot.h src/robot.cpp
        src/block.h src/block.cpp
        src/gameentity.cpp src/gameentity.h
        src/updateentity.cpp src/updateentity.h
        src/pausableentity.cpp src/pausableentity.h
        src/mainwindow.cpp src/mainwindow.h
        src/resizablegraphicsview.cpp src/resizablegraphicsview.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(robots
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET robots APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(robots SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(robots
            ${PROJECT_SOURCES}
                src/mainwindow.h src/mainwindow.cpp src/mainwindow.ui
                src/room.h src/room.cpp
                src/robot.h src/robot.cpp
                src/block.h src/block.cpp
                src/DtoMap.h
                src/robotdto.h src/robotdto.cpp
                src/blockdto.h src/blockdto.cpp
                src/Serializable.h
                src/roomdto.h src/roomdto.cpp
                src/jsonfileaccessor.h src/jsonfileaccessor.cpp
                src/gameentity.h src/gameentity.cpp
                src/pausableentity.h src/pausableentity.cpp
                src/updateentity.h
                src/propertyview.h src/propertyview.cpp
                src/blockcomposer.h src/blockcomposer.cpp
                src/scene.h src/scene.cpp

                src/signalsender.h src/signalsender.cpp
                src/robotcomposer.h src/robotcomposer.cpp
                src/resizablegraphicsview.h src/resizablegraphicsview.cpp
                src/graphicsitemcomposer.h

        )
    endif()
endif()

target_link_libraries(robots PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.robots)
endif()
set_target_properties(robots PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS robots
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(robots)
endif()
