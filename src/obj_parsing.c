

#include "../headers/minishell.h"

t_mytoken	*new_token(char *str, t_lexer type)
{
	t_mytoken	*token;

	token = malloc(sizeof(*token));
	if (!token)
		return (NULL);
	token->prev = NULL;
	token->cmd_id = -1;
	token->type = type;
	token->pos = -1;
	token->content = ft_strdup(str);
	token->next = NULL;
	return (token);
}

void	token_addtop(t_tokentree *tokentree, t_mytoken *token)
{

}

void	token_addbot(t_tokentree *tokentree, t_mytoken *token)
{

}

void	token_insert(t_tokentree *tokentree, t_mytoken *token)
{

}

void	tokentree_clean(t_tokentree *tokentree)
{
	t_mytoken *current;

	current = *tokentree;
	free(current);
	*tokentree = NULL;

}
