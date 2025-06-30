cmake_minimum_required(VERSION 3.31)
project(Wii-Fit-Password-Retriever)

# Binary linker stuff
set(BIN2S ${DEVKITPRO}/tools/bin/bin2s)
set(BINARY_AS ${DEVKITPPC}/bin/powerpc-eabi-as)

set(MACHDEP "-DGEKKO -mrvl -mcpu=750 -meabi -mhard-float")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_ASM_FLAGS "-x assembler-with-cpp")
set(CMAKE_C_FLAGS "-Wall -Wextra -Wno-unused-function -O2 ${CMAKE_CXX_FLAGS} ${MACHDEP}")
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wno-unused-function -O2 ${CMAKE_CXX_FLAGS} ${MACHDEP} -fdiagnostics-color")
set(CMAKE_EXECUTABLE_SUFFIX ".elf")

include_directories(${LIBOGCDIR}/include)
include_directories(${DEVKITPRO}/portlibs/wii/include)
include_directories(${DEVKITPRO}/portlibs/ppc/include)
link_directories(${DEVKITPRO}/portlibs/wii/lib)
link_directories(${DEVKITPRO}/portlibs/ppc/lib)
link_directories(${DEVKITPRO}/libogc/lib/wii)

add_executable(Wii-Fit-Password-Retriever
        main.cpp
        save.cpp
        tui.cpp
        utils.cpp
        extract.cpp
        extract.h
)

target_link_libraries(Wii-Fit-Password-Retriever
        PRIVATE wiiuse bte asnd ogc qrencode z bz2
)
