#include "./tests.h"
#include "../minishell.h"

static void	clear_env_list(t_env **list)
{
	t_env	*curr;
	t_env	*next;

	while (*list)
	{
		curr = *list;
		next = curr->next;
		free(curr->key);
		free(curr->value);
		free(curr);
		*list = next;
	}
	*list = NULL;
}

int	test_cd_absolute_path(void)
{
	t_shelly	shell = {0};
	char		*args[] = {"cd", "/tmp", NULL};
	char		*pwd;
	int			res;

	res = ft_cd(args, &shell);
	pwd = get_env_value("PWD", &shell);
	if (res != 0 || !pwd || ft_strncmp(pwd, "/tmp", 5) != 0)
	{
		free(pwd);
		clear_env_list(&shell.env_list);
		return (EXIT_FAILURE);
	}
	free(pwd);
	clear_env_list(&shell.env_list);
	return (EXIT_SUCCESS);
}

int	test_cd_home(void)
{
	t_shelly	shell = {0};
	char		*args[] = {"cd", NULL};
	char		*pwd;
	char		*home;
	int			res;

	home = getenv("HOME");
	set_env_var(&shell, "HOME", home);
	res = ft_cd(args, &shell);
	pwd = get_env_value("PWD", &shell);
	if (res != 0 || !pwd || ft_strncmp(pwd, home, ft_strlen(home) + 1) != 0)
	{
		free(pwd);
		clear_env_list(&shell.env_list);
		return (EXIT_FAILURE);
	}
	free(pwd);
	clear_env_list(&shell.env_list);
	return (EXIT_SUCCESS);
}

int	test_cd_minus(void)
{
	t_shelly	shell = {0};
	char		*args1[] = {"cd", "/tmp", NULL};
	char		*args2[] = {"cd", "/", NULL};
	char		*args3[] = {"cd", "-", NULL};
	char		*pwd;
	int			res;

	ft_cd(args1, &shell);
	ft_cd(args2, &shell);
	res = ft_cd(args3, &shell);
	pwd = get_env_value("PWD", &shell);
	if (res != 0 || !pwd || ft_strncmp(pwd, "/tmp", 5) != 0)
	{
		free(pwd);
		clear_env_list(&shell.env_list);
		return (EXIT_FAILURE);
	}
	free(pwd);
	clear_env_list(&shell.env_list);
	return (EXIT_SUCCESS);
}

int	test_cd_tilde(void)
{
	t_shelly	shell = {0};
	char		*args[] = {"cd", "~", NULL};
	char		*pwd;
	char		*home;
	int			res;

	home = getenv("HOME");
	set_env_var(&shell, "HOME", home);
	res = ft_cd(args, &shell);
	pwd = get_env_value("PWD", &shell);
	if (res != 0 || !pwd || ft_strncmp(pwd, home, ft_strlen(home) + 1) != 0)
	{
		free(pwd);
		clear_env_list(&shell.env_list);
		return (EXIT_FAILURE);
	}
	free(pwd);
	clear_env_list(&shell.env_list);
	return (EXIT_SUCCESS);
}

int	test_cd_too_many_args(void)
{
	t_shelly	shell = {0};
	char		*args[] = {"cd", "/tmp", "/var", NULL};
	int			res;

	res = ft_cd(args, &shell);
	if (res == 0)
	{
		clear_env_list(&shell.env_list);
		return (EXIT_FAILURE);
	}
	clear_env_list(&shell.env_list);
	return (EXIT_SUCCESS);
}

int	test_cd_home_unset(void)
{
	t_shelly	shell = {0};
	char		*args[] = {"cd", NULL};
	int			res;

	res = ft_cd(args, &shell);
	if (res == 0)
	{
		clear_env_list(&shell.env_list);
		return (EXIT_FAILURE);
	}
	clear_env_list(&shell.env_list);
	return (EXIT_SUCCESS);
}

int	main(void)
{
	RUN_TEST(test_cd_absolute_path);
	RUN_TEST(test_cd_home);
	RUN_TEST(test_cd_home_unset);
	RUN_TEST(test_cd_minus);
	RUN_TEST(test_cd_tilde);
	RUN_TEST(test_cd_too_many_args);
	return (0);
}
