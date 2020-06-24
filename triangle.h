#define TRIANGLE_H
#ifndef FILE_H
#include "file.h"
#endif
#ifndef SCREEN_H
#include "screen.h"
#endif

int get_begin_line_triangle(int h);
int get_hauteur_triangle(int size);
void affichage_triangle(plateau P);
int get_nb_ele_triangle(int size);
plateau create_plateau_triangle(int size);
int choix_pos_triangle(int size);
int get_nb_ele_line_triangle(int hauteur);
int get_pos_top_triangle(int index);
int get_pos_down_triangle(int index);
plateau triangle_to_matrice(plateau P);
int get_hauteur_index_triangle(int index);
int verif_triangle(int index, plateau P, bloc B);
void pose_triangle(int index, plateau * P, bloc B);
int poser_triangle(plateau * P);
int delete_vertical_triangle(plateau * P);
void scroll_triangle(plateau * P, int h);
int delete_horizontal_triangle(plateau * P);
void triangle_all_bloc_game(int size, int w, int h);
void triangle_3bloc_game(int size);
