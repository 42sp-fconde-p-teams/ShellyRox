
#ifndef TESTS_H
# define TESTS_H

// project header files
# include "../lib/libft/libft.h"
# include "../minishell.h"

int	start_capture(void);
char	*end_capture(int saved_stdout);
void	init_test_log(void);
extern FILE	*g_test_log;

// def funny stuff here, friendo!

// MACRO for individual test running and result printing
#define RUN_TEST(test_func) \
	do { \
		init_test_log(); \
		if (test_func() != 0) { \
			fprintf(g_test_log, "      [FAIL] Case: %s\n", #test_func); \
		} else { \
			fprintf(g_test_log, "      [PASS] Case: %s\n", #test_func); \
		} \
		fflush(g_test_log); \
	} while (0)

#endif
