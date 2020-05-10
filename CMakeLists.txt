cmake_minimum_required(VERSION 3.5)

set(QUICK_EVNET_NAME "quickevent")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#编译动态库或静态库
set(quickevent_BUILD_SHARED_LIBS false)

#可执行文件输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG
	${PROJECT_SOURCE_DIR}/Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE
	${PROJECT_SOURCE_DIR}/Release)

#库文件输出目录
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG
        ${PROJECT_SOURCE_DIR}/Debug)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE
        ${PROJECT_SOURCE_DIR}/Release)


#是否编译示例
set(quickevent_BUILD_EXAMPLES ON)

add_subdirectory(event)

if(quickevent_BUILD_EXAMPLES)
        add_subdirectory(example)
endif()

add_custom_target(clean-all
   COMMAND ${CMAKE_BUILD_TOOL} clean
)
