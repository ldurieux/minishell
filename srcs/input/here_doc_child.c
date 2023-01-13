/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_child.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurieux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 15:09:17 by ldurieux          #+#    #+#             */
/*   Updated: 2023/01/12 15:09:19 by ldurieux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

static void	handle_abort_line(int sign)
{
	(void) sign;
	write(1, "\n", 1);
	exit(127);
}

char	*here_doc_child(char *end_str, char *ps2, int fd)
{
	char			*buffer;
	t_ftvector		*str;
	struct termios	attributes;
	int				i;

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
		free(buffer);
		buffer = readline(ps2);
	}
	ft_vector_push_back(str, "\0");
	write(fd, str->data, ft_strlen(str->data));
	free(buffer);
	exit(0);
}
