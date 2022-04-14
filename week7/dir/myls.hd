#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
	DIR *dp;
	struct dirent *dent;
	struct stat sbuf;
	char path[BUFSIZ];

	//명렁어가 2개의 요소로 이뤄지지 않았을 때는 사용법을 출력하고 종료
	if(argc != 2) {
		printf("Usage : %s dirname\n", argv[0]);
		exit(1);
	}

	//디렉토리 포인터로 디렉토리를 오픈한다.
	if((dp = opendir(argv[1])) == NULL) {
		perror("opendir\n");
		exit(1);
	}

	//현재 오픈한 디렉토리 안의 내용을 하나씩 읽어온다.
	while((dent = readdir(dp))) {
		//받아온 디렉토리 안의 내용이 .(현재 디렉토리)이면 무시
		if(dent->d_name[0] != '.') {
			//sprintf로 path에 현재 경로와 파일 이름을 담는다.
			sprintf(path, "%s/%s", argv[1], dent->d_name);
			//경로와 파일 이름을 담은 path로 state정보를 읽어온다.
			stat(path, &sbuf);

			//그렇게 읽어온 정보가 만약 directory라면 밑의 정보를 출력
			if(S_ISDIR(sbuf.st_mode)) {

				printf("Name : %s\n", dent->d_name);
				printf("Inode(dirent) : %d\n", (int)dent->d_ino);
				printf("Inode(stat) : %d\n", (int)sbuf.st_ino);
				printf("Mode : %o\n", (unsigned int)sbuf.st_mode);
				printf("Uid : %d\n", (int)sbuf.st_uid);
				printf("Size = %d\n", (int)sbuf.st_size);
				printf("-----------------------\n");
			}
		}
	}
	closedir(dp);
}
