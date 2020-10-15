# ft_ls
School 21 (42) project. Implementation bash ls function.
# Multiplay-text-column output
The number of spaces between files depends on lenths of the biggest file in directory and lenth current file.\
Default value wich responsible counts of spaces is 1.
* `space = 1`
* `max_len` // length of the longest file
* `cur_len` // length of the current file for printing\
```NUMBER_OF_SPACES = max_len - cur_len + space```\
This formule work then lenth whole line with spaces less then $COLUMNS
## WHAT IS $COLUMNS
COLUMNS is shell(bash) variable which represent width of the open terminal. 
### How get COLUMNS?
```C
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>

int main (int argc, char **argv)
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    printf ("lines %d\n", w.ws_row);
    printf ("columns %d\n", w.ws_col);
    return (0);
}
```
len one raw equel $COLUMNS\
```
if (len > $COLUMNS)
    number_raw = int($COLUMNS / len)
```
