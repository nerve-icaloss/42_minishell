

#include "../headers/minishell.h"

t_myexec	*exec_init(char *str)
{
	t_myexec	*exec;

	exec = malloc(sizeof(*exec));
	if (!exec)
		return (NULL);
	exec->pid = -1;
	exec->input = ft_strdup(str);
	exec->parsing = token_init(str, input);
	exec->cmd_count = -1;
	exec->cmdtab = NULL;
	return (exec);
}

void	exec_addleft(t_exectree *exectree, t_myexec *exec)
{

}

void	exec_addright(t_exectree *exectree, t_myexec *exec)
{

}

void	exectree_clean(t_exectree *exectree)
{
	t_myexec *current;

	current = *exectree;
	free(current);
	*exectree = NULL;
}
