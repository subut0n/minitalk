/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addzikow <addzikow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 16:04:03 by addzikow          #+#    #+#             */
/*   Updated: 2020/12/18 14:39:18 by addzikow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;
	char	*tobyte;

	i = 0;
	tobyte = (char *)s;
	while (i < n)
	{
		tobyte[i] = (char)c;
		i++;
	}
	s = (void *)tobyte;
	return (s);
}
