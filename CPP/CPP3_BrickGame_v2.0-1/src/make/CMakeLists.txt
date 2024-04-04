cmake_minimum_required(VERSION 3.5)

project(s21_snake VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        ../gui/desktop/main.cpp
        ../gui/desktop/mainwindow.h
        ../gui/desktop/mainwindow.cpp
        ../gui/desktop/mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(s21_snake
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ../brick_game/snake/snakemodel.h ../brick_game/snake/snakemodel.cpp
        ../brick_game/snake/snakeview.h ../brick_game/snake/snakeview.cpp
        ../brick_game/snake/snakecontroller.h ../brick_game/snake/snakecontroller.cpp
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET s21_snake APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(s21_snake SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(s21_snake
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(s21_snake PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.s21_snake)
endif()
set_target_properties(s21_snake PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS s21_snake
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(s21_snake)
endif()

# Enable testing for the project
enable_testing()

# Find package for Google Test
find_package(GTest REQUIRED)

# Define the source files for the test executable
set(TEST_SOURCES
    ../tests/snake_all_tests.cpp
)

# Add a new executable for the tests
add_executable(s21_snake_tests
    ${TEST_SOURCES}
    ../brick_game/snake/snakemodel.h 
    ../brick_game/snake/snakemodel.cpp
)

# Include the directories for the tests
target_include_directories(s21_snake_tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../brick_game/snake
)

# Link against Google Test and the Qt libraries necessary for testing
target_link_libraries(s21_snake_tests
    PRIVATE GTest::GTest GTest::Main
    PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
)

# You might need to add compile definitions if you have them for your project, e.g.:
# target_compile_definitions(s21_snake_tests PRIVATE TEST_DEFINITION)

# Add the test to CTest so you can run 'make test' or 'ctest' to execute tests
add_test(NAME SnakeModelTests COMMAND s21_snake_tests)

# Use this if you need to set a working directory for your tests
# set_target_properties(s21_snake_tests PROPERTIES
#     WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/tests
# )