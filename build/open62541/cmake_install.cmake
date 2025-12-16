# Install script for directory: C:/Users/Stasia/Documents/GitHub/prog_kurs/prog_kurs/thirdparty/open62541

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/dynamic_opcua_server")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/Stasia/Documents/GitHub/prog_kurs/prog_kurs/build/bin/Debug/open62541.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/Stasia/Documents/GitHub/prog_kurs/prog_kurs/build/bin/Release/open62541.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/Stasia/Documents/GitHub/prog_kurs/prog_kurs/build/bin/MinSizeRel/open62541.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/Stasia/Documents/GitHub/prog_kurs/prog_kurs/build/bin/RelWithDebInfo/open62541.lib")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/open62541/open62541Targets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/open62541/open62541Targets.cmake"
         "C:/Users/Stasia/Documents/GitHub/prog_kurs/prog_kurs/build/open62541/CMakeFiles/Export/8cb9d92d46a89e68bf96c40f4a60fffd/open62541Targets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/open62541/open62541Targets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/open62541/open62541Targets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/open62541" TYPE FILE FILES "C:/Users/Stasia/Documents/GitHub/prog_kurs/prog_kurs/build/open62541/CMakeFiles/Export/8cb9d92d46a89e68bf96c40f4a60fffd/open62541Targets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/open62541" TYPE FILE FILES "C:/Users/Stasia/Documents/GitHub/prog_kurs/prog_kurs/build/open62541/CMakeFiles/Export/8cb9d92d46a89e68bf96c40f4a60fffd/open62541Targets-debug.cmake")
  endif()
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/open62541" TYPE FILE FILES "C:/Users/Stasia/Documents/GitHub/prog_kurs/prog_kurs/build/open62541/CMakeFiles/Export/8cb9d92d46a89e68bf96c40f4a60fffd/open62541Targets-minsizerel.cmake")
  endif()
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/open62541" TYPE FILE FILES "C:/Users/Stasia/Documents/GitHub/prog_kurs/prog_kurs/build/open62541/CMakeFiles/Export/8cb9d92d46a89e68bf96c40f4a60fffd/open62541Targets-relwithdebinfo.cmake")
  endif()
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/open62541" TYPE FILE FILES "C:/Users/Stasia/Documents/GitHub/prog_kurs/prog_kurs/build/open62541/CMakeFiles/Export/8cb9d92d46a89e68bf96c40f4a60fffd/open62541Targets-release.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/open62541" TYPE FILE FILES
    "C:/Users/Stasia/Documents/GitHub/prog_kurs/prog_kurs/build/open62541/open62541Config.cmake"
    "C:/Users/Stasia/Documents/GitHub/prog_kurs/prog_kurs/build/open62541/open62541ConfigVersion.cmake"
    "C:/Users/Stasia/Documents/GitHub/prog_kurs/prog_kurs/build/open62541/open62541Macros.cmake"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/open62541/tools" TYPE DIRECTORY FILES
    "C:/Users/Stasia/Documents/GitHub/prog_kurs/prog_kurs/thirdparty/open62541/tools/certs"
    "C:/Users/Stasia/Documents/GitHub/prog_kurs/prog_kurs/thirdparty/open62541/tools/nodeset_compiler"
    "C:/Users/Stasia/Documents/GitHub/prog_kurs/prog_kurs/thirdparty/open62541/tools/schema"
    "C:/Users/Stasia/Documents/GitHub/prog_kurs/prog_kurs/thirdparty/open62541/deps/ua-nodeset"
    USE_SOURCE_PERMISSIONS FILES_MATCHING REGEX "/[^/]*$" REGEX "/[^/]*\\.pyc$" EXCLUDE)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/open62541/tools" TYPE FILE FILES
    "C:/Users/Stasia/Documents/GitHub/prog_kurs/prog_kurs/thirdparty/open62541/tools/generate_datatypes.py"
    "C:/Users/Stasia/Documents/GitHub/prog_kurs/prog_kurs/thirdparty/open62541/tools/generate_nodeid_header.py"
    "C:/Users/Stasia/Documents/GitHub/prog_kurs/prog_kurs/thirdparty/open62541/tools/generate_statuscode_descriptions.py"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/open62541" TYPE FILE FILES "C:/Users/Stasia/Documents/GitHub/prog_kurs/prog_kurs/build/open62541/src_generated/open62541/config.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES "C:/Users/Stasia/Documents/GitHub/prog_kurs/prog_kurs/thirdparty/open62541/deps/ms_stdint.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/open62541" TYPE FILE FILES "C:/Users/Stasia/Documents/GitHub/prog_kurs/prog_kurs/thirdparty/open62541/include/open62541/architecture_definitions.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/open62541/win32" TYPE FILE FILES "C:/Users/Stasia/Documents/GitHub/prog_kurs/prog_kurs/thirdparty/open62541/arch/win32/ua_architecture.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/open62541" TYPE FILE FILES "C:/Users/Stasia/Documents/GitHub/prog_kurs/prog_kurs/build/open62541/src_generated/open62541/statuscodes.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/open62541" TYPE FILE FILES "C:/Users/Stasia/Documents/GitHub/prog_kurs/prog_kurs/build/open62541/src_generated/open62541/nodeids.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/open62541" TYPE FILE FILES "C:/Users/Stasia/Documents/GitHub/prog_kurs/prog_kurs/thirdparty/open62541/include/open62541/common.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/open62541" TYPE FILE FILES "C:/Users/Stasia/Documents/GitHub/prog_kurs/prog_kurs/thirdparty/open62541/include/open62541/types.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/open62541" TYPE FILE FILES "C:/Users/Stasia/Documents/GitHub/prog_kurs/prog_kurs/build/open62541/src_generated/open62541/types_generated.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/open62541" TYPE FILE FILES "C:/Users/Stasia/Documents/GitHub/prog_kurs/prog_kurs/build/open62541/src_generated/open62541/types_generated_handling.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/open62541" TYPE FILE FILES "C:/Users/Stasia/Documents/GitHub/prog_kurs/prog_kurs/thirdparty/open62541/include/open62541/util.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/open62541/plugin" TYPE FILE FILES "C:/Users/Stasia/Documents/GitHub/prog_kurs/prog_kurs/thirdparty/open62541/include/open62541/plugin/log.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/open62541/plugin" TYPE FILE FILES "C:/Users/Stasia/Documents/GitHub/prog_kurs/prog_kurs/thirdparty/open62541/include/open62541/plugin/network.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/open62541/plugin" TYPE FILE FILES "C:/Users/Stasia/Documents/GitHub/prog_kurs/prog_kurs/thirdparty/open62541/include/open62541/plugin/accesscontrol.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/open62541/plugin" TYPE FILE FILES "C:/Users/Stasia/Documents/GitHub/prog_kurs/prog_kurs/thirdparty/open62541/include/open62541/plugin/pki.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/open62541/plugin" TYPE FILE FILES "C:/Users/Stasia/Documents/GitHub/prog_kurs/prog_kurs/thirdparty/open62541/include/open62541/plugin/securitypolicy.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/open62541/plugin" TYPE FILE FILES "C:/Users/Stasia/Documents/GitHub/prog_kurs/prog_kurs/thirdparty/open62541/include/open62541/plugin/pubsub.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES "C:/Users/Stasia/Documents/GitHub/prog_kurs/prog_kurs/thirdparty/open62541/deps/ziptree.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES "C:/Users/Stasia/Documents/GitHub/prog_kurs/prog_kurs/thirdparty/open62541/deps/aa_tree.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/open62541/plugin" TYPE FILE FILES "C:/Users/Stasia/Documents/GitHub/prog_kurs/prog_kurs/thirdparty/open62541/include/open62541/plugin/nodestore.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/open62541" TYPE FILE FILES "C:/Users/Stasia/Documents/GitHub/prog_kurs/prog_kurs/thirdparty/open62541/include/open62541/server_pubsub.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/open62541" TYPE FILE FILES "C:/Users/Stasia/Documents/GitHub/prog_kurs/prog_kurs/thirdparty/open62541/include/open62541/server.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/open62541" TYPE FILE FILES "C:/Users/Stasia/Documents/GitHub/prog_kurs/prog_kurs/thirdparty/open62541/include/open62541/client.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/open62541" TYPE FILE FILES "C:/Users/Stasia/Documents/GitHub/prog_kurs/prog_kurs/thirdparty/open62541/include/open62541/client_highlevel.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/open62541" TYPE FILE FILES "C:/Users/Stasia/Documents/GitHub/prog_kurs/prog_kurs/thirdparty/open62541/include/open62541/client_subscriptions.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/open62541" TYPE FILE FILES "C:/Users/Stasia/Documents/GitHub/prog_kurs/prog_kurs/thirdparty/open62541/include/open62541/client_highlevel_async.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/open62541/plugin" TYPE FILE FILES "C:/Users/Stasia/Documents/GitHub/prog_kurs/prog_kurs/thirdparty/open62541/plugins/include/open62541/plugin/accesscontrol_default.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/open62541/plugin" TYPE FILE FILES "C:/Users/Stasia/Documents/GitHub/prog_kurs/prog_kurs/thirdparty/open62541/plugins/include/open62541/plugin/pki_default.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/open62541/plugin" TYPE FILE FILES "C:/Users/Stasia/Documents/GitHub/prog_kurs/prog_kurs/thirdparty/open62541/plugins/include/open62541/plugin/log_stdout.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/open62541/plugin" TYPE FILE FILES "C:/Users/Stasia/Documents/GitHub/prog_kurs/prog_kurs/thirdparty/open62541/plugins/include/open62541/plugin/nodestore_default.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/open62541" TYPE FILE FILES "C:/Users/Stasia/Documents/GitHub/prog_kurs/prog_kurs/thirdparty/open62541/plugins/include/open62541/server_config_default.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/open62541" TYPE FILE FILES "C:/Users/Stasia/Documents/GitHub/prog_kurs/prog_kurs/thirdparty/open62541/plugins/include/open62541/client_config_default.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/open62541/plugin" TYPE FILE FILES "C:/Users/Stasia/Documents/GitHub/prog_kurs/prog_kurs/thirdparty/open62541/plugins/include/open62541/plugin/securitypolicy_default.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/open62541" TYPE FILE FILES "C:/Users/Stasia/Documents/GitHub/prog_kurs/prog_kurs/thirdparty/open62541/include/open62541/network_tcp.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/open62541" TYPE FILE FILES "C:/Users/Stasia/Documents/GitHub/prog_kurs/prog_kurs/thirdparty/open62541/include/open62541/architecture_functions.h")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("C:/Users/Stasia/Documents/GitHub/prog_kurs/prog_kurs/build/open62541/arch/cmake_install.cmake")
  include("C:/Users/Stasia/Documents/GitHub/prog_kurs/prog_kurs/build/open62541/doc/cmake_install.cmake")
  include("C:/Users/Stasia/Documents/GitHub/prog_kurs/prog_kurs/build/open62541/tools/packaging/cmake_install.cmake")

endif()

