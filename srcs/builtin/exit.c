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

int	main_exit(int argc, char **argv, char **envp, t_ftmap *vars)
{
	int		res;
	t_vars	*var;

	(void)envp;
	if (argc < 2)
	{
		var = ft_map_find(vars, "?");
		if (!var || !var->value)
			exit(0);
		exit(ft_atoi(var->value));
	}
	res = ft_atoi(argv[1]);
	exit(res);
}
