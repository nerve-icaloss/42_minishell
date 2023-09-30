

#include "../headers/minishell.h"

t_myexec	*new_exec(char *str)
{
	t_myexec	*exec;

	exec = malloc(sizeof(*exec));
	if (!exec)
		return (NULL);
	exec->pid = -1;
	exec->input = ft_strdup(str);
	exec->parsing = new_element(str, input);
	exec->cmd_count = -1;
	exec->cmdtab = NULL;
	return (exec);
}

void	add_exec_left(t_exectree *exectree, t_myexec *exec)
{

}

void	add_exec_right(t_exectree *exectree, t_myexec *exec)
{

}

void	clean_exectree(t_exectree *exectree)
{
	t_myexec *current;

	current = *exectree;
	free(current);
	*exectree = NULL;
}
