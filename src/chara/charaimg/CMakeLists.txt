add_library(charaimg STATIC charaimg.cpp image.cpp)
target_include_directories(charaimg PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(charaimg gdiplus)