if (APPLE)
    cmake_minimum_required(VERSION 3.3.2)
else (APPLE)
    cmake_minimum_required(VERSION 2.8)
endif()

project(MWAC_External_Interfaces)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

find_package(Cppcheck)

add_subdirectory(src/vdifio)
add_subdirectory(src/interfaces)


IF (CPPCHECK_FOUND)
    EXECUTE_PROCESS(WORKING_DIRECTORY ${CMAKE_SOURCE_DIR} COMMAND ${CPPCHECK_EXECUTABLE} --inconclusive --enable=style --enable=warning --language=c++ --xml --xml-version=2 src/ 
        RESULT_VARIABLE rval
        ERROR_VARIABLE result
        )
    FILE(WRITE ${CMAKE_SOURCE_DIR}/cppcheck-results.xml ${result})
    
ENDIF (CPPCHECK_FOUND)       

