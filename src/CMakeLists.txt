add_subdirectory(chara)
add_subdirectory(sendmsg)
add_subdirectory(recvmsg)

add_executable(${PROJECT_NAME_DC} WIN32 dtpchara.cpp)
target_include_directories(${PROJECT_NAME_DC} PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME_DC} recvmsg chara)