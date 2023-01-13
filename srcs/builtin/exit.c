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
			res = 0;
		else
			res = ft_atoi(var->value);
		ft_free_map(vars);
		exit(res);
	}
	res = ft_atoi(argv[1]);
	ft_free_map(vars);
	exit(res);
}
