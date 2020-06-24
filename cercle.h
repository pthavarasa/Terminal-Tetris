#define CERCLE_H
#ifndef FILE_H
#include "file.h"
#endif
#ifndef SCREEN_H
#include "screen.h"
#endif

int get_dots(int size);
int get_upper_pos(plateau p, int pos);
int get_lower_pos(plateau p, int pos);
int get_left_pos(plateau p, int pos);
int get_right_pos(plateau p, int pos);
plateau create_cercle(plateau P);
void affichage_cercle(plateau P);
void seek_to_next_line();
int get_user_pos(int size);
int get_user_pos_horizontal(int size);
int append_bloc(plateau * p, bloc b, int pos);
int bloc_area_verify(plateau * p, bloc b, int pos, int pos_tmp);
void bloc_area_clear(plateau * p, bloc b, int pos);
int random_number(int max);
void print_bloc(bloc b);
int verify_vertical(plateau p, int pos);
int verify_horizontal(plateau p, int pos);
void cancel_vertical(plateau * p, int pos);
void cancel_horizontal(plateau * p, int pos);
int cancel_plateau_lc(plateau * P, int pos, int x, int y);
plateau create_plateau(int size, int forme);
void shift_blocs(plateau * p, int pos);
void cercle_3bloc_animate_game(int size, int animation_delay);
void cercle_all_bloc_game(int size, int w, int h);
void cercle_3bloc_game(int size);
