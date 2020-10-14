#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

typedef struct dirent t_dirent;

void finish_him(int line) {
	printf("line: %d errno: %d: %s\n", line, errno, strerror(errno));
	exit(0);
}

char* str_elem_type(const unsigned char d_type) {
	switch (d_type) {
		case	DT_BLK: return "This is a block device.";
		case	DT_CHR: return "This is a character device";
		case	DT_DIR: return "This is a directory";
		case	DT_FIFO: return "This is a named pipe (FIFO)";
		case	DT_LNK: return "This is a symbolic link";
		case	DT_REG: return "This is a regular file";
		case	DT_SOCK: return "This is a UNIX domain socket";
		case	DT_UNKNOWN: return "The file type could not be determined";
	}
	return "";
}

void print_dirent(const t_dirent* dir) {
	printf("d_ino: %ld\n", dir->d_ino);
	printf("d_off: %ld\n", dir->d_off);
	printf("d_reclen: %d\n", dir->d_reclen);
	printf("d_type: %s\n", str_elem_type(dir->d_type));
	printf("d_name: %s\n\n", dir->d_name);
}




int main(int argc, char **argv)
{
	if (argc < 2) {
		return 0;
	}

	DIR* dir;
	printf("directory to open: %s\n\n", argv[1]);

	dir = opendir(argv[1]);
	if (dir == NULL)
		finish_him(__LINE__);

	t_dirent* rd_dir;

	rd_dir = readdir(dir);

	//if (rd_dir == NULL)
	//	finish_him(errno, __LINE__);

	while ((rd_dir = readdir(dir)) != NULL)
		print_dirent(rd_dir);

	if (closedir(dir) == - 1)
		finish_him(__LINE__);

	return 0;
}
