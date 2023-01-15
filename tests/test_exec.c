#include <stdio.h>
#include <stdlib.h>

#include "libft_def.h"
#include "libft.h"
#include "t_exec_unit.h"
#include "t_node.h"
#include "lexer.h"
#include "parser.h"
#include "build_exec.h"
#include "executor.h"

int		get_n_redir(t_node *node);
void	node_print(t_node *root, int depth);

char	**g_envp;

static char	*get_redir_typename(int type)
{
	char	*dict[5] = { "REDIR_NONE", "REDIR_IN", "REDIR_OUT", "REDIR_IN_HERE", "REDIR_OUT_APPEND"};
	return (dict[type]);
}

static void	print_tok_arr(t_toks *toks)
{
	int	i;

	i = -1;
	if (!toks->arr)
	{
		printf("toks->arr is null\n\n");
		return ;
	}
	while (++i < toks->n_toks)
		printf("toks->arr.content[%d]: %s\n", i, toks->arr[i].content);
	printf("\n");
}


static void	print_each_unit(t_exec_unit *unit)
{
	int	i;

	i = -1;
	//printf("in %s, unit_addr: %p\n", __func__, unit);
	//printf("in %s, unit->argv: %p\n", __func__, unit->argv);
	
	while (unit->argv[++i])
		printf("argv[%d]: %s\n", i, unit->argv[i]);
	printf("\nn_word: %d\n\n", i);
	i = -1;
	while (++i < unit->n_redir)
		printf("type: %s, redir_content: %s\n", get_redir_typename(unit->redir_arr[i].type), unit->redir_arr[i].content);
	printf("\nn_redir: %d\n\n", i);
	printf("------------------------\n");
}


static void	test_build_unit(char *str)
{
	t_toks	toks;
	int		stat;
	t_node	*root;
	t_unit_arr units;

	stat = lexer(str, &toks);
	if (stat)
	{
		printf("Failed to build toks arr in lexer\n\n");
		printf("\n>=========================<\n\n");
		return ;
	}
	print_tok_arr(&toks);
	root = parse_tokens(toks.arr, toks.n_toks);
	//	node_print(root, 0);
	printf("\n\n");
	printf("zero means codeok: %d\n\n", build_exec_unit(root, &units));
	for (int i = 0; i < units.n_unit; i++)
	{
		//printf("in %s, units.arr + i: %p\n", __func__, units.arr);
		if (!units.arr)
		{
			printf("units.arr is null!!\n\n");
			break ;
		}
		print_each_unit(units.arr + i);
	}
	//printf("units.arr[0].argv[n_word]: %s\n", units.arr[0].argv[units.arr[0].n_word]);
	//printf("units.arr[0].redir_content: %s\n", units.arr[0].redir_arr[units.arr[0].n_redir].content);
	//printf("units.arr[0].redir_type: %s\n", get_redir_typename(units.arr[0].redir_arr[units.arr[0].n_redir].type));
	printf("\n\n");
	node_destroy(root);
	token_destroy(&toks);
	units_destroy(&units);
}

//유효한 인풋만 넣어야 함, 유효하지 않은 경우 쓰레기값이 전달될 것임
static void	test_get_n_redir(char *str, t_toks *toks)
{
	t_node	*root;
	t_node	*simple_cmd;
	int		stat;

	printf("\n\n");

	stat = lexer(str, toks);
	if (stat)
	{
		printf("Failed to build toks arr in lexer\n\n");
		printf("\n>=========================<\n\n");
		return ;
	}
	root = parse_tokens(toks->arr, toks->n_toks);
	//node_print(root, 0);
	printf("root: %p\n", root);
	simple_cmd = root->childs->content;
	printf("input: %s\n\n", str);
	printf("n_redir: %d\n\n", get_n_redir(simple_cmd));
	node_destroy(root);
	token_destroy(toks);
	printf("\n>=========================<\n\n");
}

static void	test_exec(char *input)
{
	t_toks	toks;
	t_node	*root;
	t_unit_arr units;
	int			status;

	status = 100;
	if (lexer(input, &toks) != CODE_OK
			|| !(root = parse_tokens(toks.arr, toks.n_toks))
			|| build_exec_unit(root, &units) != CODE_OK
			|| (status = executor(&units)) != CODE_OK)
		dprintf(2, "Some error occur\n");
	//현재 err_io 발생중... 어디지 ㅇㅁㅇ?
	dprintf(2, "status code: %d\n\n", status);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_toks	toks;

	(void)argc;
	(void)argv;
	g_envp = envp;
	/*
	   printf(">=========TEST GET_N_REDIR<=========\n");
	   test_get_n_redir("<a <b cat -e file >a > c >d", &toks);
	   test_get_n_redir("cat <a file -e file <a >b <<b", &toks);
	   test_get_n_redir("cat <a file -e file <a >b <<b", &toks);
	   test_get_n_redir("\"cat <a file -e file <a >b <<b", &toks);
	   test_get_n_redir("cat <a >b <<b | cat -e > file", &toks);
	//인자로 ""만 전달하면 파서에서 널반환
	//test_get_n_redir("", &toks);
	*/
	test_get_n_redir(0, &toks);
	toks.arr = 0;


	/*
	   printf("\n>=========================<\n\n");
	   printf(">=========TEST GET_EXEC_UNIT<=========\n");
	   test_build_unit("<a <b cat -e file >a > c >d");
	   test_build_unit("<a <b cat -e | file >a > c >d");
	   test_build_unit("<a <b cat -e | file a b c >a > c >d | cat -e");
	   test_build_unit("<a <b cat -e file >a good bad > c >d");
	   */
	test_build_unit("a");
	printf("\n\n>=========TEST EXECTUION<=========\n\n\n");
	//test_exec("cat README.md -e");
//	test_exec("cat -e README.md");
//	test_exec("ls -l | cat");
//	test_exec("cat | no_cmd");
	//test_exec("yes you | cat | no_cmd");
//	test_exec("cat Makefile | cat | cat");
	test_exec("cat Makefile | head -n 5 | cat | tail -n 5");
//	test_exec("yes you | cat | cat | head -n 5");
//	system("lsof -p");
	//test_exec("echo -e hi | cat | ls | cat -e");
	//system("leaks test_exec");
}
