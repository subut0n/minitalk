/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addzikow <addzikow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 15:18:10 by addzikow          #+#    #+#             */
/*   Updated: 2021/03/23 16:30:07 by addzikow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*element;
	t_list	*save;

	element = *lst;
	while (element)
	{
		save = element->next;
		ft_lstdelone(element, del);
		element = save;
	}
	*lst = NULL;
}
