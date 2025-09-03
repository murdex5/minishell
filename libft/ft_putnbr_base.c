/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadferna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 09:46:27 by kadferna          #+#    #+#             */
/*   Updated: 2024/12/30 09:46:28 by kadferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_base(unsigned int nbr, char *base)
{
	int		base_len;
	char	c;
	int		i;

	i = -1;
	if (!base)
		return ;
	base_len = 0;
	while (base[base_len])
	{
		while (i < base_len)
		{
			if (base[i++] == base[base_len])
				return ;
		}
		if (base[base_len] == '+' || base[base_len] == '-')
			return ;
		base_len++;
	}
	if (base_len <= 1)
		return ;
	if (nbr >= (unsigned int)base_len)
		ft_putnbr_base(nbr / base_len, base);
	c = base[nbr % base_len];
	write(1, &c, 1);
}
