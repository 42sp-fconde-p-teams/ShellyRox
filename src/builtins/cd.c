/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csila-s <csila-s@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by csila-s         #+#    #+#             */
/*   Updated: 2026/03/27 00:37:45 by csilva-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csila-s <csila-s@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by csila-s         #+#    #+#             */
/*   Updated: 2026/04/13 00:00:00 by fconde-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*get_target_path(char **args, t_shelly *shell, int *print_path)
{
	char	*path;

	*print_path = 0;
	if (!args[1] || ft_strncmp(args[1], "--", 3) == 0)
	{
		path = get_env_value("HOME", shell);
		if (!path)
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (path);
	}
	if (ft_strncmp(args[1], "-", 2) == 0)
	{
		path = get_env_value("OLDPWD", shell);
		if (!path)
			ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		else
			*print_path = 1;
		return (path);
	}
	return (expand_tilde(args[1], shell));
}

static void	update_pwd_env(t_shelly *shell, char *old_path)
{
	char	new_path[4096];

	if (old_path)
		set_env_var(shell, "OLDPWD", old_path);
	if (getcwd(new_path, sizeof(new_path)))
		set_env_var(shell, "PWD", new_path);
}

int	ft_cd(char **args, t_shelly *shell)
{
	char	*target;
	char	old_path[4096];
	int		print_path;

	if (args[1] && args[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	target = get_target_path(args, shell, &print_path);
	if (!target)
		return (1);
	if (!getcwd(old_path, sizeof(old_path)))
		old_path[0] = '\0';
	if (chdir(target) != 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(target);
		free(target);
		return (1);
	}
	update_pwd_env(shell, old_path[0] ? old_path : NULL);
	if (print_path)
		ft_printf("%s\n", target);
	free(target);
	return (0);
}

