/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fconde-p <fconde-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 16:55:46 by fconde-p          #+#    #+#             */
/*   Updated: 2026/03/01 21:10:40 by fconde-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./lib/libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

typedef struct s_shely
{
	char	**envp;
	char	**argv;
}	t_shell;

typedef enum e_bool
{
	BOOL_FALSE,
	BOOL_TRUE
}	t_bool;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_IN,
	TOKEN_HEREDOC,
	TOKEN_APPEND,
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	t_bool			quoted;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

// Parser structures
typedef struct s_redir
{
	t_token_type	type;
	char			*filename;
	struct	s_redir	*next;
}	t_redir;

typedef struct s_command
{
	char	**cmd;
	t_redir	*redir;
}	t_command;

typedef struct s_pipe
{
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}	t_pipe;

union u_node_value
{
	t_command	*command;
	t_pipe		*pipe;
};

typedef struct s_ast_node
{
	t_token_type		node_type;
	union u_node_value	value;
}	t_ast_node;

// parser functions
t_ast_node	*parser(t_token *tokens);
t_ast_node	*parse_command(t_token	*token);
int	count_words_token(t_token *token);
void	add_redir_command(t_ast_node **node, t_token **token);
t_ast_node	*parse_command(t_token	*token);
t_ast_node	*parser(t_token *tokens);

// def funny stuff here, friendo!
int		ft_sample(void);			// REMOVE ASAP!
int		ft_sample_fail(void);		// REMOVE ASAP!
int		ft_sample_success(void);	// REMOVE ASAP!

t_token	*set_tokens(char *s);
int		get_token_len(char *str);

#endif
