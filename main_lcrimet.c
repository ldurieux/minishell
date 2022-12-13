/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_lcrimet.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <lcrimet@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 22:13:18 by ldurieux          #+#    #+#             */
/*   Updated: 2022/12/13 15:18:19 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifdef LCRIMET
# include "input.h"
# include "exec.h"
# include "vars.h"
# include <stdio.h>

int	main(int argc, char **argv, char **envp)
{
	t_exec	exec;
	t_ftmap	*vars;
	char	*cmd;

	(void)argc;
	(void)argv;
	vars = get_vars(envp);
	exec_init(&exec, ft_vars_to_envp(vars));
	cmd = get_input("minishell > ");
	exec_add_cmd(&exec, cmd, NULL);
	exec_run(&exec);
	ft_print_env_map(vars);
	ft_free_map(vars);
	return (0);
}
#endif
