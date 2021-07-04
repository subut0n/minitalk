/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addzikow <addzikow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 16:18:39 by addzikow          #+#    #+#             */
/*   Updated: 2021/07/04 19:32:02 by addzikow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# define _XOPEN_SOURCE 700

#include "../libft/libft.h"
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <signal.h>
#include <sys/types.h>

char	*alloc(char *str, int buffer, int size);
char	*add_char_buffer(char c, char *str);
void	recover_bits(int sig);
void	send_to_client(int signal);
void    handle_signal(int sig, siginfo_t *info, void *context);
bool	check_signal(bool can_send);

#endif