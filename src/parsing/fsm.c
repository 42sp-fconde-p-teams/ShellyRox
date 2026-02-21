#include "../../includes/minishell.h"

// test 1:
// IN -> echo "Hello 'world'"
// OUT -> t_tokens *tokens --> [
//		{
//			"echo"
//			"TOKEN_WORD"
//		},
//		{
//			"hello 'world'",
//			"TOKEN_WORD"
//}]
//
//Parser -->
//IN -> t_tokens *tokens --> [
//		{
//			"echo"
//			"TOKEN_WORD"
//		},
//		{
//			"hello 'world'",
//			"TOKEN_WORD"
//}]
//
//OUT -> t_ast command_table 
//{
//	t_cmd = {
//		["echo", "hello 'world'", NULL]
//		next = NULL;
//	}
//} 
