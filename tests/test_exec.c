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
#include "envmanager.h"
#include "heredoc.h"

int		get_n_redir(t_node *node);
void	node_print(t_node *root, int depth);

static void	test_get_n_redir(char *str, t_toks *toks)__attribute__((unused));
static void	test_build_unit(char *str)__attribute__((unused));
static void	test_exec(char *input)__attribute__((unused));


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
	node_destroy(root);
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
	node_destroy(root);
	token_destroy(toks);
	printf("\n>=========================<\n\n");
}

static void	test_exec(char *input)
{
	t_toks		toks;
	t_node		*root;
	t_unit_arr	units;
	int			status;

	status = 42;
	dprintf(2, "input: %s\n\n", input);
	if (lexer(input, &toks) != CODE_OK)
		dprintf(2, "Failed while lexing\n");
	root = parse_tokens(toks.arr, toks.n_toks);
	if (!root)
		dprintf(2, "Failed while parsing\n");
	if (root && build_exec_unit(root, &units) != CODE_OK)
		dprintf(2, "Failed while building exec_units\n");
	if (root && (status = executor(&units)) != CODE_OK)
		dprintf(2, "Failed while executing\n");
	token_destroy(&toks);
	node_destroy(root);
	units_destroy(&units);
	dprintf(2, "in %s, status code: %d\n", __func__, status);
	dprintf(2, "\n>============================<\n\n\n");
	toks.arr = 0;
	toks.n_toks = 0;
}

void	set_command_1(char *command[20])
{
	ft_bzero(command, 320);
	command[0] = "a";
	//command[0] = "<a <b cat -e file >a > c >d";
	command[1] = "cat <a file -e file <a >b <<b";
	command[2] = "cat <a file -e file <a >b <<b";
	command[3] = "\"cat <a file -e file <a >b <<b";
	command[4] = "cat <a >b <<b | cat -e > file";
}

void	set_command_2(char *command[20])
{
	ft_bzero(command, 320);
	command[0] = "a";
	//command[0] = "<a <b cat -e file >a > c >d";
	command[1] = "<a <b cat -e | file >a > c >d";
	command[2] = "<a <b cat -e | file a b c >a > c >d | cat -e";
	command[3] = "<a <b cat -e file >a good bad > c >d";
	command[4] = "a";
}

void	set_command_3(char *command[20])
{
	ft_bzero(command, 320);
	/********basic test***********/
	command[0] = "cat README.md -e";
	command[1] = "cat -e README.md";
	command[2] = "ls -l | cat | cat";
	command[3] = "cat | no_cmd";
	command[4] = "cat Makefile | head -n 5 | cat | tail -n 5";
	command[5] = "echo -e hi | cat | ls | cat -e";

	/*******uncloosed pipe test*********/
	command[6] = "yes you | cat | no_cmd";
	command[7] = "yes you | ls | cat";
	command[8] = "yes you | cat | cat | head -n 5";
	command[9] = "cat </dev/urandom | cat | cat | head -n 5";

	/*******redirection test***********/
	command[10] = "echo hi > a > b | cat | no_cmd";
	command[11] = "<README.md cat > hi";
	command[12] = "cat README.md > a > b>c | ls | cat c";
	command[13] = "echo append >> c";

	/*******edge case: only redir, only word********/
	// TODO: 15번째, 16번째 테스트 각각 파싱, 렉싱에서 터짐
	// 터지는게 정상적인지 고려할 것
	command[14] = "<a";
	command[15] = "";
	command[16] = 0;
	command[17] = "<README.md >a";
	command[18] = "<README.md <Makefile >nofile";
	command[19] = ">out <nofile";
	command[20] = "<nofile >out";
	
	/********* 빌트인 관련 명령어 점검 *************/
	command[21] = "echo hi";
	command[22] = "cd ..";
	command[23] = "echo hi | echo hi";
	command[24] = "echo hi | echo hello | cat";
	command[24] = "env | echo hello | cat";
	//exit하면 프로세스 종료되어서 테스트 진행이 안됨
	//command[25] = "exit";
	//
	//
	/********* 권한이 없는 파일, 디렉토리 등 엣지케이스 **********/
	command[31] = "./srcs";
	command[32] = "./no_permission_file";

	/********* 히어독 관련 로직 점검 **************/
	
}

int	main(int argc, char *argv[], char *envp[])
{
	t_toks	toks;
	char	*commands[40];
	int		i;
	int		stat;

	(void)argc;
	(void)argv;
	(void)envp;
	
	set_command_1(commands);
	printf(">=========TEST GET_N_REDIR<=========\n");
	i = -1;
	while (++i < 0)
		test_get_n_redir(commands[i], &toks);
	printf("\n>=========================<\n\n\n");


	printf(">=========TEST GET_EXEC_UNIT<=========\n");
	set_command_2(commands);
	i = -1;
	while (++i < 0)
		test_build_unit(commands[i]);
	printf("\n>=========================<\n\n\n");


	printf("\n\n>=========TEST EXECTUION<=========\n\n\n");
	stat = envman_init(envp);
	if (stat)
		return (1);
	//stat = heredoc_init();
	if (stat)
		return (1);
	set_command_3(commands);
	//5, 9, 13 단위로 서로 다른 테스트
	i = 13;
	while (++i <= 16)
		test_exec(commands[i]);
	//test_exec("./srcs");
	//test_exec("./no_permission_file");
	//test_exec("exit");
	//아래 테케는 아직 동작하지 않음
	//test_exec("<< EOF cat");
	system("leaks --list test_exec");
	return (0);
}
