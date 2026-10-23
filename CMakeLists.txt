cmake_minimum_required(VERSION 3.10)
project(Projet-IA41)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)



file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")



add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE    
 ${CMAKE_SOURCE_DIR}/src)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)

#for SFML
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)