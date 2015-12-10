if (APPLE)
    cmake_minimum_required(VERSION 3.3.2)
else (APPLE)
    cmake_minimum_required(VERSION 2.8)
endif()

project(MWAC_External_Interfaces)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

find_package(Cppcheck)
find_package(doxygen)

#add_subdirectory(src/vdifio)
add_subdirectory(src/interfaces)


IF (CPPCHECK_FOUND)
    EXECUTE_PROCESS(WORKING_DIRECTORY ${CMAKE_SOURCE_DIR} COMMAND ${CPPCHECK_EXECUTABLE} --inconclusive --enable=style --enable=warning --language=c++ --xml-version=2 ./src/ 
        RESULT_VARIABLE rval
        ERROR_FILE ${CMAKE_SOURCE_DIR}/reports/cppcheck-results.xml
        )
#   FILE(WRITE ${CMAKE_SOURCE_DIR}/reports/cppcheck-results.xml ${result})
    EXECUTE_PROCESS(WORKING_DIRECTORY ${CMAKE_SOURCE_DIR} COMMAND ${CPPCHECK-HTML_EXECUTABLE} --file=./reports/cppcheck-results.xml --report-dir=./reports)

ENDIF (CPPCHECK_FOUND)       
IF (DOXYGEN_FOUND)
    EXECUTE_PROCESS(WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/src COMMAND doxygen ./doxyfile.cfg)
ENDIF (DOXYGEN_FOUND)

