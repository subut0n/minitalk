/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_argstoints.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addzikow <addzikow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 10:07:10 by addzikow          #+#    #+#             */
/*   Updated: 2021/06/08 10:07:41 by addzikow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int *ft_argstoints(int ac, char **av)
{
	char **fchar;
	int *fint;
	int i;

	fchar = malloc(sizeof(char *) * (ac));
	if (!fchar)
		return (NULL) ;
	i = 0;
	while (i < ac - 1)
	{
		fchar[i] = av[i + 1];
		i++;
	}
	fchar[ac - 1] = NULL;
	fint = malloc(sizeof(int *) * (ac));
	if (!fint)
		return(NULL);
	i = 0;
	while (fchar[i])
	{
		fint[i] = ft_atoi(fchar[i]);
		i++;
	}
	fint[ac - 1] = '\0';
	return (fint);
}