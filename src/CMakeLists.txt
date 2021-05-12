target_include_directories(saneoder PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/common
    ${CMAKE_CURRENT_SOURCE_DIR}/lib
    ${CMAKE_CURRENT_SOURCE_DIR}/protos
)

target_sources(saneoder PRIVATE
    lib/gop.c
    lib/disk.c
    lib/memorymap.c
    protos/eggload.c
)