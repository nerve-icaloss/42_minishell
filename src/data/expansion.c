/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <hmelica@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 18:23:30 by hmelica           #+#    #+#             */
/*   Updated: 2023/10/14 18:23:33 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*extract_value(char **line, int *i, t_lstvar lst)
{
	int		j;
	char	*name;
	char	*ret;

	j = 0;
	while ((*line)[*i + j] && !ft_isspace((*line)[*i + j]))
		j++;
	name = ft_substr(*line, *i, j);
	ret = var_get_value(lst, name);
	free(name);
	*i += j;
	return (ret);
}

void	var_expansion(char **line, t_myenv *myenv)
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
		while ((*line)[i + j] && ((*line)[i + j] != '$'
					|| ((*line[i + j + 1] == '$' && ++j))))
			j++;
		ret = ft_strjoin2(ret, ft_substr(*line, i, j), 1, 1);
		i += j;
		if ((*line)[i - 1] == '$' && ++i)
			ret = ft_strjoin2(ret, extract_value(line, &i, myenv->lst_var),
					1, 0);
		j = 0;
	}
	free(*line);
	*line = ret;
}
