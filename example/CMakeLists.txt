cmake_minimum_required(VERSION 3.5)

project(QuickEventExample)
if(QUICKEVENTEXAMPLE_SOURCE_DIR)
    set(QUICKEVENTEXAMPLE_SOURCE_DIR ${PROJECT_SOURCE_DIR})
endif()

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)

if(quickevent_BUILD_SHARED_LIBS)

else()
        add_definitions("-DUSE_STATIC")
endif()

find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets)

include_directories(../event)

add_executable(${PROJECT_NAME}
    dialog.cpp
    dialog.ui
    orderwork.cpp
    student.cpp
    testwork.cpp
    userwork.cpp
    main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE ${QUICK_EVNET_NAME} Qt5::Core Qt5::Gui Qt5::Widgets)
