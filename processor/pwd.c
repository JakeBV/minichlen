#include "minishell.h"

void shell_pwd(t_data *data, char **args)
{
	char *pwd;

	(void)data;
	(void)args;
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		display_error("minishell", "malloc", "Allocation memory failed\n");
		ft_exit(9);
	}
	ft_putendl_fd(pwd, 1);
	free(pwd);
}