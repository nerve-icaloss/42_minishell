/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:10:03 by nserve            #+#    #+#             */
/*   Updated: 2023/10/14 14:28:06 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_utils.h"
#include "parser.h"

t_node *choose_first_child(t_token *tok, t_myenv *env)
{
	t_source	*src;
	t_node	*cmd;

	if (!tok)
		return (errno = ENODATA, NULL);
	if (tok->type == TOK_WORD)
		cmd = parse_command(tok, env);
	else if (tok->type == TOK_BRACKET)
	{
		src = tok->src;
		token_clean(tok);
		tok = tokenize(src);
		cmd = parse_bracket(tok, env);
	}
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

t_node *insert_lvl_parent(t_node *parent, t_token *tok, int type)
{
	t_node		*lvl;

	if (!parent || !tok)
		return (errno = ENODATA, NULL);
	if (parent->type == type && tok->type == type)
		return (token_clean(tok), parent);
	lvl = node_new(type);
	if (!lvl)
		return (NULL);
	lvl->fd[IN] = -1;
	lvl->fd[OUT] = -1;
	if ((parent)->type < type)
		node_parent_add(parent, lvl);
	if (parent->type > type)
		node_parent_insert(parent, lvl);
	parent = lvl;
	return (token_clean(tok), parent);
}

t_node *choose_lvl(t_node *parent, t_token *tok, int node_type, t_myenv *env)
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
		cmd = parse_bracket(tok, env);
	}
	else if (tok->type == TOK_WORD)
		cmd = parse_command(tok, env);
	else if (tok->type <= node_type)
		cmd = parse_lvl(parent, tok, (node_type - 1), env);
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
	if (parent->type > child->type)
	{
		node_child_add(parent, child);
		return (parent);
	}
	else
		return (child);
}

void	handle_error_and_clean(t_node *parent, t_token *tok, int type)
{
	t_source	*src;

	if (!parent || !tok)
		return (errno = ENODATA, (void)NULL);
	src = tok->src;
	if (type != NODE_BRACKET)
		if (type < tok->type && tok->type < TOK_EOF)
			untokenize(src);
	if (tok->type == TOK_SYNTAX)
		parent->exit = 2;
	if (parent->children == 0 && type == NODE_PIPE)
	{
		if (type == NODE_PIPE)
			write(2, "bash: syntax error near unexpected token `|'", 44);
		if (type == NODE_OR)
			write(2, "bash: syntax error near unexpected token `||'", 44);
		if (type == NODE_AND)
			write(2, "bash: syntax error near unexpected token `&&'", 44);
		if (type == NODE_BRACKET)
			write(2, "bash: syntax error near unexpected token `('", 44);
		parent->exit = 2;
	}
	token_clean(tok);
}
