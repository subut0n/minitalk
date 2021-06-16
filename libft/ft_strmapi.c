/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addzikow <addzikow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 16:06:25 by addzikow          #+#    #+#             */
/*   Updated: 2021/03/23 16:45:30 by addzikow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*tab;

	i = 0;
	if (!s)
		return (NULL);
	tab = malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!(tab))
		return (NULL);
	while (s[i])
	{
		tab[i] = (*f)(i, s[i]);
		i++;
	}
	tab[i] = '\0';
	return (tab);
}
