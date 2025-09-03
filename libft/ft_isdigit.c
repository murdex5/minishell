/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:36:10 by kadferna          #+#    #+#             */
/*   Updated: 2024/12/09 16:45:37 by kadferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_isdigit(int c)
{
	if (!(c >= '0' && c <= '9'))
		return (0);
	return (1);
}
/*
#include <stdio.h>
int main(int ac, char **av)
{
    if (ac != 2)
        return 1;
    else
    {
        if (ft_isdigit(av[1][0]) == 1)
            printf("is digit\n");
        else
            printf("not digit\n");
    }
    return 0;
}*/
