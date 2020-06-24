#define LOSANGE_H
#ifndef FILE_H
#include "file.h"
#endif
#ifndef SCREEN_H
#include "screen.h"
#endif

int get_begin_line_losange(int h, int size);
int get_nb_ele_losange(int size);
int get_hauteur_index_losange(int index, int size);
int get_hauteur_losange(int size);
int get_pos_top_losange(int index, int size);
int get_pos_down_losange(int index, int size);
int get_nb_ele_line_losange(int h, int size);
//int get_begin_line_losange(int h, int size);
void pose_losange(int index, plateau * P, bloc B);
void affichage_losange(plateau P);
int choix_pos_losange(int size);
int verif_losange(int index, plateau P, bloc B);
int poser_losange(plateau * P);
int delete_vertical_losange(plateau * P);
void scroll_losange(plateau * P, int h);
int delete_horizontal_losange(plateau * P);
plateau create_plateau_losange(int size);
plateau losange_to_matrice(plateau P);
void losange_3bloc_game(int size);
void losange_all_bloc_game(int size, int w, int h);
