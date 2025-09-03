/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 20:44:15 by kadferna          #+#    #+#             */
/*   Updated: 2025/08/18 20:44:18 by kadferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close2_fd(int fd1, int fd2)
{
	close(fd1);
	close(fd2);
}

void	perror_exit(char *msg, int i)
{
	perror(msg);
	exit(i);
}
