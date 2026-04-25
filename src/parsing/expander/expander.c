/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fconde-p <fconde-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 18:00:00 by fconde-p          #+#    #+#             */
/*   Updated: 2026/04/25 20:05:30 by csilva-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

static void	handle_word_expansion(t_token *current,
		t_shelly *shelly, t_token **tokens)
{
	char	*temp_value;
	t_bool	quoted_flag;
	char	**split_words;

	temp_value = expand_tilde(current->value, shelly);
	free(current->value);
	current->value = temp_value;
	quoted_flag = current->quoted;
	temp_value = expand_variables(current->value, shelly, quoted_flag);
	free(current->value);
	current->value = temp_value;
	if (!quoted_flag && !ft_strchr(current->value, '\"')
		&& !ft_strchr(current->value, '\'') && ft_strchr(current->value, ' '))
	{
		split_words = ft_split(current->value, ' ');
		free(current->value);
		current->value = ft_strdup(split_words[0]);
		insert_new_tokens(tokens, current, split_words);
		ft_free_array(split_words);
	}
	temp_value = remove_quotes(current->value, &quoted_flag);
	current->quoted = quoted_flag;
	current->value = temp_value;
}

t_token	*expander(t_token *tokens, t_shelly *shelly)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (current->type == TOKEN_WORD)
			handle_word_expansion(current, shelly, &tokens);
		current = current->next;
	}
	return (tokens);
}
