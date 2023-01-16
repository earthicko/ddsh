#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include "executor_internal.h"
#include "libft_def.h"
#include "strutils.h"


#include <sys/errno.h>

extern char	**g_envp;

#include "libft.h"

char	**get_envp_paths(char *envp[])
{
	int		i;

	i = -1;
	while (envp && envp[++i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (ft_split(envp[i] + 5, ':'));
	}
	return (0);
}

static char	*join_path_cmd(char *path, char *cmd)
{
	char	*path_prefix;
	char	*whole_path;

	path_prefix = ft_strjoin(path, "/");
	whole_path = ft_strjoin(path_prefix, cmd);
	free(path_prefix);
	return (whole_path);
}

char	*find_cmd_path(char *cmd, char **envp_paths)
{
	char	*cmd_path;
	int		i;

	if (!cmd)
		return (0);
	if (ft_strchr(cmd, '/') && access(cmd, F_OK) == 0)
	{
		cmd_path = ft_strdup(cmd);
		if (!cmd_path)
		{
			printf("ft_strdup failed\n");
			exit(EXIT_FAILURE);
		}
		return (cmd_path);
	}
	i = -1;
	while (envp_paths && envp_paths[++i])
	{
//		dprintf(2, "cmd: %s, cmd_path: %s\n", cmd, envp_paths[i]);
		cmd_path = join_path_cmd(envp_paths[i], cmd);
		if (access(cmd_path, F_OK) == 0)
			return (cmd_path);
		free(cmd_path);
	}
	return (0);
}

/*******************************************************/

//ft_syscall 함수 사용할까?
static int	set_fd_stream(t_info *info)
{
	const t_exec_unit	cur_unit = info->units->arr[info->cur_idx];

	//dup2 이후에 첫번째 매개변수를 close 해야하나 ?!?
	//안해도 된다고 생각함. 만약 new_pipe를 꼭 닫아야 하는 상황이라면
	//dup2를 하는 행위자체가 말이 안돼. (같은 객체를 가리키는 서로다른 파일디스크립터가 생기는 것이니)
	//errno = 0;
	if (info->units->n_unit == 1)
	{

		if (process_redir(cur_unit.redir_arr, cur_unit.n_redir) != CODE_OK)
		{
			dprintf(2, "failed to redir\n");
			return (CODE_ERROR_IO);
		}
		return (CODE_OK);
	}
	if (info->cur_idx == 0)
	{
		if (close(info->new_pipe[READ]) < 0
			|| dup2(info->new_pipe[WRITE], STDOUT_FILENO) < 0
			|| close(info->new_pipe[WRITE]) < 0)
			//|| dprintf(2, "pass all 1\n") < 0)
		{
			//dprintf(2, "here 1?\n");
			return (CODE_ERROR_IO);
		}
	}
	else if (info->cur_idx == info->n_unit - 1)
	{
		if (dup2(info->old_pipe[READ], STDIN_FILENO) < 0
			|| close(info->old_pipe[READ]) < 0)
			//|| dprintf(2, "pass all 2\n") < 0)
		{
			//dprintf(2, "here 2?\n");
			return (CODE_ERROR_IO);
		}
	}
	else
		if (close(info->new_pipe[READ]) < 0
			|| dup2(info->old_pipe[READ], STDIN_FILENO) < 0
			|| close(info->old_pipe[READ]) < 0
			|| dup2(info->new_pipe[WRITE], STDOUT_FILENO) < 0
			|| close(info->new_pipe[WRITE]) < 0)
			//|| dprintf(2, "pass all 3\n") < 0)
		{
			//dprintf(2, "here 3?\n");
			return (CODE_ERROR_IO);
		}
	if (process_redir(cur_unit.redir_arr, cur_unit.n_redir) != CODE_OK)
	{
		dprintf(2, "failed to redir\n");
		return (CODE_ERROR_IO);
	}
	//perror("what error?");
	//dprintf(2, "child errno: %d\n", errno);
	return (CODE_OK);
}

//<리팩토링 시급함>
//각 unit에 대한 정보로부터 명령어 실행
//exit status에 주의할것!
//
//어차피 execve호출 후 종료되거나, exit을 하게 돼서 반환형이 필요없음
//
// //참고만 stat, lstat 심볼릭 링크파일인 경우 동작이 다르대..
 void	child_exec_cmd(t_info *info)
{
	struct stat	s_statbuf;
	char	**argv;
	int		status;
	char	*whole_path;

	//IO 실패시 exit status가 어떻게 될까..? (fork한 상태에서)
	//일단 1로 처리
	//bash문서에서 발췌
	//If a command fails because of an error during expansion or redirection, the exit status is greater than zero.
//
	//dprintf(2, "in %s, before set stream\n", __func__);
	//대체 왜 이 함수 들어오자마자 에러노가 22임??
	//dprintf(2, "in %s, child errno: %d\n", __func__, errno);
	if (set_fd_stream(info) < 0)
		exit(EXIT_FAILURE);
	//dprintf(2, "cur_dx: %d\n", info->cur_idx);
	argv = info->units->arr[info->cur_idx].argv;
	//1. 에러메시지 별로 분기를 나누어야 하나?
	//일단 else if에선 io_err와 malloc_err 묶어서 처리
	//
	//정말 억까케이스로 파일명에 /가 있고, PATH 경로에 해당파일이 등록돼있다면?
	//
	//CODE_OK는 '존재하는 파일이 있을 때'만 반환하면 어떨까?->처리 완료
//
//	status = find_exec(&argv[0]);
//
	//find_exec 대신 pipex에서 경로찾는 함수 이용
	char	**envp_paths = get_envp_paths(g_envp);
	//dprintf(2, "in %s, argv[0]: %s\n", __func__, argv[0]);
	whole_path = find_cmd_path(argv[0], envp_paths);
	if (!whole_path)
	{
		dprintf(2, "Failed to find whole path\n");
		exit(EXIT_FAILURE);
	}
	free(argv[0]);
	argv[0] = whole_path;
	status = CODE_OK;
	if (status == CODE_ERROR_GENERIC)
	{
		dprintf(2, "shell: %s: command not found\n", argv[0]);
		exit(127);
	}
	else if (status != CODE_OK)
	{
		dprintf(2, "shell: error occured\n");
		exit(EXIT_FAILURE);
	}
	if (access(argv[0], F_OK) < 0)
	{
		dprintf(2, "shell: %s: No such file or directory\n", argv[0]);
		exit(127);
	}
	if (access(argv[0], X_OK) == 0)
	{
		//dprintf(3, "before execve cur_idx: %d\n\n", info->cur_idx);
		execve(argv[0], argv, g_envp);
	}
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
			dprintf(2, "shell: %s: is a directory\n", argv[0]);
		else
			dprintf(2, "shell: %s: Permission denied\n", argv[0]);
		exit(126);
	}
	//As the convention, call _exit(127) in such case
	exit(127);
}
