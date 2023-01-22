#include <termios.h>
#include "libft_def.h"

# define INIT 0
# define RESTORE 1

// minishell 시작할 때 init
// 이후 exit직전에 RESTORE호출 (builtin exit에 추가해두면 될듯)
int	term_manager(int mode)
{
	static struct termios	org_term;
	static struct termios	new_term;
	
	// <클러스터에서 확인후 수정 필요>
	// 터미널과 bash에서 각각 stty입력해서 변화를 본 후, 서로 다른 옵션 on, off 해주기
	// 현재 집 맥에서는 bash 실행시 PENDIN옵션이 on되기에 일단 맞춰둠
	if (mode == INIT)
	{
		if (tcgetattr(0, &org_term) < 0 || tcgetattr(0, &new_term) < 0)
			return (CODE_ERROR_GENERIC);
		new_term.c_cflag |= PENDIN;
		tcsetattr(0, TCSANOW, &new_term);
	}
	else if (mode == RESTORE)
	{
		if (tcsetattr(0, TCSANOW, &org_term) < 0)
			return (CODE_ERROR_GENERIC);
	}
	else
		return (CODE_ERROR_GENERIC);
	return (CODE_OK);
}
