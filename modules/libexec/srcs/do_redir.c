#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include "heredoc.h"
#include "executor_internal.h"
#include "libft_def.h"
#include "t_exec_unit.h"

// TODO: 반복문 조건 깔끔하게 고칠 것

int	process_redir(t_redir *redir_arr, int n_redir)
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
		//REDIR_NONE일 때 널 함수포인터에 대한 가드가 필요함
		//여기 깔끔하게 고칠 수 있나?
		if (redir_arr[i].type == REDIR_NONE)
		{
			printf("in %s, redir type error\n", __func__);
			continue ;
		}
		if (do_redir[redir_arr[i].type](redir_arr + i) != CODE_OK)
		{
			dprintf(2, "in %s, fail here?\n", __func__);
			return (CODE_ERROR_IO);
		}
	}
	return (CODE_OK);
}

int	do_redir_in(t_redir *redir_arr)
{
	int	fd;

	fd = open(redir_arr->content, O_RDONLY);
	if (fd < 0 || dup2(fd, STDIN_FILENO) < 0 || close(fd) < 0)
		return (CODE_ERROR_IO);
	return (CODE_OK);
}

int	do_redir_out(t_redir *redir_arr)
{
	int	fd;
	
	fd = open(redir_arr->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0 || dup2(fd, STDOUT_FILENO) < 0 || close(fd) < 0)
		return (CODE_ERROR_IO);
	return (CODE_OK);
}

//heredoc_file을 언제 free해주어야 하지?
//clear 호출될 때 처리하는게 자연스러움
//
//아직 파스트리에서 heredoc 실행을 안해서 동작하지 않음
int do_redir_in_here(t_redir *redir_arr)
{
	//히어독 매니저로부터 파일명 받아온 후, redir_in과 동일하게 처리
	int		fd;
	char	*heredoc_file;

	(void)redir_arr;
	if (heredoc_get_next_filename(&heredoc_file) != CODE_OK)
		return (CODE_ERROR_IO);
	fd = open(heredoc_file, O_RDONLY);
	free(heredoc_file);
	if (fd < 0 || dup2(fd, STDIN_FILENO) < 0 || close(fd) < 0)
		return (CODE_ERROR_IO);
	return (CODE_OK);
}

int	do_redir_out_append(t_redir *redir_arr)
{
	int	fd;
	
	fd = open(redir_arr->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0 || dup2(fd, STDOUT_FILENO) < 0 || close(fd) < 0)
		return (CODE_ERROR_IO);
	return (CODE_OK);
}
