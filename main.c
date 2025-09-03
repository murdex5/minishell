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

void	signal_handler(int sig)
{
	g_signal_recieved = sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void print_tokens(t_token *head)
{
    t_token *current = head;
    int count = 0;

    printf("=== TOKEN LIST ===\n");
    while (current != NULL)
    {
        printf("[%d] Value: '%s'\n", count, current->value);
        printf("     Type:  ");
        
        switch (current->type)
        {
            case TOKEN_WORD:        printf("WORD"); break;
            case TOKEN_PIPE:        printf("PIPE"); break;
            case TOKEN_REDIR_IN:   printf("REDIR_IN"); break;
            case TOKEN_REDIR_OUT:  printf("REDIR_OUT"); break;
            case TOKEN_REDIR_APPEND: printf("REDIR_APPEND"); break;
            case TOKEN_HEREDOC:     printf("HEREDOC"); break;
            case TOKEN_EOF:         printf("EOF"); break;
            default:                printf("UNKNOWN (%d)", current->type);
        }
        printf("\n\n");
        
        current = current->next;
        count++;
    }
    printf("=== TOTAL: %d tokens ===\n", count);
}


int	main(int argc, char **argv, char *envp[])
{
	char				*line;
	struct sigaction	sa;
	t_token				*token;
	t_ast_node *pipe;

	(void)argc;
	(void)argv;
	sa.sa_handler = signal_handler;
	pipe = NULL;
	token = NULL;
	if (!process_signals(&sa))
		exit(1);
	while (1)
	{
		if (g_signal_recieved)
			g_signal_recieved = 0;
		line = readline("minishell: ");
		if (line == NULL)
			return (ft_exit(line, token), 0);
		if (*line)
		{
			add_history(line);
			token = init_tokens(line);
			pipe = parse(token);
			execute_ast_pipeline(pipe, envp);
			token = NULL;
		}
		free(line);
	}
	free(line);
	free_on_exiting_list(token);
	return (0);
}
