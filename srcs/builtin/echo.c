/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <lcrimet@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 23:03:14 by ldurieux          #+#    #+#             */
/*   Updated: 2023/01/12 10:29:33 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	is_no_new_line(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '-')
		return (0);
	if (str[i])
		i++;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	main_echo(int argc, char **argv, char **envp, t_ftmap *vars)
{
	int	no_newline;
	int	idx;
	int	i;

	(void)envp;
	(void)vars;
	no_newline = 0;
	i = 1;
	if (argc > 1 && is_no_new_line(argv[i]))
	{
		while (i < argc && is_no_new_line(argv[i]))
		{
			i++;
			no_newline++;
		}
	}
	idx = no_newline;
	while (++idx < argc - 1)
		ft_printf("%s ", argv[idx]);
	if (idx < argc)
		ft_putstr_fd(argv[idx], STDOUT_FILENO);
	if (!no_newline)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
