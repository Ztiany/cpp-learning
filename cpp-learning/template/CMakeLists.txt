file(GLOB files "./*.cpp")

foreach(file ${files})
    get_filename_component(name ${file} NAME)
    message(add-executable: ${file})
    add_executable(${name} ${file})
endforeach()
