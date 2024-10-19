# Define the minimum required CMake version
cmake_minimum_required(VERSION 3.10)

# Set the project name and specify C++ standard
project(appDB LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

# Define compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive -Wwrite-strings -Wextra -g")
include_directories(include /usr/include/mysql /usr/include/cppconn)

# Define source files[-Wwrite-strings]
file(GLOB SRC_FILES "src/*.cpp")

# Define the executable target
add_executable(${PROJECT_NAME} ${SRC_FILES})

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE mysqlcppconn ssl crypto curl)

# Set the output directories for build artifacts
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Add a custom clean target
add_custom_target(app
    COMMAND ${CMAKE_COMMAND} -E rm -f $<TARGET_OBJECTS:${PROJECT_NAME}>
    COMMAND ${CMAKE_COMMAND} -E rm -f ${PROJECT_NAME}
)
