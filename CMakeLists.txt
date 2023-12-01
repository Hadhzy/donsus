cmake_minimum_required(VERSION 3.22)


project(donsus
        VERSION 0.1.0
        LANGUAGES C
)

add_executable(
        donsus
        Donsus/main.c
        Donsus/src/handle_file.c
        Modules/main.c
        Donsus/src/parser/lexer/lexer.c
        Donsus/src/parser/lexer/token.c
        Donsus/src/don_array.c
)

target_include_directories(
        donsus
        PUBLIC Include/
)