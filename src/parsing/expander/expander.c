/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fconde-p <fconde-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 18:00:00 by fconde-p          #+#    #+#             */
/*   Updated: 2026/05/23 15:49:46 by fconde-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	handle_word_expansion(t_token *curr,
	t_shelly *shelly, t_token **tokens)
{
	char	*temp_value;
	t_bool	quoted_flag;
	char	**split_words;

	temp_value = expand_tilde(curr->value, shelly);
	free(curr->value);
	curr->value = temp_value;
	quoted_flag = curr->quoted;
	temp_value = expand_variables(curr->value, shelly, quoted_flag);
	free(curr->value);
	curr->value = temp_value;
	if (!quoted_flag && !ft_strchr(curr->value, '\"')
		&& !ft_strchr(curr->value, '\'') && ft_strchr(curr->value, ' '))
	{
		split_words = ft_split(curr->value, ' ');
		free(curr->value);
		curr->value = ft_strdup(split_words[0]);
		insert_new_tokens(tokens, curr, split_words);
		ft_free_array(split_words);
	}
	temp_value = remove_quotes(curr->value, &quoted_flag);
	curr->quoted = quoted_flag;
	curr->value = temp_value;
}

static void	clean_delimiter(t_token *delim)
{
	t_bool	quoted_flag;

	delim->value = remove_quotes(delim->value, &quoted_flag);
	delim->quoted = quoted_flag;
}

t_token	*expander(t_token *tokens, t_shelly *shelly)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (current->type == TOKEN_HEREDOC && current->next
			&& current->next->type == TOKEN_WORD)
		{
			clean_delimiter(current->next);
			current = current->next->next;
			continue ;
		}
		if (current->type == TOKEN_WORD)
			handle_word_expansion(current, shelly, &tokens);
		current = current->next;
	}
	return (tokens);
}
