cmake_minimum_required(VERSION 3.22)
project(update_repos)

set(CMAKE_CXX_STANDARD 17)

find_package(yaml-cpp REQUIRED)

add_executable(update_repos main.cpp)
target_link_libraries(update_repos PRIVATE ${YAML_CPP_LIBRARIES})
