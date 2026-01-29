#!/bin/bash
set -e

# # Deleta a pasta build se existir
# rm -rf build

# Cria novamente
mkdir -p build
cd build

# Gera arquivos de build
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..

# Compila usando todos os núcleos
# make -j$(nproc)
make
# Limpa a tela
clear

# Executa o programa
make run
