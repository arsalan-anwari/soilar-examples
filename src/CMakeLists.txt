cmake_minimum_required( VERSION 2.8 )

## Sources and headers
include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )
#include_directories( "<<path/to/include/" )
include_directories(${WIRINGPI_INCLUDE_DIRS}) 

## Find all source and header files to be compiled into object files
file( GLOB_RECURSE SOURCES *.cc *.hh *.cpp *.hpp *.c *.h )

## Add Libraries
# add_library(<<LibraryName>> SHARED IMPORTED)
# set_property(TARGET <<LibraryName>>  PROPERTY IMPORTED_LOCATION "/path/to/lib/")

## Find Required Packages
# find_package(<<LibraryName>> REQUIRED)
find_package(WiringPi REQUIRED)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package( Boost COMPONENTS thread chrono timer REQUIRED)
include_directories( ${Boost_INCLUDE_DIR} )

## C++ compiler options

### Compiler settings
set( CMAKE_CXX_FLAGS_DEBUG "-g -O0" )
set( CMAKE_CXX_FLAGS_RELEASE "-O2" )
set( CMAKE_CXX_STANDARD_REQUIRED ON ) #...is required...
set( CMAKE_CXX_EXTENSIONS ON ) #...with compiler extensions like gnu++11

### Set custom flags
set( CMAKE_CXX_FLAGS "-Wextra -lrt -lm -std=c++11 -I -L/usr/local/libs" ) 


## Source file containing the "main" function
set( MAIN_SOURCE main.cpp )
## Specify a name for the generated executable file
set( MAIN_EXE_NAME ${PROJECT_NAME_}.exe )


## 1. Compile...
add_executable( ${MAIN_EXE_NAME} ${MAIN_SOURCE} ${SOURCES} )


## 2. Link...
target_link_libraries( ${MAIN_EXE_NAME} ${WIRINGPI_LIBRARIES} ${Boost_LIBRARIES} )
#target_link_libraries( ${MAIN_EXE_NAME} ${CMAKE_CXX_FLAGS} ${WIRINGPI_LIBRARIES} )
# target_link_libraries(${MAIN_EXE_NAME} <<Libraryname>> )


## 3. Install...
install( TARGETS ${MAIN_EXE_NAME}
         RUNTIME DESTINATION bin )
