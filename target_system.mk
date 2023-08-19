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

ifeq ($(TARGET_SYSTEM), macos)
DEFINES	= 

else ifeq ($(TARGET_SYSTEM), linux_x86_64)
DEFINES	= 

else ifeq ($(TARGET_SYSTEM), linux_termux)
DEFINES	= -D'DIR_HEREDOC="/data/data/com.termux/files/usr/tmp"'

else
DEFINES	= 

endif
