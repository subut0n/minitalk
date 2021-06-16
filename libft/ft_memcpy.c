/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addzikow <addzikow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 16:03:43 by addzikow          #+#    #+#             */
/*   Updated: 2021/01/08 14:13:24 by addzikow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*desttobyte;
	const char	*srctobyte;

	if (!dest && !src)
		return (NULL);
	desttobyte = (char *)dest;
	srctobyte = (const char *)src;
	while (n--)
		*desttobyte++ = *srctobyte++;
	return (dest);
}
