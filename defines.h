#ifndef DEFINES_H
#define DEFINES_H

#include <qglobal.h>

void initRandomWithTime();
int randomInt(int min, int max);

/* Strings for the configuration file */
extern const char *OP_GRP;
extern const char *OP_UMARK;
extern const char *OP_MENU;
extern const char *OP_LEVEL;
extern const char *HS_GRP[3];
extern const char *HS_NAME;
extern const char *HS_MIN;
extern const char *HS_SEC;

/* States of a case (unsigned int) */
#define NOTHING    0
#define MINE       1
#define COVERED    2
#define UNCERTAIN  4
#define MARKED     8
#define UNCOVERED  16
#define EXPLODED   32
#define ERROR      64                        

/* Layout dimensions */
#define CASE_W   20
#define CASE_H   20

/* Predefined levels */
typedef struct { uint width, height, nbMines; } Level;
extern const Level LEVELS[3];

typedef struct { uint sec, min, mode; } Score;

#endif // DEFINES_H
