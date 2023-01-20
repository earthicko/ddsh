#ifndef HEREDOC_H
# define HEREDOC_H

int	heredoc_read(char *delimeter);
int	heredoc_get_filename(int doc_id, char **buf);
int	heredoc_get_next_filename(char **buf);
int	heredoc_clear(int doc_id);

#endif
