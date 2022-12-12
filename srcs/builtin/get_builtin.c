/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurieux <ldurieux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 23:03:21 by ldurieux          #+#    #+#             */
/*   Updated: 2022/12/12 23:03:22 by ldurieux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

t_builtin	get_builtin(char *name)
{
	if (ft_strcmp(name, "echo") == 0)
		return (main_echo);
	if (ft_strcmp(name, "cd") == 0)
		return (main_cd);
	if (ft_strcmp(name, "pwd") == 0)
		return (main_pwd);
	if (ft_strcmp(name, "export") == 0)
		return (main_export);
	if (ft_strcmp(name, "unset") == 0)
		return (main_unset);
	if (ft_strcmp(name, "env") == 0)
		return (main_env);
	if (ft_strcmp(name, "exit") == 0)
		return (main_exit);
	return (NULL);
}
