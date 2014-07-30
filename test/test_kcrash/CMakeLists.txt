cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)

set(QT_MIN_VERSION "5.3.0")
set(KF5_MIN_VERSION "5.0.0")

find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS Widgets)

find_package(ECM 0.0.11 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR})

find_package(KF5 ${KF5_MIN_VERSION} REQUIRED COMPONENTS
    Crash)

add_executable(test_kcrash test_kcrash.cpp)

target_link_libraries(test_kcrash 
    Qt5::Widgets KF5::Crash
)
