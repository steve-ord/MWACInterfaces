
include_directories(./)

add_library(mwac_interfaces STATIC  File.cpp GPUBlock.cpp EDABlock.cpp)
install(FILES mwa_eda.h DESTINATION include)
install(FILES GPUBlock.h DESTINATION include)
install(FILES EDABlock.h DESTINATION include)




install(TARGETS mwac_interfaces ARCHIVE DESTINATION lib)


