#include "input.h"
#include "parsing.h"

char	*here_doc_replace_vars(char *str, t_ftmap *vars)
{
	int		idx;
	char	*name;
	int		size;
	t_vars	*replacement_vars;

	idx = -1;
	while (str[++idx])
	{
		if (str[idx] != '$' || !str[idx + 1])
			continue ;
		name = get_var_name(str + idx + 1);
		if (!name)
			return (str);
		replacement_vars = ft_map_find(vars, name);
		size = get_replaced_size(str, name, replacement_vars);
		str = create_new_str(str, size, replacement_vars, idx);
		free(name);
		if (!str)
			return (NULL);
		idx = -1;
	}
	return (str);
}
