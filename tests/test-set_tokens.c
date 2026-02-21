
#include "../minishell.h"
#include "./tests.h"

int	should_pass(void)
{
	char	*str_out;
	char	str_in[] = "teste";

	str_out = set_tokens(str_in);
	if (ft_strncmp(str_in, str_out, 6) == 0)
		return (0);
	else
		return (1);
}

int	main(void)
{
	RUN_TEST(should_pass);
	return (0);
}
