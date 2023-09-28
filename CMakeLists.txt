cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(Project)
set(CMAKE_CXX_STANDARD 23)

#opengl
find_package( OpenGL REQUIRED )
include_directories( ${OPENGL_INCLUDE_DIRS} )

#include GLEW GLFW
include_directories($ENV{GLEW_INCLUDE_DIR})
include_directories($ENV{GLFW_INCLUDE_DIR})
include_directories($ENV{ASSIMP_BUILD_INCLUDE_DIR})
include_directories($ENV{ASSIMP_INCLUDE_DIR})

#library
link_directories($ENV{GLEW_LIBRARY})
link_directories($ENV{GLFW_LIBRARY})
link_directories($ENV{ASSIMP_LIBRARY})

#fastnoise
set(FASTNOISE2_NOISETOOL OFF CACHE BOOL "Build Noise Tool" FORCE)
add_subdirectory( ${CMAKE_SOURCE_DIR}/include/fastnoise )

#glm
include_directories("${CMAKE_SOURCE_DIR}/include/glm")
include_directories("${CMAKE_SOURCE_DIR}/src/Enums")
include_directories("${CMAKE_SOURCE_DIR}/src/Structs")

SET(SRC ${CMAKE_SOURCE_DIR}/src)

include_directories(${CMAKE_SOURCE_DIR}/include)

file(GLOB_RECURSE tinyEXR
        "${CMAKE_SOURCE_DIR}/include/tinyexr/*.h"
        "${CMAKE_SOURCE_DIR}/include/tinyexr/*.cpp"
        "${CMAKE_SOURCE_DIR}/include/tinyexr/*.c"
        )

file (GLOB_RECURSE fileSRC
        "${CMAKE_SOURCE_DIR}/src/*.h"
        "${CMAKE_SOURCE_DIR}/src/*.cpp"
        "${CMAKE_SOURCE_DIR}/src/*.c"
        "${CMAKE_SOURCE_DIR}/include/stb/*.h"
        )

file (GLOB_RECURSE glmSRC
        "${CMAKE_SOURCE_DIR}/include/glm*.h"
        "${CMAKE_SOURCE_DIR}/include/glm*.hpp"
        "${CMAKE_SOURCE_DIR}/include/glm*.c"
        "${CMAKE_SOURCE_DIR}/include/glm*.cpp"
        )

add_executable(proj ${fileSRC})
target_link_libraries(proj OpenGL::GL glew32 glfw3 assimp-vc143-mt)

