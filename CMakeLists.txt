cmake_minimum_required(VERSION 3.12)
project(LibMessageKit VERSION 1.0.0 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Library source files
set(LIB_SOURCES
        src/core/call.c
        src/core/call_history.c
        src/core/contacts.c
        src/core/conversations.c
        src/core/core.c
        src/core/group_messages.c
        src/core/messages.c
        src/core/settings.c
        src/network/network.c
)

# Library header files
set(LIB_HEADERS
        include/libmessagekit/private/network.h
        include/libmessagekit/call.h
        include/libmessagekit/call_history.h
        include/libmessagekit/common.h
        include/libmessagekit/config.h
        include/libmessagekit/contacts.h
        include/libmessagekit/conversations.h
        include/libmessagekit/core.h
        include/libmessagekit/group_messages.h
        include/libmessagekit/libmessagekit.h
        include/libmessagekit/messages.h
        include/libmessagekit/settings.h
)

# Make the library
add_library(libmessagekit STATIC ${LIB_SOURCES} ${LIB_HEADERS})

# Set include directories
target_include_directories(libmessagekit
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Installation rules
install(TARGETS libmessagekit
        EXPORT libmessagekitTargets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
)

install(FILES ${LIB_HEADERS} DESTINATION include/libmessagekit)

# Export the targets
install(EXPORT libmessagekitTargets
        FILE LibMessageKitTargets.cmake
        NAMESPACE LibMessageKit::
        DESTINATION lib/cmake/LibMessageKit
)

# Make a Config file
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
        "LibMessageKitConfigVersion.cmake"
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY SameMajorVersion
)

# Install the config files
install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/LibMessageKitConfigVersion.cmake"
        DESTINATION lib/cmake/LibMessageKit
)