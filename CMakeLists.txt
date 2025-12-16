cmake_minimum_required(VERSION 3.10)
project(OPCUAWin32GUI)

set(CMAKE_CXX_STANDARD 17)

# УБРАТЬ configure_file и ${CMAKE_CURRENT_BINARY_DIR}/resource.h
add_executable(opcua_gui
    src/simple_opcua_gui.cpp
    src/opcua_client.cpp
    src/graph_window.cpp
    src/graph_renderer.cpp
    simple_dialog.rc
    # УБРАТЬ эту строку: ${CMAKE_CURRENT_BINARY_DIR}/resource.h
)

# Указываем директорию для RC компилятора
set_source_files_properties(simple_dialog.rc PROPERTIES
    COMPILE_FLAGS "-I${CMAKE_CURRENT_SOURCE_DIR}"
)

target_include_directories(opcua_gui PRIVATE 
    include
    ${CMAKE_CURRENT_SOURCE_DIR}  # корневая директория
)

if(WIN32)
    target_link_libraries(opcua_gui
        comctl32
        ws2_32
        gdi32
        user32
    )
    
    set_target_properties(opcua_gui PROPERTIES
        WIN32_EXECUTABLE TRUE
        LINK_FLAGS "/SUBSYSTEM:WINDOWS"
    )
endif()