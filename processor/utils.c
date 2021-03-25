#include "minishell.h"
#include "parseader.h"

int check_symbols(char *name, char *content)
{
	int i;

	if (!ft_isalpha(name[0]) && name[0] != '_')
		return (1);
	i = 0;
	while (name[++i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (1);
	}
	return (0);
}

t_list_env *strdup_list(t_list_env **src)
{
	t_list_env *new;
	t_list_env *tmp;
	t_list_env *node;

	tmp = *src;
	new = NULL;
	while (tmp)
	{
		node = ft_mylstnew1(tmp->name, tmp->content, tmp->has_equal);
		ft_mylstadd_back(&new, node);
		tmp = tmp->next;
	}
	return (new);
}

t_list_env *sort_list(t_list_env *src)
{
	t_list_env *root;
	t_list_env *new_root;
	t_list_env *node;
	t_list_env *current;

	root = strdup_list(&src);
	new_root = NULL;
	while (root)
	{
		node = root;
		root = root->next;
		if (!new_root || ft_strcmp(node->name, new_root->name) < 0)
		{
			node->next = new_root;
			new_root = node;
		}
		else
		{
			current = new_root;
			while (current->next && ft_strcmp(node->name, current->next->name) >= 0)
				current = current->next;
			node->next = current->next;
			current->next = node;
		}
	}
	return (new_root);
}
