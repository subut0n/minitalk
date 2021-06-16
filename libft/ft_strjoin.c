/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addzikow <addzikow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 16:05:42 by addzikow          #+#    #+#             */
/*   Updated: 2021/03/23 16:43:05 by addzikow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	int		size;
	char	*tab;

	if (!s1 || !s2)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2);
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	tab = malloc(sizeof(char) * (size + 1));
	if (!(tab))
		return (NULL);
	i = 0;
	j = 0;
	while (i < size)
	{
		while (s1[j])
			tab[i++] = s1[j++];
		j = 0;
		while (s2[j])
			tab[i++] = s2[j++];
	}
	tab[i] = '\0';
	return (tab);
}
