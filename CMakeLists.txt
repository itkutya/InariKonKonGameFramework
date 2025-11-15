cmake_minimum_required(VERSION 4.1.0)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(InariKonKon VERSION 0.1.0 LANGUAGES C CXX)

include(FetchContent)

FetchContent_Declare(glfw GIT_REPOSITORY https://github.com/glfw/glfw.git GIT_TAG master)
FetchContent_MakeAvailable(glfw)

FetchContent_Declare(glad GIT_REPOSITORY https://github.com/Dav1dde/glad.git GIT_TAG glad2 SOURCE_SUBDIR cmake)
FetchContent_MakeAvailable(glad)
glad_add_library(opengl STATIC API gl:core=4.6)
glad_add_library(vulkan STATIC API vulkan=1.4)

FetchContent_Declare(nlohmann_json GIT_REPOSITORY https://github.com/nlohmann/json.git GIT_TAG master)
FetchContent_MakeAvailable(nlohmann_json)

set(INARIKONKON_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(INARIKONKON_SOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

file(GLOB_RECURSE INARIKONKON_SOURCE_FILES CONFIGURE_DEPENDS "${INARIKONKON_SOURCES_DIR}/*.cpp")

add_library(${CMAKE_PROJECT_NAME} STATIC ${INARIKONKON_SOURCE_FILES})

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE glfw opengl vulkan nlohmann_json::nlohmann_json)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${INARIKONKON_SOURCES_DIR})
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${INARIKONKON_INCLUDE_DIR})

###
add_executable(TestApp main.cpp)
target_link_libraries(TestApp InariKonKon)