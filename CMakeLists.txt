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
    main.cpp
    ${SOURCES}
)

# Inclui diretórios (src raiz cobre todas as subpastas)
target_include_directories(main PRIVATE
    ${PROJECT_SOURCE_DIR}/src
)



# --- LIBZIP Configuration ---
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBZIP REQUIRED libzip)

if(LIBZIP_FOUND)
    message(STATUS "libzip found")
    target_include_directories(main PRIVATE ${LIBZIP_INCLUDE_DIRS})
    target_link_libraries(main PRIVATE ${LIBZIP_LIBRARIES})
endif()


# --- ICU Configuration ---
find_package(ICU REQUIRED COMPONENTS uc i18n)
if(ICU_FOUND)
    message(STATUS "ICU found: ${ICU_INCLUDE_DIRS}")
    target_include_directories(main PRIVATE ${ICU_INCLUDE_DIRS})
    target_link_libraries(main PRIVATE ${ICU_LIBRARIES})
endif()

# Adiciona símbolos de debug (sem sanitizers)
set_target_properties(main PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    COMPILE_FLAGS "-g"
)

# Alvo customizado para rodar o programa
add_custom_target(run
    COMMAND $<TARGET_FILE:main>
    DEPENDS main
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)
