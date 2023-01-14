#include "exec_internal.h"
#include "libft_def.h"
#include "t_exec_unit.h"


#include <stdio.h>

int	free_unit_member(t_exec_unit *unit)
{
	free(unit->argv);
	free(unit->redir_arr);
	unit->argv = 0;
	unit->redir_arr = 0;
	return (CODE_ERROR_MALLOC);
}

int	free_single_unit(t_exec_unit *unit, int i, int j)
{
	int	idx;

	idx = -1;
	while (++idx < i)
		free(unit->argv[idx]);
	idx = -1;
	while (++idx < j)
		free(unit->redir_arr[idx].content);
	free(unit->argv);
	free(unit->redir_arr);
	unit->argv = 0;
	unit->redir_arr = 0;
	return (CODE_ERROR_MALLOC);
}

//반환형이 CODE_ERROR_MALLOC이 맞는지 다시 고심할 것
int	free_all_unit(t_unit_arr *units, int idx)
{
	int	i;

	i = -1;
	// 널인자에 대한 보호를 추가하는게 맞나?
	// 이 함수는 두 경우에 호출됨
	// 1. build_exec_unit에서 동적할당 실패시
	// 2. units_destroy에서
	// 1번의 경우 상관없지만 2번의 경우 malloc에러 리턴하면 다소 논리상 어색함
	// 그러나 호출되는 destroy함내에 은닉돼있어 상관없을 것 같기도
	if (!units->arr)
		return (CODE_OK);
	while (++i < idx)
		free_single_unit(units->arr + i, units->arr[i].n_word, \
				units->arr[i].n_redir);
	free(units->arr);
	units->arr = 0;
	return (CODE_ERROR_MALLOC);
}
