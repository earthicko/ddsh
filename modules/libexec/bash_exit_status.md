# BASH EXIT STATUS (from man)

For the shell's purposes, a command which exits with a zero exit status has succeeded.  An exit status of zero indicates success.  A non-zero exit  status indicates failure.  When a command terminates on a fatal signal N, bash uses the value of 128+N as the exit status.

If  a  command  is  not found, the child process created to execute it returns a status of 127.  If a command is found but is not executable, the return status is 126.

If a command fails because of an error during expansion or redirection, the exit status is greater than zero.

Shell builtin commands return a status of 0 (true) if successful, and non-zero (false) if an error occurs while they execute.  All  builtins  return  an exit status of 2 to indicate incorrect usage.

Bash  itself returns the exit status of the last command executed, unless a syntax error occurs, in which case it exits with a non-zero value.  See also the exit builtin command below.

# BASH EXIT STATUS (from gnu manual)

The exit status of an executed command is the value returned by the waitpid system call or equivalent function. Exit statuses fall between 0 and 255, though, as explained below, the shell may use values above 125 specially. Exit statuses from shell builtins and compound commands are also limited to this range. Under certain circumstances, the shell will use special values to indicate specific failure modes.

-> exit status는 0~255 사이다. 그럼에도 쉘은 아마 125 이상의 값을 특별하게 사용할 것이다.

-> 복합 명령어와 빌트인 커맨드 둘다 이 범위로 제한된다.

-> 특정 상황에서 쉘은 실패 모드를 나타내기 위해 특별한 값을 사용한다. 


For the shell’s purposes, a command which exits with a zero exit status has succeeded. A non-zero exit status indicates failure. This seemingly counter-intuitive scheme is used so there is one well-defined way to indicate success and a variety of ways to indicate various failure modes. When a command terminates on a fatal signal whose number is N, Bash uses the value 128+N as the exit status.

-> 0으로 종료한 프로그램은 성공 상태를 나타낸다. 0이 아닌 exit status는 실패다.

-> 이는 직관적이지 않은 것처럼 보이므로, 성공을 나타내는 하나의 잘 정의된 방법과 실패를 나타내는 다양한 방법이 존재한다.


If a command is not found, the child process created to execute it returns a status of 127. If a command is found but is not executable, the return status is 126.

-> 명령어를 찾지 못했다면 해당 명령어를 실행하기 위해 생성된 자식 프로세스는 127을 리턴한다.

-> 커맨드를 찾았으나 실행가능하지 않으면 126을 리턴한다. (디렉토리이거나 실행권한이 없을 때)


If a command fails because of an error during expansion or redirection, the exit status is greater than zero.

-> 확장, 또는 리다이렉션 도중 실패시 exit status는 0 보다 크다

**\<non_exisiting 의 경우 1로 종료된다**


The exit status is used by the Bash conditional commands (see Conditional Constructs) and some of the list constructs (see Lists of Commands).

-> 맨대토리 외 요구사항 (if문 또는 &&, ||, ;)


All of the Bash builtins return an exit status of zero if they succeed and a non-zero status on failure, so they may be used by the conditional and list constructs. All builtins return an exit status of 2 to indicate incorrect usage, generally invalid options or missing arguments.

-> 모든 빌트인 명령어는 성공시 exit status 0을 반환하고, 실패시 0이 아닌 status를 반환한다.

-> **모튼 빌트인 명령어는 *잘못된* 사용법에 대해 exit status 2를 반환한다. 일반적으로 유효하지 않은 옵션이나 인자가 누락됐을 경우 등**


The exit status of the last command is available in the special parameter $? (see Special Parameters).

-> $?라는 특별한 변수에 마지막 명령어의 exit_status가 저장된다.
