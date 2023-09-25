cmake_minimum_required(VERSION 3.14)

project(SmartCalc_v2 VERSION 0.1 LANGUAGES CXX)

set(ENV{LC_NUMERIC} "en_US.UTF-8")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets PrintSupport)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets PrintSupport)

# Создаем библиотеку для S21Parser
add_library(S21ParserLib model/s21_parser.cc model/s21_parser.h)
target_link_libraries(S21ParserLib PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::PrintSupport)

set(PROJECT_SOURCES
    main.cc
    controller/controller.cc
    controller/controller.h
    model/calcmodel.cc
    model/calcmodel.h
    model/s21_validator.cc
    model/s21_validator.h
    view/calcview.cc
    view/calcview.h
    graph/graphview.cc
    graph/graphview.h
    graph/qcustomplot/qcustomplot.cpp
    graph/qcustomplot/qcustomplot.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(SmartCalc_v2
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(SmartCalc_v2 SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(SmartCalc_v2
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(SmartCalc_v2 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::PrintSupport S21ParserLib)
target_compile_options(SmartCalc_v2 PRIVATE -Wall -Werror -Wextra)

set_target_properties(SmartCalc_v2 PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS SmartCalc_v2
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(SmartCalc_v2)
endif()

#Включаем поддержку тестов
enable_testing()

#Добавляем флаги для gcov
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")

#Ищем библиотеку Google Test
include(FetchContent)
FetchContent_Declare(
googletest
URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
)
FetchContent_MakeAvailable(googletest)

#Добавляем тесты
add_executable(
SmartCalc_v2_test
tests/test.cc
)

#Связываем библиотеку Google Test и S21ParserLib с тестами
target_link_libraries(SmartCalc_v2_test PRIVATE gtest_main S21ParserLib)

#Добавляем тесты в CTest
include(GoogleTest)

gtest_discover_tests(SmartCalc_v2_test
                    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                    PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
                    )

#Добавляем цель 'coverage'
add_custom_target(coverage
    COMMAND gcov -r -o . CMakeFiles/SmartCalc_v2_test.dir/tests/test.cc.gcno
    COMMAND lcov --capture --directory . --output-file coverage.info
    COMMAND lcov --remove coverage.info '/usr/*' --output-file coverage.info
    COMMAND genhtml coverage.info --output-directory out
)
add_dependencies(coverage SmartCalc_v2_test)