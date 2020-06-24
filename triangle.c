#include "triangle.h"

int get_begin_line_triangle(int h){
	int nb_ele, index, hauteur;
	if (h<0) return -99;
	for (nb_ele=1, index=0, hauteur=0; hauteur != h; hauteur++, index+=nb_ele, nb_ele+=2){}
	return index;
}

int get_hauteur_index_triangle(int index){
	int h, nb_ele, j;
	if (index < 0) return -99;
	for (h=0, nb_ele=1, j=0; index > j; j+=nb_ele, nb_ele+=2, h++){}
	if (j > index) return h-1;
	return h;
}

int get_nb_ele_line_triangle(int hauteur){
	if (hauteur<0) return -99;
	int h=0, nb_ele=1;
	for (; hauteur != h; nb_ele+=2, h++){}
	return nb_ele;
}

int get_hauteur_triangle(int size){
	int h, nb_ele;
	for (nb_ele=1, h=0; nb_ele!=size; nb_ele+=2, h++){}
	return h;
}

int get_nb_ele_triangle(int size){
	int j, nb_ele, h;
	for (nb_ele=1, h=0, j=1; nb_ele!=size; nb_ele+=2, h++, j+=nb_ele){}
	return j;
}

int get_pos_top_triangle(int index){
	if (index < 0) return -99;
	return index - (get_nb_ele_line_triangle(get_hauteur_index_triangle(index)) - 1 );
}

int get_pos_down_triangle(int index){
	if (index < 0) return -99;
	return index + (get_nb_ele_line_triangle(get_hauteur_index_triangle(index)) + 1 );
}

void affichage_triangle(plateau P){
	int i, j, m, index, nb_ele_line, v=get_hauteur_triangle(P.size);

	for (i=0, j=97; i<P.size-2; i++, j++){
		if (j==97) printf ("  %c ",j);
		else printf ("%c ",j);
	}
	printf ("\n");
	for(index=0, nb_ele_line=1, j=65; nb_ele_line != P.size; j++, nb_ele_line += 2, v--){ 
		printf ("%c ",j);
 		for (i=0; i<P.size; i++){ 
 			
			if (i+1 == (P.size - nb_ele_line) / 2){ 
				for (m=0; m<nb_ele_line; i++, m++){
					if (P.p[index]==1) printf (SQUARESYMBOL);		
					else printf (DOTSYMBOL);
					index++;
				}
			}
			else printf ("  ");
		}
		printf ("\n");
	}
}

int choix_pos_triangle(int size){
	int hmax = get_hauteur_triangle(size), t, h, v, index;
	char s[100];
	do{
		printf ("Choisis la colonne sur la quelle tu veux jouer [A-Z] \n");
		scanf("%s",s);
	} while((*s < 65 || *s > 90) || (*s - 'A' > hmax || *s - 'A' < 0));
	h = *s - 'A';
	t = get_begin_line_triangle(h);
	do{
		printf ("Choisis la ligne sur la quelle tu veux jouer [a-z] \n");
		scanf("%s",s);
		v = *s - 'a';
		v++;
		index = t + (v - ((size - get_nb_ele_line_triangle(h)) / 2));
	} while((*s < 97 || *s > 122) || index < get_begin_line_triangle(h) || index >= get_begin_line_triangle(h+1));
	return index;
}

plateau create_plateau_triangle(int size){
	plateau P;
	P.size = size;
	P.forme = 1;
	P.p = malloc(sizeof(int) * get_nb_ele_triangle(size));
	for (int i=0; i<get_nb_ele_triangle(P.size); i++) P.p[i]=0;
	return P;
}

plateau triangle_to_matrice(plateau P){
	int i, j, m, index, nb_ele;
	plateau C;
	C.size=P.size-2;
	C.forme=P.forme;
	C.p = malloc(sizeof(int) * C.size * C.size);
	for (i=0; i<C.size*C.size; i++) C.p[i]=-1;
	for (i=0, nb_ele=1, index=0; i<get_hauteur_triangle(C.size)+1; i++, nb_ele+=2){
		for (j=0; j<C.size; j++) if (j == (C.size - nb_ele) / 2) for (m=0; m<nb_ele; m++, j++) C.p[i * C.size + j] = P.p[index++];
	}
	return C;
}

int verif_triangle(int index, plateau P, bloc B){
	int i, j, l, indx;
	for (j=0; j<B.x; j++){
		for (i=0; i<B.y; i++){
			if (*(B.b + j*B.x + i)){
				indx=index;
				for (l=0; l<B.x-j-1; l++) indx=get_pos_top_triangle(indx);
				indx=indx+i;
				if (get_hauteur_index_triangle(index) != get_hauteur_index_triangle(indx)+B.x-1-j) return 0;
				if (P.p[indx]) return 0;
			}
		}
	}
	return 1;
}

void pose_triangle(int index, plateau * P, bloc B){
	int i, indx, j, l;
	for (j=0; j<B.x; j++){
		for (i=0; i<B.y; i++){
			if (*(B.b + j*B.x + i)){
				indx=index;
				for (l=0; l<B.x-j-1; l++) indx=get_pos_top_triangle(index);
				indx=indx+i;
				P->p[indx]=1;
			}
		}
	}
}

int delete_vertical_triangle(plateau * P){
	int run, nb_ele, j, i, h, * t, index, score=0;
	t = malloc(sizeof(int) * P->size);
	for (i=0; i<P->size; i++) t[i]=0;
	run=1;
	for (h=0, nb_ele=1; nb_ele < P->size; nb_ele+=2, h++){}
	nb_ele-=2;
	h--;
	for (j=0; j<nb_ele; j++){
		index=get_begin_line_triangle(h)+j;
		if (P->p[index]==1){
			if (h!=get_hauteur_index_triangle(get_pos_top_triangle(index))+1){}
			else{
				for (i=1; h==get_hauteur_index_triangle(get_pos_top_triangle(index))+i && run; i++){
					index = get_pos_top_triangle(index);
					if (P->p[index]!=1) run=0;
				}
				
			}
		}
		else run=0;
		if (run) t[j] = 1;
		run=1;
	}
	for (j=0; j<P->size; j++){
		if (t[j]){
			index=get_begin_line_triangle(h)+j;
			while (get_hauteur_index_triangle(index) == get_hauteur_index_triangle(get_pos_top_triangle(index))+1){
				P->p[index]=0;
				score++;
				index = get_pos_top_triangle(index);
			}
			P->p[index]=0;
		}
	}
	return score;
}

void scroll_triangle(plateau * P, int h){
	int i, index;
	h--;
	while (h!=-1){
		for (i=0; i<get_nb_ele_line_triangle(h); i++){
			index=get_begin_line_triangle(h)+i;
			if (P->p[index]==1){
				P->p[index]=0;
				while (get_hauteur_index_triangle(index) == get_hauteur_index_triangle(get_pos_down_triangle(index))-1 && P->p[get_pos_down_triangle(index)]==0){
					index = get_pos_down_triangle(index);
				}
				P->p[index]=1;
			}
		}
		h--;
	}
}

int delete_horizontal_triangle(plateau * P){
	int nb_ele, i, h, run, score=0;
	for (nb_ele=1, h=0, run=1; h!=get_hauteur_triangle(P->size)-1; h++, nb_ele+=2){
		for (i=0; i<nb_ele && run; i++){
			if (!P->p[get_begin_line_triangle(h)+i]) run=0;
		}
		if (run) {
			for (i=0; i<nb_ele; i++, score++) P->p[get_begin_line_triangle(h)+i]=0;
			scroll_triangle(P,h);
		}
		run=1;
	}
	return score;
}

void triangle_all_bloc_game(int size, int w, int h){
  Screen * s;
  plateau P, C;

  bloc blocs[20] = {b1,  b2,  b3,  b4,  b5,  b6,  b7,  b8,  b9,  b10, 
  				    b11, b12, b13, b14, b15, b16, b17, b18, b19, b20};
  
  int t[20] = {9,1,3,2,14,13,7,6,8,0,10,12,11,5,4,16,15,18,17,19};

  int score = 0, input, health = 3, i, j, count=0, pos;
  char result[50];
  char str[50];

  P = create_plateau_triangle(size);
  C = triangle_to_matrice(P);
  s = create_screen(w, h);

  update_game_screen(s, C);
  clear_string(s, 17, P.size*2+6);
  for(j = 0; j*7+15 < P.size+7; j++){
		  for(i = 0;P.size*2+10+(10*i)+4 < w && count < 20; i++, count++){
		  	update_bloc(s, blocs[t[count]], j*7+15, P.size*2+10+(10*i));
		  	sprintf(result, "%.f", (float)count); 
		  	update_string(s, result, j*7+17, P.size*2+11+(10*i));
		  }
	  }
	  count++;
	  for(j = 0; j*7+P.size+7+5 < h; j++){
		  for(i = 0; 3+(10*i)+4 < w && count < 20; i++, count++){
		  	update_bloc(s, blocs[count], j*7+P.size+7+5, 3+(10*i));
		  	sprintf(result, "%.f", (float)count); 
		  	update_string(s, result, j*7+P.size+7+7, 4+(10*i));
		  }
	  }
  	while(1){
  	  C = triangle_to_matrice(P);
      update_matrix(s, &C, 6, 4);
	  
	  update_health(s, P.size, health, 6, 6);
	  
	  update_score(s, P.size, 4);
	  
	  print_screen(s);
	  if(health == 0)break;
	  do{
		printf("Choose a bloc[0 - 19] to set : ");
		scanf("%s",str);
		input = string_to_int(str);
	  } while(input < 0 || input > 19);

	  pos = choix_pos_triangle(P.size);

	  if (!verif_triangle(pos,P,blocs[input])) health--;
	  else {
	  	pose_triangle(pos,&P,blocs[input]);
	  	score += delete_horizontal_triangle(&P);
	  	score += delete_vertical_triangle(&P);
	  }      
  }
  printf("Your score : %d\nGame End\n", score);
}

void triangle_3bloc_game(int size){
  Screen * s;
  plateau P, C;
  int score = 0, health = 3, pos, input=-1;
  char str[100];

  int t[20] = {9,1,3,2,14,13,7,6,8,0,10,12,11,5,4,16,15,18,17,19};

  bloc blocs[20] = {b1,  b2,  b3,  b4,  b5,  b6,  b7,  b8,  b9,  b10, 
  				    b11, b12, b13, b14, b15, b16, b17, b18, b19, b20};

  bloc * rand_blocs[3] = {&b1, &b2, &b3};

  P = create_plateau_triangle(size);
  C = triangle_to_matrice(P);
  s = create_screen(P.size*2+35, P.size+10);

  update_game_screen(s, C);
  
  while(1){
  	  C = triangle_to_matrice(P);
  	  affichage_triangle(P);
  	  clear_string(s, 15, P.size*2+10);
  	  clear_string(s, 14, P.size*2+10);
  	  clear_string(s, 13, P.size*2+10);
  	  clear_string(s, 12, P.size*2+10);
  	  
      update_matrix(s, &C, 6, 4);
	  update_bloc(s, *rand_blocs[0], 15, P.size*2+7);
	  update_bloc(s, *rand_blocs[1], 15, P.size*2+17);
	  update_bloc(s, *rand_blocs[2], 15, P.size*2+27);
	  
	  update_health(s, P.size, health, 6, 6);
	  
	  update_score(s, P.size, score);
	  
	  print_screen(s);
	  if(health == 0)break;

	  do{
		printf("Choose a bloc[1 - 3] to set : ");
		scanf("%s",str);
		input = string_to_int(str);
	  } while(input < 1 || input > 3);
	  input--;

	  pos = choix_pos_triangle(P.size);

	  if (!verif_triangle(pos,P,*rand_blocs[input])) health--;
	  else {
	  	pose_triangle(pos,&P,*rand_blocs[input]);
	  	score += delete_horizontal_triangle(&P);
	  	score += delete_vertical_triangle(&P);
	  	rand_blocs[input] = &(blocs[t[random_number(20)]]);
	  }     
  }
  printf("Your score : %d\nGame End\n", score);
}

