cmake_minimum_required (VERSION 2.8)

project (quadtest)

# ------------------------------------------------------------------------------
# create file tree
# ------------------------------------------------------------------------------

file(MAKE_DIRECTORY bin)

# ------------------------------------------------------------------------------
# compiler settings
# ------------------------------------------------------------------------------
if(CMAKE_COMPILER_IS_GNUCXX)
	if(NOT CMAKE_CXX_FLAGS MATCHES "-std=c\\+\\+11")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
	endif()
endif()
set(CMAKE_CXX_EXTENSIONS 0)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED 1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

set(CMAKE_BUILD_TYPE Release)

# ------------------------------------------------------------------------------
# compilation
# ------------------------------------------------------------------------------

file(GLOB_RECURSE SOURCES "src/*.cpp")

set(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})

add_executable (
	quadtest ${SOURCES}
)

# ------------------------------------------------------------------------------
# libs
# ------------------------------------------------------------------------------

find_package(OpenCV CONFIG REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(quadtest ${OpenCV_LIBRARIES})

