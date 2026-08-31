/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmagand <jmagand@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-24 18:21:37 by jmagand           #+#    #+#             */
/*   Updated: 2025-03-24 18:21:37 by jmagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handle_message(t_string *g_string, __pid_t client_pid)
{
	ft_printf("%s\n", g_string->string);
	kill(client_pid, SIGUSR1);
	g_string->char_count = 0;
	g_string->bit_count = 0;
	g_string->current_char = 0;
	ft_memset(g_string->string, 0, g_string->capacity);
}
