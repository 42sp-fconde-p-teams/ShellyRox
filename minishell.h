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
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

typedef enum e_bool
{
	BOOL_FALSE,
	BOOL_TRUE
}	t_bool;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_CMD,
	TOKEN_FLAG
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
typedef struct s_cmd
{
	char			**cmd;
	struct s_cmd	*next;
}	t_cmd;
	// thinking about the cmd struct use...

typedef struct s_ast_node {
	t_token_type	node_type;
	union u_node_value
	{
		typedef struct s_command
		{
			char **cmd;
		}	command;
		typedef struct s_pipe
		{
			struct s_ast_node *left;
		 	struct s_ast_node *right;
		}	pipe;
		typedef struct s_redir
		{
			char **cmd;
			char *filename;
			int fd;
		}	redirect;
		typedef struct s_and_or
		{
			struct s_ast_node *left;
			struct s_ast_node *right;
		}	and_or;
	};
} t_ast_node;



// def funny stuff here, friendo!
int	ft_sample(void);			// REMOVE ASAP!
int	ft_sample_fail(void);		// REMOVE ASAP!
int	ft_sample_success(void);	// REMOVE ASAP!

t_token	*set_tokens(char *s);
int	get_token_len(char *str);

#endif
