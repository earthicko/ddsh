# 특수 변수

`DDSH_`로 시작하는 변수는 현재 터미널 상태에 관련된 특수한 값으로 확장된다. `ESC_`로 시작하는 변수는 이스케이프 문자로 확장된다. 기본적으로 특수 변수에는 값을 설정할 수 없고 설정된 값이 있어도 확장 과정에서 무시된다.

- `$DDSH_TIME`: 현재 시간 문자열로 확장된다. `$DDSH_TIME_FORMAT`을 `strftime`이 정의하는 형식에 따라 설정해야 동작한다.
- `$DDSH_PWD`: `$PWD`와 다르게 셸의 실제 현재 디렉토리로 확장된다.
- `$DDSH_HOSTNAME`: 현재 시스템의 hostname으로 확장된다.

아래 이스케이스 확장 기능은 명령줄에서 `\`를 통해 직접 문자를 이스케이프 시키는 기능이 완성될 시 삭제될 것이다.

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
