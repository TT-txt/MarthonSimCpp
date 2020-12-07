cmake_minimum_required(VERSION 3.9)
project(ProjetMarathon)

set(CompilerFlags
    CMAKE_CXX_FLAGS
    CMAKE_CXX_FLAGS_DEBUG
    CMAKE_CXX_FLAGS_RELEASE
    CMAKE_C_FLAGS
    CMAKE_C_FLAGS_DEBUG
    CMAKE_C_FLAGS_RELEASE
)

set(LIBS
    lib/etape.cpp
    lib/coureur.cpp
    lib/inOut.cpp
)

set(SRC
    src/main.cpp
)

if (MSVC)
    foreach (CompilerFlag ${CompilerFlags}) #for VISUAL STUDIO
        string(REPLACE "/MD" "/MT" ${CompilerFlag} "${${CompilerFlag}}")
        string(REPLACE "/W3" "/W4" ${CompilerFlag} "${${CompilerFlag}}")
        set(CompilerFlag "${CompilerFlag} /std:c++17")
    endforeach()
    set(SMFL_STATIC_LIBRAIRIES TRUE)
    set(SFML_DIR "C:/SFML-2.5.1/lib/cmake/SFML")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU") #for les bgs qui utilisent linux
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -Wextra -std=c++17")
endif()

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Configs" FORCE) #for @everyone
find_package(SFML COMPONENTS graphics window system REQUIRED)

add_library(libs ${LIBS})
add_executable(main ${SRC})
target_link_libraries(main libs sfml-graphics sfml-window pthread) 
