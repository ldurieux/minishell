/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_lcrimet.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <lcrimet@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 22:13:18 by ldurieux          #+#    #+#             */
/*   Updated: 2022/12/13 11:33:31 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifdef LCRIMET
#include "input.h"
#include "exec.h"
#include "vars.h"
#include <stdio.h>

int	main(int argc, char **argv, char **envp)
{
	t_exec	exec;
	t_ftmap	*vars;
	int		ret_code;
	char	**envp_2;
	(void)argc;
	(void)argv;
	vars = get_vars(envp);
	envp_2 = ft_vars_to_envp(vars);
	exec_init(&exec, envp);
	exec_add_cmd(&exec, get_input("minishell > "), NULL);
	ret_code = exec_run(&exec);
	exec_destroy(&exec);
	printf("%s\n", envp_2[0]);
	// vars = ft_add_var("MINISHELL=EZ", SHELL, vars);
	// ft_print_env_map(vars);
	return (ret_code);
}
#endif
