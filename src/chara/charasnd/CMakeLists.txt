add_library(charasnd STATIC charasnd.cpp sound.cpp)
target_include_directories(charasnd PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(charasnd winmm)