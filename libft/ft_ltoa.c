/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addzikow <addzikow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 16:00:37 by addzikow          #+#    #+#             */
/*   Updated: 2021/03/23 16:35:39 by addzikow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	numb_of_digits(long n)
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

static char	*malloc_string(long n)
{
	char	*str;

	if (n < 0)
	{
		str = malloc(sizeof(char) * (numb_of_digits(n) + 2));
		if (!(str))
			return (NULL);
	}
	else
	{
		str = malloc(sizeof(char) * (numb_of_digits(n) + 1));
		if (!(str))
			return (NULL);
	}
	return (str);
}

static char	*pos_transcripted_string(long n, char *str)
{
	int		i;
	long	nbr;

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

char	*ft_ltoa(long n)
{
	char	*str;
	long	numb;

	numb = n;
	if (numb < 0)
		numb *= -1;
	str = malloc_string(numb);
	if (!(str))
		return (NULL);
	str = pos_transcripted_string(numb, str);
	return (str);
}
