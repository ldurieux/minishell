/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_abort_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurieux <ldurieux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 18:44:00 by ldurieux          #+#    #+#             */
/*   Updated: 2023/01/14 18:44:03 by ldurieux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	handle_abort_line_input(int sign)
{
	(void) sign;
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
	g_process_killed = 2;
}

void	handle_abort_line_exec(int sign)
{
	(void)sign;
	g_process_killed = 1;
}

void	handle_abort_line_here_doc(int sign)
{
	(void) sign;
	write(1, "\n", 1);
	exit(127);
}
