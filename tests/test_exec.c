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
	char	*dict[5];

	dict[0] = "REDIR_NONE";
	dict[1] = "REDIR_IN";
	dict[2] = "REDIR_OUT";
	dict[3] = "REDIR_IN_HERE";
	dict[4] = "REDIR_OUT_APPEND";
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
	while (unit->argv[++i])
		printf("argv[%d]: %s\n", i, unit->argv[i]);
	printf("\nn_word: %d\n\n", i);
	i = -1;
	while (++i < unit->n_redir)
		printf("type: %s, redir_content: %s\n",
			get_redir_typename(unit->redir_arr[i].type),
			unit->redir_arr[i].content);
	printf("\nn_redir: %d\n\n", i);
	printf("------------------------\n");
}

static void	test_build_unit(char *str)
{
	t_toks		toks;
	int			stat;
	t_node		*root;
	t_unit_arr	units;
	int			i;

	stat = lexer(str, &toks);
	if (stat)
	{
		printf("Failed to build toks arr in lexer\n\n");
		printf("\n>=========================<\n\n");
		return ;
	}
	print_tok_arr(&toks);
	root = parse_tokens(toks.arr, toks.n_toks);
	printf("\n\n");
	printf("zero means codeok: %d\n\n", build_exec_unit(root, &units));
	i = 0;
	while (i < units.n_unit)
	{
		if (!units.arr)
		{
			printf("units.arr is null!!\n\n");
			break ;
		}
		print_each_unit(units.arr + i);
		i++;
	}
	printf("\n\n");
	_node_destroy(root);
	token_destroy(&toks);
	units_destroy(&units);
}

// 유효한 인풋만 넣어야 함, 유효하지 않은 경우 쓰레기값이 전달될 것임
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
	printf("root: %p\n", root);
	if (!root)
	{
		printf("Failed to parse token\n");
		return ;
	}
	simple_cmd = root->childs->content;
	printf("input: %s\n\n", str);
	printf("n_redir: %d\n\n", get_n_redir(simple_cmd));
	_node_destroy(root);
	token_destroy(toks);
	printf("\n>=========================<\n\n");
}

static void	test_exec(char *input)
{
/*
<<<<<<< HEAD
	t_toks	toks;
	t_node	*root;
	t_unit_arr units;
	int			status;

	status = 100;
	
	dprintf(2, "input: %s\n\n", input);
	if (lexer(input, &toks) != CODE_OK
			|| !(root = parse_tokens(toks.arr, toks.n_toks))
			|| build_exec_unit(root, &units) != CODE_OK
			|| (status = executor(&units)) != CODE_OK)
		dprintf(2, "\nin %s, Some error occured\n", __func__);
	//현재 err_io 발생중... 어디지 ㅇㅁㅇ?
	dprintf(2, "in %s, status code: %d\n", __func__, status);
	dprintf(2, "\n>==============<\n\n\n");
=======
*/
	t_toks		toks;
	t_node		*root;
	t_unit_arr	units;
	int			status;

	status = 100;
	dprintf(2, "input: %s\n\n", input);
	if (lexer(input, &toks) != CODE_OK)
		dprintf(2, "Some error occur\n");
	root = parse_tokens(toks.arr, toks.n_toks);
	if (!root)
		dprintf(2, "Some error occur\n");
	if (build_exec_unit(root, &units) != CODE_OK)
		dprintf(2, "Some error occur\n");
	if ((status = executor(&units)) != CODE_OK)
		dprintf(2, "Some error occur\n");
	dprintf(2, "in %s, status code: %d\n", __func__, status);
	dprintf(2, "\n>============================<\n\n\n");
}

void	set_command_1(char **command)
{
	command[0] = "a";
	//command[0] = "<a <b cat -e file >a > c >d";
	command[1] = "cat <a file -e file <a >b <<b";
	command[2] = "cat <a file -e file <a >b <<b";
	command[3] = "\"cat <a file -e file <a >b <<b";
	command[4] = "cat <a >b <<b | cat -e > file";
}

void	set_command_2(char **command)
{
	command[0] = "a";
	//command[0] = "<a <b cat -e file >a > c >d";
	command[1] = "<a <b cat -e | file >a > c >d";
	command[2] = "<a <b cat -e | file a b c >a > c >d | cat -e";
	command[3] = "<a <b cat -e file >a good bad > c >d";
	command[4] = "a";
}

void	set_command_3(char **command)
{
	command[0] = "<README.md cat | cat | cat | cat";
	//command[0] = "cat README.md -e";
	command[1] = "cat -e README.md";
	command[2] = "ls -l | cat";
	command[3] = "cat | no_cmd";
	command[4] = "yes you | cat | no_cmd";
	command[5] = "cat Makefile | cat | cat";
	command[6] = "cat Makefile | head -n 5 | cat | tail -n 5";
	command[7] = "yes you | cat | cat | head -n 5";
	command[8] = "echo -e hi | cat | ls | cat -e";
//>>>>>>> refs/remotes/origin/main
}

//테스트케이스 반복문으로 작성하면 훨씬 깔끔한듯(다른사람이 볼 때)
//
//다만 반복문으로 작성했을 때, 특정 줄만 테스트 돌리기가 쉽지 않음.
//
//또 wgcc때문에 모든 함수는 최소 한 번이상 호출해야함(메이크파일 고쳐서 해결되긴 할듯)
//그래서 각 테스트 함수를 최소한 한번 호출하기 위해서는 출력을 최소화하는 함수 호출이 필요
//(결국 특정한 인풋을 처리하는게 필요함, 0번 인덱스에 해당 인풋을 넣어도 되긴 할듯)
int	main(int argc, char *argv[], char *envp[])
{
	t_toks	toks;
	char	*commands[10];
	int		i;

	(void)argc;
	(void)argv;
	g_envp = envp;
	set_command_1(commands);
	printf(">=========TEST GET_N_REDIR<=========\n");
	i = -1;
	while (++i < 0)
		test_get_n_redir(commands[i], &toks);
	//test_get_n_redir("", &toks);
	test_get_n_redir(0, &toks);
	toks.arr = 0;
	printf("\n>=========================<\n\n\n");
	printf(">=========TEST GET_EXEC_UNIT<=========\n");
	set_command_2(commands);
	i = -1;
	while (++i < 1)
		test_build_unit(commands[i]);
	printf("\n\n>=========TEST EXECTUION<=========\n\n\n");

/**********************************/
//<<<<<<< HEAD
	/********basic test***********/
	/*
	test_exec("cat README.md -e");
	test_exec("cat -e README.md");
	test_exec("ls -l | cat | cat");
	test_exec("cat | no_cmd");
	*/

	/*******uncloosed pipe test*********/
	/*
	test_exec("yes you | cat | no_cmd");
	test_exec("yes you | ls | cat");
	test_exec("cat README.md | cat | cat");
	test_exec("cat README.md | head -n 5 | cat | tail -n 5");
	test_exec("yes you | cat | cat | head -n 5");
	test_exec("echo -e hi | cat | ls | cat -e");
	*/

	/******redirection test*********/
	//test_exec("echo hi > a > b | cat | no_cmd");
	//test_exec("<README.md cat > hi");
	//test_exec("echo hi > a > b > c | ls | cat c");
	//test_exec("echo append >> c");
	//위 테스트 케이스 세그폴트 발생
	//
	//system("leaks test_exec");
//=======
/**********************************/

	set_command_3(commands);
	i = -1;
	while (++i < 9)
		test_exec(commands[i]);
	//test_exec("echo append >> c");
	//아래 테케는 아직 동작하지 않음
	//test_exec("<< EOF cat");
	//system("lsof -p");
	//system("leaks test_exec");
	return (0);
//>>>>>>> refs/remotes/origin/main
}
