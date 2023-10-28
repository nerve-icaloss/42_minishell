/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:10:03 by nserve            #+#    #+#             */
/*   Updated: 2023/10/28 15:55:09 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/parser.h"

t_node	*bracket_first_child(t_token *tok)
{
	t_source	*src;
	t_node		*cmd;

	if (!tok)
		return (errno = ENODATA, NULL);
	src = tok->src;
	if (tok->type == TOK_EOB)
	{
		syntax_error_token(TOK_EOB);
		token_clean(tok);
		cmd = node_new(NODE_CMD);
		if (!cmd)
			return (NULL);
		cmd->exit = 2;
	}
	else
	{
		token_clean(tok);
		tok = tokenize(src);
		cmd = parse_bracket(tok);
	}
	return (cmd);
}

t_node	*choose_first_child(t_token *tok)
{
	t_source	*src;
	t_node		*cmd;

	if (!tok)
		return (errno = ENODATA, NULL);
	src = tok->src;
	if (tok->type == TOK_WORD)
		cmd = parse_command(tok);
	else if (tok->type == TOK_BRACKET || tok->type == TOK_EOB)
		cmd = bracket_first_child(tok);
	else
	{
		if (tok->type < TOK_EOB)
			syntax_error_token(tok->type);
		token_clean(tok);
		cmd = node_new(NODE_CMD);
		if (!cmd)
			return (NULL);
		cmd->exit = 2;
	}
	return (cmd);
}

t_node	*insert_lvl_parent(t_node *parent, t_token *tok, int type)
{
	t_node		*lvl;

	if (!parent || !tok)
		return (errno = ENODATA, NULL);
	if (parent->type == type && tok->type == type)
		return (token_clean(tok), parent);
	lvl = node_new(type);
	if (!lvl)
		return (NULL);
	if ((parent)->type < type)
		node_parent_add(parent, lvl);
	if (parent->type > type)
		node_parent_insert(parent, lvl);
	parent = lvl;
	return (token_clean(tok), parent);
}

t_node	*choose_lvl(t_node *parent, t_token *tok, int node_type)
{
	t_source	*src;
	t_node		*cmd;

	if (!parent || !tok)
		return (errno = ENODATA, NULL);
	if (tok->type == TOK_BRACKET)
	{
		src = tok->src;
		token_clean(tok);
		tok = tokenize(src);
		cmd = parse_bracket(tok);
	}
	else if (tok->type == TOK_WORD)
		cmd = parse_command(tok);
	else if (tok->type <= node_type)
		cmd = parse_lvl(parent, tok, (node_type - 1));
	else
		cmd = NULL;
	if (cmd && cmd->exit)
		parent->exit = cmd->exit;
	return (cmd);
}

t_node	*insert_lvl_child(t_node *parent, t_node *child)
{
	t_node	*parent_child;

	if (!parent || !child)
		return (errno = ENODATA, NULL);
	if (parent == child)
		return (parent);
	if (parent->type == NODE_BRACKET)
		return (node_tree_clean(child), parent);
	if (parent->type == NODE_CMD && child->type == NODE_BRACKET)
		return (node_tree_clean(parent), child);
	if (parent->type > child->type)
	{
		parent_child = parent->first_child;
		while (parent_child)
		{
			if (parent_child == child)
				return (parent);
			parent_child = parent_child->next_sibling;
		}
		node_child_add(parent, child);
		return (parent);
	}
	else
		return (child);
}
