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
// getenvp: set (char ***)buf
int	envmanager(char **envp, void *buf, char *name, char *val);
```

이 모듈은 외부에 1개의 인터페이스용 함수를 제공한다.

이 함수는 5개의 기능을 가지고 있으며, 매개 변수의 어떤 부분을 `NULL`로 입력하느냐에 따라 각각의 기능이 발동한다. 이 함수의 반환값은 `libft_def.h`의 `enum e_returncode`에 정의된 의미를 가진다. 동작이 성공할 시 `CODE_OK` (`0`), 실패할 시 음수를 반환한다.

|envp|buf|name|val|기능|
|----|---|----|---|----|
|(char **)envp|NULL|NULL|NULL|환경 변수 입력|
|NULL|NULL|NULL|NULL|초기화|
|NULL|(char **)buf|(char *)name|NULL|변수의 값 조회|
|NULL|NULL|(char *)name|(char *)val|변수 생성/값 설정/값 변경|
|NULL|(char ***)buf|NULL|NULL|execve()에 사용할 envp 생성|

입력된 매개 변수의 값이 위 표와 일치하지 않을 경우 `CODE_ERROR_DATA`를 반환한다.

이 모듈은 내부적으로 `struct s_enventry`를 사용하여 환경 변수의 <이름>-<값> 쌍을 관리한다.

# 기능 설명

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
- `CODE_ERROR_DATA`: `'='`가 포함되지 않은 문자열이 있음
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
- `CODE_ERROR_MALLOC`: 메모리를 할당할 수 없음

비정상 종료시에도 기존 엔트리가 보존된다. 따라서 이 기능을 호출하는 함수에는 비정상 종료를 감지할 시 프로그램을 종료시킬 것인지 결정하는 로직이 필요하다.

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
