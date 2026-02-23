/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addzikow <addzikow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 12:05:42 by addzikow          #+#    #+#             */
/*   Updated: 2021/07/04 17:54:33 by addzikow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minitalk.h"

static volatile int	g_received = 0;

static void	server_response(int sig, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (sig == SIGUSR1)
		g_received = 1;
	else if (sig == SIGUSR2)
	{
		write(1, "minitalk: message sent with success!\n", 36);
		_exit(EXIT_SUCCESS);
	}
}

static pid_t	init_client(char *str)
{
	struct sigaction	act;
	pid_t				pid;

	pid = ft_atoi(str);
	if (pid <= 0)
	{
		ft_putstr_fd("Invalid PID\n", 2);
		exit(EXIT_FAILURE);
	}
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = server_response;
	if ((sigaction(SIGUSR1, &act, NULL) == -1)
		|| (sigaction(SIGUSR2, &act, NULL) == -1))
	{
		ft_putstr_fd("minitalk: signal setup failed\n", 2);
		exit(EXIT_FAILURE);
	}
	return (pid);
}

static void	send_bits(pid_t pid, char c)
{
	int	bit;
	int	sig;
	int	attempts;

	bit = 0;
	while (bit < 8)
	{
		if ((c >> bit) & 1)
			sig = SIGUSR2;
		else
			sig = SIGUSR1;
		g_received = 0;
		if (kill(pid, sig) == -1)
		{
			ft_putstr_fd("Message can not be sent.\n", 2);
			exit(EXIT_FAILURE);
		}
		attempts = 0;
		while (!g_received && attempts < 50)
		{
			usleep(100);
			attempts++;
		}
		bit++;
	}
}

int	main(int argc, char **argv)
{
	pid_t	pid;
	int		i;

	if (argc != 3)
	{
		ft_putstr_fd("Usage: ./client <pid> <message>\n", 2);
		exit(EXIT_FAILURE);
	}
	pid = init_client(argv[1]);
	i = 0;
	while (argv[2][i])
	{
		send_bits(pid, argv[2][i]);
		i++;
	}
	send_bits(pid, '\0');
	return (0);
}
