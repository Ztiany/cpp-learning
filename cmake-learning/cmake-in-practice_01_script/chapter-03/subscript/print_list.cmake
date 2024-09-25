
function(print_list)
    message("--------------------------------")
    message("ARGV: ${ARGV}")
    math(EXPR end "${ARGC} -1")
    foreach (x RANGE 0 ${end})
        if (${x} EQUAL ${end})
            println("${ARGV${x}}")
        else ()
            print("${ARGV${x}}  |  ")
        endif ()
    endforeach ()
endfunction()


# see: <https://stackoverflow.com/questions/51040536/how-to-print-without-newline-in-cmake>
function(print)
    execute_process(COMMAND ${CMAKE_COMMAND} -E echo_append "${ARGV}")
endfunction()

function(println)
    execute_process(COMMAND ${CMAKE_COMMAND} -E echo "${ARGV}")
endfunction()
