cmake_minimum_required(VERSION 3.0)

project(os9fetch LANGUAGES C CXX)


# compile flags
add_compile_options(${COMPILE_FLAGS})
add_compile_definitions(
    _GNU_SOURCE
    CONFIG_BIGNUM
    CONFIG_VERSION=${QUICKJS_VERSION}
    CONFIG_AGENT=0
)

set(QJSC_CONFIG -DCONFIG_PREFIX="/usr/local" -DCONFIG_LTO)
set(QJSC_EXE "${EXECUTABLE_OUTPUT_PATH}/qjsc")
set(QJS_CONFIG ${QJSC_CONFIG} -DCONFIG_CC="clang")


###############################################################################
## file globbing ##############################################################
###############################################################################

# these instructions search the directory tree when CMake is
# invoked and put all files that match the pattern in the variables
# `sources` and `data`
file(GLOB_RECURSE sources   
    src/**/**/**/*.c src/**/**/**/*.h src/**/**/**/*.cpp src/**/**/**/*.hpp 
    src/**/**/*.c src/**/**/*.h src/**/**/*.cpp src/**/**/*.hpp 
    src/**/*.c src/**/*.h src/**/*.cpp src/**/*.hpp 
    src/*.c src/*.h src/*.cpp src/*.hpp
)
file(GLOB_RECURSE data resources/*)
# you can use set(sources src/main.cpp) etc if you don't want to
# use globbing to find files automatically

###############################################################################
## target definitions #########################################################
###############################################################################

# add the data to the target, so it becomes visible in some IDE
if(CMAKE_SYSTEM_NAME MATCHES Retro)
    add_application(os9fetch ${sources} ${data})
else()
    add_executable(os9fetch ${sources} ${data})
endif()
target_link_directories(os9fetch PUBLIC ${CMAKE_SOURCE_DIR}/lib )

set_property(TARGET os9fetch PROPERTY CXX_STANDARD 20)

# just for os9fetch add some compiler flags
target_compile_options(os9fetch PUBLIC -std=c++20 -Wall -Wfloat-conversion)

set_target_properties(os9fetch PROPERTIES COMPILE_OPTIONS -ffunction-sections)
#target_link_libraries(os9fetch "${RETRO68_ROOT}/InterfaceAndLibraries/Libraries/StubLibraries/ThreadsLib")

#target_link_libraries( os9fetch ThreadsLib)

target_link_libraries( os9fetch PowerMgrLib)
target_link_libraries( os9fetch NameRegistryLib)
target_link_libraries( os9fetch AppleScriptLib)
target_link_libraries( os9fetch -Lglut.lib)
include_directories( "${RETRO68_TOOLCHAIN}universal/CIncludes/")

if(CMAKE_SYSTEM_NAME MATCHES Retro68)
    set_target_properties(os9fetch PROPERTIES LINK_FLAGS "-Wl,--mac-strip-macsbug")
endif()

# this copies all resource files in the build directory
# we need this, because we want to work with paths relative to the executable
file(COPY ${data} DESTINATION resources)