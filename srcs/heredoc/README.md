# here-document 관리 유틸리티

```c
int	heredocmanager(int mode, int doc_id, void *buf);
```

### 의존성 정보

- `libenvman.a`

# 개요

```c
enum e_heredocmode
{
	HEREDOCMODE_INIT = 0,
	HEREDOCMODE_READ,
	HEREDOCMODE_GETFILENAME,
	HEREDOCMODE_CLEAR
};

// mode: INIT | READ | GETFILENAME | CLEAR
// init: sets directory of temp files to $HOME
// read: reads here_doc to doc_id, using delimeter (char *)buf
// getfilename: store filename of doc_id on (char **)buf
// clear: clear all docs if doc_id < 0, else clear doc_id
int	heredocmanager(int mode, int doc_id, void *buf);
```

이 함수는 `mode`의 값에 따라 here-document를 생성하고 삭제할 수 있다.
이 함수는 지금까지 생성된 here-document의 수 (이하 `n_heredoc`)를 기록한다. 이 값은 `READ` 모드로 한번 호출될 때마다 `1`씩 증가한다.

생성된 N개의 here-document들은 각각 `0`...`N-1`번의 번호를 가지고 있다. 이는 `GETFILENAME`이나 `CLEAR` 모드로 호출할 때 필요한 값이다.

- `mode`가 `INIT`일 시:

현재 `$HOME`을 임시 파일 저장 디렉토리로 설정한다. 이후 모든 임시 파일은 여기에 생성하고 여기에서 찾게 된다.

- `mode`가 `READ`일 시:

콘솔에서 입력을 받아 here-document에 저장한다.

- `mode`가 `GETFILENAME`일 시:

`doc_id`번째 here-document의 경로를 반환한다.

- `mode`가 `CLEAR`일 시:

`doc_id`번째 혹은 모든 here-document를 삭제한다.

### here-document가 저장되는 위치

here-document는 임시 파일로 저장된다. 이들의 파일 이름은 다음과 같다.

```
.heredoc_{TTY 이름}_{doc_id}
```

`INIT` 기능을 한번 실행했다면 이들은 `$HOME`에 저장되고, 그렇지 않을 시 현재 디렉토리 (CWD)에 저장된다. 현재 디렉토리는 `cd` 명령으로 변경할 수 있으므로 반드시 셸이 실행되자마자 `INIT` 기능을 실행 해야한다.

# 기능 설명

### mode == INIT

```c
int heredocmanager(int mode, int doc_id, void *buf);

heredocmanager(HEREDOCMODE_INIT, 0, NULL);
```

현재 환경 변수에서 `$HOME`을 찾아 임시 파일을 저장할 디렉토리로 설정한다. 실패 시 현재 디렉토리로 설정한다.

반환 값은 다음과 같다.

- `CODE_OK`: 정상적으로 완료됨
- `CODE_ERROR_DATA`: 환경 변수에서 `HOME`을 찾을 수 없음
- `CODE_ERROR_MALLOC`: 메모리를 할당할 수 없음

### mode == READ

```c
int heredocmanager(int mode, int doc_id, void *buf);

heredocmanager(HEREDOCMODE_READ, 0, "EOF");
```

`(char *)buf`를 delimeter로 사용하여 here-document를 생성하고, 콘솔에서 입력을 받아 임시 파일에 저장한다. 생성된 here-document에는 자동으로 번호가 부여되고, `n_heredoc`이 `1` 증가한다. `doc_id`는 무시된다.

이때 IEEE 1003 2.7.4에 명시된 규칙이 적용된다.

반환 값은 다음과 같다.

- `CODE_OK`: 정상적으로 완료됨
- 0이 아닌 수: 오류가 발생함

이때 오류가 발생할 시 이미 생성된 임시 파일은 삭제된다.

### mode == GETFILENAME

```c
int heredocmanager(int mode, int doc_id, void *buf);

char *filename;
heredocmanager(HEREDOCMODE_GETFILENAME, 0, &filename);
```

`(char **)buf`가 가리키는 주소에 `doc_id`번 here-document의 파일 경로를 기록한다.

반환 값은 다음과 같다.

- `CODE_OK`: 정상적으로 완료됨
- `CODE_ERROR_SCOPE`: 올바르지 않은 `doc_id` (음수거나 `n_heredoc` 이상)
- `CODE_ERROR_GENERIC`: 현재 TTY의 이름을 찾을 수 없거나 메모리가 부족함

### mode == CLEAR

```c
int heredocmanager(int mode, int doc_id, void *buf);

heredocmanager(HEREDOCMODE_CLEAR, -1, NULL);
```

`doc_id`가 음수일 시 모든 임시 파일을 삭제한다. `doc_id`가 `0` 이상 `n_heredoc` 미만일 시 `doc_id`번 임시 파일을 삭제한다. `buf`는 무시된다.

반환 값은 다음과 같다.

- `CODE_OK`: 정상적으로 완료됨
- `CODE_ERROR_SCOPE`: 올바르지 않은 `doc_id` (`n_heredoc` 이상)
- `CODE_ERROR_GENERIC`: 현재 TTY의 이름을 찾을 수 없거나 메모리가 부족함

모든 임시 파일을 삭제하는 모드에서는 항상 `CODE_OK`를 반환한다.
