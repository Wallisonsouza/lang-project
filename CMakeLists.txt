cmake_minimum_required(VERSION 3.10)
project(MyInterpreter)

# Define a versão do C++
set(CMAKE_CXX_STANDARD 20)       # mudar aqui para C++20
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)    # opcional: desativa extensões do compilador

# Pega todos os arquivos .cpp
file(GLOB SOURCES "src/**/*.cpp" "*.cpp")

# Cria o executável
add_executable(main ${SOURCES})

# Inclui diretórios
target_include_directories(main PRIVATE
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/src/core
    ${PROJECT_SOURCE_DIR}/src/errors
    ${PROJECT_SOURCE_DIR}/src/handlers
    ${PROJECT_SOURCE_DIR}/src/registry
    ${PROJECT_SOURCE_DIR}/src/plugins
)

# Alvo customizado para rodar o programa
add_custom_target(run
    COMMAND $<TARGET_FILE:main>
    DEPENDS main
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)
