# Modos de operação do Mull

O Mull suporta diferentes modos de operação, permitindo sua utilização tanto em projetos simples quanto em sistemas maiores integrados a ferramentas de build e pipelines de CI/CD.

De forma geral, o Mull pode ser utilizado em dois modos principais:

- Modo Standalone
- Modo Integrado a Ferramentas de Build
---

## Modo standalone

No modo **standalone**, o Mull é utilizado diretamente a partir da linha de comando, apontando para um diretório específico onde será aplicada a mutação, sem integração explícita com ferramentas de build.

Nesse modo, o desenvolvedor é responsável por:
- compilar o código manualmente com o plugin do Mull;
- gerar o executável instrumentado;
- executar o `mull-runner` diretamente sobre esse executável.
---
## Modo integrado a ferramentas de build
No modo integrado, o Mull é utilizado em conjunto com ferramentas de build já existentes no projeto.

Nesse cenário, o processo de compilação é controlado pela ferramenta de build, e o Mull é acoplado ao compilador utilizado internamente.

O Mull se integra principalmente a ferramentas baseadas em Clang/LLVM, respeitando as flags e configurações do sistema de build.

As principais ferramentas de build suportadas para integração com o Mull são:
- Make
- CMake

Na documentação oficial do Mull, são apresentados tutoriais específicos demonstrando a integração com essas ferramentas:

- Makefile Integration:
  https://mull.readthedocs.io/en/latest/tutorials/MakefileIntegration.html
- CMake Integration:
  https://mull.readthedocs.io/en/latest/tutorials/CMakeIntegration.html

Esse modo é mais adequado para projetos de médio e grande porte, onde a automação do processo de compilação/testes e integração com pipelines de CI/CD é essencial.
