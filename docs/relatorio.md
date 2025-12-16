# mull-project

Este projeto tem como objetivo **demonstrar o uso de mutation testing** em código C, utilizando a ferramenta **Mull**, integrada ao framework de testes **Unity**.

Os passos abaixo mostram como configurar o ambiente e executar o projeto no **Ubuntu (WSL)**.

---

## Ambiente de execução

O projeto foi desenvolvido e executado no seguinte ambiente:

- **Sistema operacional:** Ubuntu 24.04.3 LTS  
- **Plataforma:** WSL 2 (Windows Subsystem for Linux)  
- **Arquitetura:** x86_64  

---

## Passo 1 — Instalação do Mull

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
mull-runner-19 --version
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

## Passo 2 — Download do projeto e código-fonte

Após a instalação do Mull e das dependências do compilador, o próximo passo é obter o código-fonte do projeto.

Clone o repositório utilizando o Git:

```bash
git clone https://github.com/Gabrielhxavier/mull-project
cd mull-project
```
Esse repositório contém:
* O código sob teste (brake_status.c)
* A suíte de testes unitários (teste_brake_status.c)
* O arquivo de configuração do Mull (mull.yml)
* A documentação conceitual e de apoio (diretório docs/)

## Passo 3 — Clonar o framework de testes Unity

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
├── README.md
├── docs/
│   ├── configuring_mull.md
│   ├── operation_modes.md
│   ├── Mutators.rst
│   └── relatorio.md
└── unity/
    └── src/
        ├── unity.c
        └── unity.h
```

Essa estrutura é suficiente para executar os testes unitários com o Unity e realizar a instrumentação e execução do mutation testing com o Mull.

## Sistema sob Teste (SUT)

O sistema sob teste consiste em uma função que determina o estado do freio a partir de duas entradas:

- `pos` (posição do pedal do freio): valor esperado entre **0 e 100**
- `brake_switch` (sensor de acionamento): **0 (desligado)** ou **1 (ligado)**

A função retorna uma string representando o estado do sistema, por exemplo:
- `released`
- `inconclusive`
- `brake_light`
- `brake_hard`
- `brake_invalid`

> Observação: o código é propositalmente simples, pois o objetivo principal é evidenciar a técnica de mutation testing.

---

## Suíte de Testes (Unity)

Os testes unitários foram implementados utilizando o framework **Unity**, com 7 casos cobrindo:
- valores inválidos de entrada
- comportamento para freio solto (posição 0 e sensor desligado)
- condições inconclusivas
- freio leve e forte

A execução dos testes unitários serve como linha de base (baseline) antes da aplicação de mutações.

---

## Configuração do Mull (`mull.yml`)

A ferramenta Mull foi configurada através do arquivo `mull.yml`.  
Para este projeto, foram utilizados os seguintes grupos de mutadores:

- `cxx_comparison` (mutações em operadores de comparação: `<`, `>`, `<=`, `==`, etc.)
- `cxx_logical` (mutações em operadores lógicos)

Esses mutadores são adequados para o SUT, pois o código contém predominantemente condições e comparações.

Exemplo:

```yaml
mutators:
  - cxx_comparison
  - cxx_logical
```
## Execução dos testes e mutation testing
Esta seção descreve o procedimento adotado para a execução dos testes unitários e, em seguida, para a aplicação do **mutation testing** utilizando a ferramenta **Mull**.

### Testes unitários
Inicialmente, os testes unitários são compilados e executados **sem o uso do Mull**, com o objetivo de validar a suíte de testes antes da aplicação das mutações.

A compilação é realizada com o compilador Clang:

```bash
clang-19 test_brake_status.c unity/src/unity.c -o test_brake_status
```

Em seguida, os testes são executados:
```bash
./test_brake_status
```

A saída esperada indica que todos os testes foram executados com sucesso, servindo como baseline para a etapa de mutation testing.

### Compilação instrumentada e execução do mull
Para a aplicação do mutation testing, é necessário gerar um executável instrumentado com o plugin do Mull.

Primeiramente, o framework de testes Unity é compilado separadamente, sem o plugin do Mull, uma vez que não faz parte do código sob teste:
```bash
clang-19 -Iunity/src -c unity/src/unity.c -o unity.o
```
Em seguida, o arquivo de testes (que inclui o código sob teste) é compilado com o plugin de instrumentação do Mull, responsável por gerar os mutantes a partir do código:
```bash
clang-19 \
  -fpass-plugin=/usr/lib/mull-ir-frontend-19 \
  -g -grecord-command-line \
  -Iunity/src \
  -c test_brake_status.c -o test_brake_status.o
```
Após a compilação, os arquivos objeto são linkados para a geração do executável instrumentado:
```bash
clang-19 test_brake_status.o unity.o -o test_brake_status.mull
```

Por fim, o Mull é executado sobre o binário instrumentado:
```bash
mull-runner-19 ./test_brake_status.mull -ide-reporter-show-killed
```
## Resultados
A execução do Mull gera, no terminal, um relatório detalhado contendo informações sobre a geração, execução e detecção dos mutantes. A saída observada para este experimento é apresentada a seguir:
```text
[info] Warm up run (threads: 1)
       [################################] 1/1. Finished in 2ms
[info] Filter mutants (threads: 1)
       [################################] 1/1. Finished in 0ms
[info] Baseline run (threads: 1)
       [################################] 1/1. Finished in 2ms
[info] Running mutants (threads: 12)
       [################################] 13/13. Finished in 18ms
[info] Killed mutants (13/13):
/home/gabriel/brake_status/brake_status.c:4:12: warning: Killed: Replaced < with >= [cxx_lt_to_ge]
    if(pos < 0  || pos > 100)
           ^
/home/gabriel/brake_status/brake_status.c:4:24: warning: Killed: Replaced > with <= [cxx_gt_to_le]
    if(pos < 0  || pos > 100)
                       ^
/home/gabriel/brake_status/brake_status.c:9:18: warning: Killed: Replaced == with != [cxx_eq_to_ne]
    else if((pos == 0) && (brake_switch == 0))
                 ^
/home/gabriel/brake_status/brake_status.c:9:41: warning: Killed: Replaced == with != [cxx_eq_to_ne]
    else if((pos == 0) && (brake_switch == 0))
                                        ^
/home/gabriel/brake_status/brake_status.c:14:19: warning: Killed: Replaced == with != [cxx_eq_to_ne]
    else if(((pos == 0) && (brake_switch == 1)) || ((pos > 0) && (brake_switch == 0)))
                  ^
/home/gabriel/brake_status/brake_status.c:14:42: warning: Killed: Replaced == with != [cxx_eq_to_ne]
    else if(((pos == 0) && (brake_switch == 1)) || ((pos > 0) && (brake_switch == 0)))
                                         ^
/home/gabriel/brake_status/brake_status.c:14:58: warning: Killed: Replaced > with <= [cxx_gt_to_le]
    else if(((pos == 0) && (brake_switch == 1)) || ((pos > 0) && (brake_switch == 0)))
                                                         ^
/home/gabriel/brake_status/brake_status.c:14:80: warning: Killed: Replaced == with != [cxx_eq_to_ne]
    else if(((pos == 0) && (brake_switch == 1)) || ((pos > 0) && (brake_switch == 0)))
                                                                               ^
/home/gabriel/brake_status/brake_status.c:19:18: warning: Killed: Replaced > with <= [cxx_gt_to_le]
    else if((pos > 0  && pos <= 30) && (brake_switch == 1))
                 ^
/home/gabriel/brake_status/brake_status.c:19:30: warning: Killed: Replaced <= with > [cxx_le_to_gt]
    else if((pos > 0  && pos <= 30) && (brake_switch == 1))
                             ^
/home/gabriel/brake_status/brake_status.c:19:54: warning: Killed: Replaced == with != [cxx_eq_to_ne]
    else if((pos > 0  && pos <= 30) && (brake_switch == 1))
                                                     ^
/home/gabriel/brake_status/brake_status.c:24:18: warning: Killed: Replaced > with <= [cxx_gt_to_le]
    else if((pos > 30) && (brake_switch == 1))
                 ^
/home/gabriel/brake_status/brake_status.c:24:41: warning: Killed: Replaced == with != [cxx_eq_to_ne]
    else if((pos > 30) && (brake_switch == 1))
                                        ^
[info] All mutations have been killed
[info] Mutation score: 100%
[info] Total execution time: 29ms
```
O uso da opção -ide-reporter-show-killed permite que o relatório seja exibido diretamente no terminal, onde cada linha indica:
* o arquivo e linha onde a mutação foi aplicada,
* o operador original e o operador mutado,
* o tipo de mutador utilizado (por exemplo, cxx_eq_to_ne, cxx_gt_to_le).

Além disso, o relatório apresenta informações relevantes sobre:

* tempo de execução dos testes,
* número total de mutantes gerados,
* número de mutantes mortos,
* mutation score final.

## Customização e tipos de relatórios do Mull

Além da saída padrão exibida no terminal, o Mull oferece diferentes **formatos de relatório**, que permitem analisar os resultados do mutation testing em maior nível de detalhe.  
Esses relatórios são configurados por meio da opção `--reporters`, combinada com o diretório de saída definido por `--report-dir`.

---

## Relatório no terminal (IDE Reporter)

O relatório padrão do Mull é exibido diretamente no terminal.  
Para visualizar explicitamente os **mutantes mortos**, foi utilizada a opção:

```bash
mull-runner-19 ./test_brake_status.mull -ide-reporter-show-killed
```
Esse modo apresenta:
* localização exata da mutação (arquivo, linha e coluna),
* operador original e operador mutado,
* tipo de mutador aplicado,
* resumo final com mutation score e tempo de execução.
Esse formato é útil para análise rápida.


## Relatório em formato de patches
O Patch Reporter gera arquivos .patch, onde cada arquivo representa uma mutação aplicada ao código, no formato de um diff semelhante ao utilizado pelo Git.
```bash
mkdir -p patches

mull-runner-19 ./test_brake_status.mull \
  --reporters=Patches \
  --report-dir=patches
```
Após a execução, o diretório patches/ contém arquivos .patch, cada um descrevendo:
* a linha original do código,
* a mutação aplicada,
* a alteração sintática introduzida pelo mutador.

Esse tipo de relatório é especialmente útil para:
* compreender visualmente cada mutação,
* revisar mutações individualmente,
* demonstrar o impacto das mutações no código-fonte.

Exemplo de um .patch:
```text
--- a/home/gabriel/brake_status/brake_status.c 0
+++ b/home/gabriel/brake_status/brake_status.c 0
@@ -9,1 +9,1 @@
-    else if((pos == 0) && (brake_switch == 0))
+    else if((pos != 0) && (brake_switch == 0))
--
LLVM Version: 19.1.1
Mull Version: 0.27.1
URL: https://github.com/mull-project/mull

```
É possível ainda aplicar os .patch ao código fonte.
Para mais informações sobre a aplicação de patches, consulte a documentação oficial do Mull:  
https://mull.readthedocs.io/en/latest/tutorials/GeneratePatches.html

## Relatório em SQLite
O SQLite Reporter gera um banco de dados relacional contendo informações detalhadas sobre todos os mutantes e suas execuções.
```bash
mkdir -p reports

mull-runner-19 ./test_brake_status.mull \
  --reporters=SQLite \
  --report-dir=reports
```
O arquivo gerado (.sqlite dentro de reports) pode ser analisado utilizando a ferramenta sqlite3 através de queries.

Exemplo de acesso ao banco de dados:
```bash
sqlite3 reports/.sqlite
```
O banco de dados contém duas tabelas: mutant e information.

A tabela de informações armazena uma série de pares chave/valor com determinados dados sobre o Mull e a tabela de mutantes armazena o nome do operador de mutação, a localização do mutante e informações sobre a execução de cada mutante: duração, status (morto ou sobrevivente) e a saída dos testes associada a cada mutante.

### Exemplo de consultas:
#### Selecionar todas as linhas da tabela mutant:
```bash
.headers on
```
```bash
.mode column
```
```bash
SELECT * FROM mutant;
```
Saída esperada (primeira linha):
```text
mutant_id                                                     mutator       filename                                   directory  line_number  column_number  end_line_number  end_column_number  status  duration  stdout                                                        stderr
------------------------------------------------------------  ------------  -----------------------------------------  ---------  -----------  -------------  ---------------  -----------------  ------  --------  ------------------------------------------------------------  ------
cxx_lt_to_ge:/home/gabriel/brake_status/brake_status.c:4:12:  cxx_lt_to_ge  /home/gabriel/brake_status/brake_status.c             4            12             4                13                 1       4         test_brake_status.c:46:test_invalid1:PASS
4:13                                                                                                                                                                                                                test_brake_status.c:47:test_invalid2:PASS
                                                                                                                                                                                                                    test_brake_status.c:19:test_released:FAIL: Expected 'release
                                                                                                                                                                                                                    d' Was 'brake_invalid'
                                                                                                                                                                                                                    test_brake_status.c:24:test_inconclusive1:FAIL: Expected 'in
                                                                                                                                                                                                                    conclusive' Was 'brake_invalid'
                                                                                                                                                                                                                    test_brake_status.c:29:test_inconclusive2:FAIL: Expected 'in
                                                                                                                                                                                                                    conclusive' Was 'brake_invalid'
                                                                                                                                                                                                                    test_brake_status.c:34:test_light:FAIL: Expected 'brake_ligh
                                                                                                                                                                                                                    t' Was 'brake_invalid'
                                                                                                                                                                                                                    test_brake_status.c:39:test_hard:FAIL: Expected 'brake_hard'
                                                                                                                                                                                                                     Was 'brake_invalid'
```
O campo `status` armazena um valor numérico, cujo significado é descrito na tabela a seguir:

| Valor numérico | Valor textual   | Descrição                                                                 |
|---------------|-----------------|---------------------------------------------------------------------------|
| 1             | Failed          | O teste falhou (o código de saída é diferente de 0).                      |
| 2             | Passed          | O teste foi executado com sucesso (o código de saída é igual a 0).        |
| 3             | Timedout        | A execução do teste excedeu o tempo máximo permitido.                     |
| 4             | Crashed         | O programa de teste foi finalizado de forma abrupta (crash).              |
| 5             | AbnormalExit    | O programa de teste foi encerrado explicitamente (por exemplo, `exit(1)`).|
| 6             | DryRun          | O teste não foi executado (modo *Dry Run* habilitado).                    |
| 7             | FailFast        | O mutante já foi morto por outro teste, portanto esta execução foi ignorada.|

#### Quantidade de mutantes por tipo:
```bash
SELECT mutator, COUNT(*) 
FROM mutant 
GROUP BY mutator;
```
#### Resumo do status dos mutantes:
```bash
SELECT status, COUNT(*) 
FROM mutant 
GROUP BY status;
```
## MutationTestingElementsReporter:
 **MutationTestingElementsReporter** gera um relatório em **formato JSON**, compatível com o padrão **Mutation Testing Elements (MTE)**.

Esse padrão define uma **estrutura comum de dados** para resultados de mutation testing, permitindo que diferentes ferramentas e plataformas consumam e processem os resultados de forma padronizada.

Entretanto, na versão do Mull utilizada neste projeto (Mull 19), esse reporter não está disponível.

Para mais informações, consulte:  
[https://mull.readthedocs.io/en/latest/tutorials/GeneratePatches.html](https://github.com/stryker-mutator/mutation-testing-elements)

## Junção e uso combinado de relatórios de mutação

O Mull permite a geração de diferentes tipos de relatórios a partir de uma mesma execução de mutation testing:

```bash
mull-runner-19 ./test_brake_status.mull \
  --reporters=IDE \
  --reporters=Patches \
  --report-dir=patches \
  -ide-reporter-show-killed

```
## Conceitos adicionais do Mull

Esta seção tem como objetivo apresentar conceitos importantes do Mull que influenciam diretamente seu uso e configuração. 
Para evitar a sobrecarga deste relatório principal, esses tópicos foram documentados de forma separada, em arquivos específicos, disponíveis no diretório `docs/`.

Os tópicos abordados incluem os operadores de mutação suportados, as formas de configuração do Mull e as ferramentas de build com as quais o Mull pode ser integrado.

### Operadores de mutação suportados

O Mull oferece suporte a diversos operadores de mutação, responsáveis por modificar expressões aritméticas, lógicas, comparações e outras construções do código-fonte.

A descrição detalhada dos operadores suportados, juntamente com exemplos, pode ser encontrada no documento:

[`docs/Mutators.rst`](./Mutators.rst)

### Configuração do Mull

O Mull permite configurar quais operadores de mutação serão utilizados, além de definir filtros de arquivos e outras opções por meio do arquivo `mull.yml`.

As opções de configuração e exemplos práticos estão documentados em:

[`docs/configuring_mull.md`](./configuring_mull.md)

### Modos de operação do Mull

O Mull pode ser usado em diferentes modos de operação: standalone e integrado a ferramentas de build.

Os modos de operação do Mull são apresentados de forma mais detalhada em:

[`docs/operation_modes.md`](./operation_modes.md)

## Considerações finais
Os tópicos apresentados neste relatório foram elaborados com base na documentação oficial do Mull.
Para aprofundar o conhecimento e explorar funcionalidades adicionais, recomenda-se consultar diretamente a documentação oficial, disponível nos seguintes canais:
- Repositório GitHub: https://github.com/mull-project/mull
- Documentação online: https://mull.readthedocs.io/en/latest


