# 🌳 Roadmap: Implementação da AST (Árvore Binária)

## Contexto

No minishell, a AST (Abstract Syntax Tree) representa a hierarquia de um comando.
Nodes internos são **operadores** (`|`, redirections) e as **folhas** são os comandos com seus argumentos.

```
    PIPE
   /    \
 CMD    CMD
echo   cat file.txt
 |
 └── args: ["echo", "hello", NULL]
```

O `parser` produz a AST a partir dos tokens gerados pelo `lexer`.
O `executor` consome a AST para executar os comandos.

---

## Tasks

### TASK 1 — Definir os tipos e a struct `t_ast_node` no header

**Arquivo:** `minishell.h`

- [ ] Adicionar enum `t_node_type` com os valores:
  - `NODE_CMD` — folha: representa um comando com seus argumentos
  - `NODE_PIPE` — operador `|`
  - `NODE_REDIR_IN` — redirecionamento `<`
  - `NODE_REDIR_OUT` — redirecionamento `>`
  - `NODE_APPEND` — redirecionamento `>>`
  - `NODE_HEREDOC` — redirecionamento `<<`
- [ ] Adicionar struct `t_ast_node` com os campos:
  - `t_node_type type`
  - `struct s_ast_node *left`
  - `struct s_ast_node *right`
  - `char **args` (usado em `NODE_CMD`)
  - `char *file` (usado em nodes de redirecionamento)
- [ ] Declarar os protótipos das funções da AST no header

> **Critério de aceite:** O projeto compila sem erros com as novas definições.

---

### TASK 2 — Implementar criação de nodes em `src/parsing/ast.c`

**Arquivo novo:** `src/parsing/ast.c`

- [ ] Implementar `t_ast_node *ast_new_node(t_node_type type)` — aloca e inicializa um node zerado
- [ ] Implementar `t_ast_node *ast_new_cmd(char **args)` — cria um node folha com os argumentos do comando
- [ ] Implementar `t_ast_node *ast_new_op(t_node_type type, t_ast_node *left, t_ast_node *right)` — cria um node operador com filhos esquerdo e direito
- [ ] Adicionar `src/parsing/ast.c` ao `Makefile`

> **Critério de aceite:** Funções retornam `NULL` em falha de alocação; nodes são alocados e inicializados corretamente.

---

### TASK 3 — Implementar liberação recursiva da AST

**Arquivo:** `src/utils/cleanup.c`

- [ ] Implementar `void ast_free(t_ast_node *node)` com traversal em **pós-ordem** (libera filhos antes do pai)
- [ ] Garantir guard para `node == NULL` (não crasha com árvore vazia)
- [ ] Liberar `node->args` (array de strings) e `node->file` quando existirem
- [ ] Verificar ausência de leaks com `valgrind --leak-check=full`

> **Critério de aceite:** Valgrind não reporta leaks ao criar e destruir uma árvore completa.

---

### TASK 4 — Escrever testes unitários para a AST

**Arquivo:** `tests/test-ast.c`

- [ ] Teste: `ast_new_cmd` com args válidos — verifica se `node->args[0]` está correto e `type == NODE_CMD`
- [ ] Teste: `ast_new_op` — verifica se `left` e `right` são atribuídos corretamente e `type` bate com o esperado
- [ ] Teste: `ast_new_node` — verifica se `left`, `right`, `args` e `file` iniciam como `NULL`
- [ ] Teste: `ast_free(NULL)` — verifica que não crasha (guard obrigatório)
- [ ] Adicionar `test-ast.c` ao `tests/makefile`

> **Critério de aceite:** Todos os testes passam com `make unit-tests`.

---

### TASK 5 — Implementar o parser recursivo descendente

**Arquivo:** `src/parsing/parser.c`

- [ ] Implementar `t_ast_node *parse_pipeline(t_token **tok)` — consome `TOKEN_PIPE` e chama `parse_command` para cada lado
- [ ] Implementar `t_ast_node *parse_command(t_token **tok)` — consome `TOKEN_WORD` em sequência e monta `NODE_CMD`
- [ ] Tratar redirections dentro de `parse_command` — ao encontrar `TOKEN_REDIR_*`, cria node de redirecionamento e encapsula o comando como filho
- [ ] Retornar `NULL` e limpar memória em caso de erro de sintaxe

> **Critério de aceite:** `echo hello | cat` gera uma AST com `NODE_PIPE` na raiz e `NODE_CMD` como filhos esquerdo e direito.

---

### TASK 6 — Integrar a AST no fluxo principal

**Arquivo:** `src/main.c`

- [ ] Chamar `lexer(line)` → `t_token *tokens`
- [ ] Chamar `parser(tokens)` → `t_ast_node *ast` (substituindo o atual `t_cmd *`)
- [ ] Passar a AST para `executor(ast, &shelly)`
- [ ] Chamar `ast_free(ast)` e `free_tokens(tokens)` no cleanup do loop
- [ ] Garantir que `free_tokens` existe em `src/utils/cleanup.c`

> **Critério de aceite:** O loop do shell compila e executa sem crashes com entradas simples.

---

### TASK 7 — Atualizar o executor para traversal da AST

**Arquivo:** `src/execution/executor.c`

- [ ] Implementar traversal recursivo com base em `node->type`
- [ ] Caso `NODE_CMD` → verificar se é builtin; se não, usar `execve`
- [ ] Caso `NODE_PIPE` → `fork()` + `pipe()`, filho esquerdo escreve, filho direito lê
- [ ] Caso `NODE_REDIR_*` → configurar FDs com `open()` / `dup2()` antes de executar o filho
- [ ] Fechar todos os FDs abertos após uso

> **Critério de aceite:** `echo hello | cat` e `echo hello > out.txt` executam corretamente no shell.

---

## Ordem de execução

```
TASK 1 (struct)
  → TASK 2 (criação de nodes)
    → TASK 3 (free recursivo)
      → TASK 4 (testes unitários)
        → TASK 5 (parser)
          → TASK 6 (integração main)
            → TASK 7 (executor)
```
