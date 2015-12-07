
include_directories(./)

add_library(vdifio STATIC vdifio.c)
install(FILES vdifio.h DESTINATION include)
install(TARGETS vdifio ARCHIVE DESTINATION lib)


