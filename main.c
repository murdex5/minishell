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
	char				*line;
	struct sigaction	sa;
	t_token				*token;
	t_ast_node			*pipe;
	char				**envp_copy;
	struct termios		original_term;
	int					exit_code;
	int temp_exit;

	exit_code = 0;
	(void)argc;
	(void)argv;
	save_terminal_state(&original_term);
	pipe = NULL;
	token = NULL;
	envp_copy = copy_environment(envp);
	if (!process_signals(&sa))
		exit(1);
	while (1)
	{
		if (g_signal_received)
			g_signal_received = 0;
		line = readline("minishell: ");
		if (line == NULL)
		{
			restore_terminal_state(&original_term);
			return (ft_exit(line, token), exit_code);
		}
		if (!validate_quotes(line))
		{
			free(line);
			continue ;
		}
		if (!validate_quotes(line))
		{
			free(line);
			continue ;
		}
		if (*line)
		{
			token = NULL;
			pipe = NULL;
			add_history(line);
			token = init_tokens(line);
			expand_token_variables(token, exit_code, &envp_copy);
			pipe = parse(token);
			if (pipe)
			{
				temp_exit = execute_ast_pipeline(pipe, &envp_copy, exit_code);
				exit_code = temp_exit;
				free_on_exiting_list(token);
			}
		}
		free(line);
	}
	restore_terminal_state(&original_term);
	free_environment(envp_copy);
	return (exit_code);
}
