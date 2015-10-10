/* this file provides missing basic functions on platform 19 thus
* it should not be compiled when target is platform 21 or AARCH64
*/
#include "config.h"
#ifndef P21
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#include "AndroidFixup.h"

ssize_t getdelim(char **linep, size_t *n, int delim, FILE *fp){
  int ch;
  size_t i = 0;
  if(!linep || !n || !fp){
    errno = EINVAL;
    return -1;
  }
  if(*linep == NULL){
    if(NULL==(*linep = malloc(*n=128))){
      *n = 0;
      errno = ENOMEM;
      return -1;
    }
  }
  while((ch = fgetc(fp)) != EOF){
    if(i + 1 >= *n){
      char *temp = realloc(*linep, *n + 128);
      if(!temp){
	errno = ENOMEM;
	return -1;
      }
      *n += 128;
      *linep = temp;
    }
    (*linep)[i++] = ch;
    if(ch == delim)
      break;
  }
  (*linep)[i] = '\0';
  return !i && ch == EOF ? -1 : i;
}

ssize_t getline(char **linep, size_t *n, FILE *fp){
  return getdelim(linep, n, '\n', fp);
}
#endif
