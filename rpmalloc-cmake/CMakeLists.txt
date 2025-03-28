set(CMAKE_C_STANDARD 11)
add_compile_options(/experimental:c11atomics)
add_library(rpmalloc STATIC ../rpmalloc/rpmalloc/rpmalloc.c)
