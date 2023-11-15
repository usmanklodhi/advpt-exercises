cmake_minimum_required(VERSION 3.10)

project(CMake_Test)

option(USE_V1 "use Version1 for CMake" ON)
option(USE_V2 "use Version2 for CMake" OFF)
option(USE_V3 "use Version3 for CMake" OFF)
option(DEBUGABLE "enable or disable the USE_DEBUG option" ON)

#---------------------------------------------------------------------------------------------------
if(DEBUGABLE)
   if(USE_V2 OR USE_V3)
       option(USE_DEBUG "build with addition debug messages" OFF)

        if(USE_DEBUG)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -pedantic -g -DDEBUG")
        else(USE_DEBUG)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -pedantic")
        endif(USE_DEBUG)
    endif(USE_V2 OR USE_V3)
else(DEBUGABLE)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -pedantic")
endif(DEBUGABLE)

#---------------------------------------------------------------------------------------------------
#Version 1
#---------------------------------------------------------------------------------------------------
if(USE_V1)

    include_directories(
       ${PROJECT_SOURCE_DIR}/header
    )

    add_executable(app main.cpp src/foo.cpp src/bar.cpp)
endif(USE_V1)

#---------------------------------------------------------------------------------------------------
#Version 2
#---------------------------------------------------------------------------------------------------
if(USE_V2)
    include_directories(
        ${PROJECT_SOURCE_DIR}/header
    )

    file(GLOB all_SRC
        "${PROJECT_SOURCE_DIR}/*.cpp"
        "${PROJECT_SOURCE_DIR}/src/*.cpp"
    )

    add_executable(app ${all_SRC})
endif(USE_V2)

#---------------------------------------------------------------------------------------------------
#Version 3
#---------------------------------------------------------------------------------------------------
if(USE_V3)
    include_directories(
       ${PROJECT_SOURCE_DIR}/header
    )

    add_subdirectory(${PROJECT_SOURCE_DIR}/src)

    add_executable(app main.cpp)

    target_link_libraries(app foolib)
    target_link_libraries(app barlib)

    #target_link_libraries(app foobar)
endif(USE_V3)

