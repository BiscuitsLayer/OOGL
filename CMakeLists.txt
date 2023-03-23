### Entrypoint ###
cmake_minimum_required(VERSION 3.14)
set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)
project(OOGL)

### Definitions ###
set(CMAKE_CXX_STANDARD 20)

### OpenGL ###
# Add package
find_package(OpenGL REQUIRED)
# Provide includes
include_directories(${OPENGL_INCLUDE_DIRS})

### GL_MATH ###
# Add sources variable
file(GLOB GL_MATH_SRC "src/GL/Math/*.cpp")

### GL_WINDOW ###
# Add sources variable
file(GLOB GL_WINDOW_SRC "src/GL/Window/Window.cpp" "src/GL/Window/Window_Win32.cpp")

### GL_OPENGL ###
# Add sources variable
file(GLOB GL_OPENGL_SRC "src/GL/GL/*.cpp")

### GL_UTIL ###
# Add sources variable
file(GLOB GL_UTIL_SRC "src/GL/Util/*.cpp")

### Zlib ###
# Add a new library
file(GLOB GL_ZLIB_SRC "src/GL/Util/zlib/*.c")
add_library(GL_ZLIB STATIC ${GL_ZLIB_SRC})
# Link the library
target_link_libraries(GL_ZLIB PUBLIC)

### Libjpeg ###
# Add a new library
file(GLOB GL_LIBJPEG_SRC "src/GL/Util/libjpeg/*.c")
add_library(GL_LIBJPEG STATIC ${GL_LIBJPEG_SRC})
# Link the library
target_link_libraries(GL_LIBJPEG PUBLIC GL_ZLIB)

### Libpng ###
# Add a new library
file(GLOB GL_LIBPNG_SRC "src/GL/Util/libpng/*.c")
add_library(GL_LIBPNG STATIC ${GL_LIBPNG_SRC})
# Link the library
target_link_libraries(GL_LIBPNG PUBLIC GL_ZLIB)

### OOGL ###
# Add a new library (main target)
add_library(${PROJECT_NAME} STATIC ${GL_MATH_SRC} ${GL_WINDOW_SRC} ${GL_OPENGL_SRC} ${GL_UTIL_SRC})
# Provide includes
target_include_directories(${PROJECT_NAME} PUBLIC "src" "include")
# Link the main target
target_link_libraries(${PROJECT_NAME} PUBLIC ${OPENGL_LIBRARIES} GL_LIBJPEG GL_LIBPNG GL_ZLIB)