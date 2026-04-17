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

int	should_do_nothing_with_no_args(void)
{
	t_shelly	shell = {0};
	char		*args[] = {"unset", NULL};
	int			res;

	set_env_var(&shell, "TEST", "VAL");
	res = ft_unset(args, &shell);
	if (res != 0)
	{
		clear_env_list(&shell.env_list);
		return (EXIT_FAILURE);
	}
	if (!get_env_value("TEST", &shell))
	{
		clear_env_list(&shell.env_list);
		return (EXIT_FAILURE);
	}
	clear_env_list(&shell.env_list);
	return (EXIT_SUCCESS);
}

int	should_remove_existing_variable(void)
{
	t_shelly	shell = {0};
	char		*args[] = {"unset", "TEST", NULL};
	char		*val;

	set_env_var(&shell, "TEST", "VAL");
	ft_unset(args, &shell);
	val = get_env_value("TEST", &shell);
	if (val != NULL)
	{
		free(val);
		clear_env_list(&shell.env_list);
		return (EXIT_FAILURE);
	}
	clear_env_list(&shell.env_list);
	return (EXIT_SUCCESS);
}

int	should_handle_non_existent_variable(void)
{
	t_shelly	shell = {0};
	char		*args[] = {"unset", "NON_EXISTENT", NULL};
	int			res;

	res = ft_unset(args, &shell);
	if (res != 0)
	{
		clear_env_list(&shell.env_list);
		return (EXIT_FAILURE);
	}
	clear_env_list(&shell.env_list);
	return (EXIT_SUCCESS);
}

int	should_remove_multiple_variables(void)
{
	t_shelly	shell = {0};
	char		*args[] = {"unset", "VAR1", "VAR3", NULL};
	char		*val;

	set_env_var(&shell, "VAR1", "1");
	set_env_var(&shell, "VAR2", "2");
	set_env_var(&shell, "VAR3", "3");
	ft_unset(args, &shell);
	if (get_env_value("VAR1", &shell) != NULL)
	{
		clear_env_list(&shell.env_list);
		return (EXIT_FAILURE);
	}
	val = get_env_value("VAR2", &shell);
	if (!val || ft_strncmp(val, "2", 1) != 0)
	{
		free(val);
		clear_env_list(&shell.env_list);
		return (EXIT_FAILURE);
	}
	free(val);
	if (get_env_value("VAR3", &shell) != NULL)
	{
		clear_env_list(&shell.env_list);
		return (EXIT_FAILURE);
	}
	clear_env_list(&shell.env_list);
	return (EXIT_SUCCESS);
}

int	should_handle_empty_env_list(void)
{
	t_shelly	shell = {0};
	char		*args[] = {"unset", "VAR", NULL};
	int			res;

	res = ft_unset(args, &shell);
	if (res != 0)
	{
		clear_env_list(&shell.env_list);
		return (EXIT_FAILURE);
	}
	clear_env_list(&shell.env_list);
	return (EXIT_SUCCESS);
}

int	main(void)
{
	RUN_TEST(should_do_nothing_with_no_args);
	RUN_TEST(should_remove_existing_variable);
	RUN_TEST(should_handle_non_existent_variable);
	RUN_TEST(should_remove_multiple_variables);
	RUN_TEST(should_handle_empty_env_list);
	return (0);
}
