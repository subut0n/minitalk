/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addzikow <addzikow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 16:15:00 by addzikow          #+#    #+#             */
/*   Updated: 2021/07/04 19:43:24 by addzikow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minitalk.h"

pid_t	g_client_pid = 0;

void	print_pid(void)
{
	char	*pid;

	pid = ft_itoa(getpid());
	write(1, "PID: ", 5);
	write(1, pid, ft_strlen(pid));
	write(1, "\n", 1);
	free(pid);
}

void	send_to_client(int signal)
{
	if (kill(g_client_pid, signal) == -1)
	{
		printf("minitalk: a signal error has occurred.\n");
		exit(EXIT_FAILURE);
	}
}

void	handle_signal(int sig, siginfo_t *info, void *context)
{
	(void)context;
	if (sig == SIGUSR1)
		recover_bits(0);
	if (sig == SIGUSR2)
		recover_bits(1);
	if (info->si_pid > 0)
		g_client_pid = info->si_pid;
	if (kill(g_client_pid, SIGUSR1) == -1)
	{
		printf("minitalk: a signal error has occurred.\n");
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char *argv[])
{
	struct sigaction	act;

	(void)argv;
	if (argc != 1)
	{
		ft_putstr("./server does not support arguments.\n");
		exit(EXIT_FAILURE);
	}
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = handle_signal;
	print_pid();
	if ((sigaction(SIGUSR1, &act, NULL) == -1)
		|| (sigaction(SIGUSR2, &act, NULL) == -1))
	{
		printf("minitalk: a signal error has occurred.\n");
		exit(EXIT_FAILURE);
	}
	while ('1')
		pause();
	return (0);
}
