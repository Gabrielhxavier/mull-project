# 🧬 mull-project

Este projeto tem como objetivo **demonstrar o uso de mutation testing** em código C, utilizando a ferramenta **Mull**, integrada ao framework de testes **Unity**.

Os passos abaixo mostram como configurar o ambiente e executar o projeto no **Ubuntu (WSL)**.

---

## 🖥️ Ambiente de execução

O projeto foi desenvolvido e executado no seguinte ambiente:

- **Sistema operacional:** Ubuntu 24.04.3 LTS  
- **Plataforma:** WSL 2 (Windows Subsystem for Linux)  
- **Arquitetura:** x86_64  

---

## 🔧 Passo 1 — Instalação do Mull

### 1.1 Adicionar o repositório oficial do Mull

Execute o seguinte comando no terminal:

```bash
curl -1sLf 'https://dl.cloudsmith.io/public/mull-project/mull-stable/setup.deb.sh' | sudo -E bash
```
Esse comando adiciona o repositório oficial do Mull ao sistema.

### 1.2 Instalar o Mull

Em seguida, instale o pacote executando:
```bash
sudo apt-get update && apt-get install mull-19
```

### 1.3 Verificar a instalação
Para verifica a instalação, execute:

```bash
$ mull-runner-19 --version
```
A saída esperada deve ser semelhante a:

```
Mull: Practical mutation testing and fault injection for C and C++
Home: https://github.com/mull-project/mull
Docs: https://mull.readthedocs.io
Support: https://mull.readthedocs.io/en/latest/Support.html
Version: 0.27.1
LLVM: 19.1.1
```

### 1.4 Dependências necessárias de clang (compilador)
O Mull é um plugin de compilador e, portanto, está associado a versões específicas do Clang (compilador) e LLVM (API).

#### 1.4.1 Instalação do Clang globalmente
Embora o Mull venha com o LLVM e o Clang necessários para rodar o plugin, é importante garantir que você tenha uma versão global do Clang instalada para rodar a instrumentação de mutações.

Para isso, execute o seguinte comando para instalar a versão compatível globalmente no sistema:
```bash
sudo apt install clang-19 llvm-19
```
Verifique se a instalação foi bem sucedida:
```bash
clang-19 --version
```

## 🔽 Passo 2 — Download do projeto e código-fonte

Após a instalação do Mull e das dependências do compilador, o próximo passo é obter o código-fonte do projeto.

Clone o repositório utilizando o Git:

```bash
git clone https://github.com/GabrielXavier/mull-project
cd mull-project
```
Esse repositório contém:
* O código sob teste (brake_status.c)
* A suíte de testes unitários (teste_brake_status.c)
* O arquivo de configuração do Mull (mull.yml)

## 🔽 Passo 3 — Clonar o framework de testes Unity

O projeto utiliza Unity, um framework leve para testes unitários em C.

Para clonar o Unity na raiz do projeto, execute:
```bash
git clone https://github.com/ThrowTheSwitch/Unity.git unity
```
Os seguintes aequivos do Unity são utilizados:
* unity/src/unity.h
* unity/src/unity.c
  
## Estrutura esperada do projeto
Após o clone do projeto e do Unity, a estrutura de diretórios deve ser a seguinte:
```
mull-project/
├── brake_status.c
├── test_brake_status.c
├── mull.yml
└── unity/
    └── src/
        ├── unity.c
        └── unity.h
```

Essa estrutura é suficiente para executar os testes unitários com o Unity e realizar a instrumentação e execução do mutation testing com o Mull.
