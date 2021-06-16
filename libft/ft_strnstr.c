/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addzikow <addzikow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 11:25:13 by addzikow          #+#    #+#             */
/*   Updated: 2021/03/23 16:47:48 by addzikow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int		i;
	char	*str;
	char	*str2;
	int		l;

	i = 0;
	str = (char *)haystack;
	str2 = (char *)needle;
	if ((int)len == -1)
		len = ft_strlen(haystack) + len;
	if (needle[0] == '\0')
		return (str);
	l = ft_strlen(needle);
	while (str[i] && i <= (int)len - l)
	{
		if (ft_strncmp(&str[i], str2, l) == 0)
			return (&str[i]);
		i++;
	}
	return (NULL);
}
