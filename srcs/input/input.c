/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <lcrimet@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 10:56:37 by lcrimet           #+#    #+#             */
/*   Updated: 2023/01/12 14:38:43 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "exec.h"

static void	handle_abort_line(int sign)
{
	int	i;

	i = 0;
	(void) sign;
	if (!g_pids)
	{
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
	else
	{
		while (g_pids[i])
		{
			write(1, "\n", 1);
			kill(g_pids[i], SIGINT);
			i++;
		}
	}
}

static void	handle_quit(char *str, struct termios saved)
{
	if (!str)
	{
		tcsetattr(STDIN_FILENO, TCSANOW, &saved);
		rl_clear_history();
		write(1, "exit\n", 5);
		exit(0);
	}
}

char	*get_input(char *ps1)
{
	char			*buffer;
	struct termios	saved;
	struct termios	attributes;

	tcgetattr(STDIN_FILENO, &saved);
	tcgetattr(STDIN_FILENO, &attributes);
	attributes.c_lflag &= ECHO;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &attributes);
	signal(SIGINT, handle_abort_line);
	buffer = NULL;
	while (!buffer)
	{
		buffer = readline(ps1);
		handle_quit(buffer, saved);
	}
	add_history(buffer);
	tcsetattr(STDIN_FILENO, TCSANOW, &saved);
	return (buffer);
}
