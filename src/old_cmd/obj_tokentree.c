

#include "../headers/minishell.h"

int	token_addleft(t_mytoken *root, t_lexer type, int id, char *str)
{
	t_mytoken	*to_add;

	if (type == t_pipe || type == t_out || !root || root->left || !str)
		return (-1);
	to_add = malloc(sizeof(*to_add));
	if (!to_add)
		return (-1);
	to_add->type = type;
	to_add->type_id = id;
	to_add->content = str;
	to_add->left = NULL;
	to_add->right = NULL;
	root->left = to_add;
	return (0);
}

int	token_addright(t_mytoken *root, t_lexer type, int id, char *str)
{
	t_mytoken	*to_add;

	if (type == t_cmd || type == t_in || !root || root->right || !str)
		return (-1);
	to_add = malloc(sizeof(*to_add));
	if (!to_add)
		return (-1);
	to_add->type = type;
	to_add->type_id = id;
	if (*str)
		to_add->content = str;
	to_add->left = NULL;
	to_add->right = NULL;
	root->right = to_add;
	return (0);
}

int	tokentree_init(t_tokentree *origin, char *str)
{
	t_mytoken	*root;

	if (!str || !origin)
		return (-1);
	root = malloc(sizeof(*root));
	if (!root)
		return (-1);
	root->type = t_input;
	root->type_id = 0;
	root->content = ft_strdup(str);
	root->left = NULL;
	root->right = NULL;
	*origin = root;
	return (0);
}

static void	postorder_free(t_mytoken *root)
{
	if (!root)
		return ;
	postorder_free(root->left);
	postorder_free(root->right);
	free(root->content);
	free(root);
}

void	tokentree_clean(t_tokentree *origin)
{
	if (!origin)
		return ;
	postorder_free(*origin);
	*origin = NULL;
}
