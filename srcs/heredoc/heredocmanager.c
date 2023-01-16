#include "libft_def.h"
#include "heredoc_internal.h"

// mode: INIT | READ | GETFILENAME | CLEAR
// init: sets directory of temp files to $HOME
// read: reads here_doc to doc_id, using delimeter (char *)buf
// getfilename: store filename of doc_id on (char **)buf
// getnextfilename: store filename of next doc_id on (char **)buf
// clear: clear all docs if doc_id < 0, else clear doc_id
int	heredocmanager(int mode, int doc_id, void *buf)
{
	static int	n_heredoc;
	static int	i_current;
	static char	*temp_dir;

	if (mode == HEREDOCMODE_INIT)
		return (heredoc_init_(&n_heredoc, &i_current, &temp_dir));
	if (mode == HEREDOCMODE_READ)
		return (heredoc_read_(&n_heredoc, temp_dir, buf));
	if (mode == HEREDOCMODE_GETFILENAME)
		return (heredoc_get_filename_(n_heredoc, temp_dir, doc_id, buf));
	if (mode == HEREDOCMODE_GETNEXTFILENAME)
		return (heredoc_get_next_filename_(
				n_heredoc, temp_dir, &i_current, buf));
	if (mode == HEREDOCMODE_CLEAR)
		return (heredoc_clear_(&n_heredoc, &i_current, temp_dir, doc_id));
	return (CODE_ERROR_SCOPE);
}
