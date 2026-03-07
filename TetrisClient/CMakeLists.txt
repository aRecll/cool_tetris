cmake_minimum_required(VERSION 3.19)
project(TetrisClient LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Gui Widgets Network)

qt_standard_project_setup()
include_directories(src/core src/ui src/ui/menus src/ui/ingame)

qt_add_executable(TetrisClient
    WIN32 MACOSX_BUNDLE
    src/main.cpp

    # Core
    src/core/tetromino.h src/core/tetromino.cpp
    src/core/game_logic.h src/core/game_logic.cpp

    # UI
    src/ui/mainwindow.h src/ui/mainwindow.cpp
    src/ui/ingame/fild_widget.h src/ui/ingame/fild_widget.cpp
    src/ui/ingame/game_widget.h src/ui/ingame/game_widget.cpp
    src/ui/ingame/next_pieces_widget.h src/ui/ingame/next_pieces_widget.cpp
    src/ui/ingame/poket_piece_widget.h src/ui/ingame/poket_piece_widget.cpp
    src/ui/ingame/score_widget.h src/ui/ingame/score_widget.cpp
    src/ui/ingame/pause_widget.h src/ui/ingame/pause_widget.cpp
    src/ui/ingame/overlay_widget.h src/ui/ingame/overlay_widget.cpp
    src/ui/ingame/game_over_widget.h src/ui/ingame/game_over_widget.cpp
    src/ui/menus/menu_widget.h src/ui/menus/menu_widget.cpp
    src/ui/menus/setting_widget.h src/ui/menus/setting_widget.cpp
)

target_link_libraries(TetrisClient
    PRIVATE
        Qt::Core
        Qt::Widgets
)

include(GNUInstallDirs)

install(TARGETS TetrisClient
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET TetrisClient
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
