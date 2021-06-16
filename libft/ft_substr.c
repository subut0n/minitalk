/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addzikow <addzikow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 16:07:31 by addzikow          #+#    #+#             */
/*   Updated: 2021/03/23 16:51:58 by addzikow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	i = 0;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		str = malloc(sizeof(char) * 1);
		if (!(str))
			return (NULL);
		str[0] = '\0';
		return (str);
	}
	if (len > ft_strlen(s))
		len = ft_strlen(&s[start]);
	str = malloc(sizeof(char) * (len + 1));
	if (!(str))
		return (NULL);
	while (s[start] && i < len)
		str[i++] = s[start++];
	str[i] = '\0';
	return (str);
}
