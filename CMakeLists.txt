cmake_minimum_required(VERSION 3.10)
project(dynamic_opcua_server)

# Настройки C++ - УКАЗЫВАЕМ C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Для Windows: поддержка UTF-8
if(MSVC)
    add_compile_options(/utf-8 /std:c++17)
endif()

# Используем уже скачанную библиотеку open62541
set(OPEN62541_DIR ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/open62541)
add_subdirectory(${OPEN62541_DIR} ${CMAKE_BINARY_DIR}/open62541)

# Наш исполняемый файл
add_executable(voltmeter_server
    src/main.cpp
    src/DynamicTagManager.cpp
)

# Подключаем библиотеки
target_link_libraries(voltmeter_server open62541)

# Для Windows добавляем системные библиотеки
if(WIN32)
    target_link_libraries(voltmeter_server ws2_32)
    target_compile_definitions(voltmeter_server PRIVATE _WINSOCK_DEPRECATED_NO_WARNINGS)
endif()

# Подключаем заголовочные файлы
target_include_directories(voltmeter_server PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${OPEN62541_DIR}/include
)