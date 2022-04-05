#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char* argv[]) {
	struct stat buf;

	//파라미터가 없다면 부족하다고 표시를 한다.
	if(argc == 1) {
		perror("lack argumentation");
		exit(1);
	}

	//stat으로 buf에 stat정보를 저장한다.
	//stat(argv[1], &buf);

	//만약 심볼릭 링크 파일이라면 lstat으로 다시 읽는다.
	//그런데 생각해보니까 그냥 lstat으로 link파일이 아닌 일반 파일을 읽어도 구별을 해주나?
	//그러면 그냥 lstat으로만 써도 될듯
	//근데 그렇게 하니까 inode 값이 달라지는데..?
	//if(S_ISLNK(buf.st_mode))
		lstat(argv[1], &buf);

	printf("Inode = %d\n", (int)buf.st_ino);
	printf("Mode = %o\n", (unsigned int)buf.st_mode);
	printf("Nlink = %o\n", (unsigned int)buf.st_nlink);
	printf("UID = %d\n", (int)buf.st_uid);
	printf("GID = %d\n", (int)buf.st_gid);
	printf("SIZE = %d\n", (int)buf.st_size);
	printf("Atime = %d\n", (int)buf.st_atime);
	printf("Mtime = %d\n", (int)buf.st_mtime);
	printf("Ctime = %d\n", (int)buf.st_ctime);
	printf("Blksize = %d\n", (int)buf.st_blksize);
	printf("Blocks = %d\n", (int)buf.st_blocks);


	//buf.st_fstype 멤버변수가 없다는 오류가 뜬다.
	//	printf("FStype = %s\n", buf.st_fstype);

	return 0;
}
