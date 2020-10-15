#include <stdio.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>


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
	printf("printing dirent\n");
	printf("d_ino: %ld\n", dir->d_ino);
	printf("d_off: %ld\n", dir->d_off);
	printf("d_reclen: %d\n", dir->d_reclen);
	printf("d_type: %s\n", str_elem_type(dir->d_type));
	printf("d_name: %s\n\n", dir->d_name);
}

void get_and_print_stat(const char* path_name) {
	struct stat* st = malloc(sizeof(struct stat));
	stat(path_name, st);

	/**
	dev_t     st_dev;          ID of device containing file
	ino_t     st_ino;          Inode number
	mode_t    st_mode;         File type and mode
	nlink_t   st_nlink;        Number of hard links
	uid_t     st_uid;          User ID of owner
	gid_t     st_gid;          Group ID of owner
	dev_t     st_rdev;         Device ID (if special file)
	off_t     st_size;         Total size, in bytes
	blksize_t st_blksize;      Block size for filesystem I/O
	blkcnt_t  st_blocks;       Number of 512B blocks allocated
	struct timespec st_atim;   Time of last access
	struct timespec st_mtim;   Time of last modification
	struct timespec st_ctim;  Time of last status change

	**/
	printf("printing stat\n");
	printf("st_mode: %d\n", st->st_mode); ///+
	printf("st_nlink: %lu\n", st->st_nlink); ///+
	printf("st_uid: %d\n", st->st_uid); ///+
	struct passwd* pswd = getpwuid(st->st_uid);
	printf("owner: %s\n", pswd->pw_name);
	printf("st_gid: %d\n", st->st_gid); ///+
	struct group* grp = getgrgid(st->st_gid);
	printf("group: %s\n", grp->gr_name);
	printf("st_rdev: %lu\n", st->st_rdev);
	printf("st_size: %ld\n", st->st_size); ///+
	printf("st_blksize: %ld\n", st->st_blksize);
	printf("st_blocks: %ld\n", st->st_blocks); ///+
	printf("last_mod_time: %s\n\n", ctime(&st->st_mtim.tv_sec)); ///last modifiaction time

	free(st);
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


	//if (rd_dir == NULL)
	//	finish_him(errno, __LINE__);

	while ((rd_dir = readdir(dir)) != NULL) {
		print_dirent(rd_dir);
		get_and_print_stat(rd_dir->d_name);
	}

	if (closedir(dir) == - 1)
		finish_him(__LINE__);

	return 0;
}
