# Mull-Project

Este projeto tem como objetivo demonstrar o uso da ferramenta **Mull** para *mutation testing* em programas escritos em **C**, como parte da avaliação da disciplina **Noções de Automação de Testes**.

Para isso, foi desenvolvido um código simples em C, acompanhado de uma suíte de testes unitários, a fim de exemplificar o processo de instrumentação, execução e análise de mutações utilizando o Mull em conjunto com o framework **Unity**.

---

## 📁 Project structure

A estrutura de diretórios do projeto é apresentada a seguir:

```text
mull-project/
├── brake_status.c            - Código-fonte sob teste
├── test_brake_status.c       - Suíte de testes unitários
├── mull.yml                  - Arquivo de configuração do Mull
├── README.md                 - Este arquivo
├── docs/
│   ├── configuring_mull.md   - Documentação de apoio (configuração do Mull)
│   ├── operation_modes.md    - Documentação de apoio (modos de operação)
│   ├── Mutators.rst          - Documentação de apoio (operadores de mutação)
│   └── relatorio.md          - Relatório/entregável do projeto
└── unity/                    - Framework de testes Unity
    └── src/
        ├── unity.c
        └── unity.h
```
Para executar o passo a passo completo do desenvolvimento e da utilização da ferramenta, consulte o arquivo:

➡️ [`docs/relatorio.md`](./docs/relatorio.md)

## 👨‍💻 Autor
Desenvolvido por: Gabriel Xavier
