cmake_minimum_required(VERSION 3.8)
project(ros2_esp32)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

add_executable(integer_publisher src/integer_publisher.cpp)
ament_target_dependencies(integer_publisher rclcpp std_msgs)

add_executable(string_publisher src/string_publisher.cpp)
ament_target_dependencies(string_publisher rclcpp std_msgs)

install(TARGETS
  integer_publisher
  DESTINATION lib/${PROJECT_NAME}
)

install(TARGETS
  string_publisher
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
