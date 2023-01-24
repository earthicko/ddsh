# 문자열 유틸리티

```c
#include "strutils.h"
```

# 개요

```c
typedef struct s_pchararr
{
	int		len;
	int		cap;
	char	**data;
}	t_pchararr;

t_pchararr	*pchararr_create(void);
t_pchararr	*pchararr_destroy(t_pchararr *pchararr);
int			pchararr_expand(t_pchararr *pchararr);
int			pchararr_append(t_pchararr *pchararr, char *data);

int			remove_quotes(char **buf);
int			is_valid_name(char *str);
int			is_builtin_command(char *str);
int			find_exec(char **buf);
```

유용하게 사용할 수 있는 문자열 관련 유틸리티 함수들이다.

# 기능 설명

### t_pchararr

*Pointer Char Array*

`char *` 자료형 변수를 담는 배열이다. 아래 설명할 메소드들을 통해 가변 길이 배열처럼 편리하게 사용할 수 있다.

### pchararr_create, pchararr_destroy

```c
t_pchararr *pchararr_create(void);
t_pchararr *pchararr_destroy(t_pchararr *pchararr);

t_pchararr *arr = pchararr_create();
pchararr_destroy(arr);
```

`t_pchararr` 구조체를 하나 동적 할당한다. 실패시 `NULL`을 반환한다.

생성된 구조체는 반드시 `pchararr_destroy()`를 사용하여 할당을 해제해야 한다. 이때 내부 배열에 담긴 문자열들은 `free()`되지 않으므로 원본 포인터를 잘 관리해야 한다.

### pchararr_expand, pchararr_append

```c
int pchararr_append(t_pchararr *pchararr, char *data);

char *element = "FOO";
pchararr_append(arr, element);
```

`pchararr`의 맨 마지막 원소로 `data`를 추가한다. 이때 `data`의 값은 복제되지 않으므로 원본 포인터를 잘 관리해야 한다.

기 할당된 메모리가 부족할 시 내부적으로 `pchararr_expand()`가 호출되어 자신에게 할당된 메모리를 2배 늘린다. 성공시 `CODE_OK`를, 실패시 `CODE_ERROR_MALLOC`을 반환한다. 실패하더라도 기존의 내용물은 보존된다.

### remove_quotes

```c
int remove_quotes(char **buf);

char *word = "\"Hello, 'World'!\"";
remove_quotes(&word);
printf("%s\n", word); // Hello, World!
```

`buf`가 가리키는 주소의 문자열에서 따옴표를 제거한 결과를 해당 주소에 다시 할당하여 기록한다. 이때 `*buf`는 반드시 `free()` 가능해야 한다. 성공시 `CODE_OK`를, 실패시 `CODE_ERROR_MALLOC`을 반환한다.

### is_valid_name

```c
int is_valid_name(char *str);
```

`str`이 올바른 이름(IEEE 1003 3.235)인지 여부를 검사하여 `TRUE` 또는 `FALSE`의 값을 반환한다.

### is_builtin_command

```c
int is_builtin_command(char *str);
```

`str`이 minishell 과제에서 요구하는 7개의 빌트인 명령어 중 하나인지 여부를 검사하여 `TRUE` 또는 `FALSE`의 값을 반환한다.

### find_exec

```c
int	find_exec(char **buf);
```

`buf`가 가리키는 주소의 문자열을 Simple Command의 첫 단어라고 가정하고, 이를 실제 실행 파일의 경로로 변환하려 시도한다(*IEEE 1003 2.9.1 Command Search and Execution 참조*). `*buf`의 기존의 값은 `free()`되고 변환된 주소가 새로 할당되어 저장된다. 따라서 `*buf`는 반드시 `free()` 가능해야 한다.

반환 값은 다음과 같다.

- `CODE_OK`: 정상적으로 종료됨, `*buf`는 실제 실행 파일 경로임
- `1`: `*buf`는 빌트인 명령어임
- `CODE_ERROR_MALLOC`: 메모리를 할당할 수 없음
- `CODE_ERROR_GENERIC`: `*buf`가 슬래시가 포함된 존재하지 않는 경로거나 `$PATH`에서 `*buf`를 찾을 수 없음
