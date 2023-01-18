#include <stdlib.h>
#include <unistd.h>
#include "strutils.h"
#include "libft.h"
#include "heredoc_internal.h"

static char	*_extract_filename(int slot)
{
	char	*cursor;
	char	*fullname;

	fullname = ttyname(slot);
	if (!fullname)
		return (NULL);
	cursor = fullname;
	while (*cursor)
		cursor++;
	while (cursor != fullname)
	{
		if (*cursor == '/')
			break ;
		cursor--;
	}
	if (*cursor == '/')
		cursor++;
	return (ft_strdup(cursor));
}

// TODO: prefix_filename에 현재 cwd가 저장됨.
// cwd를 만약 heredoc진행 중 삭제해버린다면, 이에 대한 예외처리가 필요해보임
int	_heredoc_init(
		int *n_heredoc, int *i_current, char **prefix_filename)
{
	char	*home_dir;
	char	*ttyfilename;
	char	*temp;

	ttyfilename = _extract_filename(ttyslot());
	if (!ttyfilename)
		return (CODE_ERROR_GENERIC);
	home_dir = getcwd(NULL, 0);
	if (!home_dir)
		return (CODE_ERROR_GENERIC);
	temp = ft_strmerge(
			5, home_dir, "/", ttyfilename, PREFIX_HEREDOC_TEMPFILE, "_");
	free(home_dir);
	free(ttyfilename);
	*prefix_filename = temp;
	if (!temp)
		return (CODE_ERROR_MALLOC);
	_heredoc_clear(n_heredoc, i_current, *prefix_filename, -1);
	return (CODE_OK);
}
