#define FILE_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define DOT 0
#define EMPTY -1
#define SQUARE 2
#define DOTSYMBOL "· "
#define SQUARESYMBOL "\x1B[31m◼\x1B[0m "
#define SIZE 19

struct plateau{
	int size;
	int * p;
	int forme;
};
typedef struct plateau plateau;


struct bloc{
	int x, y;
	int *b;
	int forme;
};
typedef struct bloc bloc;


static int f1[2][2] = {{ SQUARE, SQUARE},{ DOT, SQUARE}};
static bloc b1 = {2, 2, &f1[0][0] , 0};

static int f2[2][2] = {{ DOT, SQUARE},{ SQUARE, SQUARE}};
static bloc b2 = {2, 2, &f2[0][0] , 0};

static int f3[3][2] = {{ SQUARE, SQUARE},{ DOT, SQUARE}, { DOT, SQUARE}};
static bloc b3 = {3, 2, &f3[0][0] , 0};

static int f4[2][3] = {{ SQUARE, DOT, DOT},{ SQUARE, SQUARE, SQUARE}};
static bloc b4 = {2, 3, &f4[0][0] , 0};

static int f5[2][3] = {{ SQUARE, SQUARE, SQUARE},{ DOT, SQUARE, DOT}};
static bloc b5 = {2, 3, &f5[0][0] , 0};

static int f6[3][2] = {{ DOT, SQUARE},{ SQUARE, SQUARE},{ DOT, SQUARE}};
static bloc b6 = {3, 2, &f6[0][0], 0};

static int f7[3][2] = {{ SQUARE, DOT},{ SQUARE, SQUARE}, { DOT, SQUARE}};
static bloc b7 = {3, 2, &f7[0][0] , 0};

static int f8[2][3] = {{ SQUARE, SQUARE, DOT},{ DOT, SQUARE, SQUARE}};
static bloc b8 = {2, 3, &f8[0][0] , 0};

static int f9[2][2] = {{ SQUARE, SQUARE},{ SQUARE, SQUARE}};
static bloc b9 = {2, 2, &f9[0][0] , 0};

static int f10[2][2] = {{ SQUARE, DOT},{ SQUARE, SQUARE}};
static bloc b10 = {2, 2, &f10[0][0] , 0};

static int f11[2][2] = {{ SQUARE, SQUARE},{ SQUARE, DOT}};
static bloc b11 = {2, 2, &f11[0][0] , 0};

static int f12[3][2] = {{ DOT, SQUARE},{ DOT, SQUARE}, { SQUARE, SQUARE}};
static bloc b12 = {3, 2, &f12[0][0] , 0};

static int f13[2][3] = {{ SQUARE, SQUARE, SQUARE}, { DOT, DOT, SQUARE}};
static bloc b13 = {2, 3, &f13[0][0] , 0};

static int f14[2][3] = {{ DOT, SQUARE, DOT},{ SQUARE, SQUARE, SQUARE}};
static bloc b14 = {2, 3, &f14[0][0] , 0};

static int f15[3][2] = {{ SQUARE, DOT},{ SQUARE, SQUARE}, { SQUARE, DOT}};
static bloc b15 = {3, 2, &f15[0][0] , 0};

static int f16[3][2] = {{ DOT, SQUARE},{ SQUARE, SQUARE},{ SQUARE, DOT}};
static bloc b16 = {3, 2, &f16[0][0] , 0};

static int f17[2][3] = {{ DOT, SQUARE, SQUARE}, { SQUARE, SQUARE, DOT}};
static bloc b17 = {2, 3, &f17[0][0] , 0};

static int f18[1][4] = {{ SQUARE, SQUARE, SQUARE, SQUARE}};
static bloc b18 = {1, 4, &f18[0][0] , 0};

static int f19[4][1] = {{ SQUARE}, {SQUARE}, {SQUARE}, {SQUARE}};
static bloc b19 = {4, 1, &f19[0][0] , 0};

static int f20[1][1] = {{ SQUARE}};
static bloc b20 = {1, 1, &f20[0][0] , 0};
