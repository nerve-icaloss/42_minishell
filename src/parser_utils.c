/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:10:03 by nserve            #+#    #+#             */
/*   Updated: 2023/10/06 15:10:12 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_utils.h"
#include "parser.h"

t_node *choose_first_child(t_source *src)
{
	t_token	*tok;
	t_node	*cmd;

	if (!src)
		return (errno = ENODATA, NULL);
	printf("welcome to first child\n");
	tok = tokenize(src);
	printf("tok_type=%u\n", tok->type);
	if (tok->type == TOK_WORD)
		cmd = parse_command(tok);
	else if (tok->type == TOK_BRACKET)
		cmd = parse_bracket(tok);
	else
	{
		token_clean(tok);
		cmd = node_new(NODE_CMD);
		if (!cmd)
			return (NULL);
		cmd->exit = 2;
	}
	return (cmd);
}

t_node *insert_lvl_parent(t_node *parent, t_token *tok, size_t type)
{
	t_node		*lvl;

	printf("insert parent lvl:%ld\n", type);
	printf("before: parent=%p | parent_type=%d | parent_parent=%p | parent_fchild=%p\n", parent, parent->type, parent->parent, parent->first_child);
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
		node_last_retrieve(parent, lvl);
	parent = lvl;
	return (token_clean(tok), parent);
}

t_node *choose_next_lvl(t_node *parent, t_token *tok, size_t node_type)
{
	t_node		*cmd;

	if (!parent || !tok)
		return (errno = ENODATA, NULL);
	if (tok->type == TOK_BRACKET)
		cmd = parse_bracket(tok);
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

t_node *insert_lvl_child(t_node *parent, t_node *child)
{
	if (!parent || !child)
		return (errno = ENODATA, NULL);
	printf("before: parent=%p | parent_type=%d | parent_parent=%p | parent_fchild=%p\n", parent, parent->type, parent->parent, parent->first_child);
	if (parent->type > child->type)
	{
		node_child_add(parent, child);
		return (parent);
	}
	else
		return (child);
}

void	handle_error_and_clean(t_node *parent, t_token *tok, size_t type)
{
	t_source	*src;

	if (!parent || !tok)
		return (errno = ENODATA, (void)NULL);
	src = tok->src;
	if (type < tok->type && tok->type < TOK_EOB)
		untokenize(src);
	if (tok->type == TOK_SYNTAX)
		parent->exit = 2;
	token_clean(tok);
}
