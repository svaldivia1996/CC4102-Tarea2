cmake_minimum_required(VERSION 3.13)  # CMake version check
project(dijkstra)               # Create project "simple_example"
set(CMAKE_CXX_STANDARD 14)            # Enable c++14 standard

# uncomment this line if you want to create graphs for the fibonacci heaps
#set(USE_GRAPHVIZ "USE_GRAPHVIZ")
set(GRAPHVIZ_DIR "/usr/local/include/graphviz")

# eog is the default name of my image viewer in Ubuntu 22.02
set(IMVIEWER_COMMAND_NAME "eog")

# Add main.cpp file of project root directory as source file
add_library(fibonacci_heap_lib 
    nbnode.cpp nbnode.h
    cyclic_doubly_linked_list.cpp cyclic_doubly_linked_list.h
    fibonacci_heap.cpp fibonacci_heap.h
)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(simple_example test.cpp)
target_link_libraries(simple_example fibonacci_heap_lib)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(main main.cpp)
target_link_libraries(main fibonacci_heap_lib)

if(USE_GRAPHVIZ)
    message(STATUS "Using graphviz library...")
    if(EXISTS ${GRAPHVIZ_DIR})
        message(STATUS "graphviz library found at directory ${GRAPHVIZ_DIR}")
        add_compile_definitions(USE_GRAPHVIZ)
        add_compile_definitions(IMVIEWER_COMMAND_NAME="${IMVIEWER_COMMAND_NAME}")
        include_directories("/usr/local/include/graphviz")
        target_link_libraries(simple_example gvc cgraph)
        target_link_libraries(main gvc cgraph)
    else()
        message(WARINING "Couldn't find graphviz library at directory ${GRAPHVIZ_DIR}. Compiling program without graphviz...")
    endif()
endif()

