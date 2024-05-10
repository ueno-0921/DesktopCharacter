add_library(argparse STATIC argparse.cpp)
target_include_directories(argparse PRIVATE ${PROJECT_SOURCE_DIR}/include)