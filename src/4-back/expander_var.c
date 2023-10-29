/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <hmelica@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 18:23:30 by hmelica           #+#    #+#             */
/*   Updated: 2023/10/29 13:09:47 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static char	*extract_value(char *line, t_myenv *env)
{
	int		j;
	char	*name;
	char	*ret;

	j = 0;
	if (line[0] && line[0] == '?' && !ft_isalnum(line[1]))
		return (ft_offset(line, 1), ft_itoa(*env->exit));
	while (line[j] && (ft_isalnum(line[j]) || line[j] =='_'))
		j++;
	if (j == 0 && line[j] != '$')
		return (ft_strdup("$"));
	name = ft_substr(line, 0, j);
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
	len = ft_strlen(i) + ft_strlen(*start);
	j = ft_strjoin2(*start, i, 0, 1);
	if (!j)
		return ;
	i = *start;
	*start = ft_strjoin2(j, k + 1, 1, 0);
	if (i)
		free(i);
	*p = *start + len;
}

void	update_quotes(char *i[2], char *j[2], char *line, char *k)
{
	ft_memset(i, 0, sizeof (char *) * 2);
	ft_memset(j, 0, sizeof (char *) * 2);
	if (!k)
		return ;
	i[0] = ft_strchr(line, '"');
	if (i[0])
		i[1] = ft_strchr(i[0] + 1, '"');
	while (i[0] && i[1] && (i[1] < k))
	{
		i[0] = ft_strchr(i[1] + 1, '"');
		if (i[0])
			i[1] = ft_strchr(i[0] + 1, '"');
	}
	j[0] = ft_strchr(line, '\'');
	if (j[0])
		j[1] = ft_strchr(j[0] + 1, '\'');
	while (j[0] && j[1] && (j[1] < k))
	{
		j[0] = ft_strchr(j[1] + 1, '\'');
		if (j[0])
			j[1] = ft_strchr(j[0] + 1, '\'');
	}
}

/*
 * [0] is open
 * [1] is close
 * */
void	var_expansion(char **line, t_myenv *env)
{
	char	*p;
	char	*i[2];
	char	*j[2];
	char	*k;

	if (!env || !line || !*line)
		return (errno = ENODATA, (void) NULL);
	p = *line;
	k = ft_strchr(p, '$');
	while (p && *p && k)
	{
		update_quotes(i, j, *line, k);
		if ((!j[0] || !j[1] || j[0] > k || j[1] < k || (i[0] && i[1] && i[0]
					< j[0] && i[1] > j[0])))
		{
			var_replace(line, &p, env, k);
		}
		else if (j[0] && j[1] && j[0] < k && (!i[0] || !i[1] || j[0] < i[0]))
			p = j[1] + 1;
		k = ft_strchr(p, '$');
	}
}
