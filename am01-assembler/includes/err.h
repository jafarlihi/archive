#ifndef ERR_H
#define ERR_H

void printErr(char *fmt, ...);
void printInfo(char *fmt, ...);

#ifdef DEBUG
void printDbg(char *fmt, ...);
#endif

#endif
