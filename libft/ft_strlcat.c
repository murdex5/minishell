/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 14:06:45 by kadferna          #+#    #+#             */
/*   Updated: 2024/12/11 14:36:47 by kadferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dest_len;
	size_t	i;

	if (size == 0)
		return (ft_strlen(src));
	dest_len = 0;
	while (dst[dest_len] != '\0' && dest_len < size)
		dest_len++;
	if (dest_len == size)
		return (size + ft_strlen(src));
	i = 0;
	while (src[i] != '\0' && dest_len + i < size - 1)
	{
		dst[dest_len + i] = src[i];
		i++;
	}
	dst[dest_len + i] = '\0';
	return (dest_len + ft_strlen(src));
}
/*
#include <stdio.h>

int	main(void)
{
	char	dest[30];
	int		len;

	ft_memset(dest, 0, 30);
	char * src = (char *)"AAAAAAAAA";
	dest[0] = 'B';
	printf("Before strlcat: '%s'\n", dest);
	len = ft_strlcat(dest, src, 0);
	int i = strcmp(dest, "B");
	printf("%s \n", dest);
	printf("%d %d \n", i, len);
	return (0);
}*/
