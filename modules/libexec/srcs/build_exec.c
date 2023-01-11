#include <stdlib.h>
#include "libft.h"
#include "libft_def.h"
#include "t_exec_unit.h"
#include "t_node.h"
#include "exec_internal.h"

static int	build_unit_fail(t_exec_unit *unit)
{
	free(unit->argv);
	free(unit->redir_arr);
	unit->argv = 0;
	unit->redir_arr = 0;
	return (CODE_ERROR_MALLOC);
}

//free하는 로직 수정이 필요할듯..
//만약 여기서 실패하는 경우를 이 안에서 처리하면 아래 반복문 밑에서 따로 잡아줄 필요는 없음
static int	build_unit(t_exec_unit *unit, t_list *curr)
{
	const int	n_redir = get_n_redir(curr);
	const int	n_word = node_getntokens((t_node *)curr->content) - n_redir;

	unit->argv = (char **)malloc(sizeof(char *) * n_word);
	unit->redir_arr = (t_redir *)malloc(sizeof(t_redir) * n_redir);
	// 따로 함수를 뺄까?
	if (!unit->argv || unit->redir_arr)
		return (build_unit_fail(unit));
}

static int	get_n_unit(t_node *root)
{
	int		n_unit;
	t_list	*cur;

	n_unit = 0;
	cur = root->childs;
	while (cur)
	{
		cur = cur->next;
		n_unit++;
	}
	return (n_unit);
}

int	build_exec_unit(t_node *root, t_unit_arr *execs)
{
	const int	n_unit = get_n_unit(root);
	t_list		*curr;
	int			idx;

	execs->arr = (t_exec_unit *)malloc(sizeof(t_exec_unit) * n_unit);
	if (execs->arr)
		return (CODE_ERROR_MALLOC);
	//bzero로 초기화하면 전부 널로 채워지는지 한번 체크할 것
	execs->n_unit = n_unit;
	ft_bzero(execs->arr, n_unit * sizeof(t_exec_unit));
	curr = root->childs;
	idx = -1;
	while (++idx < n_unit)
	{
		build_unit(execs->arr + idx, curr);
		if (!execs->arr[idx].argv || !execs->arr[idx].redir_arr)
			return (build_exec_fail(execs, idx));
		curr = curr->next;
	}
}
