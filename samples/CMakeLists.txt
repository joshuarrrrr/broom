add_executable(triangle triangle.cpp)
target_link_libraries(triangle broomstick spdlog::spdlog
                      spdlog::spdlog_header_only)

add_executable(texture texture.cpp)
target_link_libraries(texture broomstick spdlog::spdlog
                      spdlog::spdlog_header_only)
