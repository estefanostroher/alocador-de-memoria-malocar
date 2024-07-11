### README

# Compilação/Execução do programa Malocar escrito em linguagem C

Este README fornece instruções sobre como compilar e executar o programa malocar em C utilizando diferentes compiladores tanto no Linux quanto no Windows.

## Índice
1. [Requisitos](#requisitos)
2. [Compilação no Linux](#compilacao-no-linux)
   - [Usando GCC](#usando-gcc-linux)
3. [Compilação no Windows](#compilacao-no-windows)
   - [Usando MinGW](#usando-mingw-windows)
   - [Usando Clang](#usando-clang-windows)
   - [Usando GCC](#usando-gcc-windows)
4. [Execução do Programa](#execucao-do-programa)

## Requisitos

- Um editor de texto ou IDE (por exemplo, Visual Studio Code, Atom, Sublime Text, etc).
- Compilador C adequado ao seus sistema operacional.

## Compilação no Linux

### Usando GCC (Linux)

1. **Instalar GCC (se não estiver instalado)**:
   ```sh
   sudo apt update
   sudo apt install gcc
   ```

2. **Compilar o programa**:
   ```sh
   gcc -o meu_programa meu_programa.c
   ```

3. **Executar o programa**:
   ```sh
   ./meu_programa
   ```

## Compilação no Windows

### Usando MinGW (Windows)

1. **Instalar MinGW**:
   - Baixe o instalador do MinGW em [MinGW-w64](http://mingw-w64.org/doku.php/download).
   - Siga as instruções de instalação.

2. **Adicionar MinGW ao PATH**:
   - Adicione o diretório `bin` do MinGW ao PATH do Windows.

3. **Compilar o programa**:
   ```sh
   gcc -o meu_programa.exe meu_programa.c
   ```

4. **Executar o programa**:
   ```sh
   ./meu_programa.exe
   ```

### Usando Clang (Windows)

1. **Instalar Clang**:
   - Baixe o instalador do LLVM em [LLVM releases](https://releases.llvm.org/download.html).
   - Siga as instruções de instalação.

2. **Adicionar LLVM ao PATH**:
   - Adicione o diretório `bin` do LLVM ao PATH do Windows.

3. **Compilar o programa**:
   ```sh
   clang -o meu_programa.exe meu_programa.c
   ```

4. **Executar o programa**:
   ```sh
   ./meu_programa.exe
   ```

### Usando GCC (Windows via Cygwin)

1. **Instalar Cygwin**:
   - Baixe o instalador do Cygwin em [Cygwin](https://www.cygwin.com/).
   - Durante a instalação, selecione o pacote `gcc-core`.

2. **Abrir o terminal Cygwin**.

3. **Compilar o programa**:
   ```sh
   gcc -o meu_programa.exe meu_programa.c
   ```

4. **Executar o programa**:
   ```sh
   ./meu_programa.exe
   ```

## Execução do Programa

Após a compilação bem-sucedida, o programa pode ser executado diretamente no terminal ou no prompt de comando, conforme mostrado nas seções acima. Certifique-se de estar no diretório correto onde o executável foi gerado.
