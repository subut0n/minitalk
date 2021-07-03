/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addzikow <addzikow@42student.lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 16:15:00 by addzikow          #+#    #+#             */
/*   Updated: 2021/06/24 19:18:53 by addzikow         ###   ########lyon.fr   */
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


char    *add_char_buffer(char c, char *str)
{
    char *ret;
    int size;
    int i;

    size = 0;
    while (str[size])
        size++;
    ret = malloc(sizeof(char) * (size + 1));
    if (!ret)
    {
        printf("minitalk: Memory allocation issue.");
        exit (EXIT_FAILURE);
    }
    i = -1;
    while (str[++i])
        ret[i] = str[i];
    ret[i + 1] = c;
    free(str);
    return (ret);
}

void    recover_bits(int sig, char *str)
{
    static char c = 0;
    static int bits = 0;

    c += (sig << bits++);
    if (bits == 8)
    {
        if (c == '\0')
        {
            str = add_char_buffer('\n', str);
            str = add_char_buffer(c, str);
            ft_putstr_fd(str, 1);
            free(str);
        }
        else
            str = add_char_buffer(c, str);
        c = 0;
        bits = 0;
    }
}
void    handle_signal(int sig, siginfo_t *info, void *context)
{   
    char *str;
    (void)context;

    str = malloc(sizeof(char));
    if (sig == SIGUSR1)
        recover_bits(0, str);
    if (sig == SIGUSR2)
        recover_bits(1, str);
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

////////////////////////////////////////////////////////////////

// void	print_pid(void)
// {
// 	ft_putstr_fd("Server PID: ", 1);
// 	ft_putnbr_fd(getpid(), 1);
// 	ft_putchar_fd('\n', 1);
// }

// void	write_char(int sig)
// {
// 	static char unsigned	c = 0;
// 	static int				i = 0;

// 	c |= (sig << i++);
// 	if (i > 7)
// 	{
// 		if (c == '\0')
// 		{
// 			ft_putchar_fd('\n', 1);
// 			ft_putchar_fd(c, 1);
// 		}
// 		else
// 			ft_putchar_fd(c, 1);
// 		i = 0;
// 		c = 0;
// 	}
// }

// void	write_signal(int sig, siginfo_t *info, void *context)
// {
// 	if (sig == SIGUSR1)
// 		write_char(0);
// 	if (sig == SIGUSR2)
// 		write_char(1);
// 	(void)context;
// 	kill(info->si_pid, SIGUSR1);
// }

// void	init_signal(void)
// {
// 	struct sigaction	sa;

// 	sa.sa_flags = SA_SIGINFO;
//     sa.sa_sigaction = write_signal;
// 	if (sigaction(SIGUSR1, &sa, NULL) == -1)
// 	{
// 		ft_putstr_fd("Error: initialize of signal is failed", 1);
// 		exit(0);
// 	}
// 	if (sigaction(SIGUSR2, &sa, NULL) == -1)
// 	{
// 		ft_putstr_fd("Error: initialize of signal is failed", 1);
// 		exit(0);
// 	}
// }

// int	main(void)
// {
// 	print_pid();
// 	init_signal();
// 	while (1)
// 		pause();
// 	return (0);
// }