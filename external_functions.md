## readline 라이브러리

### readline

```c
char* readline(const char* prompt);
```

`prompt`를 화면에 표시한 후 입력된 문자열을 반환한다.
반환된 문자열에서 마지막 `\n`은 제거된다. 이 문자열은 `malloc()` 되었으므로 추후 `free()` 해야 한다.

문자열을 읽던 중 `EOF`를 발견할 시 그 줄이 비어있었다면 `NULL`을 반환하고 비어있지 않다면 `\n`과 같은 방식으로 처리한다.

### rl_clear_history

```c
void rl_clear_history(void);
```

히스토리를 삭제한다.

### rl_on_new_line

```c
int rl_on_new_line(void);
```

화면을 업데이트하는 데 관련된 내부 함수들에게 입력 프롬프트가 새 줄로 넘어갔음을 통지한다. 사용자가 엔터 키를 누를 시 보통 라이브러리가 자동으로 호출하므로 이 함수를 애플리케이션이 직접 호출할 경우는 많지 않다.

### rl_replace_line

```c
void rl_replace_line(const char* text, int clear_undo);
char* rl_line_buffer; // 화면에 입력되었지만 아직 엔터 키를 누르지 않은 상태의 문자열이 저장된 버퍼
// point: 입력 커서의 위치, mark: 텍스트의 위치를 표현하는 단위
```

`rl_line_buffer`의 내용을 `text`로 대체한다. point와 mark는 가능하면 보존된다. `clear_undo`가 `0`이 아닐 시, undo list에서 현재 라인이 삭제된다.

### rl_redisplay

```c
void rl_redisplay(void);
```

`rl_line_buffer`의 내용을 화면에 표시(반영)한다.

### add_history

```c
void add_history(char* string);
```

`string`을 히스토리 목록의 마지막에 추가한다.

## 파일 입력/출력

### access

```c
int access(const char* path, int mode);
```

`path`가 가리키는 파일의 접근 가능 여부를 확인한다. 이때 `mode`에는 `R_OK`, `W_OK`, `X_OK`, `F_OK`의 속성 중 확인할 권한에 관련된 속성을 OR 연산 하여 입력한다.

성공시 `0`, 실패시 `-1` 반환 및 `errno`.

### open

```c
int open(const char* path, int oflag);
```

파일을 연다. 성공시 음수가 아닌 file descriptor, 실패시 `-1` 반환 및 `errno`.

### read

```c
ssize_t read(int fd, void* buf, size_t nbyte);
```

`fd`가 가리키는 파일에서 정보를 `nbyte`만큼 읽어서 `buf`가 가리키는 공간에 저장한다. 성공시 읽은 바이트 수 (`EOF`에 도달 시 `0`), 실패시 `-1` 반환 및 `errno`.

### write

```c
ssize_t write(int fd, const void* buf, size_t nbyte);
```

`fd`가 가리키는 파일에 `buf`가 가리키는 공간에 있는 정보를 `nbyte`만큼 기록한다. 성공시 기록한 바이트 수, 실패시 `-1` 반환 및 `errno`.

### close

```c
int close(int fd);
```

파일을 닫는다. 성공시 `0`, 실패시 `-1` 반환 및 `errno`.

## 파일 상태 조회

### stat, lstat, fstat

```c
int stat(const char* path, struct stat* buf);
int lstat(const char* path, struct stat* buf);
int fstat(int filedes, struct stat* buf);
```

`stat`은 `path`가 가리키는 파일의 정보를 획득하여 `buf`가 가리키는 공간에 저장한다.
`lstat`은 `stat`과 같지만 `path`가 심볼릭 링크일 경우 링크가 가리키는 파일이 아닌 링크 자체의 정보를 획득한다.
`fstat`은 `filedes`가 가리키는 파일의 정보를 획득한다.

`struct stat`의 명세는 `<sys/stat.h>`에 기술되며, `_DARWIN_FEATURE_64_BIT_INODE` 매크로의 활성 여부에 따라 달라진다.

성공시 `0`, 실패시 `-1` 반환 및 `errno`.

### unlink

```c
int unlink(const char* path);
```

`path`가 가리키는 링크를 디렉토리와 분리시키고 이 링크의 카운터를 1 감소시킨다. 감소한 결과 카운트가 0이라면 이 파일은 삭제된다. 성공시 `0`, 실패시 `-1` 반환 및 `errno`.

### opendir

```c
DIR* opendir(const char* filename);
```

`filename`이 가리키는 디렉토리를 열고 추후 이를 조작할 시 사용할 수 있는 포인터를 반환한다. 실패시 `NULL`을 반환한다.

### readdir

```c
struct dirent* readdir(DIR* dirp);
```

`dirp`가 가리키는 디렉토리 안에서 다음 디렉토리 엔트리를 향한 포인터를 반환한다. 오류가 발생하거나 디렉토리의 끝에 도달할 시 `NULL`을 반환하며, 오류 시에는 `errno`가 설정된다. 이 엔트리는 `dirp`에 대해 `readdir()` 또는 `closedir()`을 호출하기 전 까지 유효하다. 이때 엔트리의 순서는 정의되어 있지 않고 운영 체제가 결정한다.

### closedir

```c
int closedir(DIR* dirp);
```

`dirp`가 가리키는 디렉토리 스트림을 닫고 관련된 자원의 할당을 해제한다. 성공시 `0`, 실패시 `-1` 반환 및 `errno`.

## 현재 디렉토리 제어

### getcwd

```c
char* getcwd(char* buf, size_t size);
```

현재 디렉토리 (Current Working Directory)를 절대경로 형식으로 `buf`가 가리키는 공간에 저장하고, `buf`과 같은 값을 반환한다. `buf`에 확보된 메모리 크기를 `size`로 알려줄 수 있다. `buf`가 `NULL`일 시 `size`는 무시되고 이 함수가 필요한 만큼 메모리를 할당하여 반환한다. 이 반환값은 추후 `free()`해야 한다. 실패시 `NULL` 반환 및 `errno`.

### chdir

```c
int chdir(const char* path);
```

현재 디렉토리를 `path`로 변경한다. 성공시 `0`, 실패시 `-1` 반환 및 `errno`.

## 프로세스 제어

### fork

```c
pid_t fork(void);
```

부모 (이 함수를 호출하는 프로세스)의 완전하고 새로운 복사본인 자식 프로세스를 만든다.

> 부모와 다른 부분도 있다. 자식은 자신의 pid와 부모 pid가 다르다. 이때 부모 pid는 호출한 프로세스의 pid가 된다.

부모의 fd들은 모두 복사되고 파일 내의 포인터 또한 공유된다. 즉 한 쪽에서 행한 입출력 작업은 반대쪽에 영향을 미친다.

성공시 자식 입장에서는 `0`을, 부모 입장에서는 새 자식의 pid를 반환받는다. 실패시 자식은 생성되지 않으므로 반환 값은 존재하지 않고, 부모에게 `-1`이 반환되며 `errno`가 설정된다.

### wait, waitpid, wait3, wait4

```c
pid_t wait(int* stat_loc);
pid_t waitpid(pid_t pid, int* stat_loc, int options);
pid_t wait3(int* stat_loc, int options, struct rusage* rusage);
pid_t wait4(pid_t pid, int* stat_loc, int options, struct rusage* rusage);
```

위 함수들은 모두 `wait4()`를 통해 구현되었다. `wait4`는 어떤 프로세스가 종료되거나 호출자가 시그널을 받을 때 까지 호출자를 정지한다.

- `pid`: 기다릴 대상 프로세스의 id를 지정한다.
  - `pid == -1`: 자식 중 어떤 프로세스라도 종료될 시 깨어난다.
  - `pid == 0`: 자신의 프로세스 그룹 안에서 어떠한 자식 프로세스라도 종료될 시 깨어난다.
  - `pid < -1`: `pid`의 절댓값과 프로세스 그룹 id가 같은 프로세스 중 어떠한 프로세스라도 종료될 시 깨어난다.
  - `pid > 0`: 해당 `pid`를 기다린다.
- `stat_loc`: `wait4()`를 종료하게 만든 프로세스의 마지막 상태를 이 주소에 저장하게 된다. 여기에 저장된 값을 다음 매크로에 입력하면 자세한 정보를 득할 수 있다.
  - `WIFEXITED()`: `_exit(2)`나 `exit(3)`에 의해 정상적으로 종료되었는가?
  - `WIFSIGNALED()`: 시그널을 수신하여 종료되었는가?
  - `WIFSTOPPED()`: 프로세스가 종료된게 아니라 정지 상태인가? (`WUNTRACED` 옵션이 켜졌거나 `ptrace`로 추적중일 시 유효함)
- `options`: 다음의 옵션들을 OR 연산하여 입력한다.
  - `WNOHANG`: 상태를 보고하고자 하는 프로세스가 없을 시엔 호출자를 멈추지 않는다(즉 pid 조건에 해당하는 프로세스가 없을 시 무한정 대기할 수 있다).
  - `WUNTRACED`: `SIGTTIN`, `SIGTTOU`, `SIGTSTP`로 인해 멈춘 (정지 상태) 자식 프로세스도 상태를 보고하도록 한다.
- `rsuage`: `NULL`이 아닐 시 종료된 프로세스와 그의 자식의 자원 사용 현황을 이 주소에 저장한다.

`wait3()`은 `wait4()`의 `pid`에 `-1`을 입력한 것과 같다. 즉 모든 자식 프로세스를 기다린다.

`waitpid()`는 `wait4()`의 `rusage`에 `NULL`을 입력한 것과 같다. `wait()`는 `pid`에 `-1`, `options`에 `0`, `rusage`에 `NULL`을 입력한 것과 같다.

### signal

```c
typedef void (*sig_t)(int);
sig_t signal(int sig, sig_t func);
```

`sig`에 해당하는 시그널을 수신할 시 수행할 함수 `func`를 지정한다. 성공시 이전에 지정되어있던 함수의 포인터가 반환되고 실패시 SIG_ERR가 반환되며 `errno`가 설정된다.

### sigaction

```c
int sigaction(int sig, sigaction* act, sigaction* oact);
struct  sigaction
{
    union __sigaction_u __sigaction_u;
    sigset_t sa_mask;
    int sa_flags;
};
union __sigaction_u {
    void (*__sa_handler)(int);
    void (*__sa_sigaction)(int, siginfo_t*, void*);
};
#define sa_handler      __sigaction_u.__sa_handler
#define sa_sigaction    __sigaction_u.__sa_sigaction
```

`sig`에 해당하는 시그널을 수신할 시 수행할 행동을 `act`가 가리키는 구조체에 지정한다. 실행할 함수는 `__sigaction_u`에 지정하되 `sa_handler` 형식 또는 `sa_sigaction` 형식 중 하나를 선택한다. `sa_mask`로 해당하는 시그널을 지정한다. `sa_flags`로 옵션을 지정한다.

성공시 `0`, 실패시 `-1` 반환 및 `errno`.

### sigemptyset, sigaddset

```c
int sigaddset(sigset_t* set, int signo);
int sigemptyset(sigset_t* set);
```

`set`가 가리키는 시그널 세트를 조작한다. `sigset_t`형 변수를 사용하기 전에는 반드시 `sigemptyset()`을 사용하여 초기화시켜야 한다. `sigaddset`를 사용하여 `signo`를 `set`에 추가한다. 이들은 항상 0을 반환한다.

### kill

```c
int kill(pid_t pid, int sig);
```

`pid`에 해당하는 프로세스에 `sig`에 해당하는 시그널을 보낸다. 

- `pid > 0`: 시그널을 프로세스 ID가 `pid`인 프로세스에 보낸다.
- `pid == 0`: 시그널을 이 함수를 호출하는 프로세스와 그룹 ID가 같은 모든 프로세스에 보낸다.
- `pid == -1`: 시그널을 호출자가 수퍼유저 권한을 가지고 있을 시 자신과 시스템 프로세스를 제외한 모든 프로세스에 보낸다.

성공시 `0`, 실패시 `-1` 반환 및 `errno`.

### exit

```c
void exit(int status);
```

프로세스를 종료한다. 모든 출력 스트림에 남아있는 자료를 기록한다. 모든 입력 스트림을 닫는다. `status`에서 최하위의 8개 비트 정수를 부모 프로세스에 전달한다.

### execve

```c
int execve(const char* path, char* const argv[], char* const envp[]);
```

`path`가 가리키는 파일을 `argv`와 `envp` 환경 변수를 주어 실행한다. 이 함수를 호출한 프로세스는 (성공적 실행 시) 새 프로세스로 탈바꿈한다.

`argv`는 `char*`의 배열이며 마지막 값이 `NULL`이다. 이들은 새 프로세스에 그대로 전달된다. 최소 1개의 문자열을 제공해야 하고, 관습 상 첫 문자열은 `path`에서 프로그램의 이름에 해당하는 부분이다.

`envp` 또한 `char*`의 배열이며 마지막 값이 `NULL`이다. 이는 보통 전역 변수 `environ`으로 접근할 수 있다.

`close-on-exec` 플래그가 설정되지 않은 fd는 새 프로세스에서도 그대로 남아있다. 차단하거나 무시하도록 설정된 시그널은 signal action에 관련 없이 계속 차단 혹은 무시된다. 그렇지 않은 시그널은 새 프로세스에서는 기본 액션으로 재설정된다. 

실행에 성공할 시 반환이 이루어질 수 없다. 실패시 `-1`이 반환되고 `errno`가 설정된다.

## 입력/출력 흐름 제어

### dup, dup2

```c
int dup(int fd);
int dup2(int fd, int fd2);
```

`dup()`는 `fd`가 가리키는 파일의 file descriptor를 복제하여 반환한다. 이 값은 현재 사용중이지 않은 fd 중 가장 작은 값이다. 복제된 fd에 가하는 모든 입력과 출력은 원본에 가하는 것과 동일하여 어떤 방법으로도 구분해낼 수 없다. 

`dup2()`는 file descriptor를 `fd2`의 값으로 복제하려 시도한다. `fd == fd2`일 시 어떠한 작업도 이루어지지 않고 `fd2`가 그대로 반환된다. `fd2`가 이미 사용중일 시 해당 파일에서 할당을 해제한 후 반환한다. 

성공시 복제된 descriptor, 실패시 `-1` 반환 및 `errno`.

### pipe

[읽기] [쓰기] 순서대로 구성된 파이프를 생성한다. `fd[1]`에 쓴 자료는 `fd[0]`에서 읽을 수 있다. 파이프는 양단의 fd가 모두 닫힐 때까지 존속한다. 

한 쪽의 fd가 닫힌 파이프는 *widowed* 되었다고 표현한다. window된 파이프에 쓰기를 시도하면 `SIGPIPE` 시그널을 받게 된다. 파이프에서 읽기 작업을 하는 프로세스에게 `EOF`를 전달하는 유일한 방법이 파이프를 widow화 시키는 것이다. 즉 `read()`를 호출할 시 버퍼를 소모한 후 `0`을 반환받게 된다.

성공시 `0`, 실패시 `-1` 반환 및 `errno`.

## 에러 처리

### strerror, perror

```c
char* strerror(int errnum);
void perror(const char* s);
```

`strerror()`는 `errnum`에 해당하는 에러 메시지 문자열을 반환한다.

`perror()`는 현재 `errno`에 해당하는 에러 메시지를 출력한다. 이때 `s`가 `NULL`이 아니고 `s[0]`이 `'\0'`이 아닐 시 (즉 문자열의 내용이 있을 시) 해당 문자열이 `s의 내용: 에러 메시지` 형식으로 출력되고, 문자열의 내용이 없을 시 콜론 없이 에러 메시지만 출력된다.

## 환경 변수

### getenv

```c
char* getenv(const char *name);
```

`name`의 이름을 가진 환경 변수의 문자열 주소를 반환한다. 이때 애플리케이션이 이 주소에 담긴 자료를 조작해서는 안 된다. 실패시 `NULL`을 반환한다.

## TTY 개체 제어

### isatty, ttyname, ttyslot

```c
int isatty(int fd);
char* ttyname(int fd);
int ttyslot(void);  // 레거시인가?
```

`isatty()`는 `fd`가 유효한 터미널 타입의 디바이스인지 확인하여 유효하다면 `1`, 아니라면 `0`을 반환하고 `errno`를 설정한다.

`ttyname()`은 `isatty(fd)`가 참인 `fd`에 대해 디바이스의 이름을 반환한다. 실패시 `NULL`을 반환한다.

> 이때 반환값이 `free()` 가능한가?

`ttyslot()`은 현재 프로세스를 컨트롤하는 터미널 디바이스의 번호를 반환한다. 실패시 `0`을 반환한다.

### ioctl

```c
int ioctl(int filedes, unsigned long request);
```

`filedes`가 가리키는 터미널의 속성을 변경한다. `request`의 값을 조작하는 데 필요한 매크로 및 정의는 `<sys/ioctl.h>`에 존재한다.

> 정확한 정의는 찾지 못했으며 `<sys/ioctl_compat.h>`에 존재할 수도 있다.

## termios 개체 제어

### tcsetattr, tcgetattr

```c
int tcsetattr(int filedes, int optional_actions, const struct termios* termios_p);
int tcgetattr(int filedes, struct termios* termios_p);
```

`tcsetattr()`는 `termios_p`에 저장된 터미널의 속성을 `filedes`가 가리키는 터미널에 반영한다. `optional_actions`에는 `<termios.h>`에 정의된 값들을 OR 연산하여 입력할 수 있다. 성공시 `0`, 실패시 `-1` 반환 및 `errno`.

`tcgetattr()`는 `filedes`가 가리키는 터미널의 속성을 `termios_p`에 저장한다. 성공시 `0`, 실패시 `-1` 반환 및 `errno`.

## terminfo (curses 에뮬레이션) 제어

### tgetent

```c
int tgetent(char* bp, const char* name);
```

`name`의 이름을 가진 터미널에 대한 엔트리를 가져온다. 이후 실행되는 함수들은 해당 터미널을 조작하게 된다. 에뮬레이션이기 때문에 `bp`는 무시된다. 성공시 `1`, 엔트리가 없을 시 `0`, terminfo의 DB가 없을 시 `-1`을 반환한다.

### tgetflag, tgetnum, tgetstr

```c
int tgetflag(char* id);
int tgetnum(char* id);
char* tgetstr(char* id, char** area);
```

이 함수들은 `id`의 이름을 가진 속성을 조회한다. 이때 `id`의 첫 2개 문자만이 입력된다. 속성은 정수 값 또는 문자열을 가질 수 있는데, 그 종류에 맞는 함수를 사용하여 값을 조회해야 한다.

`tgetflag()`는 속성이 지원되는지 여부를 참값 또는 `0`으로 반환한다.
`tgetnum()`는 속성의 값을 반환한다. 존재하지 않을 시 `-1`을 반환한다. `tgetstr()`는 속성의 값을 반환하면서 `area`가 가리키는 공간에도 복사한다. 존재하지 않을 시 `NULL`을 반환한다. 이때 `*area`는 문자열의 맨 끝으로 전진한다.

### tgoto, tputs

```c
char* tgoto(const char* cap, int col, int row);
int tputs(const char* str, int affcnt, int (*putc)(int));
```

`tgoto()`는 터미널의 커서를 (col, row)로 옮길 때 사용할 수 있는 문자열을 생성한다. 이때 `cap`에 escape sequence 문자열을 제공해야 하며 이는 `tgetstr()`로 획득할 수 있다. 실패 시 `NULL`을 반환한다.

`tputs()`는 `str`에 패딩 관련 정보를 추가하여 `putc` 함수를 사용해 출력한다. `affcnt`에는 이 동작에 영향을 받는 줄의 개수를 입력하거나, 이 정보가 필요하지 않은 경우 `1`을 입력한다. 이때 `str`에는 `tgetstr` 또는 `tgoto`가 생성한 문자열을 입력한다.
