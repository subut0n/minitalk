/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addzikow <addzikow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 12:05:42 by addzikow          #+#    #+#             */
/*   Updated: 2021/06/16 17:56:43 by addzikow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minitalk.h"

int init_client(char *str)
{
    int pid;

    pid = ft_atoi(str);
    if (pid < 100 || pid > 99998)
    {
        ft_putstr("Invalid PID\n");
        exit(EXIT_FAILURE);
    }
    return (pid);
}

void send_bits(pid_t pid, char c)
{
    int bit;
    int send;
    int signal;

    while (bit < 8)
    {
        send = (c >> bit++) & 1;
        if (send == 0)
            signal = SIGUSR1;
        if (send == 1)
            signal = SIGUSR2;
        if (kill(pid, signal) == -1)
        {
            ft_putstr("Message can not be sent.\n");
            exit(EXIT_FAILURE);
        }
    }
}

int main(int argc, char **argv)
{
    pid_t pid;
    int i;

    if (argc != 3)
    {
        ft_putstr("Minitalk args should be : ./client <pid> <message>\n");
        exit(EXIT_FAILURE);
    }
    pid = init_client(argv[1]);
    i = -1;
    while (argv[2][++i])
        send_bits(pid, argv[2][i]);
}