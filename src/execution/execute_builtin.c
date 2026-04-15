/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fconde-p <fconde-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 23:00:00 by fconde-p          #+#    #+#             */
/*   Updated: 2026/04/14 22:47:19 by fconde-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	execute_builtin(char *cmd, char **args, t_shelly *shelly)
{
	if (!cmd)
		return (-1);
	if (ft_strncmp(cmd, "env", 3) == 0 && cmd[3] == '\0')
		return (ft_env(shelly));
	if (ft_strncmp(cmd, "pwd", 3) == 0 && cmd[3] == '\0')
		return (ft_pwd());
	if (ft_strncmp(cmd, "cd", 2) == 0 && cmd[2] == '\0')
		return (ft_cd(args, shelly));
	if (ft_strncmp(cmd, "exit", 4) == 0 && cmd[4] == '\0')
		return (ft_exit(shelly, args));
	if (ft_strncmp(cmd, "export", 6) == 0 && cmd[6] == '\0')
		return (ft_export(args, shelly));
	return (-1);
}
