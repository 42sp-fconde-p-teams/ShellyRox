# include "../minishell.h"
#include "./tests.h"

int should_create_ast_node(void)
{
	t_token *token = malloc(sizeof(t_token));
	t_token *token2 = malloc(sizeof(t_token));
	token->prev = NULL;
	token->next = token2;
	token->type = TOKEN_WORD;
	token->value = "echo";
	token2->type = TOKEN_WORD;
	token2->prev = token;
	token2->next = NULL;
	token2->value = "'hello'";
	if (parser(token) == 0)
		return (EXIT_SUCCESS);
	else
		return (EXIT_FAILURE);
}

int	main(void)
{
	RUN_TEST(should_create_ast_node);
	return (0);
}
