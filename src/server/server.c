/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmagand <jmagand@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-17 18:51:36 by jmagand           #+#    #+#             */
/*   Updated: 2025-02-17 18:51:36 by jmagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

static t_string	*g_string = NULL;

static t_string	*init_g_string(void)
{
	t_string	*new_string;

	new_string = (t_string *)malloc(sizeof(t_string));
	if (!new_string)
	{
		ft_putendl_fd("\nError:", 2);
		ft_putendl_fd("Malloc failed for new_string", 2);
		new_string = NULL;
		exit(EXIT_FAILURE);
	}
	new_string->string = (char *)malloc(STRING_LEN * sizeof(char));
	if (!new_string->string)
	{
		ft_putendl_fd("\nError:", 2);
		ft_putendl_fd("Malloc failed for new_string->string", 2);
		free(new_string);
		exit(EXIT_FAILURE);
	}
	new_string->bit_count = 0;
	new_string->char_count = 0;
	new_string->current_char = 0;
	new_string->capacity = STRING_LEN;
	ft_memset(new_string->string, 0, STRING_LEN);
	return (new_string);
}

static int	handle_complete_char(__pid_t client_pid)
{
	size_t	new_len;
	char	*new_string;

	if (!g_string || !g_string->string)
		return (1);
	if (g_string->char_count >= g_string->capacity - 1)
	{
		new_len = g_string->capacity * 2;
		new_string = ft_realloc(g_string->string, g_string->capacity, new_len);
		if (!new_string)
		{
			ft_putendl_fd("\nError:", 2);
			ft_putendl_fd("Realloc failed for new_string", 2);
			return (1);
		}
		g_string->string = new_string;
		g_string->capacity = new_len;
	}
	g_string->string[g_string->char_count++] = g_string->current_char;
	if (g_string->current_char == '\0')
		handle_message(g_string, client_pid);
	return (0);
}

static void	receipt_signal(int signum, __pid_t client_pid)
{
	if (!g_string || !g_string->string)
		return ;
	if (signum == SIGUSR2)
		g_string->current_char |= (1 << g_string->bit_count);
	g_string->bit_count++;
	if (g_string->bit_count == 8)
	{
		if (handle_complete_char(client_pid))
		{
			if (g_string->string)
			{
				free(g_string->string);
				g_string->string = NULL;
			}
			if (g_string)
				free(g_string);
			exit(EXIT_FAILURE);
		}
		g_string->current_char = 0;
		g_string->bit_count = 0;
	}
}

static void	siginfo_handler(int signum, siginfo_t *info, void *ucontext)
{
	__pid_t	client_pid;

	(void)ucontext;
	client_pid = info->si_pid;
	if (signum == SIGINT)
	{
		if (g_string)
		{
			free(g_string->string);
			free(g_string);
		}
		exit(EXIT_SUCCESS);
	}
	if (!g_string)
	{
		g_string = init_g_string();
		if (!g_string)
		{
			ft_putendl_fd("Error:", 2);
			ft_putendl_fd("Failed to initialize g_string", 2);
			return ;
		}
	}
	receipt_signal(signum, client_pid);
	kill(client_pid, SIGUSR2);
}

int	main(int ac, char **av)
{
	struct sigaction	s_act;

	(void)av;
	if (ac != 1)
	{
		ft_putendl_fd("Error:", 2);
		ft_putendl_fd("Exec ./server doesn´t need arg", 2);
		return (EXIT_FAILURE);
	}
	s_act.sa_sigaction = siginfo_handler;
	sigemptyset(&s_act.sa_mask);
	s_act.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &s_act, NULL) == -1 || sigaction(SIGUSR2, &s_act,
			NULL) == -1 || sigaction(SIGINT, &s_act, NULL) == -1)
		return (1);
	ft_printf("\nServer PID = %d\n\n", getpid());
	while (1)
		pause();
	return (0);
}
