/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmagand <jmagand@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-17 18:51:01 by jmagand           #+#    #+#             */
/*   Updated: 2025-02-17 18:51:01 by jmagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

volatile sig_atomic_t	g_signal_received = 0;

static void	sigusr_handler(int signum)
{
	if (signum == SIGUSR2)
		g_signal_received = 1;
	else if (signum == SIGUSR1)
	{
		ft_putendl_fd("\nSuccess:", 1);
		ft_putendl_fd("String received", 1);
	}
}

static void	send_char(char c, __pid_t server_pid)
{
	int	i;
	int	total_wait;

	i = 0;
	while (i < 8)
	{
		g_signal_received = 0;
		if (c & (1 << i))
			kill(server_pid, SIGUSR2);
		else
			kill(server_pid, SIGUSR1);
		total_wait = 0;
		while (!g_signal_received && total_wait < MAX_ATTEMPTS)
		{
			usleep(100);
			total_wait += 100;
		}
		if (total_wait >= MAX_ATTEMPTS)
		{
			ft_putendl_fd("\nError:", 2);
			ft_putendl_fd("No response from server", 2);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

static void	send_string(char *s, __pid_t server_pid)
{
	int	i;

	i = 0;
	while (s[i])
		send_char(s[i++], server_pid);
	send_char('\0', server_pid);
}

static bool	check_args(int ac, char **av)
{
	int	i;

	if (ac != 3 || av[2][0] == '\0')
	{
		ft_putendl_fd("Error:", 2);
		if (ac != 3)
			ft_putendl_fd("./client <server_pid> <string>", 2);
		else if (av[2][0] == '\0')
			ft_putendl_fd("String is null", 2);
		return (false);
	}
	i = 0;
	while (av[1][i])
	{
		if (!ft_isdigit(av[1][i]))
		{
			ft_putendl_fd("Error:", 2);
			ft_putendl_fd("PID must contains only digits", 2);
			return (false);
		}
		i++;
	}
	return (true);
}

int	main(int ac, char **av)
{
	struct sigaction	s_act;
	__pid_t				server_pid;
	int					i;

	i = 0;
	if (!check_args(ac, av))
		return (1);
	server_pid = ft_atoi(av[1]);
	if (server_pid == 0)
	{
		ft_putendl_fd("PID must be a positive value", 2);
		return (1);
	}
	s_act.sa_handler = sigusr_handler;
	sigemptyset(&s_act.sa_mask);
	s_act.sa_flags = 0;
	if (sigaction(SIGUSR1, &s_act, NULL) == -1 || sigaction(SIGUSR2, &s_act,
			NULL) == -1 || sigaction(SIGINT, &s_act, NULL) == -1)
		return (1);
	send_string(av[2], server_pid);
	return (0);
}
