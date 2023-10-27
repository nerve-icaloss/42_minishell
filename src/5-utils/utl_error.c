/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utl_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nserve <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 14:22:11 by nserve            #+#    #+#             */
/*   Updated: 2023/10/22 17:17:15 by nserve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	syntax_error_node(t_node_type node_type)
{
	if (node_type == NODE_PIPE)
		write(2, "minishell: syntax error near unexpected token `|'\n", 50);
	if (node_type == NODE_OR)
		write(2, "minishell: syntax error near unexpected token `||'\n", 51);
	if (node_type == NODE_AND)
		write(2, "minishell: syntax error near unexpected token `&&'\n", 51);
	if (node_type == NODE_BRACKET)
		write(2, "minishell: syntax error near unexpected token `('\n", 50);
}

void	syntax_error_token(t_tok_type tok_type)
{
	if (tok_type == TOK_PIPE)
		write(2, "minishell: syntax error near unexpected token `|'\n", 50);
	if (tok_type == TOK_OR)
		write(2, "minishell: syntax error near unexpected token `||'\n", 51);
	if (tok_type == TOK_AND)
		write(2, "minishell: syntax error near unexpected token `&&'\n", 51);
	if (tok_type == TOK_BRACKET)
		write(2, "minishell: syntax error near unexpected token `('\n", 50);
	if (tok_type == TOK_EOF)
		write(2, "minishell: syntax error near unexpected token `newline'\n",
			56);
}

void	syntax_error_redir(t_redir_type redir_type)
{
	if (redir_type == READ)
		write(2, "minishell: syntax error near unexpected token `<'\n", 50);
	if (redir_type == HEREDOC)
		write(2, "minishell: syntax error near unexpected token `<<'\n", 51);
	if (redir_type == APPEND)
		write(2, "minishell: syntax error near unexpected token `>>'\n", 51);
	if (redir_type == TRUNC)
		write(2, "minishell: syntax error near unexpected token `>'\n", 50);
}

void	cmd_notfound(char *str)
{
	char	*strerror;
	char	*not_found;

	not_found = ": command not found";
	strerror = ft_strjoin(str, not_found);
	write(2, "minishell: ", 11);
	write(2, strerror, ft_strlen(strerror));
	write(2, "\n", 1);
	free(strerror);
}

void	path_notfound(void)
{
	write(2, "minishell: ", 11);
	write(2, "env: path not found", 19);
	write(2, "\n", 1);
}
