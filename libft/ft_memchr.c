/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addzikow <addzikow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 16:03:06 by addzikow          #+#    #+#             */
/*   Updated: 2021/01/04 16:54:32 by addzikow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*tobyte;

	i = 0;
	tobyte = (unsigned char *)s;
	while (i < n)
	{
		if (tobyte[i] == (unsigned char)c)
			return ((void *)&tobyte[i]);
		i++;
	}
	return (NULL);
}
