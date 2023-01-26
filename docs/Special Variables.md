# 특수 변수

`DDSH_`로 시작하는 변수는 현재 터미널 상태에 관련된 특수한 값으로 확장된다. `ESC_`로 시작하는 변수는 이스케이프 문자로 확장된다. 기본적으로 특수 변수에는 값을 설정할 수 없고 설정된 값이 있어도 확장 과정에서 무시된다.

- `$DDSH_TIME`: 현재 시간 문자열로 확장된다. `$DDSH_TIME_FORMAT`을 `strftime`이 정의하는 형식에 따라 설정해야 동작한다.
- `$DDSH_PWD`: `$PWD`와 다르게 셸의 실제 현재 디렉토리로 확장된다.
- `$DDSH_HOSTNAME`: 현재 시스템의 hostname으로 확장된다.

## 테마

`$DDSH_THEME`에 지정된 문자열은 셸의 프롬프트 앞에 표시된다. 이때 문자열에 확장이 일어나므로 `$DDSH_TIME` 등의 특수 변수를 적절히 활용할 수 있다.

문자열이 확장된 채로 `$DDSH_THEME`에 저장되는 것을 피하기 위해 작은 따옴표 인용을 사용해야 한다.

```bash
export DDSH_THEME="$DDSH_TIME > "   # 셸이 시작될 때의 시간 문자열이 저장되어 버림
export DDSH_THEME='$DDSH_TIME > '   # 리터럴한 $DDSH_TIME이 테마 문자열에 저장되고 프롬프트가 표시될 때마다 확장됨
```

## 이스케이프

- `$ESC_RESET`
- `$ESC_RED`
- `$ESC_GREEN`
- `$ESC_YELLOW`
- `$ESC_BLUE`
- `$ESC_MAGENTA`
- `$ESC_CYAN`
- `$ESC_WHITE`
- `$ESC_BBLACK`
- `$ESC_BRED`
- `$ESC_BGREEN`
- `$ESC_BYELLOW`
- `$ESC_BBLUE`
- `$ESC_BMAGENTA`
- `$ESC_BCYAN`
- `$ESC_BWHITE`
- `$ESC_NEWLINE`
