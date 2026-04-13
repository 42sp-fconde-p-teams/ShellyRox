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
}

int	should_add_new_variable(void)
{
	t_shelly	shell = {0};
	t_env	*curr;

	if (!set_env_var(&shell, "TEST_VAR", "Hello"))
		return (EXIT_FAILURE);
	curr = shell.env_list;
	if (!curr || ft_strncmp(curr->key, "TEST_VAR", 8) != 0 
		|| ft_strncmp(curr->value, "Hello", 5) != 0)
	{
		clear_env_list(&shell.env_list);
		return (EXIT_FAILURE);
	}
	clear_env_list(&shell.env_list);
	return (EXIT_SUCCESS);
}

int	should_update_existing_variable(void)
{
	t_shelly	shell = {0};
	t_env	*curr;

	set_env_var(&shell, "TEST_VAR", "OldValue");
	if (!set_env_var(&shell, "TEST_VAR", "NewValue"))
		return (EXIT_FAILURE);
	curr = shell.env_list;
	if (ft_strncmp(curr->value, "NewValue", 8) != 0)
	{
		clear_env_list(&shell.env_list);
		return (EXIT_FAILURE);
	}
	clear_env_list(&shell.env_list);
	return (EXIT_SUCCESS);
}

int	should_handle_null_value_as_empty_string(void)
{
	t_shelly	shell = {0};
	t_env	*curr;

	if (!set_env_var(&shell, "EMPTY_VAR", NULL))
		return (EXIT_FAILURE);
	curr = shell.env_list;
	if (curr->value[0] != '\0')
	{
		clear_env_list(&shell.env_list);
		return (EXIT_FAILURE);
	}
	clear_env_list(&shell.env_list);
	return (EXIT_SUCCESS);
}

int	main(void)
{
	RUN_TEST(should_add_new_variable);
	RUN_TEST(should_update_existing_variable);
	RUN_TEST(should_handle_null_value_as_empty_string);
	return (0);
}
