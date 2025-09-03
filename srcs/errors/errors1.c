/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 19:20:51 by kadferna          #+#    #+#             */
/*   Updated: 2025/08/21 19:20:53 by kadferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	std_err_msg(char *msg)
{
	printf("Error\n %s\n", msg);
}

void	report_syntax_error(char *msg, t_token *token)
{
	printf("%s: %s\n", msg, token->value);
}
