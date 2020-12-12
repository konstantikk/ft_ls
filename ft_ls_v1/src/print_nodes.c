//
// Created by professor on 10/19/20.
//

#include "ft_ls.h"

/**
 * going to implement output to stdout -l style
 * without total
*/
char print_type(const unsigned char d_type) {
	static const char d_types[MAX_TYPES_NUM] = {
			'\0',	//0 DT_UNKNOWN
			'p',	//1 DT_FIFO
			'c',	//2 DT_CHR
			'\0',	//3 skip
			'd',	//4 DT_DIR
			'\0',	//5 skip
			'b',	//6 DT_BLK
			'\0',	//7 skip
			'-',	//8 DT_REG
			'\0',	//9 skip
			'l',	//10 DT_LINK
			'\0',	//11 skip
			's',	//12 DT_SOCK
	};

	if (d_type < MAX_TYPES_NUM)
		return d_types[d_type];
	return '\0';
}

void get_one_user_permissions(const unsigned int perms, const int pos, char* permissions) {
	permissions[pos] = perms & 1u ? EXECUTE : NONE ;
	permissions[pos - 1] = perms & (1u << 1u) ? WRITE : NONE;
	permissions[pos - 2] = perms & (1u << 2u) ? READ : NONE;
}

char* print_permissions(mode_t st_mode) {
	char* permissions;
	register int i;
	int str_pos;

	if (!(permissions = (char*)ft_memalloc(sizeof(char) * (PERMISSION_FIELDS_NUM + 1)))) {
		///finish him
	}

	i = 0;
	str_pos = PERMISSION_FIELDS_NUM - 1;
	while (i < USERS_COUNT) {
		get_one_user_permissions(st_mode & ONE_USER_MASK, str_pos, permissions);
		st_mode >>= ONE_USER_SHIFT;
		str_pos -= ONE_USER_SHIFT;
		++i;
	}

	return permissions;
}

char* print_time(const time_t *ttime)
{
	char        *str_time;
    t_full_time tm;
    t_full_time tm_now;
    time_t      now;

	str_time = ctime(ttime);
	now = time(NULL);
    tm = *localtime(ttime);
    tm_now = *localtime(&now);
    str_time += 4; //scip Www format (which day of the week)
    if (tm.tm_year < tm_now.tm_year) // TODO
    {
        str_time[ft_strlen(str_time) - NO_NEWLINE_AND_SECS - 4] = '\0';
        str_time[ft_strlen(str_time) - 1] = ' ';
        return ft_strjoin(str_time, ft_itoa(tm.tm_year + 1900)); // TODO
    }
	str_time[ft_strlen(str_time) - NO_NEWLINE_AND_SECS] = '\0';
	return str_time;
}
