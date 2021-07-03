/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addzikow <addzikow@42student.lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 12:05:42 by addzikow          #+#    #+#             */
/*   Updated: 2021/06/24 10:18:42 by addzikow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minitalk.h"

static void	server_signal(int type)
{
	if (type == SIGUSR1)
		check_signal(true);
	if (type == SIGUSR2)
	{
		printf("minitalk: The message was sent with success!\n");
		exit(EXIT_SUCCESS);
	}
}

bool	check_signal(bool can_send) 
{
	static bool	status = false;

	if (can_send)
		status = true;
	else if (status)
	{
		status = false;
		return (true);
	}
	return (false);
}

pid_t init_client(char *str)
{
    pid_t pid;

    pid = ft_atoi(str);
    if (pid < 100 || pid > 99998)
    {
        ft_putstr_fd("Invalid PID\n", 1);
        exit(EXIT_FAILURE);
    }
    if ((signal(SIGUSR1, server_signal) == SIG_ERR) //////add
		|| (signal(SIGUSR2, server_signal) == SIG_ERR))
	{
		printf("minitalk: a signal error has occurred.\n");
		exit(EXIT_FAILURE);
	}
    return (pid);
}

void send_bits(pid_t pid, char c)
{
    int bit;
    int send;
    int signal;

    bit = 0;
    while (bit < 8)
    {
        send = (c >> bit++) & 1;
        if (send == 0)
            signal = SIGUSR1;
        if (send == 1)
            signal = SIGUSR2;
        if (kill(pid, signal) == -1)
        {
            ft_putstr_fd("Message can not be sent.\n", 1);
            exit(EXIT_FAILURE);
        }
        usleep(800);
    }
}

int main(int argc, char **argv)
{
    pid_t pid;
    int i;

    if (argc != 3)
    {
        ft_putstr_fd("Minitalk args should be : ./client <pid> <message>\n", 1);
        exit(EXIT_FAILURE);
    }
    pid = init_client(argv[1]);
    i = -1;
    while (argv[2][++i])
        send_bits(pid, argv[2][i]);
    send_bits(pid, '\0');
    return (0);
}

/////////////////////////////////////////////////////////////////////////////////////


// void	send_signal(int pid, int nb)
// {
// 	if (nb == 0 && kill(pid, SIGUSR1) == -1)
// 	{
// 		ft_putstr_fd("Error: failure to send signal\n", 1);
// 		exit(0);
// 	}
// 	if (nb == 1 && kill(pid, SIGUSR2) == -1)
// 	{
// 		ft_putstr_fd("Error: failure to send signal\n", 1);
// 		exit(0);
// 	}
// }

// void	send_char_to_pid(int pid, char c)
// {
// 	int	i;
// 	int	nb;

// 	i = 0;
// 	while (i < 8)
// 	{
// 		nb = (c >> i++) & 1;
// 		send_signal(pid, nb);
// 		usleep(800);
// 	}
// }

// void	send_str_to_pid(int pid, char *str)
// {
// 	int	i;

// 	i = -1;
// 	while (str[++i])
// 		send_char_to_pid(pid, str[i]);
// 	send_char_to_pid(pid, 0);
// }

// void	handler(int sig)
// {
// 	sig = 0;
//     sig++;
//     sig--;
// }

// int	main(int argc, char **arg)
// {
// 	int	pid_server;

// 	if (argc == 3)
// 	{
// 		pid_server = ft_atoi(arg[1]);
// 		if (pid_server <= 1)
// 			ft_putstr_fd("Error PID\n", 1);
// 		signal(SIGUSR1, &handler);
// 		send_str_to_pid(pid_server, arg[2]);
// 	}
// 	else
// 		ft_putstr_fd("./client <PID server> <message>\n", 1);
// 	return (0);
// }
