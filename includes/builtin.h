/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurieux <ldurieux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 23:07:59 by ldurieux          #+#    #+#             */
/*   Updated: 2022/12/12 23:08:01 by ldurieux         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include <string.h>
# include <errno.h>
# include "libft.h"
# include "ft_printf.h"
# include "vars.h"

typedef int	(*t_builtin)(int, char **, char **, t_ftmap *);

t_builtin	get_builtin(char *name);

int			main_echo(int argc, char **argv, char **envp, t_ftmap *vars);
int			main_cd(int argc, char **argv, char **envp, t_ftmap *vars);
int			main_pwd(int argc, char **argv, char **envp, t_ftmap *vars);
int			main_export(int argc, char **argv, char **envp, t_ftmap *vars);
int			main_unset(int argc, char **argv, char **envp, t_ftmap *vars);
int			main_env(int argc, char **argv, char **envp, t_ftmap *vars);
int			main_exit(int argc, char **argv, char **envp, t_ftmap *vars);

void		export_no_args(t_ftmap *vars);

#endif // BUILTIN_H
