project(XenC)

add_executable(sandbox
    main.c
)

target_link_libraries(sandbox PRIVATE xenc)

include_directories(
    ${CMAKE_SOURCE_DIR}/src
)