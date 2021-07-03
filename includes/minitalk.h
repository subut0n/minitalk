/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addzikow <addzikow@42student.lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 16:18:39 by addzikow          #+#    #+#             */
/*   Updated: 2021/06/24 10:14:44 by addzikow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

#include "../libft/libft.h"
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <signal.h>
#include <sys/types.h>

/// TO REMOVE
void	add_char(char c);
void	send_to_client(int signal);
bool	check_signal(bool can_send);

#endif