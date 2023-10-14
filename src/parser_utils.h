/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 18:24:18 by nserve            #+#    #+#             */
/*   Updated: 2023/10/10 18:24:22 by nserve           ###   ########.fr       */
/*                                                                            */
/* **************************************:class MyClass : public QObject {
	Q_OBJECT;
public:

explicit MyClass(QObject *parent = nullptr);
	
signals:

public slots:
};************************************ */

#ifndef PARSER_UTILS_H
# define PARSER_UTILS_H

# include "../headers/minishell.h"

t_node *choose_first_child(t_token *tok);
t_node *insert_lvl_parent(t_node *parent, t_token *tok, int type);
t_node *choose_next_lvl(t_node *parent, t_token *tok, int node_type);
t_node *insert_lvl_child(t_node *parent, t_node *child);
void handle_error_and_clean(t_node *parent, t_token *tok, int type);
t_node	*parse_bracket(t_token *tok);

#endif
