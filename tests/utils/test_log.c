#include "./tests.h"
#include <stdio.h>

FILE	*g_test_log = NULL;

void	init_test_log(void)
{
	if (g_test_log == NULL)
	{
		g_test_log = fopen("test_report.log", "a");
		if (!g_test_log)
		{
			perror("Failed to open test_report.log");
		}
	}
}
