
# GraphSocial

## Visao Geral do Projeto
 - Projeto criado originalmente no sistema operacional de distribuição Linux -> Ubuntu 22.04 (LTS).


 - Projeto de Estrutura de Dados II.
Universidade de Passo Fundo (UPF)


## Instalação

### Para iniciar o projeto, deve ser instalado (LINUX):
#### Realizar atualizações dos pacotes (Sempre uma boa prática):
    sudo apt update && sudo apt upgrade

#### BUILD-ESSENTIAL (Caso não possua):
    sudo apt install build-essential

#### Biblioteca SQLITE3:
    sudo apt install sqlite3

#### Biblioteca LIBSQLITE3-DEV:
    sudo apt install libsqlite3-dev



#### Para melhor visualização de dados, adicionar a extensão SQLite Viewer (VSCode)
![image](https://github.com/lucasfriedrichh/GraphSocial/assets/91904246/ef317c9e-3af7-45c6-a47a-fa741dca5b7e)

![image](https://github.com/lucasfriedrichh/GraphSocial/assets/91904246/d5aaf3d3-76fb-40d8-8588-e991ea0d5f87)



## Demonstração
### Para gerar o executável do projeto usar o comando:
    g++ main.cpp -o 'GraphSocial' -lsqlite3 -Wall

### Apos a geração do executável, use o seguinte comando para iniciar o programa:
    ./'GraphSocial'

### Assim que iniciar o programa, será executado no teminal, mostrando as possíveis ações do usuário:

![image](https://github.com/lucasfriedrichh/GraphSocial/assets/91904246/e49d51de-926c-472a-9805-1f80dc417c1b)

 #### 1. Cadastro de usuários:

![image](https://github.com/lucasfriedrichh/GraphSocial/assets/91904246/573812a1-1efc-40b9-848e-6621a1070c33)

 - Apos cadastrar o usuário, seguindo o cadastro, sera confirmado se o usuário foi cadastrado com sucesso. Dando boas vindas e mostrando as demais funcionalidades.

#### 2. Seguir usuários:
![image](https://github.com/lucasfriedrichh/GraphSocial/assets/91904246/bbdf31b2-aadd-40f0-b43d-b471b03ed9f5)

#### 3. Deixar de seguir usuários:

![image](https://github.com/lucasfriedrichh/GraphSocial/assets/91904246/15b0004c-15cc-423f-84ec-5d9f91c67734)

#### 4. Listar usuários:
![image](https://github.com/lucasfriedrichh/GraphSocial/assets/91904246/83f432c6-2975-4ab7-bb6a-9fcf9ecf9bb2)

#### 5. Consultar dados do usuário:
![image](https://github.com/lucasfriedrichh/GraphSocial/assets/91904246/63768c3a-36ff-40b0-b5e9-90bcecec67a2)

#### 6. Excluir usuário:
![image](https://github.com/lucasfriedrichh/GraphSocial/assets/91904246/00ec9158-ce47-47e7-854a-d10345895fcc)

#### 7. Verificar caminho entre 2 usuários (Calcula o menor caminho usando dijkstra):
![image](https://github.com/lucasfriedrichh/GraphSocial/assets/91904246/79902b15-9232-404a-8fca-53bc29650b6e)

#### 8. Exportar rede:
![image](https://github.com/lucasfriedrichh/GraphSocial/assets/91904246/1a11a1a9-2298-4ebf-971e-13ef2872d1b4)

#### 9. Exibir informações da rede:
![image](https://github.com/lucasfriedrichh/GraphSocial/assets/91904246/7822bf25-74b8-45c1-9e4e-0d403da99598)

#### 0. Sair:
Finaliza o programa.


## Autores

- [@GuiTaglietti](https://www.github.com/GuiTaglietti)
- [@LucasFriedrich](https://www.github.com/lucasfriedrichh)
- [@JosePRP1](https://www.github.com/josePRP1)


## Aprendizados

Aprofundamento avançado no paradigma orientado a objetos em C++ (Headers, include guards, sobrecarga/remoção de operadores, tipos abstratos, herança, singleton, namespaces, rule of three e entre outros...);

Aprofundamento em algoritmos de grafos/árvores (entre outras estruturas de dados presentes no projeto) para melhor funcionamento da aplicação;
