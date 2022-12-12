#include "exec.h"
#include "exec_internal.h"

char	**make_argv(char *cmd, char **args, int *argc)
{
	t_ftvector	*vec;
	int			idx;

	idx = -1;
	vec = ft_vector_new(sizeof(char *), 64);
	if (!vec)
		return (NULL);
	if (!ft_vector_push_back(vec, cmd))
		return (ft_vector_delete(vec), NULL);
	//TODO
	(void)idx;
	(void)args;
	(void)argc;
	return (NULL);
}
