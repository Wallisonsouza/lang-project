cmake_minimum_required(VERSION 3.10)
project(MyInterpreter)

# Define a versão do C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

# Pega todos os arquivos .cpp dentro de src e subpastas
file(GLOB_RECURSE SOURCES
    ${PROJECT_SOURCE_DIR}/src/*.cpp
)

# Cria o executável incluindo main.cpp da raiz
add_executable(main
    main.cpp       # garante que main.cpp seja incluído
    ${SOURCES}
)

# Inclui diretórios (src raiz cobre todas as subpastas)
target_include_directories(main PRIVATE
    ${PROJECT_SOURCE_DIR}/src
)

# Alvo customizado para rodar o programa
add_custom_target(run
    COMMAND $<TARGET_FILE:main>
    DEPENDS main
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)
