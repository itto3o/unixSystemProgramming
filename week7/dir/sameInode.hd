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

	//inode를 담을 배열 생성
	//*으로 선언하면 core dump남
	int inode[BUFSIZ];

	if(argc != 2) {
		printf("Usage : %s dirname\n", argv[0]);
		exit(1);
	}

	//명령어에 입력한 디렉토리 오픈
	if((dp = opendir(argv[1])) == NULL) {
		perror("opendir\n");
		exit(1);
	}

	//디렉토리 내 파일의 정보 개수를 알기 위한 count
	int count = 0;
	//디렉토리 내 모든 내용을 읽어옴
	while((dent = readdir(dp))) {
		// . 디렉토리는 빼고
		if(dent->d_name[0] != '.') {
			sprintf(path, "%s/%s", argv[1], dent->d_name);
			stat(path, &sbuf);

			//inode를 담을 배열에 inode를 저장하고 count++
			inode[count++] = (int)sbuf.st_ino;
		}
	}

	for(int i = 0; i < count; i++) {
		for(int j = 0; j < count; j++) {
			//만약 같은 자리의 수(같은 수)면 continue
			if(i == j)
				continue;
			//같은 inode 숫자를 갖고 있으면 출력
			else if(inode[i] == inode[j] && inode[j] != 0) {
				printf("Same Inode = %d\n", inode[i]);
				//중복으로 출력하는 것을 방지하기 위해 다른 쪽의 inode정보는 0으로 초기화
				inode[j] = 0;
			}
		}
	}

	closedir(dp);
}
