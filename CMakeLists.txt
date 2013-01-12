cmake_minimum_required(VERSION 2.6)

#Déclaration du projet
project(IluziojChess)
set(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})

include_directories(
	headers/
	${sfml_include_dir}
)

link_directories(
	${sfml_lib_dir}
)

file(
	GLOB_RECURSE
	source_files
	src/*
)

file(
	GLOB_RECURSE
	header_files
	headers/*
)

#Déclaration de l'exécutable
add_executable(
	iluziojChess
	${source_files}
	${header_files}
)

target_link_libraries(
	iluziojChess
	sfml-graphics
	sfml-window
	sfml-system
)
