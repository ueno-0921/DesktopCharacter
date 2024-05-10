add_subdirectory(argparse)
add_subdirectory(charaimg)
add_subdirectory(charasnd)

add_library(chara STATIC charamgr.cpp)
target_include_directories(chara PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(chara argparse charaimg charasnd)