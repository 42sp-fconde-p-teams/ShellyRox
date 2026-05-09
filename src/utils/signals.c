/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fconde-p <fconde-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by csilva-s          #+#    #+#             */
/*   Updated: 2026/05/09 14:39:47 by fconde-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	g_sig_status;

// g_sig_status = 0;

static void	handle_sigint(int sig)
{
	(void)sig;
	g_sig_status = 130;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	setup_signals(t_sig_state state)
{
	(void)state;
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(struct sigaction));
	if (state == SIG_STATE_INTERACTIVE)
	{
		sa.sa_handler = handle_sigint;
		sigaction(SIGINT, &sa, NULL);
		sa.sa_handler = SIG_IGN;
		sigaction(SIGQUIT, &sa, NULL);
	} else if (state == SIG_STATE_CHILD)
	{
		sa.sa_handler = SIG_DFL;
		sigaction(SIGINT, &sa, NULL);
		sigaction(SIGQUIT, &sa, NULL);
	} else if (state == SIG_STATE_IGNORE)
	{
		sa.sa_handler = SIG_IGN;
		sigaction(SIGINT, &sa, NULL);
		sigaction(SIGQUIT, &sa, NULL);
	}
}
