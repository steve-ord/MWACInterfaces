
include_directories(./)

add_library(mwac_interfaces STATIC ConnectionHandler.cpp File.cpp GPUBlock.cpp)
install(FILES ConnectionHandler.h File.h DESTINATION include)
install(FILES mwa_eda.h DESTINATION include)
install(FILES GPUBlock.h DESTINATION include)




install(TARGETS mwac_interfaces ARCHIVE DESTINATION lib)


