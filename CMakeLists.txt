
# define minimum cmake version => always necessary
cmake_minimum_required(VERSION 3.0)

# define project name
project(compastro)

# include libraries
include_directories(lib/eigen) # Eigen is a header only library => no need for target_link_libraries
include_directories(lib/tintoretto)
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)


# -------------------- #
# !-- Header Files --! #
# -------------------- #

include_directories(("${CMAKE_SOURCE_DIR}/inc"))


# -------------------- #
# !-- Source Files --! #
# -------------------- #

# add all source files
file(GLOB_RECURSE SOURCES "src/*.cpp")


# ----------------- #
# !-- Variables --! #
# ----------------- #

# name of the script that we want to compile inside the app folder
set(SCRIPT_NAME "testAnimation.cpp")


# ----------------- #

# let's adapt the name of the exectutable to this
# extract base name without extension
get_filename_component(EXECUTABLE_NAME ${SCRIPT_NAME} NAME_WE) # main.cpp --> main
# add .exe extension
set(EXECUTABLE_NAME ${EXECUTABLE_NAME}.exe) # main --> main.exe

# ----------------- #

# define which script we want to execute
add_executable(${EXECUTABLE_NAME} app/${SCRIPT_NAME} ${SOURCES})

# link libraries to executable
target_link_libraries(${EXECUTABLE_NAME} sfml-graphics sfml-window sfml-system)

# say where we want to create our executable
set_target_properties(${EXECUTABLE_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)


# Add a custom command to run the executable after build
add_custom_command(TARGET ${EXECUTABLE_NAME} POST_BUILD # run once the build is done
    COMMAND ${CMAKE_COMMAND} -E echo ""
    COMMAND ${CMAKE_COMMAND} -E echo "!-- SIMULATION --!"
    COMMAND ${CMAKE_COMMAND} -E echo ""
    COMMAND $<TARGET_FILE:${EXECUTABLE_NAME}>
    COMMAND ${CMAKE_COMMAND} -E echo ""
    COMMAND ${CMAKE_COMMAND} -E echo "!-- SIMULATION COMPLETE --!"
    COMMAND ${CMAKE_COMMAND} -E echo ""
    COMMENT "Running ${EXECUTABLE_NAME} after build"

)

