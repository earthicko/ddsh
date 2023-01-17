#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include "executor_internal.h"
#include "libft_def.h"
#include "strutils.h"


#include <sys/errno.h>

/************경로 찾는 함수 임시로 가져옴***********/
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

static int	set_fd_stream(t_info *info)
{
	const t_exec_unit	cur_unit = info->units->arr[info->cur_idx];

	if (info->units->n_unit == 1)
		return (process_redir(cur_unit.redir_arr, cur_unit.n_redir));
	if (info->cur_idx == 0)
	{
		if (close(info->new_pipe[READ]) < 0
			|| dup2(info->new_pipe[WRITE], STDOUT_FILENO) < 0
			|| close(info->new_pipe[WRITE]) < 0)
			return (CODE_ERROR_IO);
	}
	else if (info->cur_idx == info->n_unit - 1)
	{
		if (dup2(info->old_pipe[READ], STDIN_FILENO) < 0
			|| close(info->old_pipe[READ]) < 0)
			return (CODE_ERROR_IO);
	}
	else
		if (close(info->new_pipe[READ]) < 0
			|| dup2(info->old_pipe[READ], STDIN_FILENO) < 0
			|| close(info->old_pipe[READ]) < 0
			|| dup2(info->new_pipe[WRITE], STDOUT_FILENO) < 0
			|| close(info->new_pipe[WRITE]) < 0)
			return (CODE_ERROR_IO);
	return (process_redir(cur_unit.redir_arr, cur_unit.n_redir));
}

//<리팩토링 시급함>
//
//어차피 execve호출 후 종료되거나, exit을 하게 돼서 반환형이 필요없음
//
// //참고만 stat, lstat 심볼릭 링크파일인 경우 동작이 다르대..
//
//
//IO 실패시 exit status가 어떻게 될까..? (fork한 상태에서)
//일단 1로 처리
//bash문서에서 발췌
//If a command fails because of an error during expansion or redirection, the exit status is greater than zero.
// TODO: argv[0]이 널인 경우에 대한 처리 추가 (인풋에 word가 없을 때)
 void	child_exec_cmd(t_info *info)
{
	struct stat	s_statbuf;
	char	**argv;
	int		status;
	char	*whole_path;

	if (set_fd_stream(info) < 0)
		exit(EXIT_FAILURE);
	//dprintf(2, "cur_dx: %d\n", info->cur_idx);
	argv = info->units->arr[info->cur_idx].argv;

	/************find_exec를 못써서 처리해둔 로직********************/

	//find_exec 대신 pipex에서 경로찾는 함수 이용
	char	**envp_paths = get_envp_paths(g_envp);
	whole_path = find_cmd_path(argv[0], envp_paths);
	if (!whole_path)
	{
		dprintf(2, "Failed to find whole path\n");
		exit(EXIT_FAILURE);
	}
	free(argv[0]);
	argv[0] = whole_path;
	/********************************************************************/

	status = find_exec(&argv[0]);
	//dprintf(2, "in %s, argv[0]: %s\n", __func__, argv[0]);
	//
	//아래부터 exit 상태 관련 로직
	//
	//일단 에러메시지 입력은 해둠 (하위 모듈에서 처리할 수 있다고 하긴 했지만)
	//
	//바로 아래 status가 1이면 빌트인
	if (status == 1)
	{
		//run builtin
		//exit (실패하면?)
	}
	if (status == CODE_ERROR_MALLOC)
	{
		dprintf(2, "in %s, critical error: malloc failed\n", __func__);
		exit(EXIT_FAILURE);
	}
	if (status == CODE_ERROR_GENERIC)
	{
		//만약 /가 존재하면 no such file 에러메시지가 나와야함
		//따라서 에러메시지 출력은 하위 모듈에서 처리하는게 나을듯
		dprintf(2, "in %s, shell: %s: command not found\n", __func__, argv[0]);
		exit(127);
	}
	if (access(argv[0], X_OK) == 0)
		execve(argv[0], argv, g_envp);
	else
	{
		//Permission denide든 file is a dir이든 둘다 126종료
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
