# Get all subdirectories under ${current_dir} and store them
# in ${result} variable
macro(subdirlist result current_dir)
    file(GLOB children ${current_dir}/*)
    set(dirlist "")

    foreach(child ${children})
        if (IS_DIRECTORY ${child})
            list(APPEND dirlist ${child})
        endif()
    endforeach()

    set(${result} ${dirlist})
endmacro()

# Prepend ${CMAKE_CURRENT_SOURCE_DIR} to a ${directory} name
# and save it in PARENT_SCOPE ${variable}
macro(prepend_cur_dir variable directory)
    set(${variable} ${CMAKE_CURRENT_SOURCE_DIR}/${directory})
endmacro()

# Add custom command to print firmware size in Berkley format
function(firmware_size target)
    add_custom_command(TARGET ${target} POST_BUILD
        COMMAND ${CMAKE_SIZE_UTIL} -B
        "$<TARGET_FILE:${target}>"
    )
endfunction()

# Add a command to generate firmare in a provided format
function(generate_object target suffix type)
    add_custom_command(TARGET ${target} POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -O ${type}
        "$<TARGET_FILE:${target}>" "${CMAKE_CURRENT_BINARY_DIR}/${target}${suffix}"
    )
endfunction()

function(target_linker_script target script)
    target_link_options(${target} PRIVATE "-T${script}")

    get_target_property(_cur_link_deps ${target} LINK_DEPENDS)
    if (_cur_link_deps STREQUAL _cur_link_deps-NOTFOUND)
        set(_cur_link_deps "")
    endif ()
    string(APPEND _cur_link_deps "${script}")
    set_target_properties(${target} PROPERTIES LINK_DEPENDS ${_cur_link_deps})
endfunction()

function(write_file_if_changed file content)
    if (EXISTS "${file}")
        file(READ "${file}" existing_content)
    else ()
        set(existing_content "")
    endif ()
    if (NOT "${existing_content}" STREQUAL "${content}")
        file(WRITE "${file}" "${content}")
    endif ()
endfunction()

function(embed_file target file symbol)
    cmake_path(IS_ABSOLUTE file is_absolute)
    if (NOT is_absolute)
        set(file "${CMAKE_CURRENT_SOURCE_DIR}/${file}")
    endif ()

    cmake_path(GET file FILENAME filename)

    set(generated_dir "${CMAKE_CURRENT_BINARY_DIR}/generated")
    if (NOT EXISTS "${generated_dir}")
        file(MAKE_DIRECTORY "${generated_dir}")
    endif ()

    set(generated_objects "${generated_dir}_objects")
    if (NOT EXISTS "${generated_objects}")
        file(MAKE_DIRECTORY "${generated_objects}")
    endif ()

    set(asm_path "${generated_objects}/${filename}.S")
    write_file_if_changed("${asm_path}"
"
.global ${symbol}_data
.global ${symbol}_size
.section .rodata
.align 4
${symbol}_data:
    .incbin \"${file}\"
1:
${symbol}_size:
    .int 1b - ${symbol}_data
")

    add_custom_command(OUTPUT "${asm_path}"
        COMMAND ${CMAKE_COMMAND} ARGS -E touch "${asm_path}"
        DEPENDS "${file}")

    target_sources("${target}" PRIVATE "${asm_path}")

    set(header_path "${generated_dir}/${filename}")

    write_file_if_changed("${header_path}.h"
"#pragma once

#ifdef _cplusplus
extern \"C\" {
#endif

extern const char ${symbol}_data[];
extern const unsigned int ${symbol}_size;

#ifdef _cplusplus
}
#endif
")

    write_file_if_changed("${header_path}.hpp"
"#pragma once

#include \"${header_path}.h\"

#include <span>

inline const std::span<const char> ${symbol}{${symbol}_data, ${symbol}_size};
")
endfunction()