/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <lcrimet@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 10:58:34 by lcrimet           #+#    #+#             */
/*   Updated: 2022/12/13 15:22:12 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef VARS_H
# define VARS_H

# include "ft_map.h"
# include "libft.h"
# include <stdint.h>
# include <stdio.h>

# define ENV 1
# define SHELL 0

typedef struct s_vars
{
	char	*value;
	char	*name;
	uint8_t	env;
}	t_vars;

/**
 * @param envp name=value must be allocated
 */
t_ftmap	*ft_add_var(char *envp, uint8_t env, t_ftmap *vars);
t_ftmap	*get_vars(char **envp);
char	**ft_vars_to_envp(t_ftmap *vars);
void	ft_free_map(t_ftmap *vars);
void	ft_print_shell_map(t_ftmap *vars);
void	ft_print_env_map(t_ftmap *vars);

#endif
