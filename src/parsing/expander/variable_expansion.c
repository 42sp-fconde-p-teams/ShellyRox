/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fconde-p <fconde-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 18:00:00 by fconde-p          #+#    #+#             */
/*   Updated: 2026/04/25 20:04:35 by csilva-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

static char	*get_var_value(char *var_name, t_shelly *shelly)
{
	if (ft_strncmp(var_name, "?", 1) == 0)
		return (ft_itoa(shelly->last_exit_status));
	return (get_env_value(var_name, shelly));
}

static int	find_var_end(char *value, int start)
{
	if (value[start] == '?')
		return (start + 1);
	while (value[start] && (ft_isalnum(value[start]) || value[start] == '_'))
		start++;
	return (start);
}

static int	process_variable(char *value, int i, t_shelly *shelly, char **res)
{
	int		start;
	char	*var_name;
	char	*var_value;

	start = find_var_end(value, i + 1);
	var_name = ft_substr(value, i + 1, start - (i + 1));
	var_value = get_var_value(var_name, shelly);
	if (var_value)
		*res = ft_strjoin_and_free(*res, var_value);
	free(var_name);
	free(var_value);
	return (start);
}

char	*expand_variables(char *value, t_shelly *shelly, t_bool is_quoted)
{
	char	*expanded_str;
	int		i;

	expanded_str = ft_strdup("");
	i = 0;
	while (value[i])
	{
		if (value[i] == '$' && value[i + 1] && \
					(ft_isalnum(value[i + 1]) || value[i + 1] == '_' || \
					value[i + 1] == '?') && (!is_quoted || value[0] == '"'))
						i = process_variable(value, i, shelly, &expanded_str);
		else
			expanded_str = ft_strjoin_char_and_free(expanded_str, value[i++]);
	}
	return (expanded_str);
}
