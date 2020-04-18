add_subdirectory(server)

add_executable(tincan main.cpp)
target_link_libraries(tincan server)