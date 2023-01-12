#include <stdlib.h>
#include "libft.h"
#include "libft_def.h"
#include "t_node.h"
#include "exec_internal.h"

int	get_n_redir(t_node *node)
{
	int		n_redir;
	t_list	*cursor;
	t_node	*curr;

	n_redir = 0;
	cursor = node->childs;
	while (cursor)
	{
		curr = cursor->content;
		curr = curr->childs->content;
		if (curr->type == NODETYPE_IO_REDIRECT)
			n_redir++;
		cursor = cursor->next;
	}
	return (n_redir);
}

//free하는 로직 수정이 필요할듯..
//만약 여기서 실패하는 경우를 이 안에서 처리하면 아래 반복문 밑에서 따로 잡아줄 필요는 없음
static int	build_unit_fail(t_exec_unit *unit)
{
	free(unit->argv);
	free(unit->redir_arr);
	unit->argv = 0;
	unit->redir_arr = 0;
	return (CODE_ERROR_MALLOC);
}

static int	build_unit(t_exec_unit *unit, t_node *simple_cmd)
{
	const int	n_redir = get_n_redir(simple_cmd);
	const int	n_word = node_getntokens(simple_cmd) - 2 * n_redir;
	int			i;

	unit->argv = (char **)malloc(sizeof(char *) * (n_word + 1));
	unit->redir_arr = (t_redir *)malloc(sizeof(t_redir) * n_redir);
	unit->n_redir = n_redir;
	if (!unit->argv || unit->redir_arr)
		return (build_unit_fail(unit));
	i = -1;
	while (++i < node_getntokens(simple_cmd))
	{
		if (cmd_elem 본 후, 만약 word라면)
			argv에 값 할당;
		else
			트리 깊이를 조금 더 들어간 다음에 리다이렉션 토큰 추출해서 redir_arr에 저장;
		simple_cmd->childs->content->childs ... 가독성이 떨어짐
	}
}

static int	get_n_unit(t_node *root)
{
	int		n_unit;
	t_list	*curr;

	n_unit = 0;
	curr = root->childs;
	while (curr)
	{
		curr = curr->next;
		n_unit++;
	}
	return (n_unit);
}

int	build_exec_unit(t_node *root, t_unit_arr *units)
{
	const int	n_unit = get_n_unit(root);
	t_list		*curr;
	int			idx;

	units->arr = (t_exec_unit *)malloc(sizeof(t_exec_unit) * n_unit);
	if (units->arr)
		return (CODE_ERROR_MALLOC);
	//bzero로 초기화하면 전부 널로 채워지는지 한번 체크할 것
	units->n_unit = n_unit;
	ft_bzero(units->arr, n_unit * sizeof(t_exec_unit));
	curr = root->childs;
	idx = -1;
	while (++idx < n_unit)
	{
		if (build_unit(units->arr + idx, curr) == CODE_ERROR_MALLOC)
			return (build_exec_fail(units, idx));
		curr = curr->next;
	}
}

echo $""
