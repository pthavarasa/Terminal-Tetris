#define SCREEN_H
#ifndef FILE_H
#include "file.h"
#endif

typedef struct screen{
  int x, y;
  char * scr;
}Screen;

Screen * create_screen(int x, int y);
void print_screen(Screen * s);
int recommanded_size(int w, int h);
int string_count(char * s);
void get_terminal_size(int* width, int* height);
void get_linux_command_output(char * var, char * command);
int fetchInput(int min, int max);
int stringToInt(char * c);
char ** string_split(char * str, char delim);
void clear_string(Screen * s, int lin, int col);
void update_string(Screen * s, char * str, int lin, int col);
void update_matrix(Screen * s, plateau * p, int lin, int col);
void update_bloc(Screen * s, bloc b, int lin, int col);
void update_game_screen(Screen * s, plateau P);
void update_score(Screen * s, int size_plateau, float score);
void update_health(Screen * s, int plateau_size, int health, int lin, int col);
void src_home(Screen * s, int w, int h);
void src_size_choose(Screen * s, int w, int h);
void src_form_choose(Screen * s, int w, int h);
void src_suggestion_choose(Screen * s, int w, int h, int cercle);
void src_clear(Screen * s, int w, int h);
int g_h_t(int size);
int string_to_int(char * s);
int random_number(int max);
