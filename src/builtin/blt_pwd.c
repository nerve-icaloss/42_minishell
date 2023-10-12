/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmelica <hmelica@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 21:35:07 by hmelica           #+#    #+#             */
/*   Updated: 2023/10/04 21:35:08 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	blt_pwd(char **argv, t_myenv env)
{
	char	str[4097];

	(void) argv;
	ft_bzero(str, 4097 * sizeof(char));
	if (!getcwd(str, 4097))
		return (ft_dprintf(2, "pwd: ERROR getting pwd\n"), 1);
	ft_printf("%s\n", str);
	return (0);
}
