cmake_minimum_required(VERSION 3.4.1)

add_library( # Sets the name of the library.
        native-lib
        SHARED
        native-lib.cpp)
# include_directories(src/main/cpp/include) # 错误的坑爹写法
include_directories(${PROJECT_SOURCE_DIR}/include) # ${PROJECT_SOURCE_DIR} = E:/AndroidWangYiCloud/NDKWorkspace/NePlayer/app/src/main/cpp

message(WARNING "path = ${PROJECT_SOURCE_DIR}")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -L${CMAKE_SOURCE_DIR}/libs/${ANDROID_ABI}") # 错误的坑爹写法
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -L${CMAKE_SOURCE_DIR}/../../../libs/${CMAKE_ANDROID_ARCH_ABI}")
find_library( # Sets the name of the path variable.
        log-lib
        log)
target_link_libraries( # Specifies the target library.
        native-lib
        avcodec avfilter avformat avutil swresample swscale
        ${log-lib})