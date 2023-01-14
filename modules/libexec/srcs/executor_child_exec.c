#include <stdlib.h>
#include "executor_internal.h"
#include "libft_def.h"
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
		if (do_redir[redir_arr[i].type](redir_arr + i) != CODE_OK)
			return (CODE_ERROR_IO);
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
}

//어차피 execve호출 후 종료되거나, exit을 하게 돼서 반환형이 필요없음
 void	child_exec_cmd(t_info *info)
{
	int	stat;
	stat = set_fd_stream(info);
	if (stat != CODE_OK)
		exit(stat);
	//각 unit에 대한 정보로부터 명령어 실행
	//exit status에 주의할것!
}
