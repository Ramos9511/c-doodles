/*  fileio.h --- header file containing file I/O macros
*/

#include <fcntl.h>
#include <stdio.h>

#define PMODE 0755

#define DELIM_STR "|"
#define DELIM_CHR '|'

#define out_str(fd, s)         \
  write((fd), (s), strlen(s)); \
  write((fd), DELIM_STR, 1)

#define fld_to_recbuff(rb, fld) \
  strcat(rb, fld);              \
  strcat(rb, DELIM_STR)

#define MAX_REC_SIZE 512