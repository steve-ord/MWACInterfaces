if (APPLE)
    cmake_minimum_required(VERSION 3.3.2)
else (APPLE)
    cmake_minimum_required(VERSION 2.8)
endif()

project(MWAC_External_Interfaces)

add_subdirectory(src/vdifio)
add_subdirectory(src/interfaces)

