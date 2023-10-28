/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <hmelica@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:05:03 by hmelica           #+#    #+#             */
/*   Updated: 2023/10/28 11:43:54 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/*
 * Replace every tilde by home directory. Returns -1 if no home set.
 * Returns the count of tilde if more than one tildes found. That means :
 *  - 1 tilde found : returns 0
 *  - 0 tilde found : returns 0
 *  - x tildes found : returns x (because it is not always normal to
 *    expand more than one tilde)
 * ret should be set to NULL
 * */
int	home_expand(const char *s, char **ret, t_myvar *var)
{
	int		count;
	int		i;
	int		j;

	if (!s || !ret || !var || !var->value)
		return (ft_dprintf(2, "minishell: HOME not set\n"), 
				*ret = ft_strdup(s), -1);
	i = 0;
	j = 0;
	count = 0;
	while (s && s[i + j])
	{
		while (s[i + j] && s[i + j] != '~')
			j++;
		*ret = ft_strjoin2(*ret, ft_substr(s, i, j), 1, 1);
		if (s[i + j] == '~' && ++i && ++count)
			*ret = ft_strjoin2(*ret, var->value, 1, 0);
		i += j;
		j = 0;
	}
	if (i == 0)
		return (*ret = ft_strdup(""), 0);
	if (count == 0 || count == 1 || !*ret)
		return (errno = ENOMEM * !*ret, -!*ret);
	return (count);
}

TEST_STATIC int	arg_parser_home(t_myenv *env, char **path)
{
	t_myvar	*var;

	var = var_get(env->lst_var, "HOME");
	if (!var || !var->value)
		return (ft_dprintf(2, "cd: HOME not set\n"), 1);
	*path = ft_strdup(var->value);
	if (!path)
		return (errno = ENOMEM, -1);
	return (0);
}

static int	arg_parser_oldpwd(t_myenv *env, char **path)
{
	t_myvar	*var;

	var = var_get(env->lst_var, "OLDPWD");
	if (!var || !var->value)
		return (ft_dprintf(2, "cd: OLDPWD not set\n"), 1);
	*path = ft_strdup(var->value);
	if (!path)
		return (errno = ENOMEM, -1);
	if (access(*path, F_OK) || !check_whole_path(*path))
		return (ft_dprintf(2, "cd: %s: %s\n", *path, strerror(errno)),
				free(*path), 1);
	ft_dprintf(1, "%s\n", *path);
	return (0);
}

/*
 * Controle les arguments pour cd
 * */
TEST_STATIC int	path_arg_parser(char **argv, t_myenv *env, char **path)
{
	if (!argv || !*argv || !path)
		return (-1);
	*path = NULL;
	if (argv[1] && argv[2])
		return (ft_dprintf(2, "cd: too many arguments\n"), 1);
	if (!argv[1])
		return (arg_parser_home(env, path));
	if ((ft_strlen(argv[1]) == 1 && *argv[1] == '-') || (ft_strlen(argv[1])
				== 2 && *argv[1] == '-' && argv[1][1] == '-'))
		return (arg_parser_oldpwd(env, path));
	*path = ft_strdup(argv[1]);
	return (0);
}

int	cd_builtin(char **argv, t_myenv *env)
{
	char	*path;

	if (path_arg_parser(argv, env, &path) || !path)
		return (1);
	if (access(path, F_OK) || !check_whole_path(path))
		return (ft_dprintf(2, "cd: %s: %s\n", path, strerror(errno)),
				free(path), 1);
	if (chdir(path))
		return (ft_dprintf(2, "cd: %s: %s\n", path, strerror(errno)),
				free(path), 1);
	free(path);
	path = getcwd(NULL, 0);
	if (!path)
		return (ft_dprintf(2, "cd: %s: %s\n", path, strerror(errno)), 1);
	if (!var_get(env->lst_var, "OLDPWD"))
		env->count++;
	if (!var_get(env->lst_var, "PWD"))
		env->count++;
	if (var_add(&env->lst_var, ft_strdup("OLDPWD"), ft_strdup(
				var_get_value(env->lst_var, "PWD")))
		|| var_add(&env->lst_var, ft_strdup("PWD"), path))
		return (-1);
	if (env_update_count(env) || envp_update(env))
		return (ft_dprintf(2, "WARN: minor error while updating envp\n"), 0);
	return (0);
}
