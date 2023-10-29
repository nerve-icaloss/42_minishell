/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 18:16:35 by nserve            #+#    #+#             */
/*   Updated: 2023/10/28 22:03:19 by hmelica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HERE_DOC_H
# define HERE_DOC_H

# include "minishell.h"

int		run_tree_doc(t_node *root, t_myenv *myenv);
int		here_doc(char *eof, t_myenv *env, int expand);
void	close_tree_doc(t_node *root);

#endif
