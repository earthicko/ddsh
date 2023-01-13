#ifndef HEREDOC_INTERNAL_H
# define HEREDOC_INTERNAL_H
# include "heredoc.h"
# define PREFIX_HEREDOC_TEMPFILE ".heredoc_"
# define PREFIX_HEREDOC_PROMPT "> "

int	heredoc_read(int *n_heredoc, char *delimeter);
int	heredoc_get_filename(int n_heredoc, int doc_id, char **buf);

#endif
