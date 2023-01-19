#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

// TODO: (구현하지 않을듯) 현재 위치하는 디렉토리 삭제시 pwd 실행 실패함(실제 배쉬는 경로 출력)
int	builtin_pwd(char **argv)
{
	char	*pwd;
	int		stat;

	(void)argv;
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (1);
	stat = printf("%s\n", pwd);
	free(pwd);
	if (stat < 0)
		return (1);
	return (0);
}
