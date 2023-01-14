/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <lcrimet@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 10:56:37 by lcrimet           #+#    #+#             */
/*   Updated: 2023/01/13 13:52:17 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "exec.h"

static void	handle_quit(int sign)
{
	(void) sign;
	rl_redisplay();
}

static void	handle_exit(char *str, struct termios saved)
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
	signal(SIGINT, handle_abort_line_input);
	signal(SIGQUIT, handle_quit);
	buffer = NULL;
	while (!buffer)
	{
		buffer = readline(ps1);
		handle_exit(buffer, saved);
	}
	add_history(buffer);
	tcsetattr(STDIN_FILENO, TCSANOW, &saved);
	return (buffer);
}
