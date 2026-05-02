# Executor Roadmap

## Estado atual

- **Lexer**: implementado (`set_tokens` + `get_token_len`) — sem detecção de aspas não fechadas
- **Parser**: implementado — retorna `t_ast_node *ast` com comandos e pipes
- **Expander**: implementado — expansão de tilde, variáveis (`$VAR`, `$?`), remoção de aspas e word splitting
- **Executor**: executa comandos simples via `fork` + `execve` com resolução de PATH
- **Redirections**: `setup_redirections()` (`<`, `>`, `>>`) + heredoc com arquivo temporário
- **Pipes**: `exec_pipe()` recursivo com encadeamento, integrado a redirections e builtins
- **Builtins**: todos os 7 implementados (`echo`, `cd`, `pwd`, `env`, `export`, `unset`, `exit`)
- **Signals**: stub vazio em `signals.c`
- **Free**: AST, redir, env_list, tokens e arrays liberados; `free-expander.c` e `free-shelly.c` ainda vazios
- **Sanitize**: target `make sanitize` com `-fsanitize=address`

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
- [x] `get_status_code()` converte `WIFEXITED`/`WIFSIGNALED` (128+sig) corretamente

---

## Etapa 3 — Implementar redirections ⚠️

**Resultado esperado**: `cat < input.txt`, `echo hello > out.txt`, `echo hello >> out.txt` funcionando.

### 3.1 — `setup_redirections()` em `redirections.c` ✅

- [x] `TOKEN_REDIR_IN` (`<`): `open` + `dup2(fd, STDIN_FILENO)` + `close`
- [x] `TOKEN_REDIR_OUT` (`>`): `open(O_TRUNC)` + `dup2(fd, STDOUT_FILENO)` + `close`
- [x] `TOKEN_APPEND` (`>>`): `open(O_APPEND)` + `dup2(fd, STDOUT_FILENO)` + `close`
- [x] `TOKEN_HEREDOC` (`<<`): arquivo temporário (`/tmp/.shelly_heredoc`), leitura via `get_next_line` antes do `fork`
- [x] Tratar erros: `perror` + retorno `-1` se `open()` falhar

### 3.2 — Assinatura e integração ✅

- [x] Assinatura: `int setup_redirections(t_redir *redir)` — retorna `0` sucesso, `-1` erro
- [x] Integrado em `exec_simple_command()` e `exec_pipe_command()`

### 3.3 — Pendências de comportamento

- [ ] **Heredoc com delimitador entre aspas** não desabilita expansão de variáveis (regra do bash: `<< 'EOF'` ⇒ não expande). Hoje todo conteúdo de heredoc é tratado como unquoted.
- [ ] **`SIGINT` durante heredoc** não cancela a leitura nem volta ao prompt
- [ ] **Nome único de arquivo temporário** — `/tmp/.shelly_heredoc` é fixo, colisão entre múltiplos heredocs em pipeline (`cmd1 << A | cmd2 << B`)
- [ ] Limpar (`unlink`) o arquivo temporário do heredoc após uso
- [ ] Erro do tipo `cat < arquivo_inexistente`: confirmar exit status `1` e mensagem alinhada com bash

### 3.4 — Testes manuais

- [ ] `echo hello > /tmp/test_out.txt` → arquivo criado com "hello"
- [ ] `cat < /tmp/test_out.txt` → imprime "hello"
- [ ] `echo world >> /tmp/test_out.txt` → arquivo contém "hello\nworld"
- [ ] `cat < arquivo_inexistente` → mensagem de erro, exit status != 0
- [ ] `cat << 'EOF'` ... `$USER` ... `EOF` → não deve expandir `$USER`

---

## Etapa 4 — Implementar pipes ✅

**Resultado esperado**: `ls | grep .c | wc -l` funcionando.

- [x] `exec_pipe()` em `pipes.c`
- [x] Pipes encadeados (recursão sobre `right` quando é outro `TOKEN_PIPE`)
- [x] Integração com redirections em `exec_pipe_command()`
- [x] Builtins forkados dentro do pipeline (saem via `exit(builtin_ret)`)
- [x] Despacho em `executor()`: `TOKEN_PIPE` → `exec_pipe()`, senão → `exec_simple_command()`

---

## Etapa 4.5 — Refatoração do executor (norma 42: max 25 linhas) ✅

- [x] `heredoc.c` — `check_here_doc()`, `read_and_write_here_doc()`, `set_here_doc_fd()`
- [x] `pipes.c` — `exec_pipe()` e `exec_pipe_command()`
- [x] `executor.c` / `executor_utils.c` — `find_path()`, `find_command()`, `exec_simple_command()`, `executor()`
- [x] Makefile e protótipos atualizados
- [x] Funções >25 linhas extraídas (`simple_command_routine`, `exec_simple_pipe_left`)

---

## Etapa 4.8 — Expander ✅

- [x] FSM de 3 estados (`NORMAL`, `SINGLE_QUOTE`, `DOUBLE_QUOTE`) via flags de aspas no token
- [x] Remoção de aspas (`remove_quotes.c`)
- [x] Tilde expansion (`tilde_expansion.c`) — `~` e `~/path`
- [x] Variable expansion (`variable_expansion.c`) — `$VAR`, `$?`
- [x] Word splitting de tokens não-quoted com espaço
- [x] `expand_ast()` chamado em `main.c` antes do parser/executor
- [x] Não expande delimitador de heredoc (literal)

---

## Etapa 4.9 — Free / Memória

### 4.9.1 — AST e tokens ✅

- [x] `free_redir()`, `free_tree()`, `free_env_list()`, `clear_token_list()`, `ft_free_array()`
- [x] `main` libera AST e tokens a cada iteração

### 4.9.2 — Executor ✅

- [x] `find_path()` corrigido (sem leak do `ft_split`)
- [x] `find_command()` libera path array e strings intermediárias
- [x] `exec_simple_command()` libera `command_line` após `waitpid()`
- [x] Removido `free(shelly.envp)` indevido na main

### 4.9.3 — Sanitize ✅

- [x] Target `make sanitize` com `-fsanitize=address`

### 4.9.4 — Pendentes

- [ ] **`free-expander.c` está vazio** — implementar liberação de strings intermediárias do expander
- [ ] **`free-shelly.c` está vazio** — liberação completa da `t_shelly` (env_list, argv) no encerramento
- [ ] **Bug em `exit` builtin** (`exit.c:41`) — `ft_free_array(args)` libera ponteiros que ainda pertencem à AST; remover ou substituir por liberação consistente
- [ ] Auditar uso de `ft_strjoin_and_free` / `ft_strjoin_char_and_free` no expander para confirmar zero leaks
- [ ] Garantir `unlink` do arquivo de heredoc ao final da execução (vazamento de FS)

---

## Etapa 5 — Builtins ✅ (com bugs)

Builtins rodam no processo atual (sem `fork`), exceto dentro de pipeline (já correto).

### 5.1 — Implementados

- [x] `is_builtin()` / dispatcher em `execute_builtin.c`
- [x] `echo` — flag `-n`
- [x] `cd` — sem args (HOME), `-` (OLDPWD), atualiza `PWD`/`OLDPWD`
- [x] `pwd` — `getcwd()` + `printf`
- [x] `env` — itera `env_list`
- [x] `export` — sem args (saída ordenada), com `KEY=VALUE`, valida identificador
- [x] `unset` — remove e valida identificador
- [x] `exit` — sem args (`last_exit_status`), com N (mascara 0–255), erro em arg não numérico

### 5.2 — Pendências e bugs

- [ ] **`exit` libera `args` da AST** (`exit.c:41`) — risco de double-free quando AST for liberada depois
- [ ] **`cd`** com `~` deve já estar coberto pelo expander; testar `cd ~` e `cd ~/Documents`
- [ ] **`export`** sem `=` (apenas `export VAR`) — confirmar comportamento (marca como exportada sem valor)
- [ ] **`exit` com argumento numérico fora de 0–255** — bash retorna o valor mod 256; verificar
- [ ] **`exit` com argumento não numérico** — deve imprimir `numeric argument required` e sair com 2
- [ ] **`exit` com >1 arg numérico** — não deve sair, retorna 1 e imprime `too many arguments`
- [ ] **Builtins em pipeline** — confirmar que `exit` em pipeline NÃO encerra o shell pai

---

## Etapa 6 — Signals ❌ (não iniciado)

`src/utils/signals.c` é stub vazio. Nenhum handler instalado.

### 6.1 — Loop principal (sem filho rodando)

- [ ] `SIGINT` (Ctrl+C) → nova linha + reescreve prompt; `last_exit_status = 130`
- [ ] `SIGQUIT` (Ctrl+\) → `SIG_IGN`
- [ ] Instalar handlers em `setup_signals()` chamado no início do `main`

### 6.2 — Durante execução de filho

- [ ] Pai ignora `SIGINT`/`SIGQUIT`; deixa o filho receber via terminal
- [ ] Após `waitpid`, exit status já é convertido por `WIFSIGNALED` (`get_status_code` ok)
- [ ] Após `SIGINT` no filho: imprimir `\n`, `last_exit_status = 130`
- [ ] Após `SIGQUIT` no filho: imprimir `Quit (core dumped)`, `last_exit_status = 131`

### 6.3 — Durante heredoc

- [ ] `SIGINT` cancela leitura, fecha fd, descarta arquivo temporário, volta ao prompt com status 130
- [ ] Restaurar handlers do shell após heredoc

---

## Etapa 7 — Erros sintáticos e edge cases ❌

### 7.1 — Lexer / Parser

- [ ] **Aspas não fechadas** (`echo "abc`) — hoje `get_token_len.c:34-35` lê além do `\0`. Detectar e retornar erro de sintaxe (status 2).
- [ ] **Pipe inicial/final** (`| ls`, `ls |`) — erro `syntax error near unexpected token`
- [ ] **Pipes consecutivos** (`ls || cat`)
- [ ] **Redirect sem alvo** (`echo >`, `cat <`) — `syntax error near unexpected token 'newline'`
- [ ] Mensagens alinhadas ao formato do bash

### 7.2 — Execução

- [ ] **Comando não encontrado** → exit status `127` + mensagem `command not found`
- [ ] **Permission denied** (`./arquivo_sem_x`) → exit status `126`
- [ ] Distinguir 126 vs 127 em `handle_error()` (hoje retorna 127 para ambos)
- [ ] **PATH vazio ou ausente** — usar busca em diretório atual / mensagem coerente
- [ ] **Diretório como comando** (`./pasta`) → `is a directory`, status 126

---

## Etapa 8 — Polimento final

- [ ] Histórico do readline (`add_history`) — confirmar que linhas vazias não entram
- [ ] Prompt customizado com cor / nome do usuário (opcional)
- [ ] Suite de testes automatizada cobrindo edge cases acima
- [ ] Norminette final em todos os arquivos novos
- [ ] Rodar valgrind/sanitize com casos típicos e confirmar zero leaks (excluindo readline known leaks)

---

## Bugs / Riscos prioritários

1. **`signals.c` vazio** — sem `SIGINT`/`SIGQUIT` o shell sai ao receber Ctrl+C. **Bloqueador para entrega.**
2. **Aspas não fechadas no lexer** — leitura além do buffer, possível crash.
3. **Heredoc com delimitador quoted** — comportamento de expansão divergente do bash.
4. **`exit` builtin** liberando `args` da AST — double-free latente.
5. **Arquivo de heredoc fixo `/tmp/.shelly_heredoc`** — colisão em pipelines, não é unlinkado.
6. **`free-expander.c` e `free-shelly.c` vazios** — limpeza de saída do shell incompleta.

---

## Referência rápida das structs (conforme `minishell.h`)

```c
typedef struct s_shelly
{
    t_env   *env_list;          // env como lista encadeada
    char    **argv;
    int     last_exit_status;
    t_bool  suppress_output;
}   t_shelly;

typedef struct s_redir
{
    t_token_type    type;       // TOKEN_REDIR_IN, TOKEN_REDIR_OUT, TOKEN_APPEND, TOKEN_HEREDOC
    char            *filename;  // arquivo alvo (ou delimitador no heredoc)
    struct s_redir  *next;
}   t_redir;

typedef struct s_command
{
    char    **cmd;
    t_redir *redir;
}   t_command;

typedef struct s_pipe
{
    t_ast_node  *left;
    t_ast_node  *right;
}   t_pipe;

typedef struct s_ast_node
{
    t_token_type        node_type;
    union u_node_value  value;
}   t_ast_node;
```
