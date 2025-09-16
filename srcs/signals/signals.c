/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 11:03:24 by kadferna          #+#    #+#             */
/*   Updated: 2025/07/14 14:44:05 by kadferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_signal_received = 1;
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	process_signals(struct sigaction *sa)
{
	sa->sa_handler = signal_handler;
	sigemptyset(&sa->sa_mask);
	sa->sa_flags = 0;
	if (sigaction(SIGINT, sa, NULL) == -1)
	{
		perror("sigaction");
		return (0);
	}
	signal(SIGQUIT, SIG_IGN);
	return (1);
}

void	save_terminal_state(struct termios *original_state)
{
	tcgetattr(STDIN_FILENO, original_state);
}

void	restore_terminal_state(struct termios *original_state)
{
	tcsetattr(STDIN_FILENO, TCSANOW, original_state);
}
