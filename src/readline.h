/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 12:33:48 by marvin            #+#    #+#             */
/*   Updated: 2023/09/15 11:53:31 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READLINE_H
# define READLINE_H

# include "../headers/minishell.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>

void	prompt_loop(t_myshell *shell);

#endif // !READLINE_H
