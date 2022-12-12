/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_argv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurieux <ldurieux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 23:02:31 by ldurieux          #+#    #+#             */
/*   Updated: 2022/12/12 23:02:34 by ldurieux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "exec_internal.h"

char	**make_argv(char *cmd, char **args, int *argc)
{
	char	**argv;
	int		idx;

	idx = -1;
	if (args)
		while (args[++idx])
			;
	else
		idx = 0;
	argv = malloc(sizeof(char **) * idx + 2);
	if (!argv)
		return (NULL);
	if (argc)
		*argc = idx + 1;
	argv[0] = cmd;
	argv[idx + 1] = NULL;
	idx = -1;
	if (args)
		while (args[++idx])
			argv[idx + 1] = args[idx];
	return (argv);
}
