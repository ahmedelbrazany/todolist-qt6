cmake_minimum_required(VERSION 3.16)

project(todolist VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# البحث عن الحزم المطلوبة
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Core Qml Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Core Qml Gui)

set(PROJECT_SOURCES
    main.cpp
    resources.qrc
    TaskManager.cpp
    Task.cpp
    TaskManager.h
    Task.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(todolist
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}

    )
else()
    if(ANDROID)
        add_library(todolist SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(todolist
            ${PROJECT_SOURCES}
        )
    endif()
endif()

# ربط المكتبات المطلوبة
target_link_libraries(todolist PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Qml Qt${QT_VERSION_MAJOR}::Gui)

# إعدادات خاصة بـ iOS أو macOS
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.todolist)
endif()

set_target_properties(todolist PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# إعدادات التثبيت
include(GNUInstallDirs)
install(TARGETS todolist
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# إذا كان الإصدار 6 من Qt، ننهي التنفيذ
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(todolist)
endif()
