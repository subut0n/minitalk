/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addzikow <addzikow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 16:07:14 by addzikow          #+#    #+#             */
/*   Updated: 2021/03/23 16:49:39 by addzikow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_set(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *str, char const *set)
{
	char	*tab;
	size_t	start;
	size_t	end;

	start = 0;
	if (!str)
		return (NULL);
	if (!set)
		return (ft_strdup(str));
	end = ft_strlen(str);
	while (is_set(str[start], set))
		start++;
	if (start == ft_strlen(str))
	{
		tab = ft_strdup("");
		if (!(tab))
			return (NULL);
		return (tab);
	}
	while (is_set(str[end - 1], set))
		end--;
	tab = ft_substr(str, start, (end - start));
	if (!(tab))
		return (NULL);
	return (tab);
}
