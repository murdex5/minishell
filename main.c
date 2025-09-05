/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 17:32:23 by kadferna          #+#    #+#             */
/*   Updated: 2025/07/12 17:32:26 by kadferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal_received = 0;

void	print_tokens(t_token *head)
{
	t_token	*current;
	int		count;

	current = head;
	count = 0;
	printf("=== TOKEN LIST ===\n");
	while (current != NULL)
	{
		printf("[%d] Value: '%s'\n", count, current->value);
		printf("     Type:  ");
		switch (current->type)
		{
		case TOKEN_WORD:
			printf("WORD");
			break ;
		case TOKEN_PIPE:
			printf("PIPE");
			break ;
		case TOKEN_REDIR_IN:
			printf("REDIR_IN");
			break ;
		case TOKEN_REDIR_OUT:
			printf("REDIR_OUT");
			break ;
		case TOKEN_REDIR_APPEND:
			printf("REDIR_APPEND");
			break ;
		case TOKEN_HEREDOC:
			printf("HEREDOC");
			break ;
		case TOKEN_EOF:
			printf("EOF");
			break ;
		default:
			printf("UNKNOWN (%d)", current->type);
		}
		printf("\n\n");
		current = current->next;
		count++;
	}
	printf("=== TOTAL: %d tokens ===\n", count);
}

void	save_terminal_state(struct termios *original_state)
{
	tcgetattr(STDIN_FILENO, original_state);
}

void	restore_terminal_state(struct termios *original_state)
{
	tcsetattr(STDIN_FILENO, TCSANOW, original_state);
}

int	main(int argc, char **argv, char *envp[])
{
	char				*line;
	struct sigaction	sa;
	t_token				*token;
	t_ast_node			*pipe;
	char				**envp_copy;
	struct termios		original_term;

	(void)argc;
	(void)argv;
	// Save original terminal state once at startup
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
		if (line == NULL) // EOF (Ctrl+D)
		{
			restore_terminal_state(&original_term);
			return (ft_exit(line, token), 0);
		}
		if (*line)
		{
			add_history(line);
			token = init_tokens(line);
			pipe = parse(token);
			if (pipe)
			{
				// Execute command
				execute_ast_pipeline(pipe, &envp_copy, token, line);
				free_on_exiting_list(token);
				token = NULL;
				pipe = NULL;
			}
		}
		free(line);
	}
	restore_terminal_state(&original_term);
	free_environment(envp_copy);
	return (0);
}
