cmake_minimum_required(VERSION 3.5)

project(${QUICK_EVNET_NAME})
if(QUICKEVENT_SOURCE_DIR)
    set(QUICKEVENT_SOURCE_DIR ${PROJECT_SOURCE_DIR})
endif()

find_package(Qt5 COMPONENTS Core Gui Widgets)

if(QUICKEVENTEXAMPLE_SOURCE_DIR)
    set(QUICKEVENTEXAMPLE_SOURCE_DIR ${PROJECT_SOURCE_DIR})
endif()

set(COMPONENT_MAJOR "2")
set(COMPONENT_MINOR "0")
set(COMPONENT_REVISION "2")

if(quickevent_BUILD_SHARED_LIBS)
        set(quickevent_BUILD_TYPE SHARED)
        add_definitions("-DUSE_SHARED")
else()
        set(quickevent_BUILD_TYPE STATIC)
        add_definitions("-DUSE_STATIC")
endif()

message(quickevent_BUILD_TYPE)

add_library(${PROJECT_NAME} ${quickevent_BUILD_TYPE}
    quick.h
    quickcontroller.h
    quickapplication.h
    quickevent.h
    quickwork.h
    quickconfig.h
    quickcontroller.cpp
    quickapplication.cpp
    quickevent.cpp
    quickwork.cpp
)

set_target_properties(${PROJECT_NAME} PROPERTIES AUTOMOC TRUE )
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core Qt5::Gui Qt5::Widgets)
