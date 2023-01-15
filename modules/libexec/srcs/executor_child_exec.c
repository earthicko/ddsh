#include <stdio.h>


#include <stdlib.h>
#include <sys/stat.h>
#include "executor_internal.h"
#include "libft_def.h"
#include "strutils.h"
#include "t_exec_unit.h"

static int	process_redir(t_redir *redir_arr, int n_redir)
{
	//놈에러 왜뜸????? 아나
	const t_do_redir	do_redir[5] = {
		[REDIR_NONE] = 0,
		[REDIR_IN] = do_redir_in,
		[REDIR_OUT] = do_redir_out,
		[REDIR_IN_HERE] = do_redir_in_here,
		[REDIR_OUT_APPEND] = do_redir_out_append
	};
	int					i;

	i = -1;
	while (++i < n_redir)
	{
		//여기 고칠 것
		//REDIR_NONE일 때 널 함수포인터에 대한 가드
		if (redir_arr[i].type == REDIR_NONE)
		{
			printf("redir type error\n");
			continue ;
		}
		if (do_redir[redir_arr[i].type](redir_arr + i) != CODE_OK)
			return (CODE_ERROR_IO);
	}
	return (CODE_OK);
}

//ft_syscall 함수 사용할까?
static int	set_fd_stream(t_info *info)
{
	const t_exec_unit	cur_unit = info->units->arr[info->cur_idx];

	//dup2 이후에 첫번째 매개변수를 close 해야하나 ?!?
	//안해도 된다고 생각함. 만약 new_pipe를 꼭 닫아야 하는 상황이라면
	//dup2를 하는 행위자체가 말이 안돼. (같은 객체를 가리키는 서로다른 파일디스크립터가 생기는 것이니)
	if (info->cur_idx == 0)
	{
		if (close(info->new_pipe[READ]) < 0
			|| dup2(info->new_pipe[WRITE], STDOUT_FILENO) < 0
			|| close(info->new_pipe[WRITE]) < 0)
			return (CODE_ERROR_IO);
	}
	else if (info->cur_idx == info->n_unit)
	{
		if (dup2(info->old_pipe[READ], STDIN_FILENO) < 0
			|| close(info->old_pipe[READ]) < 0)
			return (CODE_ERROR_IO);
	}
	else
		if (close(info->new_pipe[READ]) < 0
			|| dup2(info->old_pipe[READ], STDIN_FILENO) < 0
			|| close(info->old_pipe[READ] < 0)
			|| dup2(info->new_pipe[WRITE], STDOUT_FILENO) < 0
			|| close(info->new_pipe[WRITE]) < 0)
			return (CODE_ERROR_IO);
	if (process_redir(cur_unit.redir_arr, cur_unit.n_redir) != CODE_OK)
		return (CODE_ERROR_IO);
	return (CODE_OK);
}

//각 unit에 대한 정보로부터 명령어 실행
//exit status에 주의할것!
//
//envp 매개변수가 여기서 필요하네 ..? 전역변수로 쓸까 그냥?
//어차피 execve호출 후 종료되거나, exit을 하게 돼서 반환형이 필요없음
//
// // stat, lstat 심볼릭 링크파일인 경우 동작이 다르대..
 void	child_exec_cmd(t_info *info)
{
	//뭔가 컴파일러 경고가 뜨네?
	struct stat	s_statbuf;
	char	**argv;
	int		status;

	//IO 실패시 exit status가 어떻게 될까..? (fork한 상태에서)
	//일단 1로 처리
	//bash문서에서 발췌
	//If a command fails because of an error during expansion or redirection, the exit status is greater than zero.
	if (set_fd_stream(info) < 0)
		exit(EXIT_FAILURE);
	argv = info->units->arr[info->cur_idx].argv;
	//1. 에러메시지 별로 분기를 나누어야 하나?
	//일단 else if에선 io_err와 malloc_err 묶어서 처리
	//
	//CODE_OK가 반환되더라도 /no_exisiting_file처럼 존재하지 않는 파일일 수도 있음
	//(파일명에 /가 있으면 바로 CODE_OK를 반환하기 때문)
	//정말 억까케이스로 파일명에 /가 있고, PATH 경로에 해당파일이 등록돼있다면?
	//
	//CODE_OK는 '존재하는 파일이 있을 때'만 반환하면 어떨까?
	//그렇다면 F_OK를 굳이 한번 더 체크하지 않아도 됨
	status = find_exec(&argv[0]);
	if (status == CODE_ERROR_GENERIC)
	{
		printf("shell: %s: command not found\n", argv[0]);
		exit(127);
	}
	else if (status != CODE_OK)
	{
		printf("shell: error occured\n");
		exit(EXIT_FAILURE);
	}
	if (access(argv[0], F_OK) < 0)
	{
		printf("shell: %s: No such file or directory\n", argv[0]);
		exit(127);
	}
	if (access(argv[0], X_OK) == 0)
		execve(argv[0], argv, envp);
	else
	{
		//is a dir까지 잡아내려면 stat쓰긴 써야할듯 ㅁㄴㅇㄹ
		//이 분기에서 is_a_dir일 수도 있긴 해 ㅁㄴㄹㅇㄹ
		//Permission denide든 is a dir이든 둘다 126종료
		if (stat(argv[0], &s_statbuf) != 0)
		{
			perror("stat failed");
			exit(EXIT_FAILURE);
		}
		if (S_ISDIR(s_statbuf.st_mode))
			printf("shell: %s: is a directory\n", argv[0]);
		else
			printf("shell: %s: Permission denied\n", argv[0]);
		exit(126);
	}
	exit(EXIT_FAILURE);
}
