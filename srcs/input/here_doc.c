/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <lcrimet@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:04:55 by lcrimet           #+#    #+#             */
/*   Updated: 2022/12/12 16:45:35 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

static void	handle_abort_line(int sign)
{
	(void) sign;
	write(1, "\n", 1);
	exit (1);
}

char	*here_doc(char *end_str, char *ps2)
{
	char			*buffer;
	t_ftvector		*str;
	struct termios	saved;
	struct termios	attributes;
	int				i;

	tcgetattr(STDIN_FILENO, &saved);
	tcgetattr(STDIN_FILENO, &attributes);
	attributes.c_lflag &= ECHO;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &attributes);
	signal(SIGINT, handle_abort_line);
	str = ft_vector_new(sizeof(char), 32);
	buffer = readline(ps2);
	while (ft_strcmp(buffer, end_str) && buffer)
	{
		i = -1;
		while (buffer[++i])
			ft_vector_push_back(str, &buffer[i]);
		ft_vector_push_back(str, "\n");
		buffer = readline(ps2);
	}
	ft_vector_push_back(str, "\0");
	tcsetattr(STDIN_FILENO, TCSANOW, &saved);
	return (str->data);
}
