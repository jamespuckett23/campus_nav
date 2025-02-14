cmake_minimum_required(VERSION 3.0.2)
project(campus_routing)

## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS
lanelet2
)
find_package(roscpp REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(message_generation REQUIRED)

add_service_files(
  FILES
  Plan.srv 
)

generate_messages(
  DEPENDENCIES
  lanelet2
  nav_msgs
)

catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS roscpp geometry_msgs nav_msgs lanelet2 message_runtime
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_executable(navigator src/main.cpp)
add_executable(map_node src/MapNode.cpp)

add_dependencies(navigator ${catkin_EXPORTED_TARGETS} ${PROJECT_NAME}_generate_messages_cpp)
add_dependencies(map_node ${catkin_EXPORTED_TARGETS} ${PROJECT_NAME}_generate_messages_cpp)

target_link_libraries(navigator
  ${catkin_LIBRARIES}
)
target_link_libraries(map_node
  ${catkin_LIBRARIES}
)

install(DIRECTORY launch/
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/launch
  FILES_MATCHING PATTERN "*.launch"
)