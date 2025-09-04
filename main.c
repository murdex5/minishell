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

static volatile sig_atomic_t	g_signal_recieved = 0;

// void	signal_handler(int sig)
// {
// 	(void)sig;
// 	write(1, "\n", 1);
// 	rl_replace_line("", 0);
// 	rl_on_new_line();
// 	rl_redisplay();
// }

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

void	reset_terminal_state(void)
{
	struct termios	new_state;
	struct termios	original_state;

	save_terminal_state(&original_state);
	new_state = original_state;
	// Reset to sane defaults
	new_state.c_lflag |= (ECHO | ICANON | ISIG);
	new_state.c_lflag &= ~(ECHOCTL | IEXTEN);
	new_state.c_iflag |= (ICRNL | IXON);
	new_state.c_oflag |= (OPOST | ONLCR);
	tcsetattr(STDIN_FILENO, TCSANOW, &new_state);
	// Also reset readline's internal state
	rl_replace_line("", 0);
	rl_redisplay();
}

void signal_handler(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
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
	// Save original terminal state
	save_terminal_state(&original_term);
	pipe = NULL;
	token = NULL;
	envp_copy = copy_environment(envp);
	if (!process_signals(&sa))
		exit(1);
	while (1)
	{
		if (g_signal_recieved)
		{
			g_signal_recieved = 0;
			reset_terminal_state(); // Reset on signal
		}
		line = readline("minishell: ");
		printf("DEBUG: Read line: '%s'\n", line);
		if (line == NULL)
		{
			restore_terminal_state(&original_term);
			return (ft_exit(line, token), 0);
		}
		if (*line)
		{
			add_history(line);
			token = init_tokens(line);
			pipe = parse(token);
			// Execute and immediately reset terminal
			execute_ast_pipeline(pipe, &envp_copy, token, line);
			reset_terminal_state(); // CRITICAL: Reset after execution
			free_on_exiting_list(token);
			token = NULL;
			pipe = NULL;
		}
		free(line);
	}
	restore_terminal_state(&original_term);
	free_environment(envp_copy);
	return (0);
}
