#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "libft.h"
#include "envmanager.h"

// TODO: cd non_dir 입력시 exit status를 1(0이 아닌값)으로 수정해야함
// 이외에도 cd -a 등 전반적으로 exit status를 수정해야함
// exit status manager 호출하는 위치만 적당힐 설정해두면 될듯
// TODO: cd에 아무 인자도 입력하지 않을시 seg fault 발생
// TODO: 쉘이 처음 실행될 때에도 이미 OLDPWD가 설정돼 있음(수정하지 않아도 된다고 생각함)
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
	return (stat);
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
