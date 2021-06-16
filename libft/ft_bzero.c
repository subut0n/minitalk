/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addzikow <addzikow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 15:33:32 by addzikow          #+#    #+#             */
/*   Updated: 2020/12/18 13:54:28 by addzikow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*tobyte;

	i = 0;
	tobyte = (char *)s;
	while (i < n)
	{
		tobyte[i] = '\0';
		i++;
	}
	s = (void *)tobyte;
}
