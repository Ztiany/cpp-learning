file(GLOB files02 ./*.c)

foreach(file ${files02})
    get_filename_component(name ${file} NAME)
    add_executable(${name} ${file})
endforeach()