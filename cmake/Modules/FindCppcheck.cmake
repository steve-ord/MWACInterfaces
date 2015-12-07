find_program(CPPCHECK_EXECUTABLE cppcheck )

if (CPPCHECK_EXECUTABLE)
    SET(CPPCHECK_FOUND TRUE)
    mark_as_advanced(CPPCHECK_EXECUTABLE)
    find_program(CPPCHECK-HTML_EXECUTABLE cppcheck-htmlreport)

endif (CPPCHECK_EXECUTABLE)


