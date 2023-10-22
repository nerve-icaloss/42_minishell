/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <hmelica@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 18:23:30 by hmelica           #+#    #+#             */
/*   Updated: 2023/10/19 17:51:33 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion_var.h"

char	*extract_value(char **line, int *i, t_lstvar lst)
{
	int		j;
	char	*name;
	char	*ret;

	j = 0;
	while ((*line)[*i + j] && !ft_isspace((*line)[*i + j])
			&& (*line)[*i + j] != '$')
		j++;
	if (j == 0)
	{
		return (ft_substr(*line, *i - 1, 1));
	}
	name = ft_substr(*line, *i, j);
	if (ft_strlen(name) == 1 && *name == '?')
		ret = ft_itoa(0); // CHANGE TO LAST EXIT CODE
	else
		ret = var_get_value(lst, name);
	if (name)
		free(name);
	*i += j;
	return (ret);
}

void	var_expansion(char **line, t_myenv *env)
{
	char	*ret;
	int		i;
	int		j;

	if (!line || !*line)
		return ;
	ret = NULL;
	i = 0;
	j = 0;
	while ((*line)[i + j])
	{
		while ((*line)[i + j] && ((*line)[i + j] != '$'))
			j++;
		ret = ft_strjoin2(ret, ft_substr(*line, i, j), 1, 1);
		i += j;
		if ((*line)[i] && (*line)[i] == '$' && ++i)
			ret = ft_strjoin2(ret, extract_value(line, &i, env->lst_var),
					1, 0);
		j = 0;
	}
	free(*line);
	*line = ret;
}
