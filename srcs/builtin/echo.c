/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurieux <ldurieux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 23:03:14 by ldurieux          #+#    #+#             */
/*   Updated: 2022/12/12 23:03:15 by ldurieux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	main_echo(int argc, char **argv, char **envp)
{
	int	no_newline;
	int	idx;

	(void)envp;
	no_newline = 0;
	if (argc > 1 && ft_strcmp("-n", argv[1]) == 0)
		no_newline = 1;
	idx = no_newline;
	while (++idx < argc - 1)
		ft_printf("%s ", argv[idx]);
	if (idx < argc)
		ft_putstr_fd(argv[idx], STDOUT_FILENO);
	if (!no_newline)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
