/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fconde-p <fconde-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 18:00:00 by fconde-p          #+#    #+#             */
/*   Updated: 2026/04/03 18:00:00 by fconde-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*remove_quotes(char *value, t_bool *quoted_flag)
{
	char	*new_value;
	int		i;
	int		j;

	*quoted_flag = BOOL_FALSE;
	if (!value)
		return (NULL);
	i = 0;
	j = 0;
	new_value = ft_calloc(ft_strlen(value) + 1, sizeof(char));
	if (!new_value)
		return (NULL);
	while (value[i])
	{
		if ((value[i] == '\"' || value[i] == '\''))
		{
			*quoted_flag = BOOL_TRUE;
			i++;
			continue ;
		}
		new_value[j++] = value[i++];
	}
	new_value[j] = '\0';
	free(value);
	return (new_value);
}

static char	*expand_variables(char *value, t_shelly *shelly, t_bool is_quoted)
{
	char	*expanded_str;
	int		i;
	int		start;
	char	*var_name;
	char	*var_value;

	expanded_str = ft_strdup("");
	i = 0;
	while (value[i])
	{
		// Only expand if NOT single-quoted. 
		// If is_quoted is true and starts with single quote, we skip expansion.
		if (value[i] == '$' && value[i + 1] && \
			(ft_isalnum(value[i + 1]) || value[i + 1] == '_' || value[i + 1] == '?') && \
			(!is_quoted || value[0] == '\"'))
		{
			start = i + 1;
			if (value[start] == '?')
				start++;
			else
			{
				while (value[start] && (ft_isalnum(value[start]) || value[start] == '_'))
					start++;
			}
			var_name = ft_substr(value, i + 1, start - (i + 1));
			if (ft_strncmp(var_name, "?", 1) == 0)
				var_value = ft_itoa(shelly->last_exit_status);
			else
				var_value = get_env_value(var_name, shelly->envp);
			if (var_value)
			{
				expanded_str = ft_strjoin_and_free(expanded_str, var_value);
				free(var_value);
			}
			free(var_name);
			i = start;
		}
		else
		{
			expanded_str = ft_strjoin_char_and_free(expanded_str, value[i]);
			i++;
		}
	}
	return (expanded_str);
}

static char	*expand_tilde(char *value, t_shelly *shelly)
{
	char	*home_path;
	char	*expanded_value;

	if (!value || value[0] != '~')
		return (ft_strdup(value));
	home_path = get_env_value("HOME", shelly->envp);
	if (!home_path)
		return (ft_strdup(value));
	if (ft_strlen(value) == 1)
		expanded_value = ft_strdup(home_path);
	else if (value[1] == '/')
		expanded_value = ft_strjoin(home_path, value + 1);
	else
		expanded_value = ft_strdup(value);
	free(home_path);
	return (expanded_value);
}

void	insert_new_tokens(t_token **head, t_token *current, char **words)
{
	t_token *new_token;
	t_token *temp;
	int		i;

	i = 1; // words[0] is already in current->value
	while (words[i])
	{
		new_token = ft_calloc(1, sizeof(t_token));
		if (!new_token)
			return;
		new_token->value = ft_strdup(words[i]);
		new_token->type = TOKEN_WORD;
		new_token->quoted = BOOL_FALSE;
		
		temp = current->next;
		current->next = new_token;
		new_token->prev = current;
		new_token->next = temp;
		if (temp)
			temp->prev = new_token;
		
		current = new_token;
		i++;
	}
	(void)head;
}

t_token	*expander(t_token *tokens, t_shelly *shelly)
{
	t_token	*current;
	char	*temp_value;
	t_bool	quoted_flag;
	char	**split_words;

	current = tokens;
	while (current)
	{
		if (current->type == TOKEN_WORD)
		{
			temp_value = expand_tilde(current->value, shelly);
			free(current->value);
			current->value = temp_value;

			quoted_flag = current->quoted;
			temp_value = expand_variables(current->value, shelly, quoted_flag);
			free(current->value);
			current->value = temp_value;

			if (!quoted_flag && ft_strchr(current->value, ' '))
			{
				split_words = ft_split(current->value, ' ');
				free(current->value);
				current->value = ft_strdup(split_words[0]);
				insert_new_tokens(&tokens, current, split_words);
				ft_free_array(split_words);
			}

			temp_value = remove_quotes(current->value, &quoted_flag);
			current->quoted = quoted_flag;
			current->value = temp_value;
		}
		current = current->next;
	}
	return (tokens);
}
