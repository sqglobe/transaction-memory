# Look for library `itm` that contains required symbols
find_library(ITM
     NAMES itm itm.so libitm.so
     PATHS /usr/x86_64-linux-gnu/lib/ /usr/lib/x86_64-linux-gnu/ /usr/lib/gcc/x86_64-linux-gnu/*/
     REQUIRED)

add_library(examples INTERFACE)

target_include_directories(examples INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")
target_compile_options(examples INTERFACE -fgnu-tm)
target_link_libraries(examples INTERFACE ${ITM})
