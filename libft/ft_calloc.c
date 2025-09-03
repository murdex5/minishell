/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:19:16 by kadferna          #+#    #+#             */
/*   Updated: 2024/12/11 15:19:20 by kadferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*arr;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if (nmemb > SIZE_MAX / size)
		return (NULL);
	arr = malloc(nmemb * size);
	if (!arr)
		return (NULL);
	ft_bzero(arr, (nmemb * size));
	return (arr);
}
/*
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	size_t	nmemb;
	size_t	size;
	int		*arr;

	nmemb = -5;
	size = sizeof(int);
	arr = (int *)ft_calloc(-5, 0);
	if (!arr)
	{
		printf("Memory allocation failed\n");
		return (1);
	}
	for (size_t i = 0; i < nmemb; i++)
		printf("arr[%zu] = %d\n", i, arr[i]); // All elements will be 0
	free(arr);
	return (0);
}*/