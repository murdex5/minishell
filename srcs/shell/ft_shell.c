/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 23:11:22 by kadferna          #+#    #+#             */
/*   Updated: 2025/09/16 23:11:24 by kadferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	initialize_shell(t_shell_state *state, char *envp[])
{
	struct sigaction	sa;

	state->exit_code = 0;
	state->pipe = NULL;
	save_terminal_state(&state->original_term);
	state->envp_copy = copy_environment(envp);
	if (!process_signals(&sa))
		exit(1);
}

void	process_line(char *line, t_shell_state *state)
{
	t_token	*token;

	if (!validate_quotes(line))
	{
		free(line);
		return ;
	}
	if (*line)
	{
		add_history(line);
		token = init_tokens(line);
		expand_token_variables(token, state->exit_code, &state->envp_copy);
		state->pipe = parse(token);
		free_token(token);
		if (state->pipe)
		{
			state->temp_exit = execute_ast_pipeline(state->pipe,
					&state->envp_copy);
			state->exit_code = state->temp_exit;
		}
	}
	free(line);
}

void	shell_loop(t_shell_state *state)
{
	char	*line;

	while (1)
	{
		if (g_signal_received)
			g_signal_received = 0;
		line = readline("minishell$ ");
		if (line == NULL)
		{
			restore_terminal_state(&state->original_term);
			ft_exit(line, NULL, state->envp_copy, state->pipe);
			exit(state->exit_code);
		}
		process_line(line, state);
	}
}

void	cleanup_shell(t_shell_state *state)
{
	restore_terminal_state(&state->original_term);
	free_environment(state->envp_copy);
}
