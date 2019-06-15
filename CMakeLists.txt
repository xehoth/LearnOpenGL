cmake_minimum_required(VERSION 3.8)

if(${CMAKE_VERSION} VERSION_LESS 3.14)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
else()
    cmake_policy(VERSION 3.14)
endif()

project(LearnOpenGL VERSION 0.1 DESCRIPTION "Learn OpenGL" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# config glfw
option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(${PROJECT_SOURCE_DIR}/3rdParty/glfw)
include_directories(${PROJECT_SOURCE_DIR}/3rdParty/glfw/include)
list(APPEND LIBS glfw ${GLFW_LIBRARIES})

# config glad
set(GLAD_SRC ${PROJECT_SOURCE_DIR}/3rdParty/glad/src/glad.c)
include_directories(${PROJECT_SOURCE_DIR}/3rdParty/glad)
list(APPEND DEPS_SRC ${GLAD_SRC})

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/3rdParty/stb)

if (NOT WIN32)
    LIST(APPEND LIBS dl)
endif()

set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)

add_subdirectory(src)