/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addzikow <addzikow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 16:15:00 by addzikow          #+#    #+#             */
/*   Updated: 2021/07/03 22:46:20 by addzikow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _XOPEN_SOURCE 700
#include "../../includes/minitalk.h"

pid_t client_pid = 0;

void    print_pid(void)
{
    char *pid;

    pid = ft_itoa(getpid());
    write(1, "PID: ", 5);
    write(1, pid, ft_strlen(pid));
    write(1, "\n", 1);
    free(pid);
}

void	send_to_client(int signal)
{
	if (kill(client_pid, signal) == -1)
	{
		printf("minitalk: a signal error has occurred.\n");
		exit(EXIT_FAILURE);
	}
}

static int	alloc(char **str, size_t current, char c)
{
	char	*tmp;
	size_t	i;

	i = -1;
	if (*str == NULL)
	{
		*str = malloc((128 + 1) * sizeof(char *));
		if (*str == NULL)
			return (-1);
		return ((*str)[current] = c);
	}
	if (current >= (current + 1))
	{
		tmp = malloc((128 + 1 + current) * sizeof(char *));
		if (tmp == NULL)
			return (-1);
		while (++i < current)
			tmp[i] = (*str)[i];
		free(*str);
		tmp[i] = c;
		*str = tmp;
		return (true);
	}
	return ((*str)[current] = c);
}

static void	exit_server(char **str)
{
	if (*str != NULL)
	{
		free(*str);
		*str = NULL;
	}
	printf("minitalk: a memory error has occurred.\n");
	exit(EXIT_FAILURE);
}

void	add_char(char c)
{
	static long	current = 0;
	static char	*str = NULL;
	int			ret;

	if (c == '\0')
	{
		ret = alloc(&str, current++, '\n');
		if (ret == -1)
			exit_server(&str);
		ret = alloc(&str, current++, c);
		if (ret == -1)
			exit_server(&str);
		write(1, str, current);
		free(str);
		str = NULL;
		current = 0;
		send_to_client(SIGUSR2);
		return ;
	}
	ret = alloc(&str, current++, c);
	if (ret == -1)
		exit_server(&str);
}

void    recover_bits(int sig)
{
    static char c = 0;
    static int bits = 0;

    c += (sig << bits++);
    if (bits == 8)
    {
 
        add_char(c);
        c = 0;
        bits = 0;
    }
}

void    handle_signal(int sig, siginfo_t *info, void *context)
{   
    (void)context;

    if (sig == SIGUSR1)
        recover_bits(0);
    if (sig == SIGUSR2)
        recover_bits(1);
    if (info->si_pid > 0)
		client_pid = info->si_pid;
    if (kill(client_pid, SIGUSR1) == -1)
	{
		printf("minitalk: a signal error has occurred.\n");
		exit(EXIT_FAILURE);
	}
}

int	main(void)
{
	struct sigaction	act;

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
