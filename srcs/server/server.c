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

void	send_to_client(int sig)
{
	if (kill(g_client_pid, sig) == -1)
	{
		write(2, "minitalk: signal error\n", 22);
		_exit(EXIT_FAILURE);
	}
}

void	handle_signal(int sig, siginfo_t *info, void *context)
{
	(void)context;
	if (info->si_pid > 0)
		g_client_pid = info->si_pid;
	if (sig == SIGUSR1)
		recover_bits(0);
	else if (sig == SIGUSR2)
		recover_bits(1);
	if (kill(g_client_pid, SIGUSR1) == -1)
	{
		write(2, "minitalk: signal error\n", 22);
		_exit(EXIT_FAILURE);
	}
}

int	main(int argc, char *argv[])
{
	struct sigaction	act;

	(void)argv;
	if (argc != 1)
	{
		ft_putstr_fd("./server does not support arguments.\n", 2);
		exit(EXIT_FAILURE);
	}
	sigemptyset(&act.sa_mask);
	sigaddset(&act.sa_mask, SIGUSR1);
	sigaddset(&act.sa_mask, SIGUSR2);
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = handle_signal;
	print_pid();
	if ((sigaction(SIGUSR1, &act, NULL) == -1)
		|| (sigaction(SIGUSR2, &act, NULL) == -1))
	{
		ft_putstr_fd("minitalk: signal setup failed\n", 2);
		exit(EXIT_FAILURE);
	}
	while (1)
		pause();
	return (0);
}
