cmake_minimum_required(VERSION 3.28)
project(showcase_qt)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "D:/Qt/6.7.1/msvc2019_64")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Graphs
        REQUIRED)

add_executable(showcase_qt main.cpp
        model/Data/Image.cpp
        model/Data/Image.hpp
        model/Data/TextData.cpp
        model/Data/TextData.hpp
        controller/DataCrypto.cpp
        controller/DataCrypto.hpp
        model/Data/IData.cpp
        model/Data/IData.hpp
        model/CryptoMethods/ICryptoMethod.cpp
        model/CryptoMethods/ICryptoMethod.cpp
        model/CryptoMethods/ICryptoMethod.hpp
        model/CryptoMethods/XorMethod.cpp
        model/CryptoMethods/XorMethod.cpp
        model/CryptoMethods/XorMethod.hpp
        view/CryptoAnalysisView.cpp
        view/CryptoAnalysisView.hpp
        view/Constants.hpp)
target_link_libraries(showcase_qt
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Graphs
)

if (WIN32) # AND NOT DEFINED CMAKE_TOOLCHAIN_FILE
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core Gui Widgets)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()
