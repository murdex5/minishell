/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 11:57:47 by kadferna          #+#    #+#             */
/*   Updated: 2024/12/23 11:57:48 by kadferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	get_digit(int nb)
{
	int	digits;

	digits = 0;
	if (nb <= 0)
	{
		++digits;
		nb = -nb;
	}
	while (nb != 0)
	{
		digits++;
		nb = nb / 10;
	}
	return (digits);
}

static char	*allocate_mem(int len)
{
	char	*str;

	str = malloc(len + 1);
	if (!str)
		return (NULL);
	return (str);
}

char	*return_min(void)
{
	char	*str;

	str = malloc(12);
	if (!str)
		return (NULL);
	ft_strlcpy(str, "-2147483648", 12);
	return (str);
}

char	*ft_itoa(int nb)
{
	char	*result;
	int		len;

	if (nb == -2147483648)
		return (return_min());
	len = get_digit(nb);
	result = allocate_mem(len);
	if (!result)
		return (NULL);
	result[len] = '\0';
	if (nb == 0)
		result[0] = '0';
	if (nb < 0)
	{
		result[0] = '-';
		nb = -nb;
	}
	while (nb != 0)
	{
		--len;
		result[len] = (nb % 10) + 48;
		nb = nb / 10;
	}
	return (result);
}
/*
#include <stdlib.h>

int	main(int ac, char **av)
{
	if (ac < 2)
		return (1);           // Ensure a command-line argument is provided
	int num = atoi(av[1]);    // Convert string to integer
	char *str = ft_itoa(num); // Convert the number to a string
	printf("%s\n", str);      // Print the result
	free(str);                // Free the allocated memory
	return (0);
}
*/