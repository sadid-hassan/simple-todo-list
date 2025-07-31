cmake_minimum_required(VERSION 3.16)

# ---------------- Project Information ----------------
project(TodoListProject VERSION 0.1 LANGUAGES CXX)

# Enable automatic handling of Qt UI, MOC, and RCC
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Enforce modern C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---------------- Find Qt ----------------
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# ---------------- GUI Application ----------------
# Defines the GUI project sources
set(GUI_SOURCES
    gui-version/main.cpp
    gui-version/mainwindow.cpp
    gui-version/mainwindow.h
    gui-version/mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(TodoListGUI
        MANUAL_FINALIZATION
        ${GUI_SOURCES}
    )
else()
    add_executable(TodoListGUI
        ${GUI_SOURCES}
    )
endif()

target_link_libraries(TodoListGUI PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.TodoListGUI)
endif()

set_target_properties(TodoListGUI PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# ---------------- CLI Application ----------------
# Builds the old console-based To-Do List app
set(CLI_SOURCES
    cli-version/main_cli.cpp
)

add_executable(TerminalTodo
    ${CLI_SOURCES}
)

# ---------------- Install Rules ----------------
# Install both the GUI and CLI executables
include(GNUInstallDirs)
install(TARGETS TodoListGUI TerminalTodo
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Finalize the GUI build (Qt6 only)
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(TodoListGUI)
endif()
