# 개요

1. 메시지에 쓰이는 키워드 (`bash: ` 등)는 `includes/msgdef.h`에 정의하자
2. 프로그램 전체에 걸쳐 `ft_printf`를 사용하자
   1. 에러 메시지일 시 `ft_dprintf`를 사용하자
3. 최대한 하위 루틴에서 에러를 감지하는 순간 메시지를 출력하도록 하되, 융통성을 두자
   1. 상위 루틴에서 단지 어떤 에러 메시지를 출력해야 하는지 알아보기 위해 에러 코드를 까서 `if...else if`를 타는 상황을 막기 위함
4. 여러 번 등장하는 메시지가 아닌 한 메시지 자체를 `#define`하지 말자

# 코드 예시

```c
/* msgdef.h */
#define MSG_SHELL "dshell: "
#define MSG_BUILTIN_EXIT "cd: "

/* builtin_exit.c */
// exit의 파라미터로 숫자가 아닌 것을 줄 때 에러
ft_dprintf(STDERR_FILENO, "%s%s%s: numeric argument required\n", MSG_SHELL, MSG_BUILTIN_EXIT, argv[1]);
```

```c
/* msgdef.h */
#define MSG_SHELL_PROMPT

/* main.c */
str = readline(MSG_SHELL_PROMPT);
```
