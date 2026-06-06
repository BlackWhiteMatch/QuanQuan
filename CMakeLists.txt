cmake_minimum_required(VERSION 3.19)
project(QuanQuan LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Sql)

set(CMAKE_AUTORCC ON)

qt_standard_project_setup()

qt_add_executable(QuanQuan
    WIN32 MACOSX_BUNDLE
    main.cpp
    dbmanager.h
    dbmanager.cpp
    loginwindow.h
    loginwindow.cpp
    loginwindow.ui
    mainwindow.h
    mainwindow.cpp
    mainwindow.ui
    resources.qrc
    applemsgbox.h
    applemsgbox.cpp
)

target_link_libraries(QuanQuan
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::Sql
)

install(TARGETS QuanQuan
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET QuanQuan
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
