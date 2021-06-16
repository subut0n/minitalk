/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addzikow <addzikow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 16:00:52 by addzikow          #+#    #+#             */
/*   Updated: 2020/12/18 14:31:20 by addzikow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*dest_c;
	unsigned char	*src_c;

	src_c = (unsigned char *)src;
	dest_c = (unsigned char *)dest;
	i = 0;
	while (i < n && src_c[i] != (unsigned char)c)
	{
		dest_c[i] = src_c[i];
		i++;
	}
	if (i == n)
		return (NULL);
	else
	{
		dest_c[i] = src_c[i];
		i++;
		return (&dest_c[i]);
	}
}
