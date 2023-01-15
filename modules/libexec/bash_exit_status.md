# BASH EXIT STATUS (from man)

For the shell's purposes, a command which exits with a zero exit status has succeeded.  An exit status of zero indicates success.  A non-zero exit  status indicates failure.  When a command terminates on a fatal signal N, bash uses the value of 128+N as the exit status.

If  a  command  is  not found, the child process created to execute it returns a status of 127.  If a command is found but is not executable, the return status is 126.

If a command fails because of an error during expansion or redirection, the exit status is greater than zero.

Shell builtin commands return a status of 0 (true) if successful, and non-zero (false) if an error occurs while they execute.  All  builtins  return  an exit status of 2 to indicate incorrect usage.

Bash  itself returns the exit status of the last command executed, unless a syntax error occurs, in which case it exits with a non-zero value.  See also the exit builtin command below.
