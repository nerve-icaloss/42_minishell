/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <hmelica@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 18:23:30 by hmelica           #+#    #+#             */
/*   Updated: 2023/10/26 15:57:02 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static char	*extract_value(char *line, t_myenv *env)
{
	int		j;
	char	*name;
	char	*ret;

	j = 0;
	while (line[j] && ft_isalnum(line[j]))
		j++;
	if (j == 0 && line[j] == '\0')
		return (ft_strdup("$"));
	name = ft_substr(line, 0, j);
	if (ft_strlen(name) == 1 && *name == '?')
		ret = ft_itoa(*env->exit);
	else
		ret = ft_strdup(var_get_value(env->lst_var, name));
	if (name)
		free(name);
	ft_offset(line, j);
	return (ret);
}

void	var_replace(char **start, char **p, t_myenv *env, char *k)
{
	size_t				len;
	char				*i;
	char				*j;

	if (!start || !*start || !p || !*p || !k)
		return ;
	i = extract_value(k + 1, env);
	if (!i)
		return (ft_offset(k, 1));
	*k = '\0';
	len = ft_strlen(i);
	j = ft_strjoin2(*start, i, 0, 1);
	if (!j)
		return ;
	i = *start;
	*start = ft_strjoin2(j, k + 1, 1, 0);
	if (i)
		free(i);
	*p = *start + len;
}

void	var_expansion(char **line, t_myenv *env)
{
	char				*p;
	char				*i;
	char				*j;
	char				*k;

	if (!env || !line || !*line)
		return (errno = ENODATA, (void) NULL);
	p = *line;
	k = ft_strchr(p, '$');
	while (p && *p && k)
	{
		i = ft_strchr(p, '"');
		j = ft_strchr(p, '\'');
		if ((!j || j > k || (i && i < j)))
		{
			var_replace(line, &p, env, k);
		}
		else if (j && j < k && (!i || j < i))
			p = ft_strchr(j + 1, *j);
		k = ft_strchr(p, '$');
	}
}
