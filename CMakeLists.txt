cmake_minimum_required(VERSION 3.22)

project(donsus
        VERSION 0.1.0
        LANGUAGES C
)


set(CMAKE_BUILD_TYPE Debug)

# add_compile_options(-fsanitize=address) # libasan needed
# add_link_options(-fsanitize=address) #libasan needed

add_executable(
        donsus
        Donsus/main.c
        Donsus/src/handle_file.c
        Modules/main.c

        # src/
        Donsus/src/parser/lexer/lexer.c
        Donsus/src/parser/lexer/token.c
        Donsus/src/don_array.c

        # parser/
        Donsus/src/parser/parser.c

        # error/
        Donsus/error/lexer_error.c

        # test/
        test/test.c

)

target_compile_options(donsus
        PRIVATE
        -Wall -Wextra -Wpedantic
)
target_include_directories(
        donsus
        PUBLIC Include/
)