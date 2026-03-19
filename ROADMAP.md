# Executor Roadmap

## Estado atual

- Lexer: implementado
- Parser: implementado — retorna `t_ast_node *`
- Executor: stubs vazios com tipos errados (`t_cmd *` não existe)
- Builtins: stubs vazios
- Signals: vazio

---

## Etapa 1 — Corrigir base antes de executar qualquer coisa

- [ ] Corrigir assinatura em `executor.c`, `pipes.c` e `redirections.c` de `t_cmd *cmd` para `t_ast_node *ast`
- [ ] Adicionar `last_exit_status` na struct `t_shell` em `minishell.h`

```c
typedef struct s_shely
{
    char    **envp;
    char    **argv;
    int     last_exit_status;
}   t_shell;
```

- [ ] Atualizar `main.c` para capturar o retorno do executor e salvar em `shelly.last_exit_status`

---

## Etapa 2 — Executar um comando simples

Objetivo: `ls` ou `echo hello` funcionando.

- [ ] Implementar resolução de PATH em `src/utils/` — busca o executável nas entradas de `PATH` no `envp`
- [ ] Implementar execução de comando simples em `executor.c`:
  - `fork()`
  - No filho: `execve(path, cmd->cmd, shell->envp)`
  - No pai: `waitpid()` e salvar exit status

Resultado esperado: comandos externos simples funcionando no terminal.

---

## Etapa 3 — Redirections

Objetivo: `cat < input.txt` e `echo hello > out.txt` funcionando.

- [ ] Implementar `setup_redirections()` em `redirections.c`:
  - `TOKEN_REDIR_IN` → `open()` + `dup2(fd, STDIN_FILENO)`
  - `TOKEN_REDIR_OUT` → `open()` + `dup2(fd, STDOUT_FILENO)`
  - `TOKEN_APPEND` → `open()` com `O_APPEND` + `dup2(fd, STDOUT_FILENO)`
  - `TOKEN_HEREDOC` → escrever em pipe + `dup2(fd[0], STDIN_FILENO)`
- [ ] Chamar `setup_redirections()` dentro do processo filho antes do `execve`

---

## Etapa 4 — Pipes

Objetivo: `ls | grep .c | wc -l` funcionando.

- [ ] Implementar `execute_pipes()` em `pipes.c`:
  - Percorrer a árvore recursivamente (nó `TOKEN_PIPE` tem `left` e `right`)
  - Criar pipe com `pipe()`
  - `fork()` para cada lado
  - Conectar `stdout` do filho esquerdo ao `stdin` do filho direito com `dup2()`
  - Fechar file descriptors não usados
  - Aguardar todos os filhos com `waitpid()`
- [ ] Integrar com redirections (redirections têm prioridade sobre o pipe)

---

## Etapa 5 — Builtins

Builtins rodam no processo atual (sem `fork`), exceto em pipeline.

- [ ] Detectar se o comando é builtin antes do `fork`
- [ ] Implementar cada builtin:
  - [ ] `echo` — com suporte a `-n`
  - [ ] `cd` — atualizar `PWD` e `OLDPWD` no `envp`
  - [ ] `pwd` — imprimir diretório atual
  - [ ] `env` — listar variáveis de ambiente
  - [ ] `export` — adicionar/atualizar variável no `envp`
  - [ ] `unset` — remover variável do `envp`
  - [ ] `exit` — sair com código correto

> `cd`, `export` e `unset` precisam modificar o `envp` — o `t_shell` precisa de uma cópia própria do envp (não apontar direto pro envp do main).

---

## Etapa 6 — Signals

- [ ] Implementar handlers em `src/utils/signals.c`
- [ ] No loop principal (sem filho rodando):
  - `SIGINT` → nova linha, limpar input, exit status 130
  - `SIGQUIT` → ignorar
- [ ] Durante execução de filho:
  - `SIGINT` → matar filho, salvar exit status 130
  - `SIGQUIT` → matar filho, imprimir `Quit (core dumped)`, exit status 131
- [ ] Durante heredoc:
  - `SIGINT` → cancelar heredoc

---

## Referência rápida das structs

```c
// Nó da AST — output do parser
typedef struct s_ast_node
{
    t_token_type        node_type;   // TOKEN_WORD ou TOKEN_PIPE
    union u_node_value  value;       // .command ou .pipe
}   t_ast_node;

// Comando simples
typedef struct s_command
{
    char    **cmd;    // ex: ["echo", "hello", NULL]
    t_redir *redir;   // lista de redirections
}   t_command;

// Pipe — dois lados da árvore
typedef struct s_pipe
{
    t_ast_node  *left;
    t_ast_node  *right;
}   t_pipe;
```
