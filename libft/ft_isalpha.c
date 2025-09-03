/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:29:58 by kadferna          #+#    #+#             */
/*   Updated: 2024/12/09 16:45:58 by kadferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_isalpha(int c)
{
	if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')))
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
        if (ft_isalpha(av[1][0]) == 1)
            printf("is alpha\n");
        else
            printf("not alpha\n");
    }
    return 0;
}*/
