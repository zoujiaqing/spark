#ifndef DEBUG_H
#define DEBUG_H

//#define DEBUG 1

#ifdef DEBUG
#define LINENO  printf("%s:%d : ",__FILE__,__LINE__);
#define debug(fmt,...) LINENO printf(fmt,__VA_ARGS__);
#define debugMessage(str) LINENO printf(str);
#else
#define debug(fmt,...)
#define debugMessage(str)
#endif

#endif
