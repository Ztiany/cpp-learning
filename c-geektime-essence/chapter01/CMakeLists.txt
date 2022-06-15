file(GLOB files01 ./*.c)

foreach(file ${files01})
    get_filename_component(name ${file} NAME)
    add_executable(${name} ${file})
endforeach()