cmake_minimum_required(VERSION 3.19)
project(TetrisClient LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Gui Widgets Network Svg)

qt_standard_project_setup()
include_directories(src/core src/ui src/ui/menus src/ui/ingame src/settings src/network)
set(CMAKE_AUTORCC ON)
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
    src/ui/menus/statistic_widget.h src/ui/menus/statistic_widget.cpp
    src/ui/menus/auth_form.h src/ui/menus/auth_form.cpp
    src/settings/setting_manager.h src/settings/setting_manager.cpp
    src/network/network_client.cpp
    src/network/network_manager.h src/network/network_manager.cpp
    resources.qrc
    assets/icons/settings_icon.svg assets/icons/user_icon.svg
    assets/icons/statistic_icon.svg
    assets/backgrounds/background_main.png
)

target_link_libraries(TetrisClient
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::Network
        Qt::Svg
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
