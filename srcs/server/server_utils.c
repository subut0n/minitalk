/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addzikow <addzikow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/04 18:02:41 by addzikow          #+#    #+#             */
/*   Updated: 2021/07/04 19:43:51 by addzikow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minitalk.h"

char	*alloc(char *str, int buffer, int size)
{
	int		i;
	char	*ret;

	i = 0;
	ret = malloc(sizeof(char) * buffer);
	if (!ret)
	{
		write(2, "minitalk: malloc failed\n", 23);
		_exit(EXIT_FAILURE);
	}
	while (i < size - 1)
	{
		ret[i] = str[i];
		i++;
	}
	if (str && size > 1)
		free(str);
	return (ret);
}

char	*add_char_buffer(char c, char *str)
{
	static int	i = 0;
	static int	size = 0;
	static int	buffer = 128;

	size++;
	if (size == 1)
		str = alloc(str, buffer, size);
	else if (size == buffer)
	{
		buffer += buffer;
		str = alloc(str, buffer, size);
	}
	str[i] = c;
	i++;
	if (c == '\0')
	{
		i = 0;
		size = 0;
		buffer = 128;
	}
	return (str);
}

void	recover_bits(int sig)
{
	static char	*str = NULL;
	static char	c = 0;
	static int	bits = 0;

	c += (sig << bits++);
	if (bits == 8)
	{
		if (c == '\0')
		{
			str = add_char_buffer('\n', str);
			str = add_char_buffer(c, str);
			write(1, str, ft_strlen(str));
			free(str);
			str = NULL;
			send_to_client(SIGUSR2);
		}
		else
			str = add_char_buffer(c, str);
		c = 0;
		bits = 0;
	}
}
