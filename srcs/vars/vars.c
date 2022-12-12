/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcrimet <lcrimet@student.42lyon.fr >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 16:35:38 by lcrimet           #+#    #+#             */
/*   Updated: 2022/12/12 18:22:28 by lcrimet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/includes/ft_map.h"
#include <stdint.h>
#include <stdio.h>

#ifdef n

R"("/*)"
#endif

typedef struct s_vars
{
	char	*value;
	char	*name;
	uint8_t	env;
}	t_vars;

void	ft_free_var(void *var)
{
	free(((t_vars *)var)->name);
	free(var);
}

void	ft_free_map(t_ftmap *vars)
{
	ft_map_iter(vars, ft_free_var);
	ft_map_delete(vars);
}

t_vars	*ft_fill_map_val(char *envp)
{
	t_vars	*map_val;

	map_val = malloc(sizeof(t_vars));
	if (!map_val)
		return (NULL);
	map_val->name = ft_strtok_r((const char *)envp, "=",
			(const char **)&map_val->value);
	if (!map_val->name || !*map_val->value)
	{
		free(map_val->name);
		free(map_val);
		return (NULL);
	}
	map_val->value++;
	map_val->env = 1;
	return (map_val);
}

t_vars	*ft_add_map_val(char *envp, uint8_t env)
{
	t_vars	*map_val;

	map_val = malloc(sizeof(t_vars));
	if (!map_val)
		return (NULL);
	map_val->name = ft_strtok_r((const char *)envp, "=",
			(const char **)&map_val->value);
	if (!map_val->name || !*map_val->value)
	{
		free(map_val->name);
		free(map_val);
		return (NULL);
	}
	map_val->value++;
	map_val->env = env;
	return (map_val);
}

t_ftmap	*get_vars(char **envp)
{
	int		i;
	t_ftmap	*vars;
	t_vars	*map_val;

	i = 0;
	vars = ft_map_new(256);
	if (!vars)
		return (0);
	while (envp && envp[i])
	{
		map_val = ft_fill_map_val(envp[i]);
		if (!map_val)
			return (ft_free_map(vars), NULL);
		if (!ft_map_insert(vars, map_val->name, map_val))
			return (ft_free_map(vars), NULL);
		i++;
	}
	return (vars);
}

void	ft_print_var_info(void *var_map)
{
	if (((t_vars *)var_map)->env)
		printf("%s=%s\n", ((t_vars *)var_map)->name, ((t_vars *)var_map)->value);
}

void	ft_print_env_map(t_ftmap *vars)
{
	ft_map_iter(vars, ft_print_var_info);
}

void	ft_print_shell_info(void *var_map)
{
	printf("%s=%s\n", ((t_vars *)var_map)->name, ((t_vars *)var_map)->value);
}

void	ft_print_shell_map(t_ftmap *vars)
{
	ft_map_iter(vars, ft_print_shell_info);
}

int	main(int argc, char **argv, char **envp)
{
	t_ftmap	*vars;

	(void) argc;
	(void) argv;
	envp = 0;
	vars = get_vars(envp);
	ft_add_map_val("TEST=ca marche", 0); // TODO RAF
	ft_print_shell_map(vars);
	return (0);
}

#ifdef n
*/
#endif
