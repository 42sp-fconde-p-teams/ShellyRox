/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fconde-p <fconde-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 16:55:46 by fconde-p          #+#    #+#             */
/*   Updated: 2026/02/20 21:44:06 by fconde-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./lib/libft/libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_EOF
} t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	t_token			*prev;
	t_token			*next;
} t_token;


// def funny stuff here, friendo!
int	ft_sample(void);			// REMOVE ASAP!
int	ft_sample_fail(void);		// REMOVE ASAP!
int	ft_sample_success(void);	// REMOVE ASAP!

#endif