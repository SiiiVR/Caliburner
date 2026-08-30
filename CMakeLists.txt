cmake_minimum_required(VERSION 3.24)

project(
		Caliburner
		VERSION 0.1.0
		DESCRIPTION "Isometric 2D turn based strategy game in a medieval science-fantasy setting."
		LANGUAGES C CXX
)

# -----------------------------------------------------------------------------
# C++ configuration
# -----------------------------------------------------------------------------

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# -----------------------------------------------------------------------------
# Dependencies
# -----------------------------------------------------------------------------

include(FetchContent)

# Don't build raylib's examples.
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
		raylib
		URL https://github.com/raysan5/raylib/archive/refs/tags/6.0.tar.gz
		DOWNLOAD_EXTRACT_TIMESTAMP OFF
)

# nlohmann/json
set(JSON_BuildTests OFF CACHE INTERNAL "")
set(JSON_Install OFF CACHE INTERNAL "")

FetchContent_Declare(
		nlohmann_json
		URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz
		DOWNLOAD_EXTRACT_TIMESTAMP OFF
)

FetchContent_MakeAvailable(
		raylib
		nlohmann_json
)

# -----------------------------------------------------------------------------
# Game
# -----------------------------------------------------------------------------

file(
		GLOB_RECURSE GAME_SOURCES
		CONFIGURE_DEPENDS
		"${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
)

file(
		GLOB_RECURSE GAME_HEADERS
		CONFIGURE_DEPENDS
		"${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
)

add_executable(
		${PROJECT_NAME}
		${GAME_SOURCES}
		${GAME_HEADERS}
		src/level.cpp
		src/level.hpp
		src/gridCoord.hpp
		src/terrain.hpp
)

target_include_directories(
		${PROJECT_NAME}
		PRIVATE
		"${CMAKE_CURRENT_SOURCE_DIR}/src"
)

target_link_libraries(
		${PROJECT_NAME}
		PRIVATE
		raylib
		nlohmann_json::nlohmann_json
)

# -----------------------------------------------------------------------------
# Compiler warnings
# -----------------------------------------------------------------------------

if(MSVC)
	target_compile_options(
			${PROJECT_NAME}
			PRIVATE
			/W4
			/permissive-
	)
else()
	target_compile_options(
			${PROJECT_NAME}
			PRIVATE
			-Wall
			-Wextra
			-Wpedantic
			-Wconversion
			-Wshadow
	)
endif()

# -----------------------------------------------------------------------------
# Assets
# -----------------------------------------------------------------------------

set(GAME_ASSETS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/assets")

if(EXISTS "${GAME_ASSETS_DIR}")
	add_custom_command(
			TARGET ${PROJECT_NAME}
			POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy_directory
			"${GAME_ASSETS_DIR}"
			"$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets"
			COMMENT "Copying game assets"
	)
endif()

# Makes relative asset paths work nicely when launching from Visual Studio.
set_target_properties(
		${PROJECT_NAME}
		PROPERTIES
		VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
)

# -----------------------------------------------------------------------------
# macOS
# -----------------------------------------------------------------------------

if(APPLE)
	target_link_libraries(
			${PROJECT_NAME}
			PRIVATE
			"-framework IOKit"
			"-framework Cocoa"
			"-framework OpenGL"
	)
endif()