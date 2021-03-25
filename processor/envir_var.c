#include "minishell.h"

void 		add_var_to_list(t_list_env **envs, char *str)
{
	t_list_env *new;
	int found;

	new = ft_mylstnew(str);
	found = find_envvar(envs, new->name);
	if (found)
	{
		change_content(envs, new);
	}
	else
	{
		found = check_symbols(new->name, new->content);
		if (!found)
			ft_mylstadd_back(envs, new);
		else
		{
			display_error("minishell", "export", "not a valid identifier");
		}
	}
}

t_list_env *find_env_pointer(t_list_env *envs, char *name)
{
	t_list_env *tmp;

	tmp = envs;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, name))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

t_list_env	*get_envlist(char **env)
{
	int i;
	t_list_env *new_list;
	t_list_env *new_elem;

	i = -1;
	new_list = NULL;
	while (env[++i])
	{
		new_elem = ft_mylstnew(env[i]);
		ft_mylstadd_back(&new_list, new_elem);
	}
	i = find_envvar(&new_list, "OLDPWD");
	if (!i)
		add_var_to_list(&new_list, "OLDPWD=");
	return (new_list);
}

int	find_envvar(t_list_env **envs, char *name)
{
	t_list_env *tmp;

	tmp = *envs;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, name))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

char		*find_env_content(t_list_env *envs, char *name)
{
	t_list_env *tmp;

	tmp = envs;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, name))
			return (tmp->content);
		tmp = tmp->next;
	}
	return (NULL);
}
