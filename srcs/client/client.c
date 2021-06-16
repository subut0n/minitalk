/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addzikow <addzikow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 12:05:42 by addzikow          #+#    #+#             */
/*   Updated: 2021/06/16 14:10:24 by addzikow         ###   ########.fr       */
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

void send_bits(pid_t pid, char *msg)
{
    


}

int main(int argc, char **argv)
{
    pid_t pid;

    if (argc != 3)
    {
        ft_putstr("Minitalk args should be : ./client <pid> <message>\n");
        exit(EXIT_FAILURE);
    }
    pid = init_client(argv[2]);


}