/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurieux <ldurieux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 22:13:18 by ldurieux          #+#    #+#             */
/*   Updated: 2022/12/09 22:13:20 by ldurieux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifdef LDURIEUX

# include "exec.h"
# include "vars.h"
# include "ft_printf.h"
# include <fcntl.h>

int	main(int argc, char **argv, char **envp)
{
	t_exec		exec;
	int			ret_code;
	t_ftmap		*vars;
	char		**args;

	(void)argc;
	(void)argv;
	args = ft_calloc(sizeof(char *), 2);
	args[0] = ft_strdup("test");
	vars = get_vars(envp);
	exec_init(&exec, envp, vars);
	exec_add_cmd(&exec, ft_strdup("pwd"), args);
	ret_code = exec_run(&exec);
	exec_destroy(&exec);
	return (ret_code);
}
#endif
