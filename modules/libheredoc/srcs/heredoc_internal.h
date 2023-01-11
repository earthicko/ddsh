#ifndef HEREDOC_INTERNAL_H
# define HEREDOC_INTERNAL_H
# include "heredoc.h"
# define PREFIX_HEREDOC_TEMPFILE ".heredoc_"
# define PREFIX_HEREDOC_PROMPT "> "

int		heredoc_read(int *n_heredoc, int expand, char *delimeter);
char	*generate_filename(int doc_id);

#endif
