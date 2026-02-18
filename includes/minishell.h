/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csila-s <csila-s@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by csila-s         #+#    #+#             */
/*   Updated: 2026/02/18 12:15:04 by csilva-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <signal.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../lib/libft/libft.h"

/* Token types */
typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_REDIR_HEREDOC,
	TOKEN_EOF
}	t_token_type;

/* Token structure */
typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

/* Command structure */
typedef struct s_cmd
{
	char			**args;
	char			*infile;
	char			*outfile;
	int				append;
	int				heredoc;
	struct s_cmd	*next;
}	t_cmd;

/* Environment structure */
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

/* Main shell structure */
typedef struct s_shell
{
	t_env	*env;
	t_cmd	*cmds;
	int		exit_status;
	char	**envp;
}	t_shell;

/* Parsing functions */
t_token	*lexer(char *input);
t_cmd	*parser(t_token *tokens);
void	expander(t_cmd *cmd, t_env *env);

/* Execution functions */
void	executor(t_cmd *cmd, t_shell *shell);
void	setup_redirections(t_cmd *cmd);
void	execute_pipes(t_cmd *cmd, t_shell *shell);

/* Built-in functions */
int		builtin_cd(char **args, t_shell *shell);
int		builtin_echo(char **args);
int		builtin_env(t_env *env);
int		builtin_exit(char **args, t_shell *shell);
int		builtin_export(char **args, t_shell *shell);
int		builtin_pwd(void);
int		builtin_unset(char **args, t_shell *shell);
int		is_builtin(char *cmd);
int		execute_builtin(char **args, t_shell *shell);

/* Utility functions */
void	error_msg(char *msg);
t_env	*init_env(char **envp);
char	**env_to_array(t_env *env);
void	setup_signals(void);
void	cleanup_shell(t_shell *shell);
void	free_tokens(t_token *tokens);
void	free_cmds(t_cmd *cmds);
void	free_env(t_env *env);

#endif
