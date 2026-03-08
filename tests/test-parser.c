# include "../minishell.h"
#include "./tests.h"

int should_create_ast_node(void)
{
	t_token *token;
	t_ast_node *ast;
	char *line = "echo 'hello'";
	token = set_tokens(line);
	ast = parser(&token);
	if (ast->value.command->cmd[0] == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int should_create_pipe_ast_node(void)
{
	t_token *token;
	t_ast_node *ast;
	int i = 0;
	char *line = "echo 'hello' | wc -l";
	token = set_tokens(line);
	ast = parser(&token);
	if (ast->value.pipe->left->value.command->cmd[0] == NULL && ast->value.pipe->right->value.command->cmd[0] == NULL)
		return (EXIT_FAILURE);
	while (ast->value.pipe->left->value.command->cmd[i] != NULL)
		ft_printf("%s\n", ast->value.pipe->left->value.command->cmd[i++]);
	i = 0;
	while (ast->value.pipe->right->value.command->cmd[i] != NULL)
		ft_printf("%s\n", ast->value.pipe->right->value.command->cmd[i++]);
	return (EXIT_SUCCESS);
}

int	should_create_node_with_redirection(void)
{
	t_token *token;
	t_ast_node *ast;
	char *line = "echo 'hello' > output.txt";
	token = set_tokens(line);
	ast = parser(&token);
	if (ast->value.command->cmd[0] == NULL && ast->value.command->redir == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	shoul_create_pipe_and_redirections(void)
{
	t_token *token;
	t_ast_node *ast;
	char *line = "echo 'hello' | wc -l > output.txt";
	token = set_tokens(line);
	ast = parser(&token);
	if (ast->value.pipe->left->value.command->cmd[0] == NULL &&
	 ast->value.pipe->right->value.command->cmd[0] == NULL &&
	 ast->value.pipe->right->value.command->redir == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	main(void)
{
	RUN_TEST(should_create_ast_node);
	RUN_TEST(should_create_pipe_ast_node);
	RUN_TEST(should_create_node_with_redirection);
	RUN_TEST(shoul_create_pipe_and_redirections);
	return (0);
}
