/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addzikow <addzikow@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 16:04:32 by addzikow          #+#    #+#             */
/*   Updated: 2021/01/13 13:18:07 by addzikow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	int			size;
	const char	newline = '\n';

	if (!s || !fd)
		return ;
	size = ft_strlen(s);
	write(fd, s, size);
	write(fd, &newline, 1);
}
