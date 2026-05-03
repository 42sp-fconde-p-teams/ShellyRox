#include "../minishell.h"
#include "./tests.h"

int	should_succed_for_valid_content(void)
{
	char	line[] = "content";

	if (has_meaningful_content(line) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	else
		return (EXIT_FAILURE);
}

int	should_fail_for_empty_content(void)
{
	char	line[] = "";

	if (has_meaningful_content(line) == EXIT_FAILURE)
		return (EXIT_SUCCESS);
	else
		return (EXIT_FAILURE);
}

int	should_fail_for_space_content(void)
{
	char	line[] = "    ";

	if (has_meaningful_content(line) == EXIT_FAILURE)
		return (EXIT_SUCCESS);
	else
		return (EXIT_FAILURE);
}

int	should_fail_for_tab_content(void)
{
	char	line[] = "\t";

	if (has_meaningful_content(line) == EXIT_FAILURE)
		return (EXIT_SUCCESS);
	else
		return (EXIT_FAILURE);
}

int	should_fail_for_new_line_content(void)
{
	char	line[] = "\n";

	if (has_meaningful_content(line) == EXIT_FAILURE)
		return (EXIT_SUCCESS);
	else
		return (EXIT_FAILURE);
}

int	main(void)
{
	RUN_TEST(should_succed_for_valid_content);
	RUN_TEST(should_fail_for_empty_content);
	RUN_TEST(should_fail_for_space_content);
	RUN_TEST(should_fail_for_tab_content);
	RUN_TEST(should_fail_for_new_line_content);
	return (0);
}