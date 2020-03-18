cmake_minimum_required(VERSION 3.6 FATAL_ERROR)

project(GeometryExampleOOP VERSION 0.1.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY lib)

set(INTERFACE_HEADERS
	${CMAKE_CURRENT_SOURCE_DIR}/include/IPublic.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/IGeometry.h
	)

add_library(Geometry
	SHARED
		${INTERFACE_HEADERS}
		src/Geometry.h
		src/Geometry.cpp
		src/Rectangle.cpp
		src/Square.cpp
		src/Circle.cpp
		src/Triangle.cpp
	)

target_include_directories(Geometry
	PRIVATE
		${CMAKE_CURRENTSOURCE_DIR}/src
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		$<INSTALL_INTERFACE:include>
	)

target_compile_definitions(Geometry 
	PRIVATE
		BUILD_DLL
	)
	
add_executable(ConsoleTestDraw
	src/ConsoleTestDraw.cpp
	src/DummyDrawer.h
	src/DummyDrawer.cpp
	)
	
target_link_libraries(ConsoleTestDraw
	PRIVATE
		Geometry
	)
	
