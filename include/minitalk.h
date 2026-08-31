/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmagand <jmagand@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-17 18:39:44 by jmagand           #+#    #+#             */
/*   Updated: 2025-02-17 18:39:44 by jmagand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H
# define STRING_LEN 128
# define MAX_ATTEMPTS 250000 // 250000µs = 0.25s

# include "../libft/libft.h"
# include <signal.h>
# include <stdbool.h>
# include <stdlib.h>

typedef struct s_string
{
	char	*string;
	int		bit_count;
	int		char_count;
	char	current_char;
	long	capacity;
	int		is_complete;
}			t_string;

void	handle_message(t_string *g_string, __pid_t client_pid);

#endif
