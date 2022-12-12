/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurieux <ldurieux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 23:03:17 by ldurieux          #+#    #+#             */
/*   Updated: 2022/12/12 23:03:18 by ldurieux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	main_exit(int argc, char **argv, char **envp)
{
	int	res;

	(void)envp;
	if (argc < 2)
	{
		ft_dprintf(STDERR_FILENO, "exit must be provided with either"
			"an error code or last error code\n");
		exit(0);
	}
	res = ft_atoi(argv[1]);
	exit(res);
}
