add_executable(${PROJECT_NAME_DCI} WIN32 sendmsg.cpp)
target_include_directories(${PROJECT_NAME_DCI} PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME_DCI} PRIVATE argparse)