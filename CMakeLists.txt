cmake_minimum_required (VERSION 3.10)

if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
   set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
endif()


project(essence_emulator)

IF (WIN32)
	set(CMAKE_GENERATOR_PLATFORM "Visual Studio 15 2017")
ENDIF()


#---- Macros (credits: TrinityCore)
#Set path to macro folder
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/macros/")

#Include macros
include(GroupSources)
include(AutoCollect)
include(FindMySQL)

include_directories(${MYSQL_INCLUDE_DIRS})



#---- Compiler definitions
# Needed because of tinyformat
add_definitions(-DNOMINMAX)
# Eliminate unharmful warnings for std::copy with arrays
add_definitions(-D_SCL_SECURE_NO_WARNINGS)

add_definitions(-DTNL_DEBUG)
add_definitions(-DTNL_ENABLE_LOGGING)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#---- Boost Asio
# Use static libs only
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
find_package(Boost 1.68.0 COMPONENTS system regex filesystem thread REQUIRED)


find_package(spdlog CONFIG REQUIRED)
find_package(CURL REQUIRED)
find_package(unofficial-curlpp CONFIG REQUIRED)

# No need for the Boost.DateTime library
add_definitions(-DBOOST_DATE_TIME_NO_LIB)

set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_BUILD_TYPE RelWithDebInfo)
if(UNIX)
	SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -fpermissive")
else()
	SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} /permissive-")
endif()


# Create Bin folder
file(MAKE_DIRECTORY ${CMAKE_INSTALL_PREFIX})

add_subdirectory(dep)

include_directories(${CMAKE_SOURCE_DIR}/dep)

add_subdirectory(src)


