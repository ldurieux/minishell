/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <lcrimet@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 22:13:18 by ldurieux          #+#    #+#             */
/*   Updated: 2022/12/12 16:31:51 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifdef LCRIMET
#include "exec.h"
#include "input.h"
#include <stdio.h>

int	main(void)
{
	t_exec	exec;
	char	*str;

	exec_init(&exec, ft_strdup("/usr/bin"));
	for (int i = 0; i < 2; i++)
		exec_add_cmd(&exec, ft_strdup("/usr/bin/ls"), NULL);
	exec_run(&exec);
	exec_destroy(&exec);
	get_input("minishell > ");
	return (0);
}
#endif
