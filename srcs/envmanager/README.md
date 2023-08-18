# 환경 변수 관리자 모듈 (libenvman)

```c
#include "envmanager.h"
```

### 의존성 정보

- `libft.a`

# 개요

```c
int envman_init(char **envp);
int envman_clear(void);
int envman_getval(char *name, char **buf);
int envman_setval(char *name, char *val);
int envman_unsetval(char *name);
int envman_getenvp(char ***buf);
int envman_export(void);

int envman_split_envstr(char *str, char **ret_name, char **ret_val);
char *envman_compose_envstr(char *name, char *val);
int exit_stat_manager(int new_stat);
```

이 모듈은 `(char **)envp`를 직접 조작하지 않고도 환경 변수를 추가 및 삭제하기 위해 만들어졌다.

- `envman_init`: 환경 변수 입력
- `envman_clear`: 초기화
- `envman_getval`: 변수의 값 조회
- `envman_setval`: 변수 생성/값 설정/값 변경
- `envman_unsetval`: 변수 삭제
- `envman_getenvp`: `execve()`에 사용할 `(char **)envp` 생성
- `envman_export`: 모든 엔트리를 builtin `export` 형식에 맞추어 출력

이 모듈은 내부적으로 `struct s_enventry`를 사용하여 환경 변수의 <이름>-<값> 쌍을 관리한다.

각 유틸리티의 기능은 다음과 같다.

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
int envman_init(char **envp);

int	main(int argc, char **argv, char **envp)
{
	int		stat;
	
	(void)argc;
	(void)argv;
	stat = envman_init(envp);
	return (0);
}
```

프로그램이 실행될 적에 전달받은 `(char **)envp`를 그대로 입력한다.

이 모듈은 `envp`가 가리키는 모든 문자열을 처음 등장하는 `'='` 기준으로 2개로 분할한다. 분할된 첫번째 부분이 `t_enventry`의 `name`, 나머지 부분이 `val`에 복사된다.

반환 값은 다음과 같다.

- `CODE_OK`: 정상적으로 완료됨
- `CODE_ERROR_DATA`: 올바르지 않은 엔트리가 감지됨
- `CODE_ERROR_MALLOC`: 메모리를 할당할 수 없음

### 초기화

```c
int envman_clear(void);

int	stat = envman_clear();
```

모듈이 내부적으로 할당한 모든 메모리 등 자원을 반납하고 모듈을 초기화시킨다. 모듈은 프로그램이 처음 실행될 적의 상태로 돌아간다.

이 기능은 항상 `CODE_OK`를 반환한다.

### 변수의 값 조회

```c
int envman_getval(char *name, char **buf);

char *buf;
char *name = "FOO";
int stat = envman_getval(name, &buf);
```

`buf`에 `char *`형 변수의 주소 (`char **`)를, `name`에 찾고싶은 변수의 이름의 문자열을 입력한다.

모듈은 `name`의 이름을 가진 변수가 있는지 확인하고, 그러한 변수가 존재할 시 그 값을 `buf`가 가리키는 주소에 복사 및 할당한다.

이때 name에 `"?"`이 입력되면 예외 처리가 발동하여 마지막으로 설정된 exit status가 `buf`에 설정된다.

오류가 발생할 시 `*buf`의 값은 변하지 않는다.

반환 값은 다음과 같다.

- `CODE_OK`: 정상적으로 완료됨
- `CODE_ERROR_DATA`: 해당 변수가 존재하지 않음
- `CODE_ERROR_MALLOC`: 메모리를 할당할 수 없음

### 변수 생성/값 설정/값 변경

```c
int envman_setval(char *name, char *val);

char *name = "FOO";
char *val = "BAR";
int stat = envman_setval(name, val);
```

`name`의 이름을 가진 변수의 값을 `val`로 설정한다. 변수를 생성하기만 하고 값을 지정하고 싶지 않다면 `val`에 `NULL`을 전달한다. 이때 일치하는 이름이 없을 경우 엔트리가 새로 생성된 뒤 설정된다. 일치하는 이름이 존재할 경우 기존의 값은 삭제되고 새 값이 설정된다.

반환 값은 다음과 같다.

- `CODE_OK`: 정상적으로 완료됨
- `CODE_ERROR_DATA`: `name`이 올바른 이름이 아님
- `CODE_ERROR_MALLOC`: 메모리를 할당할 수 없음

비정상 종료시에도 기존 엔트리가 보존된다. 따라서 이 기능을 호출하는 함수에는 비정상 종료를 감지할 시 프로그램을 종료시킬 것인지 결정하는 로직이 필요하다.

### 변수 삭제

```c
char name = "FOO";
int stat = envman_unsetval(name);
```

`name`의 이름을 가진 엔트리가 삭제된다. 그러한 이름의 엔트리가 없을 시엔 아무 것도 하지 않는다.


반환 값은 다음과 같다.

- `CODE_OK`: 정상적으로 완료됨
- `CODE_ERROR_DATA`: 일치하는 이름의 엔트리가 없음

### execve()에 사용할 envp 생성

```c
char	**new_envp;

int stat = envman_getenvp(&new_envp);
```

현재의 환경 변수를 `execve()`에 매개 변수로 입력하도록 형식을 맞추어서 문자열의 배열 형태로 생성한다. 이것은 `"<name>=<val>"`의 형식으로 이루어져 있고 변수가 N개일 시 N + 1개의 원소를 가지고 있으며 마지막 원소는 `NULL`로 설정된다. 이때 값이 지정되어 있지 않은 변수는 무시된다.

`buf`가 가리키는 주소에 `char **` 자료형으로 `char *`의 배열이 동적 할당된다.

반환 값은 다음과 같다.

- `CODE_OK`: 정상적으로 완료됨
- `CODE_ERROR_MALLOC`: 메모리를 할당할 수 없음

비정상 종료시에도 기존 엔트리가 보존된다. 따라서 이 기능을 호출하는 함수에는 비정상 종료를 감지할 시 프로그램을 종료시킬 것인지 결정하는 로직이 필요하다.

### export

```c
envman_export();
```

모든 엔트리의 목록을 출력한다.

- 값이 지정되어 있을 시: `"declare -x %s=%s"`, name, value
- 값이 지정되어 있지 않을 시: `"declare -x %s"`, name

값이 지정되어 있지 않은 변수는 `envman_getenvp`가 무시하기 때문에 필요한 기능이다.

## 유틸리티

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
