cmake_minimum_required(VERSION 3.10)
project(Iterator)
# 设置变量 
set(SRC_LIST main.cpp Iterator.cpp)
# 获取路径
get_filename_component(FOLDER_NAME ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)
# 获取从目录路径提前目录
get_filename_component(FOLDER_NAME ${FOLDER_NAME} NAME)
# 设置输出路径
set(EXECUTABLE_OUTPUT_PATH ${OUTPUT_DIR}/${FOLDER_NAME}/)
add_executable(iterator ${SRC_LIST})