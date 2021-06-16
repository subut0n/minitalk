/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addzikow <addzikow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 16:05:57 by addzikow          #+#    #+#             */
/*   Updated: 2020/12/18 15:09:05 by addzikow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dst_len;
	size_t	src_len;

	i = 0;
	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (dstsize <= dst_len)
		return (src_len + dstsize);
	while ((dst_len + i) < dstsize && src[i])
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	if (dst_len + i == dstsize && dst_len < dstsize)
		dst[dst_len + --i] = '\0';
	else
		dst[dst_len + i] = '\0';
	if (dst_len > dstsize)
		return (dstsize + src_len);
	return (dst_len + src_len);
}
