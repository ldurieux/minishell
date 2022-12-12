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

int	main_env(int argc, char **argv, char **envp)
{
	size_t	idx;

	(void)argc;
	(void)argv;
	if (!envp)
		return (0);
	idx = (size_t)-1;
	while (envp[++idx])
		ft_putendl_fd(envp[idx], STDOUT_FILENO);
	return (0);
}
