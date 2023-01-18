#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include "libft.h"
#include "strutils.h"
#include "heredoc_internal.h"

static int	_heredoc_clear_entry(
				int n_heredoc, char *prefix_filename, int doc_id)
{
	int		stat;
	char	*filename;

	stat = _heredoc_get_filename(n_heredoc, prefix_filename, doc_id, &filename);
	if (stat)
		return (stat);
	unlink(filename);
	free(filename);
	return (CODE_OK);
}

static char	*_extract_dirname(char *path)
{
	char	*cursor;

	cursor = path;
	while (*cursor)
		cursor++;
	while (*cursor != '/' && cursor != path)
		cursor--;
	if (cursor == path && *cursor != '/')
		return (NULL);
	return (ft_substr(path, 0, cursor - path + 1));
}

static int	_closedir_and_return(DIR *dp, int stat)
{
	closedir(dp);
	return (stat);
}

static int	_heredoc_clear_all(char *temp_dir)
{
	DIR				*dp;
	struct dirent	*ep;
	char			*full_path;

	dp = opendir(temp_dir);
	if (!dp)
		return (CODE_ERROR_IO);
	while (TRUE)
	{
		ep = readdir(dp);
		if (!ep)
			break ;
		if (ep && ep->d_type == DT_REG && ft_strnstr(
				ep->d_name, PREFIX_HEREDOC_TEMPFILE, ft_strlen(ep->d_name)))
		{
			full_path = ft_strjoin(temp_dir, ep->d_name);
			if (!full_path)
				return (_closedir_and_return(dp, CODE_ERROR_MALLOC));
			unlink(full_path);
			free(full_path);
		}
	}
	return (_closedir_and_return(dp, CODE_OK));
}

int	_heredoc_clear(
		int *n_heredoc, int *i_current, char *prefix_filename, int doc_id)
{
	char	*dirname;
	int		stat;

	if (doc_id < 0)
	{
		dirname = _extract_dirname(prefix_filename);
		if (!dirname)
			return (CODE_ERROR_MALLOC);
		stat = _heredoc_clear_all(dirname);
		free(dirname);
		*n_heredoc = 0;
		*i_current = 0;
		return (stat);
	}
	else if (0 <= doc_id && doc_id < *n_heredoc)
	{
		if (_heredoc_clear_entry(*n_heredoc, prefix_filename, doc_id))
			return (CODE_ERROR_GENERIC);
	}
	else
		return (CODE_ERROR_SCOPE);
	return (CODE_OK);
}
