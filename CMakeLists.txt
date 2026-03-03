cmake_minimum_required(VERSION 3.19)
project(cool_tetris LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()
include_directories(src/core src/ui)
qt_add_executable(cool_tetris
    WIN32 MACOSX_BUNDLE
    src/main.cpp


    src/core/tetromino.h src/core/tetromino.cpp
    src/core/game_logic.h src/core/game_logic.cpp


    src/ui/fild_widget.h src/ui/fild_widget.cpp
    src/ui/mainwindow.h src/ui/mainwindow.cpp
    src/ui/next_pieces_widget.h src/ui/next_pieces_widget.cpp
    src/ui/game_widget.h src/ui/game_widget.cpp
    src/ui/poket_piece_widget.h src/ui/poket_piece_widget.cpp
)
target_link_libraries(cool_tetris
    PRIVATE
        Qt::Core
        Qt::Widgets
)

include(GNUInstallDirs)

install(TARGETS cool_tetris
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET cool_tetris
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
