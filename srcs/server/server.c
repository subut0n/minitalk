/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addzikow <addzikow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 16:15:00 by addzikow          #+#    #+#             */
/*   Updated: 2021/06/16 14:10:25 by addzikow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

void    print_pid(void)
{
    char *pid;

    pid = ft_itoa(getpid());
    write(1, "PID: ", 5);
    write(1, pid, ft_strlen(pid));
    write(1, "\n", 1);
    free(pid);
}

int main()
{

}