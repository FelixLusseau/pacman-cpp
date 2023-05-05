cmake_minimum_required(VERSION 3.7)

project(PacMan LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -g -std=c++2a")

file(GLOB SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

find_package(SDL2 REQUIRED SDL2)

add_executable(${PROJECT_NAME} ${SOURCES})
target_compile_definitions(${PROJECT_NAME} PRIVATE "SDL_MAIN_HANDLED")
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/pacman_sprites.bmp
	DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)	

if(MSVC)
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
endif()