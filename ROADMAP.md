# Executor Roadmap

## Estado atual

- **Lexer**: implementado (`set_tokens` + `get_token_len` funcionais)
- **Parser**: implementado — retorna `t_ast_node *ast` com comandos e pipes
- **Executor**: executa comandos simples via `fork` + `execve` com resolução de PATH
- **Redirections**: `setup_redirections()` implementado (`<`, `>`, `>>`) com error handling; heredoc como stub; integrado no executor
- **Pipes**: stub vazio em `pipes.c`
- **Builtins**: stubs vazios (assinaturas corrigidas para `t_shelly`)
- **Signals**: stub vazio em `signals.c`

---

## Etapa 1 — Corrigir assinaturas e struct base ✅

- [x] Corrigir assinatura em `executor.c`, `pipes.c` e `redirections.c` de `t_cmd *cmd` para `t_ast_node *ast`
- [x] Adicionar `last_exit_status` e `suppress_output` na struct `t_shelly`
- [x] Atualizar `main.c` para capturar o retorno do executor e salvar em `shelly.last_exit_status`

---

## Etapa 2 — Executar comando externo simples ✅

- [x] `find_path()` — extrair e splitar `PATH` do `envp`
- [x] `find_command()` — resolver caminho absoluto do executável (busca em PATH + caminhos absolutos)
- [x] `executor()` — `fork()` → `execve()` no filho, `waitpid()` no pai

---

## Etapa 3 — Implementar redirections

**Resultado esperado**: `cat < input.txt`, `echo hello > out.txt`, `echo hello >> out.txt` funcionando.

### 3.1 — Implementar `setup_redirections()` em `redirections.c` ✅

- [x] `TOKEN_REDIR_IN` (`<`): `open` + `dup2(fd, STDIN_FILENO)` + `close`
- [x] `TOKEN_REDIR_OUT` (`>`): `open(O_TRUNC)` + `dup2(fd, STDOUT_FILENO)` + `close`
- [x] `TOKEN_APPEND` (`>>`): `open(O_APPEND)` + `dup2(fd, STDOUT_FILENO)` + `close`
- [x] `TOKEN_HEREDOC` (`<<`): implementado com arquivo temporário (`/tmp/.shelly_heredoc`), leitura via `get_next_line` antes do `fork`
- [x] Tratar erros: `perror` + retorno `-1` se `open()` falhar

### 3.2 — Alterar assinatura de `setup_redirections()` ✅

- [x] Assinatura: `int setup_redirections(t_redir *redir)` — retorna `0` sucesso, `-1` erro
- [x] Protótipo atualizado em `minishell.h`

### 3.3 — Integrar no `executor()` ✅

- [x] Chamar `setup_redirections(ast->value.command->redir)` no filho, antes do `execve()`
- [x] Se retornar erro, `exit(1)` no filho

### 3.4 — Testes manuais

- [ ] `echo hello > /tmp/test_out.txt` → arquivo criado com "hello"
- [ ] `cat < /tmp/test_out.txt` → imprime "hello"
- [ ] `echo world >> /tmp/test_out.txt` → arquivo contém "hello\nworld"
- [ ] `cat < arquivo_inexistente` → mensagem de erro, exit status != 0

---

## Etapa 4 — Implementar pipes

**Resultado esperado**: `ls | grep .c | wc -l` funcionando.

- [ ] Implementar `execute_pipes()` em `pipes.c`:
  - Verificar `ast->node_type == TOKEN_PIPE`
  - Criar `pipe(fd)` para conectar esquerda → direita
  - `fork()` filho esquerdo: `dup2(fd[1], STDOUT_FILENO)`, executar `ast->value.pipe->left`
  - `fork()` filho direito: `dup2(fd[0], STDIN_FILENO)`, executar `ast->value.pipe->right`
  - Fechar `fd[0]` e `fd[1]` no pai
  - `waitpid()` para ambos os filhos, retornar status do último (direito)
- [ ] Suportar pipes encadeados (recursão: se `right` for outro `TOKEN_PIPE`)
- [ ] Integrar com redirections: chamar `setup_redirections()` em cada filho antes do `execve`
- [x] Atualizar `executor()` para despachar: se `node_type == TOKEN_PIPE` → `exec_pipe()`, senão → `exec_simple_command()`

---

## Etapa 5 — Builtins

Builtins rodam no processo atual (sem `fork`), exceto dentro de pipeline.

- [x] Corrigir tipos nos stubs: trocar `t_shell` → `t_shelly`, remover `t_env` (usar `char **envp`)
- [ ] Criar função `is_builtin(char *cmd)` que retorna `1` se for builtin
- [ ] No `executor()`: se `is_builtin()`, executar direto sem fork
- [ ] Implementar cada builtin:
  - [ ] `echo` — com flag `-n`
  - [ ] `cd` — `chdir()` + atualizar `PWD`/`OLDPWD` no envp
  - [ ] `pwd` — `getcwd()` + imprimir
  - [ ] `env` — iterar e imprimir `shelly.envp`
  - [ ] `export` — adicionar/atualizar variável em `shelly.envp`
  - [ ] `unset` — remover variável de `shelly.envp`
  - [ ] `exit` — `exit()` com código correto, liberar memória

---

## Etapa 6 — Signals

- [ ] Loop principal (sem filho rodando):
  - `SIGINT` → nova linha, limpar input, `last_exit_status = 130`
  - `SIGQUIT` → `SIG_IGN`
- [ ] Durante execução de filho:
  - `SIGINT` → esperar filho morrer, `last_exit_status = 130`
  - `SIGQUIT` → esperar filho morrer, imprimir `Quit (core dumped)`, `last_exit_status = 131`
- [ ] Durante heredoc:
  - `SIGINT` → cancelar heredoc, voltar ao prompt

---

## Referência rápida das structs (conforme `minishell.h`)

```c
typedef struct s_shelly
{
    char    **envp;
    char    **argv;
    int     last_exit_status;
    t_bool  suppress_output;
}   t_shelly;

typedef struct s_redir
{
    t_token_type    type;       // TOKEN_REDIR_IN, TOKEN_REDIR_OUT, TOKEN_APPEND, TOKEN_HEREDOC
    char            *filename;  // arquivo alvo (ou delimitador no heredoc)
    struct s_redir  *next;      // próximo redirection
}   t_redir;

typedef struct s_command
{
    char    **cmd;    // ex: ["echo", "hello", NULL]
    t_redir *redir;   // lista encadeada de redirections
}   t_command;

typedef struct s_pipe
{
    t_ast_node  *left;
    t_ast_node  *right;
}   t_pipe;

typedef struct s_ast_node
{
    t_token_type        node_type;   // TOKEN_WORD ou TOKEN_PIPE
    union u_node_value  value;       // .command ou .pipe
}   t_ast_node;
```
