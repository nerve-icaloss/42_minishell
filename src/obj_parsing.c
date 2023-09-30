

#include "../headers/minishell.h"

t_myelement	*new_element(char *str, t_lexer type)
{
	t_myelement	*element;

	element = malloc(sizeof(*element));
	if (!element)
		return (NULL);
	element->prev = NULL;
	element->cmd_id = -1;
	element->type = type;
	element->pos = -1;
	element->content = ft_strdup(str);
	element->next = NULL;
	return (element);
}

void	addtop_element(t_parsing *parsing, t_myelement *element)
{

}

void	addbot_element(t_parsing *parsing, t_myelement *element)
{

}

void	insert_element(t_parsing *parsing, t_myelement *element)
{

}

void	clear_parsing(t_parsing *parsing)
{
	t_myelement *current;

	current = *parsing;
	free(current);
	*parsing = NULL;

}
