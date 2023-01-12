cmake_minimum_required(VERSION 3.8)
project(autoware_bridge)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)

# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(rclcpp REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(carla_msgs REQUIRED)
find_package(autoware_auto_vehicle_msgs REQUIRED)
find_package(autoware_auto_control_msgs REQUIRED)

add_executable(carla_autoware_tf_node src/carla_autoware_tf.cpp)
ament_target_dependencies(carla_autoware_tf_node rclcpp tf2 tf2_ros)
#target_include_directories(autoware_bridge_node PUBLIC
#  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
#  $<INSTALL_INTERFACE:include>)
#target_compile_features(autoware_bridge_node PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17
install(TARGETS carla_autoware_tf_node
  DESTINATION lib/${PROJECT_NAME})

add_executable(carla_transfer_pointcloud_node src/carla_transfer_pointcloud.cpp)
ament_target_dependencies(carla_transfer_pointcloud_node rclcpp sensor_msgs)
install(TARGETS carla_transfer_pointcloud_node
  DESTINATION lib/${PROJECT_NAME})

add_executable(carla_vehicle_interface_node src/carla_vehicle_interface.cpp)
ament_target_dependencies(carla_vehicle_interface_node rclcpp carla_msgs autoware_auto_vehicle_msgs nav_msgs autoware_auto_control_msgs)
install(TARGETS carla_vehicle_interface_node
  DESTINATION lib/${PROJECT_NAME})

install(DIRECTORY launch
  DESTINATION share/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # uncomment the line when a copyright and license is not present in all source files
  #set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # uncomment the line when this package is not in a git repo
  #set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
