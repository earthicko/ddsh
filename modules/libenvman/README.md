# 환경 변수 관리자 모듈 (libenvman)

```c
int	envmanager(char **envp, void *buf, char *name, char *val);
```

### 의존성 정보

- `libft.a`

# 개요

```c
/* libft_def.h */
enum	e_returncode
{
	CODE_OK = 0,
	CODE_ERROR_GENERIC = -1,
	CODE_ERROR_IO = -2,
	CODE_ERROR_MALLOC = -3,
	CODE_ERROR_SCOPE = -4,
	CODE_ERROR_DATA = -5
};

/* envmanager_internal.h */
typedef struct s_enventry
{
	char	*name;
	char	*val;
}	t_enventry;

/* envmanager.h */
// init: set envp
// clear: set none
// getval: set (char **)buf, name
// setval: set name, val
// unsetval: set name
// getenvp: set (char ***)buf
int		envmanager(char **envp, void *buf, char *name, char *val);

int		envmanager_replace_envvar(char **buf, int quote_removal);
int		envman_split_envstr(char *str, char **ret_name, char **ret_val);
char	*envman_compose_envstr(char *name, char *val);
int		exit_stat_manager(int new_stat);
```

이 모듈은 외부에 1개의 인터페이스용 함수 및 4개의 유틸리티 함수를 제공한다.

`envmanager` 함수는 5개의 기능을 가지고 있으며, 매개 변수의 어떤 부분을 `NULL`로 입력하느냐에 따라 각각의 기능이 발동한다. 이 함수의 반환값은 `libft_def.h`의 `enum e_returncode`에 정의된 의미를 가진다. 동작이 성공할 시 `CODE_OK` (`0`), 실패할 시 음수를 반환한다.

|envp|buf|name|val|기능|
|----|---|----|---|----|
|`(char **)envp`|`NULL`|`NULL`|`NULL`|환경 변수 입력|
|`NULL`|`NULL`|`NULL`|`NULL`|초기화|
|`NULL`|`(char **)buf`|`(char *)name`|`NULL`|변수의 값 조회|
|`NULL`|`NULL`|`(char *)name`|`(char *)val`|변수 생성/값 설정/값 변경|
|`NULL`|`NULL`|`(char *)name`|`NULL`|변수 삭제|
|`NULL`|`(char ***)buf`|`NULL`|`NULL`|`execve()`에 사용할 envp 생성|

입력된 매개 변수의 값이 위 표와 일치하지 않을 경우 `CODE_ERROR_DATA`를 반환한다.

이 모듈은 내부적으로 `struct s_enventry`를 사용하여 환경 변수의 <이름>-<값> 쌍을 관리한다.

각 유틸리티의 기능은 다음과 같다.

- `envman_replace_envvar`: 문자열 내부에서 `$name`꼴의 패턴을 찾아 해당하는 환경 변수의 값으로 대체한다.
- `envman_split_envstr`: `name=value` 꼴의 패턴을 가진 문자열을 `name`과 `value`로 분리한다.
- `envman_compose_envstr`: `name`, `value` 2개의 문자열을 `name=value`꼴로 합친다.
- `exit_stat_manager`: 마지막 exit status를 설정하거나 반환한다.

### 올바른 환경 변수의 이름

알파벳, 언더스코어, 숫자로만 이루어져 있고 숫자로 시작하지 않는 문자열은 올바른 이름이다.
이 모듈은 환경 변수를 설정하기 전에 올바른 이름을 가지고 있는지 확인하고 올바르지 않을 시 예외 처리가 일어난다.
따라서 셸 명세에서 요구하는 `$?` 변수는 올바른 이름이 아니다. 이 기능은 예외 처리를 통해 별도로 구현되었다.

# 기능 설명

## 주 인터페이스

### 환경 변수 입력

```c
int	main(int argc, char **argv, char **envp)
{
	int		stat;
	
	(void)argc;
	(void)argv;
	stat = envmanager(envp, NULL, NULL, NULL);
	return (0);
}
```

프로그램이 실행될 적에 전달받은 `(char **)envp`를 그대로 입력하고, 나머지 매개 변수에 모두 `NULL`을 입력할 시 발동된다.

이 모듈은 `envp`가 가리키는 모든 문자열을 처음 등장하는 `'='` 기준으로 2개로 분할한다. 분할된 첫번째 부분이 `t_enventry`의 `name`, 나머지 부분이 `val`에 복사된다.

반환 값은 다음과 같다.

- `CODE_OK`: 정상적으로 완료됨
- `CODE_ERROR_DATA`: 올바르지 않은 엔트리가 감지됨
- `CODE_ERROR_MALLOC`: 메모리를 할당할 수 없음

### 초기화

```c
int	stat;
stat = envmanager(NULL, NULL, NULL, NULL);
```

모든 매개변수에 `NULL`을 입력할 시 발동된다.

모듈이 내부적으로 할당한 모든 메모리 등 자원을 반납하고 모듈을 초기화시킨다. 모듈은 프로그램이 처음 실행될 적의 상태로 돌아간다.

이 기능은 항상 `CODE_OK`를 반환한다.

### 변수의 값 조회

```c
int		stat;
char	*buf;
char	*name;

name = "FOO";
stat = envmanager(NULL, &buf, name, NULL);
```

`buf`에 `char *`형 변수의 주소 (`char **`)를, `name`에 찾고싶은 변수의 이름 문자열을, 나머지 매개 변수에 `NULL`을 입력할 시 발동된다.

모듈은 `name`의 이름을 가진 변수가 있는지 확인하고, 그러한 변수가 존재할 시 그 값을 `buf`가 가리키는 주소에 복사 및 할당한다.

이때 name에 `"?"`이 입력되면 예외 처리가 발동하여 마지막으로 설정된 exit status가 `buf`에 설정된다.

오류가 발생할 시 `*buf`의 값은 변하지 않는다.

반환 값은 다음과 같다.

- `CODE_OK`: 정상적으로 완료됨
- `CODE_ERROR_DATA`: 해당 변수가 존재하지 않음
- `CODE_ERROR_MALLOC`: 메모리를 할당할 수 없음

### 변수 생성/값 설정/값 변경

```c
int		stat;
char	*name;
char	*val;

name = "FOO";
val = "BAR";
stat = envmanager(NULL, NULL, name, val);
```

`name`에 설정할 변수의 이름 문자열을, `val`에 변수의 값 문자열을, 나머지 매개 변수에 `NULL`을 입력할 시 발동된다.

`name`의 이름을 가진 변수의 값을 `val`로 설정한다. 이때 일치하는 이름이 없을 경우 엔트리가 새로 생성된 뒤 설정된다. 일치하는 이름이 존재할 경우 기존의 값은 삭제되고 새 값이 설정된다.

반환 값은 다음과 같다.

- `CODE_OK`: 정상적으로 완료됨
- `CODE_ERROR_DATA`: `name`이 올바른 이름이 아님
- `CODE_ERROR_MALLOC`: 메모리를 할당할 수 없음

비정상 종료시에도 기존 엔트리가 보존된다. 따라서 이 기능을 호출하는 함수에는 비정상 종료를 감지할 시 프로그램을 종료시킬 것인지 결정하는 로직이 필요하다.

### 변수 삭제

```c
int		stat;
char	*name;

name = "FOO";
stat = envmanager(NULL, NULL, name, NULL);
```

`name`에 삭제할 변수의 이름 문자열을, 나머지 매개 변수에 `NULL`을 입력할 시 발동된다.

`name`의 이름을 가진 엔트리가 삭제된다. 그러한 이름의 엔트리가 없을 시엔 아무 것도 하지 않는다.


반환 값은 다음과 같다.

- `CODE_OK`: 정상적으로 완료됨
- `CODE_ERROR_DATA`: 일치하는 이름의 엔트리가 없음

### execve()에 사용할 envp 생성

```c
int		stat;
char	**new_envp;

stat = envmanager(NULL, &new_envp, NULL, NULL);
```

현재의 환경 변수를 `execve()`에 매개 변수로 입력하도록 형식을 맞추어서 문자열의 배열 형태로 생성한다. 이것은 `"<name>=<val>"`의 형식으로 이루어져 있고 변수가 N개일 시 N + 1개의 원소를 가지고 있으며 마지막 원소는 `NULL`로 설정된다.

`buf`가 가리키는 주소에 `char **` 자료형으로 `char *`의 배열이 동적 할당된다.

반환 값은 다음과 같다.

- `CODE_OK`: 정상적으로 완료됨
- `CODE_ERROR_MALLOC`: 메모리를 할당할 수 없음

비정상 종료시에도 기존 엔트리가 보존된다. 따라서 이 기능을 호출하는 함수에는 비정상 종료를 감지할 시 프로그램을 종료시킬 것인지 결정하는 로직이 필요하다.

## 유틸리티

### 환경 변수 확장

```c
int envmanager_replace_envvar(char **buf, int quote_removal);

char *str = strdup("HOME=\"$HOME\"");
printf("%s\n", str); // HOME="$HOME"
envmanager_replace_envar(&str, 1);
printf("%s\n", str); // HOME=/Users/donghyle
```

`buf`가 가리키는 문자열에서 `$name`꼴의 패턴을 찾아 해당하는 환경 변수의 값으로 대체한다.
이때 `*buf`는 반드시 `free()` 가능해야 한다. `quote_removal`은 `0` 또는 `1`의 값을 입력받을 수 있고, `1`을 입력할 시 환경 변수의 값이 아닌 부분에서 따옴표가 제거된다.

반환 값은 다음과 같다.

- `CODE_OK`: 정상적으로 완료됨
- `CODE_ERROR_MALLOC`: 메모리를 할당할 수 없음

### 환경 변수 문자열 처리

```c
int envman_split_envstr(char *str, char **ret_name, char **ret_val);
char *envman_compose_envstr(char *name, char *val);

// 쪼개기
char *str = "FOO==BAR";
char *name, *val;
envman_split_envstr(str, &name, &val);
// name = "FOO", val = "=BAR"

// 합치기
name = "SPAM";
val = "EGG";
str = envman_compose_envstr(name, val);
// str = "SPAM=EGG";
```

환경 변수를 구성하는 `name`과 `val`을 합치거나 쪼갠다.

반환 값은 다음과 같다.

**envman_split_envstr**

- `CODE_OK`: 정상적으로 완료됨
- `CODE_ERROR_DATA`: 올바르지 않은 변수 이름이 감지됨
- `CODE_ERROR_MALLOC`: 메모리를 할당할 수 없음

**envman_compose_envstr**

- `free()` 가능한 문자열 주소: 정상적으로 완료됨
- `NULL`: 메모리를 할당할 수 없음

### Exit Status 관리자

```c
int	exit_stat_manager(int new_stat);

exit_stat_manager(1); // 마지막 Exit Status를 1로 설정
int stat = exis_stat_manager(-1); // 마지막 Exit Status를 가져옴
```

`new_stat`에 음수를 입력할 시 마지막으로 설정된 Exit Status를 반환한다. 0 이상 256 미만의 수를 입력할 시 Exit Status를 이 값으로 설정한다. 그 이외의 값을 입력할 시 `-1`을 반환한다.
