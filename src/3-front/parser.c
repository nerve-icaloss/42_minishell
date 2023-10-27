/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 09:38:10 by nserve            #+#    #+#             */
/*   Updated: 2023/10/26 19:38:27 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/parser.h"

t_node	*parse_word(t_token *tok)
{
	t_node			*word;

	if (!tok || !tok->txt)
		return (errno = ENODATA, NULL);
	word = node_word_new(find_word_type(tok->txt));
	if (!word)
		return (NULL);
	if (word->rtype > WORD)
	{
		parse_redir(tok, word);
	}
	else
	{
		node_val_set(word, tok->txt);
		token_clean(tok);
	}
	return (word);
}

t_node	*parse_command(t_token *tok)
{
	t_source	*src;
	t_node		*cmd;
	t_node		*word;

	if (!tok)
		return (errno = ENODATA, NULL);
	cmd = node_new(NODE_CMD);
	if (!cmd)
		return (token_clean(tok), NULL);
	src = tok->src;
	while (tok->type == TOK_WORD && !cmd->exit)
	{
		word = parse_word(tok);
		if (!word)
			return (node_tree_clean(cmd), NULL);
		node_child_add(cmd, word);
		tok = tokenize(src);
	}
	if ( 0 < src->tok_type && src->tok_type < TOK_EOF)
		untokenize(src);
	if (src->tok_type == TOK_SYNTAX || src->tok_type == TOK_BRACKET)
		cmd->exit = 2;
	return (token_clean(tok), cmd);
}

t_node	*parse_lvl(t_node *parent, t_token *tok, int node_type)
{
	t_source	*src;
	t_node		*cmd;

	if (!parent || parent->exit || !tok)
		return (errno = ENODATA, NULL);
	src = tok->src;
	while ((tok->type <= node_type || tok->type == TOK_BRACKET))
	{
		if (tok->type == node_type)
			parent = insert_lvl_parent(parent, tok, node_type);
		else
		{
			cmd = choose_lvl(parent, tok, node_type);
			if (!cmd)
				return (node_tree_clean(parent), NULL);
			parent = insert_lvl_child(parent, cmd);
		}
		if (!parent)
			return (NULL);
		tok = tokenize(src);
	}
	handle_error_and_clean(parent, tok, node_type);
	return (parent);
}

t_node	*parse_bracket(t_token *tok)
{
	t_source	*src;
	t_node		*bracket;
	t_node		*cmd;

	if (!tok)
		return (errno = ENODATA, NULL);
	src = tok->src;
	bracket = node_new(NODE_BRACKET);
	if (!bracket)
		return (token_clean(tok), NULL);
	cmd = choose_first_child(tok);
	if (!cmd)
		return (NULL);
	tok = tokenize(src);
	while (!cmd->exit && tok->type < TOK_EOB)
	{
		cmd = parse_lvl(cmd, tok, TOK_AND);
		if (!cmd)
			return (NULL);
		tok = tokenize(src);
	}
	handle_error_and_clean(bracket, tok, NODE_BRACKET);
	bracket->exit = cmd->exit;
	node_child_add(bracket, cmd);
	return (bracket);
}

int	parse_source(t_node **root, t_source *src)
{
	t_token	*tok;
	t_node	*cmd;

	if (!src)
		return (errno = ENODATA, 1);
	tok = tokenize(src);
	cmd = choose_first_child(tok);
	if (!cmd)
		return (1);
	tok = tokenize(src);
	while (!cmd->exit && tok->type != TOK_EOF)
	{
		cmd = parse_lvl(cmd, tok, TOK_AND);
		if (!cmd)
			return (1);
		tok = tokenize(src);
	}
	*root = cmd;
	return (token_clean(tok), (*root)->exit);
}
