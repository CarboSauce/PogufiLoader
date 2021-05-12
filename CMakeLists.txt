cmake_minimum_required(VERSION 3.16)


set(CMAKE_CROSSCOMPILING "TRUE")
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")
set(CMAKE_SYSTEM_NAME "Generic")

set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_SYSTEM_NAME "")
set_property(GLOBAL PROPERTY 
             C_STANDARD 11
)
set(GENERAL_COMPILE_FLAGS 
    $<$<COMPILE_LANG_AND_ID:C,Clang,GNU,AppleClang>:$<BUILD_INTERFACE:-fshort-wchar;-ffreestanding;-nostdlib;-Wall;-Wextra>>
)


# Delaying project declaration

project (UEFIbl C ASM_NASM)


add_library(saneoder MODULE src/main.c)



add_subdirectory(edk2)
add_subdirectory(src)

target_compile_options(saneoder PRIVATE
    ${GENERAL_COMPILE_FLAGS}
)

target_link_options(saneoder PRIVATE 
    $<$<LINK_LANG_AND_ID:C,GNU,Clang,AppleClang>:-nostdinc;-nostdlib;-Wl,--subsystem,10;-eefi_main>
)

set_target_properties(saneoder PROPERTIES 
    PREFIX ""
    SUFFIX .EFI
    OUTPUT_NAME BOOTX64
)


#target_sources(saneoder PRIVATE $<TARGET_OBJECTS:edk2_lib>)
install(TARGETS saneoder 
    DESTINATION "EFI/BOOT/"
    RENAME BOOTX64.EFI
)
