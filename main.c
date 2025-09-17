/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anjbaiju <anjbaiju@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 17:32:23 by kadferna          #+#    #+#             */
/*   Updated: 2025/09/09 15:41:35 by anjbaiju         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal_received = 0;

int	main(int argc, char **argv, char *envp[])
{
	t_shell_state	state;
	int				exit_code;

	exit_code = 0;
	(void)argc;
	(void)argv;
	initialize_shell(&state, envp);
	shell_loop(&state);
	cleanup_shell(&state);
	exit_code = state.exit_code;
	return (exit_code);
}
