## Configuração do Mull

O Mull é configurado por meio de um arquivo de texto no formato **YAML**, denominado `mull.yml`.  
Por padrão, o Mull procura esse arquivo no **diretório atual de execução**.

Esse arquivo permite definir quais operadores de mutação serão utilizados, além de configurar filtros de arquivos, tempo limite de execução e opções de log.

### Exemplo de configuração:
```bash
mutators:
 - cxx_add_to_sub
 - cxx_logical
excludePaths: # support regex
 - gtest
 - gmock
timeout: # milliseconds
 - 10000 # 10 seconds
quiet: false # enables additional logging
```

### Seleção de operadores de mutação
Dessa forma, selecionar os operadores de mutação no Mutation Testing se torna uma tarefa simples, basta modificar o `mutators` no arquivo `mull.yml` e adicionar os operadores.

Os operadores podem ser definidos de três formas distintas:

#### Utilizando grupos de operadores
É possível selecionar grupos de mutadores, que englobam diversos operadores relacionados:
```bash
mutators:
 - cxx_arithmetic
 - cxx_bitwise
```
#### Utilizando operadores individuais
Também é possível definir explicitamente os operadores desejados:
```bash
mutators:
 - cxx_add_assign_to_sub_assign
 - cxx_and_to_or
```

#### Combinação de grupos e operadores individuais
Pode-se ainda mesclar grupos e operadores específicos na mesma configuração:
```bash
mutators:
  - cxx_arithmetic
  - cxx_logical
  - cxx_add_assign_to_sub_assign
```
---
Source: https://mull.readthedocs.io/en/latest/MullConfig.html
