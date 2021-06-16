/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addzikow <addzikow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 14:30:32 by addzikow          #+#    #+#             */
/*   Updated: 2021/03/23 16:31:33 by addzikow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*save;

	if (!lst || !f || !del)
		return (NULL);
	new_lst = ft_lstnew((f)(lst->content));
	if (!(new_lst))
		return (NULL);
	save = new_lst;
	lst = lst->next;
	while (lst)
	{
		new_lst->next = ft_lstnew((f)(lst->content));
		if (!(new_lst->next))
		{
			ft_lstclear(&save, del);
			return (NULL);
		}
		lst = lst->next;
		new_lst = new_lst->next;
	}
	new_lst->next = NULL;
	return (save);
}
