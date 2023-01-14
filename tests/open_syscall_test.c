#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>


//디렉토리도 파일디스크립터 3으로 열림 ㅇㅁㅇ
//아니 왜열림?
//그러면 이제 읽거나 쓸 때만 문제되나?
int	main(int argc, char **argv)
{
	int	stat;

	stat = open(argv[1], O_RDONLY);
	printf("stat: %d\n", stat);
}
