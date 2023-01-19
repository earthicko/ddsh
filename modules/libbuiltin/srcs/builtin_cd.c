#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "libft.h"
#include "envmanager.h"
#include "libft_def.h"

// FIXED: 명령어 실패에 대한 exit status 수정
// FIXED: cd에 아무 인자도 들어오지 않는 경우에 대한 분기 추가
// cd인자로 디렉토리가 입력되지 않으면 home디렉토리를 사용한다
//
// TODO: 쉘이 처음 실행될 때에도 이미 OLDPWD가 설정돼 있음(수정하지 않아도 된다고 생각함)
// TODO: 에러메시지 구현 및 놈에 맞게 수정
// TODO: (구현하지 않을듯)현재 디렉토리 상위디렉토리를 삭제할 경우 cd .. 명령어 동작이 일부 다름
static int	builtin_cd_internal(char *target)
{
	char	*pwd;
	int		stat;

	pwd = getcwd(NULL, 0);
	if (pwd)
		envman_setval("OLDPWD", pwd);
	free(pwd);
	stat = chdir(target);
	pwd = getcwd(NULL, 0);
	if (pwd)
		envman_setval("PWD", pwd);
	free(pwd);
	if (stat)
		return (1);
	return (CODE_OK);
}

int	builtin_cd(char **argv)
{
	int		stat;
	char	*target;

	argv++;
	if (*argv && !ft_strncmp(*argv, "-", 2))
	{
		if (envman_getval("OLDPWD", &target))
		{
			printf("Unimplemented error message of cd.\n");
			return (1);
		}
		printf("%s\n", target);
	}
	else if (!*argv)
	{
		if (envman_getval("HOME", &target))
		{
			printf("Unimplemented error message of cd.\n");
			return (1);
		}
	}
	else
	{
		target = ft_strdup(argv[0]);
		if (!target)
			return (1);
	}
	stat = builtin_cd_internal(target);
	free(target);
	return (stat);
}
