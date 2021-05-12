set(LIST_DIRECTORIES "TRUE")
file(GLOB_RECURSE edk2_sources /Libary/ *.c *.nasm) 

foreach(line IN LISTS edk2_sources)
    message(DEBUG ${line})    
endforeach()


add_library(edk2_lib STATIC ${edk2_sources})

include(edk2defs.cmake)

set(NASM_MACRO_HACK 
    "-DASM_PFX(x)=x"#__USER_LABEL_PREFIX %+x"
    "-DFixedPcdGet32(x)=x"#_PCD_VALUE_ %+x"
    "-DPatchPcdGet32(x)=x"#_gPcd_BinaryPatch_ %+x"
    "-DPcdGet32(x)=x"#_PCD_GET_MODE_32_ %+x"
)

target_include_directories(edk2_lib PUBLIC 
  ${CMAKE_CURRENT_SOURCE_DIR}/Include/
  ${CMAKE_CURRENT_SOURCE_DIR}/Include/X64
  PRIVATE 
  ${CMAKE_CURRENT_SOURCE_DIR}/Include/Library
  ${CMAKE_CURRENT_SOURCE_DIR}/Include/Guid
  ${CMAKE_CURRENT_SOURCE_DIR}/Include/IndustryStandard
  ${CMAKE_CURRENT_SOURCE_DIR}/Include/Protocol
  ${CMAKE_CURRENT_SOURCE_DIR}/Include/Register
  ${CMAKE_CURRENT_SOURCE_DIR}/Include/Uefi
  ${CMAKE_CURRENT_SOURCE_DIR}/Library/BaseLib
)
# Do not enable warnings, edk2 has really messy code, not my job to fix it
target_compile_options(edk2_lib PRIVATE
    $<$<COMPILE_LANG_AND_ID:C,Clang,GNU,AppleClang>:$<BUILD_INTERFACE:-fshort-wchar;-nostdinc;-ffreestanding;-nostdlib>>
    $<$<COMPILE_LANGUAGE:ASM_NASM>:$<BUILD_INTERFACE:${NASM_MACRO_HACK}>>
)

target_link_options(edk2_lib PRIVATE
    $<$<LINK_LANG_AND_ID:C,GNU,Clang,AppleClang>:-nostdinc;-nostdlib>
)

