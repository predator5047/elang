cmake_minimum_required(VERSION 2.8)
project(elang)

find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)
find_package(Qt4 REQUIRED)

include(${QT_USE_FILE})

BISON_TARGET(Parser parser.y ${CMAKE_CURRENT_BINARY_DIR}/src/parser.cpp)
FLEX_TARGET(Scanner scanner.l ${CMAKE_CURRENT_BINARY_DIR}/src/scanner.cpp)

ADD_FLEX_BISON_DEPENDENCY(Scanner Parser)


include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src")

set(ELANG_SRC ${BISON_Parser_OUTPUTS} ${FLEX_Scanner_OUTPUTS} src/main.cpp
	src/ast.cpp src/value.cpp )

set(ELANG_GUI_SRC src/maingui.cpp src/mainwindow.cpp src/highlighter.cpp)

set(ELANG_GUI_H src/mainwindow.h src/highlighter.h)
set(ELANG_GUI_UI ui/mainwindow.ui)

QT4_WRAP_CPP(ELANG_GUI_MOC_H ${ELANG_GUI_H})
QT4_WRAP_UI(ELANG_GUI_UI_H ${ELANG_GUI_UI})


add_executable(erun ${ELANG_SRC})
add_executable(egui ${ELANG_GUI_SRC} ${ELANG_GUI_UI_H} ${ELANG_GUI_H} ${ELANG_GUI_MOC_H})

target_link_libraries(egui ${QT_LIBRARIES})


