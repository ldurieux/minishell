/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurieux <ldurieux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 23:03:15 by ldurieux          #+#    #+#             */
/*   Updated: 2022/12/12 23:03:17 by ldurieux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	main_env(int argc, char **argv, char **envp, t_ftmap *vars)
{
	(void)argc;
	(void)argv;
	(void)envp;
	if (!vars)
		return (0);
	ft_print_env_map(vars);
	return (0);
}
