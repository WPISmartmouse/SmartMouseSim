cmake_minimum_required(VERSION 3.1)

project(SmartmouseSim)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

# Find the QtWidgets library
find_package(Qt5Widgets)

# Bring in ignition-transport3
find_package(ignition-transport3 QUIET REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${IGNITION-TRANSPORT_CXX_FLAGS}")
include_directories(${IGNITION-TRANSPORT_INCLUDE_DIRS})
link_directories(${IGNITION-TRANSPORT_LIBRARY_DIRS})

# Tell CMake to create the helloworld executable
add_executable(sim src/main.cpp)


# Use the Widgets module from Qt 5.
target_link_libraries(sim Qt5::Widgets ${IGNITION-TRANSPORT_LIBRARIES})
