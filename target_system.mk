OSNAME	= $(shell uname -s)

ifeq ($(OSNAME),Linux)
	ifeq ($(shell [ -d "/data/data/com.termux/files/usr" ] && echo 1), 1)
		TARGET_SYSTEM	= linux_termux
	else
		TARGET_SYSTEM	= linux_x86_64
	endif
else ifeq ($(OSNAME),Darwin)
	TARGET_SYSTEM	= macos
endif
