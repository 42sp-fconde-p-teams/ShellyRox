
#include "../minishell.h"
#include "./tests.h"

int	put_value_to_a_new_token_node(void)
{
	char	str_in[] = "teste";
	t_token	*token = NULL;

	// token = ft_calloc(1, sizeof(t_token));
	token = set_tokens(str_in);
	if (!token)
		return (EXIT_FAILURE);
	if (ft_strncmp(token->value, str_in, 6) == EXIT_SUCCESS)
	{
		free(token);
		return (EXIT_SUCCESS);
	}
	else
	{
		free(token);
		return (EXIT_FAILURE);
	}
}

int	main(void)
{
	RUN_TEST(temp_put_value_to_a_new_token_node);
	return (0);
}
