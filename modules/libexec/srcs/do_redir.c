#include <fcntl.h>
#include "heredoc.h"
#include "executor_internal.h"
#include "libft_def.h"
#include "t_exec_unit.h"

//dup2의 첫번째 인자를 close해야하는가?
//is_a_dir 처리를 어떡하지 ㅇㅁㅇ?
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

//얘가 몇번째 히얼독인지 어떻게 알지 ㅇㅁㅇ?
//hredoc 매니저에 커서 기능이 있나?
//히얼독 관련토큰 하나 소모할 때마다 +1씩 늘려주는 커서
int do_redir_in_here(t_redir *redir_arr)
{
	//히어독 매니저로부터 파일명 받아온 후, redir_in과 동일하게 처리
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
