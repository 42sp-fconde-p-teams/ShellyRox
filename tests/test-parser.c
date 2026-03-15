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

int	should_create_pipe_and_redirections(void)
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

int	should_handle_multiple_word_command(void)
{
	t_token *token;
	t_ast_node *ast;
	char *line = "ls -la";
	token = set_tokens(line);
	ast = parser(&token);
	if (ast->node_type != TOKEN_WORD || ast->value.command->cmd[0] == NULL ||
		ft_strncmp(ast->value.command->cmd[0], "ls", 2) != 0 ||
		ast->value.command->cmd[1] == NULL ||
		ft_strncmp(ast->value.command->cmd[1], "-la", 3) != 0 ||
		ast->value.command->cmd[2] != NULL ||
		ast->value.command->redir != NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	should_create_node_with_input_redirection(void)
{
	t_token *token;
	t_ast_node *ast;
	char *line = "cat < input.txt";
	token = set_tokens(line);
	ast = parser(&token);
	if (ast->node_type != TOKEN_WORD || ast->value.command->cmd[0] == NULL ||
		ft_strncmp(ast->value.command->cmd[0], "cat", 3) != 0 ||
		ast->value.command->cmd[1] != NULL ||
		ast->value.command->redir == NULL ||
		ast->value.command->redir->type != TOKEN_REDIR_IN ||
		ft_strncmp(ast->value.command->redir->filename, "input.txt", 9) != 0 ||
		ast->value.command->redir->next != NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	should_create_node_with_heredoc_redirection(void)
{
	t_token *token;
	t_ast_node *ast;
	char *line = "grep var << EOF";
	token = set_tokens(line);
	ast = parser(&token);
	if (ast->node_type != TOKEN_WORD || ast->value.command->cmd[0] == NULL ||
		ft_strncmp(ast->value.command->cmd[0], "grep", 4) != 0 ||
		ast->value.command->cmd[1] == NULL ||
		ft_strncmp(ast->value.command->cmd[1], "var", 3) != 0 ||
		ast->value.command->cmd[2] != NULL ||
		ast->value.command->redir == NULL ||
		ast->value.command->redir->type != TOKEN_HEREDOC ||
		ft_strncmp(ast->value.command->redir->filename, "EOF", 3) != 0 ||
		ast->value.command->redir->next != NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	should_create_node_with_append_redirection(void)
{
	t_token *token;
	t_ast_node *ast;
	char *line = "echo 'hello' >> output.txt";
	token = set_tokens(line);
	ast = parser(&token);
	if (ast->node_type != TOKEN_WORD || ast->value.command->cmd[0] == NULL ||
		ft_strncmp(ast->value.command->cmd[0], "echo", 4) != 0 ||
		ast->value.command->cmd[1] == NULL ||
		ft_strncmp(ast->value.command->cmd[1], "'hello'", 7) != 0 ||
		ast->value.command->cmd[2] != NULL ||
		ast->value.command->redir == NULL ||
		ast->value.command->redir->type != TOKEN_APPEND ||
		ft_strncmp(ast->value.command->redir->filename, "output.txt", 10) != 0 ||
		ast->value.command->redir->next != NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int should_create_multiple_pipe_ast_node(void)
{
	t_token *token;
	t_ast_node *ast;
	char *line = "ls | grep .c | wc -l";
	token = set_tokens(line);
	ast = parser(&token);
	// Expected: (ls | grep .c) | wc -l
	// Check the top-level pipe
	if (ast->node_type != TOKEN_PIPE)
		return (EXIT_FAILURE);
	// Check right side of top-level pipe (wc -l)
	if (ast->value.pipe->right->node_type != TOKEN_WORD ||
		ft_strncmp(ast->value.pipe->right->value.command->cmd[0], "wc", 2) != 0 ||
		ft_strncmp(ast->value.pipe->right->value.command->cmd[1], "-l", 2) != 0 ||
		ast->value.pipe->right->value.command->cmd[2] != NULL ||
		ast->value.pipe->right->value.command->redir != NULL)
		return (EXIT_FAILURE);
	// Check left side of top-level pipe (ls | grep .c)
	t_ast_node *left_pipe = ast->value.pipe->left;
	if (left_pipe->node_type != TOKEN_PIPE) return (EXIT_FAILURE); // Check left side of inner pipe (ls) if (left_pipe->value.pipe->left->node_type != TOKEN_WORD || ft_strncmp(left_pipe->value.pipe->left->value.command->cmd[0], "ls", 2) != 0 || left_pipe->value.pipe->left->value.command->cmd[1] != NULL || left_pipe->value.pipe->left->value.command->redir != NULL) return (EXIT_FAILURE); Check right side of inner pipe (grep .c)
	if (left_pipe->value.pipe->right->node_type != TOKEN_WORD ||
		ft_strncmp(left_pipe->value.pipe->right->value.command->cmd[0], "grep", 4) != 0 ||
		ft_strncmp(left_pipe->value.pipe->right->value.command->cmd[1], ".c", 2) != 0 ||
		left_pipe->value.pipe->right->value.command->cmd[2] != NULL ||
		left_pipe->value.pipe->right->value.command->redir != NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int should_create_complex_pipe_and_redirections(void)
{
	t_token *token;
	t_ast_node *ast;
	char *line = "grep 'test' < input.txt | wc -l >> output.txt";
	token = set_tokens(line);
	ast = parser(&token);
	// Expected: (grep 'test' < input.txt) | (wc -l >> output.txt)
	if (ast->node_type != TOKEN_PIPE)
		return (EXIT_FAILURE);

	// Check left side of the pipe (grep 'test' < input.txt)
	t_ast_node *left_cmd = ast->value.pipe->left;
	if (left_cmd->node_type != TOKEN_WORD ||
		ft_strncmp(left_cmd->value.command->cmd[0], "grep", 4) != 0 ||
		ft_strncmp(left_cmd->value.command->cmd[1], "test", 4) != 0 ||
		left_cmd->value.command->cmd[2] != NULL ||
		left_cmd->value.command->redir == NULL ||
		left_cmd->value.command->redir->type != TOKEN_REDIR_IN ||
		ft_strncmp(left_cmd->value.command->redir->filename, "input.txt", 9) != 0 ||
		left_cmd->value.command->redir->next != NULL)
		return (EXIT_FAILURE);

	// Check right side of the pipe (wc -l >> output.txt)
	t_ast_node *right_cmd = ast->value.pipe->right;
	if (right_cmd->node_type != TOKEN_WORD ||
		ft_strncmp(right_cmd->value.command->cmd[0], "wc", 2) != 0 ||
		ft_strncmp(right_cmd->value.command->cmd[1], "-l", 2) != 0 ||
		right_cmd->value.command->cmd[2] != NULL ||
		right_cmd->value.command->redir == NULL ||
		right_cmd->value.command->redir->type != TOKEN_APPEND ||
		ft_strncmp(right_cmd->value.command->redir->filename, "output.txt", 10) != 0 ||
		right_cmd->value.command->redir->next != NULL)
		return (EXIT_FAILURE);

	return (EXIT_SUCCESS);
}

int	main(void)
{
	RUN_TEST(should_create_ast_node);
	RUN_TEST(should_create_pipe_ast_node);
	RUN_TEST(should_create_node_with_redirection);
	RUN_TEST(should_create_pipe_and_redirections);
	RUN_TEST(should_handle_multiple_word_command);
	RUN_TEST(should_create_node_with_input_redirection);
	RUN_TEST(should_create_node_with_heredoc_redirection);
	RUN_TEST(should_create_node_with_append_redirection);
	RUN_TEST(should_create_multiple_pipe_ast_node);
	RUN_TEST(should_create_complex_pipe_and_redirections);
	return (0);
}
