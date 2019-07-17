cmake_minimum_required(VERSION 3.0)

project( MeshFlow CXX )

#### Environment
if (UNIX AND NOT APPLE) #Ubuntu...
	message(STATUS ">>> Linux")

	set(OpenCV_DIR /home/mhirano/opencv-3.4.1-tuned/build)

	include_directories(/usr/include)
	link_directories(/usr/lib/x86_64-linux-gnu)

else(APPLE)
	message(STATUS ">>> Mac")

	set(OpenCV_DIR /Users/mhirano/opencv-3.4.1-tuned/release)

	# Add include directory	(environment specific)
	include_directories(/usr/local/include)

endif()

# OpenCV
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/include )

######## ######## ######## ######## ######## ######## ######## ########
# Compiler settings
######## ######## ######## ######## ######## ######## ######## ########
# Check C++14 support and activate
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++14" COMPILER_SUPPORTS_CXX14)
if(COMPILER_SUPPORTS_CXX14)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
	set(CMAKE_CXX_STANDARD 14) # C++14...
	set(CMAKE_CXX_STANDARD_REQUIRED ON) #...is required...
	set(CMAKE_CXX_EXTENSIONS OFF) #...without compiler extensions like gnu++11
	message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has C++14 support.")
else()
	message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++14 support. Please use a different C++ compiler.")
endif()

set(CMAKE_CXX_FLAGS_DEBUG "-DDEBUG -g -pg")
message(STATUS "${CMAKE_CXX_FLAGS_DEBUG}")
set(CMAKE_CXX_FLAGS_RELEASE "-DRELEASE -O3 -DNDEBUG -march=native")
message(STATUS "${CMAKE_CXX_FLAGS_RELEASE}")
######## ######## ######## ######## ######## ######## ######## ########

set( src
		${PROJECT_SOURCE_DIR}/src/main.cpp
		${PROJECT_SOURCE_DIR}/src/VideoIO.cpp
		${PROJECT_SOURCE_DIR}/src/Mesh.cpp
		${PROJECT_SOURCE_DIR}/src/MeshFlow.cpp
		${PROJECT_SOURCE_DIR}/src/Fast_klt.cpp
		)

add_executable( ${CMAKE_PROJECT_NAME} ${src} )
target_link_libraries( ${CMAKE_PROJECT_NAME} ${OpenCV_LIBS})
