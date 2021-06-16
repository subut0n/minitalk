/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addzikow <addzikow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 12:18:58 by addzikow          #+#    #+#             */
/*   Updated: 2021/03/23 16:53:03 by addzikow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static unsigned int	numb_of_digits(unsigned int n)
{
	int		numb;
	long	nb;

	nb = n;
	numb = 0;
	if (nb < 0)
		nb = -nb;
	if (nb == 0)
		numb = 1;
	while (nb > 0)
	{
		nb = nb / 10;
		numb++;
	}
	return (numb);
}

static char	*pos_transcripted_string(unsigned int n, char *str)
{
	int				i;
	unsigned long	nbr;

	nbr = n;
	i = numb_of_digits(n) - 1;
	str[i + 1] = '\0';
	if (n == 0)
	{
		str[0] = '0';
		str[1] = '\0';
		return (str);
	}
	while (i >= 0)
	{
		str[i--] = (nbr % 10) + 48;
		nbr = nbr / 10;
	}
	return (str);
}

char	*ft_uitoa(unsigned int n)
{
	char	*str;

	str = malloc(sizeof(char) * (numb_of_digits(n) + 1));
	if (!(str))
		return (NULL);
	str = pos_transcripted_string(n, str);
	return (str);
}
