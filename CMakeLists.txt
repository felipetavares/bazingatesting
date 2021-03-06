# Compila a partir do CMake2.8
cmake_minimum_required(VERSION 2.8)
include(ExternalProject)

# ATENÇÃO: LIBVORBIS, LIBOGG e FREETYPE2
# PRECISAM SER COMPILADAS ANTES DE EXECUTAR
# O CMAKE!

ADD_DEFINITIONS(
    -std=c++11 # Or -std=c++0x
    #-pthread # Multithreaded
    -gdwarf-3 # Debug, shall we
    -Wl,-rpath=lib
    -Wall
)

#IF (WIN32)
#ADD_DEFINITIONS(
#    -Wl,--subsystem,windows
#)
#ENDIF (WIN32)

# Vamos compilar a Bazinga! Engine
project (Bazinga)

# Adiciona bibliotecas Lua ao projeto
include_directories (${CMAKE_SOURCE_DIR}/lua/lua-5.2.2/src/)

# Adiciona bibliotecas SDL ao projeto
include_directories (${CMAKE_SOURCE_DIR}/sdl/include/SDL/)

# Adiciona bibliotecas DevIL ao projeto
include_directories (${CMAKE_SOURCE_DIR}/devil/include/IL/)

# Adiciona bibliotecas Chipmunk ao projeto
include_directories (${CMAKE_SOURCE_DIR}/chipmunk/Chipmunk-6.2.1/include/chipmunk/)

# Adiciona bibliotecas Vorbis ao projeto
include_directories (${CMAKE_SOURCE_DIR}/ogg/libvorbis-1.3.4/include/vorbis/)

# Adiciona bibliotecas Ogg ao projeto
include_directories (${CMAKE_SOURCE_DIR}/ogg/libogg-1.3.2/include/)

# Adiciona bibliotecas FreeType2 ao projeto
include_directories (${CMAKE_SOURCE_DIR}/freetype/freetype-2.5.5/include/)

# Adiciona lib lua
add_library(lualib STATIC IMPORTED)
set_target_properties(lualib PROPERTIES IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/lua/lua-5.2.2/src/liblua.a")

# Adiciona libs da SDL (se estiver no windows)
IF (WIN32)
add_library(libSDL STATIC IMPORTED)
set_target_properties(libSDL PROPERTIES IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/sdl/windows/libSDL.dll.a")
add_library(libSDLmain STATIC IMPORTED)
set_target_properties(libSDLmain PROPERTIES IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/sdl/windows/libSDLmain.a")
# Adiciona libs da DevIL
add_library(devil STATIC IMPORTED)
set_target_properties(devil PROPERTIES IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/build/DevIL.lib")
ENDIF(WIN32)

#IF (UNIX)
#add_library(devil DYNAMIC IMPORTED)
#set_target_properties(devil PROPERTIES IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/build/libIL.so.1.1.0")
#ENDIF(UNIX)

# Adiciona lib Chipmunk
add_library(chipmunklib STATIC IMPORTED)
set_target_properties(chipmunklib PROPERTIES IMPORTED_LOCATION "Chipmunk-prefix/src/Chipmunk-build/src/libchipmunk.a")

# Adiciona libs do vorbis & ogg
add_library(vorbislib STATIC IMPORTED)
set_target_properties(vorbislib PROPERTIES IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/ogg/libvorbis-1.3.4/lib/.libs/libvorbis.a")
add_library(vorbisfilelib STATIC IMPORTED)
set_target_properties(vorbisfilelib PROPERTIES IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/ogg/libvorbis-1.3.4/lib/.libs/libvorbisfile.a")
add_library(ogglib STATIC IMPORTED)
set_target_properties(ogglib PROPERTIES IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/ogg/libogg-1.3.2/src/.libs/libogg.a")

# Adiciona libs FreeType2
IF(WIN32)
add_library(freetype2lib STATIC IMPORTED)
set_target_properties(freetype2lib PROPERTIES IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/freetype/freetype-2.5.5/objs/freetype.a")
ENDIF(WIN32)
IF(UNIX)
add_library(freetype2lib STATIC IMPORTED)
set_target_properties(freetype2lib PROPERTIES IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/freetype/freetype-2.5.5/objs/libfreetype.a")
ENDIF(UNIX)

add_library(bazingares STATIC IMPORTED)
set_target_properties(bazingares PROPERTIES IMPORTED_LOCATION "bazinga.res")

# Compila Lua 5.2.2
ADD_CUSTOM_TARGET(
  lua.o ALL
  COMMAND ${CMAKE_MAKE_PROGRAM} linux
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/lua/lua-5.2.2
COMMENT "Compilando Lua 5.2.2 (com o Makefile original)")

IF (WIN32)
ExternalProject_Add(
  Chipmunk
  URL ${CMAKE_SOURCE_DIR}/chipmunk/Chipmunk-6.2.1/
  INSTALL_COMMAND ""
  CMAKE_ARGS -DCMAKE_CXX_COMPILER=C:/MinGW/bin/g++.exe
             -DCMAKE_C_COMPILER=C:/MinGW/bin/gcc.exe
             -DCMAKE_CXX_FLAGS=-std=c++11
             -DCMAKE_C_COMPILER_ENV_VAR=C:/MinGW/bin/
             -DCMAKE_CXX_COMPILER_ENV_VAR=C:/MinGW/bin/
             -DCMAKE_MAKE_PROGRAM=C:/MinGW/bin/mingw32-make.exe
             -DCMAKE_AR=C:/MinGW/bin/ar.exe
)
ENDIF(WIN32)

IF(UNIX)
ExternalProject_Add(
  Chipmunk
  URL ${CMAKE_SOURCE_DIR}/chipmunk/Chipmunk-6.2.1/
  INSTALL_COMMAND ""
  CMAKE_ARGS -DCMAKE_CXX_COMPILER=clang++-3.5
  -DCMAKE_C_COMPILER=clang-3.5
  -DCMAKE_CXX_FLAGS=-std=c++11
  -DCMAKE_MAKE_PROGRAM=make
)
ENDIF(UNIX)

# Compila o executável principal
add_executable (bazinga bazinga.cpp
                        json.cpp
                        filesystem.cpp
                        object.cpp
                        map.cpp
                        video.cpp
                        cache.cpp
                        input.cpp
                        audio.cpp
                        animation.cpp
                        image.cpp
                        text.cpp
                        shader.cpp
                        console.cpp
                        editor.cpp
                        render.cpp
                        math/sm4/sm4.cpp
                        math/vec2/vec2.cpp
                        math/vec3/vec3.cpp
                        math/vec4/vec4.cpp
                        gl/glwin.cpp
                        gui.cpp
                        gui/label.cpp
                        gui/paletteitem.cpp
                        gui/button.cpp
                        gui/spacer.cpp
                        gui/slider.cpp
                        gui/progress.cpp
                        gui/rwidget.cpp
                        gui/entry.cpp
                        gui/bgraph.cpp
                        gui/scroll.cpp
                        gui/filemanager.cpp
                        gui/textarea.cpp
                        gui/checkbox.cpp)

# Linka com (opengl, lua, sdl, devil)
IF (WIN32)
target_link_libraries (bazinga glu32 opengl32)
target_link_libraries (bazinga libSDLmain)
target_link_libraries (bazinga libSDL)
target_link_libraries (bazinga bazingares)
target_link_libraries (bazinga devil)
ENDIF (WIN32)

target_link_libraries (bazinga freetype2lib)
target_link_libraries (bazinga lualib)
target_link_libraries (bazinga chipmunklib)
target_link_libraries (bazinga vorbisfilelib)
target_link_libraries (bazinga vorbislib)
target_link_libraries (bazinga ogglib)

IF (UNIX)
  target_link_libraries (bazinga ${CMAKE_SOURCE_DIR}/build/lib/libSDL-1.2.so.0.11.4 GL dl)
  target_link_libraries (bazinga ${CMAKE_SOURCE_DIR}/build/lib/libIL.so.1.1.0)
  target_link_libraries (bazinga ${CMAKE_SOURCE_DIR}/build/lib/libpng15.so.15)
  target_link_libraries (bazinga ${CMAKE_SOURCE_DIR}/build/lib/libmng.so.1)
  target_link_libraries (bazinga ${CMAKE_SOURCE_DIR}/build/lib/liblcms.so.1)
  target_link_libraries (bazinga ${CMAKE_SOURCE_DIR}/build/lib/libjpeg.so.62)
ENDIF (UNIX)

# Dependencias
ADD_DEPENDENCIES (lualib lua.o)
