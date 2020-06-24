#include "losange.h"

int get_begin_line_losange(int h, int size){
	int nb_ele, j, hauteur;
	if (h<0) return -99;
	for (nb_ele=1, j=0, hauteur=0; hauteur != h && nb_ele != size-2; j+=nb_ele, nb_ele+=2, hauteur++){}
	for (; hauteur != h; hauteur++, j+=nb_ele, nb_ele-=2){}
	return j;
}

int get_nb_ele_losange(int size){
	int j, nb_ele, h;
	for (nb_ele=1, h=0, j=1; nb_ele!=size; j+=nb_ele, nb_ele+=2, h++){}
	nb_ele-=4;
	for (; nb_ele != 1; j+=nb_ele, nb_ele-=2, h++){}
	return j;
}

int get_hauteur_index_losange(int index, int size){
	int h, nb_ele, j;
	if (index < 0) return -99;
	for (h=0, nb_ele=1, j=0; index > j && nb_ele != size; j+=nb_ele, nb_ele+=2, h++){}
	nb_ele-=4;
	for (; index > j; j+=nb_ele, nb_ele-=2, h++){}
	if (get_begin_line_losange(h,size) > index) return h-1;
	return h;
}

int get_hauteur_losange(int size){
	int h, nb_ele;
	if (size < 0) return -99;
	for (nb_ele=1, h=0; nb_ele != size; h++, nb_ele+=2){}
	nb_ele-=4;
	for (; nb_ele!=1; h++, nb_ele-=2){}
	return h;
}

int get_pos_top_losange(int index, int size){
	if (index < 0) return -99;
	if (get_hauteur_index_losange(index, size) > get_hauteur_losange(size) / 2){
		return index - (get_nb_ele_line_losange(get_hauteur_index_losange(index, size), size) + 1);
	}
	return index - (get_nb_ele_line_losange(get_hauteur_index_losange(index, size), size) - 1);
}

int get_pos_down_losange(int index, int size){
	if (index < 0) return -99;
	if (get_hauteur_index_losange(index, size) >= get_hauteur_losange(size) / 2){
		return index + (get_nb_ele_line_losange(get_hauteur_index_losange(index, size), size) - 1);
	}
	return index + (get_nb_ele_line_losange(get_hauteur_index_losange(index, size), size) + 1);
}

int get_nb_ele_line_losange(int h, int size){
	int hauteur, nb_ele; 
	if (h<0) return -99;
	for (hauteur=0, nb_ele=1; nb_ele != size-2 && hauteur != h; hauteur++, nb_ele+=2){}
	for (;hauteur != h; hauteur++, nb_ele-=2){}
	return nb_ele;
}

plateau create_plateau_losange(int size){
	plateau P;
	P.size = size;
	P.forme = 0;
	P.p = malloc(sizeof(int) * get_nb_ele_losange(size));
	for (int i=0; i<get_nb_ele_losange(P.size); i++) P.p[i]=0;
	return P;
}

void affichage_losange(plateau P){
	int i, j, m, index, nb_ele_line;

	for (i=0, j=97; i<P.size-2; i++, j++){
		if (j==97) printf ("  %c ",j);
		else printf ("%c ",j);
	}
	printf ("\n");
	
	for (index=0, nb_ele_line=1, j=65; nb_ele_line != P.size; j++, nb_ele_line+=2){
		printf ("%c ",j);
 		for (i=0; i<P.size; i++){ 
 			
			if (i+1 == (P.size - nb_ele_line) / 2){ 
				for (m=0; m<nb_ele_line; i++, m++){
					if (P.p[index]) printf (SQUARESYMBOL);		
					else printf (DOTSYMBOL);
					index++;
				}
			}
			else printf ("  ");
		}
		printf ("\n");
	}
	for (nb_ele_line-=4; nb_ele_line>=1; nb_ele_line-=2, j++){
		printf ("%c ",j);

		for (i=0; i<P.size; i++){
			if (i+1 == (P.size - nb_ele_line) / 2){
				for (m=0; m<nb_ele_line; m++, i++){
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

int choix_pos_losange(int size){
	int hmax = get_hauteur_losange(size), t, h, v, index;
	char s[100];
	do{
		printf ("Choisis la colonne sur la quelle tu veux jouer [A-Z] \n");
		scanf("%s",s);
	} while((*s < 65 || *s > 90) || (*s - 'A' > hmax || *s - 'A' < 0));
	h = *s - 'A';
	t = get_begin_line_losange(h, size);
	do{
		printf ("Choisis la ligne sur la quelle tu veux jouer [a-z] \n");
		scanf("%s",s);
		v = *s - 'a';
		v++;
		index = t + (v - ((size - get_nb_ele_line_losange(h, size)) / 2));
	} while((*s < 97 || *s > 122) || index < get_begin_line_losange(h, size) || index >= get_begin_line_losange(h+1, size));
	return index;
}

int verif_losange(int index, plateau P, bloc B){
	int i, j, l, indx;
	for (j=0; j<B.x; j++){
		for (i=0; i<B.y; i++){
			if (*(B.b + j*B.x + i)){
				indx=index;
				for (l=0; l<B.x-j-1; l++) indx=get_pos_top_losange(indx,P.size);
				indx+=i;
				if (get_hauteur_index_losange(index,P.size) != get_hauteur_index_losange(indx, P.size)+B.x-1-j) return 0;
				if (P.p[indx]) return 0;
			}
		}
	}
	return 1;
}

void pose_losange(int index, plateau * P, bloc B){
	int i, indx, j, l;
	for (j=0; j<B.x; j++){
		for (i=0; i<B.y; i++){
			if (*(B.b + j*B.x + i)){
				indx=index;
				for (l=0; l<B.x-j-1; l++) indx=get_pos_top_losange(indx,P->size);
				indx=indx+i;
				P->p[indx]=1;
			}
		}
	}
}

plateau losange_to_matrice(plateau P){
	int i, j, m, index, nb_ele, sign=1;
	plateau C;
	C.forme = 0;
	C.size = P.size-2;
	C.p = malloc(sizeof(int) * C.size * C.size);
	for (i=0; i<C.size*C.size; i++) C.p[i]=-1;
	for (i=0, nb_ele=1, index=0; i<C.size; i++){
		for (j=0; j<C.size; j++) if (j == (C.size - nb_ele) / 2) for (m=0; m<nb_ele; m++, j++) C.p[i * C.size + j] = P.p[index++];
		if (nb_ele==C.size) sign=-1;
		nb_ele+=2*sign;
	}
	return C;
}

int delete_vertical_losange(plateau * P){
	int run, nb_ele, j, i, h, * t, index, score=0;
	t = malloc(sizeof(int) * P->size);
	for (i=0; i<P->size; i++) t[i]=0;
	run=1;
	for (h=0, nb_ele=1; nb_ele < P->size; nb_ele+=2, h++){}
	nb_ele-=2;
	h--;
	for (j=0; j<nb_ele; j++){
		index=get_begin_line_losange(h,P->size)+j;
		if (P->p[index]==1){
			if (h!=get_hauteur_index_losange(get_pos_top_losange(index,P->size),P->size)+1){}
			else{
				for (i=1; h==get_hauteur_index_losange(get_pos_top_losange(index,P->size),P->size)+i && run; i++){
					index = get_pos_top_losange(index,P->size);
					if (P->p[index]!=1) run=0;
				}
				
			}
		}
		else run=0;
		index=get_begin_line_losange(h,P->size)+j;
		if (run){
			if (h!=get_hauteur_index_losange(get_pos_down_losange(index,P->size),P->size)-1){}
			else{
				for (i=1; h==get_hauteur_index_losange(get_pos_down_losange(index,P->size),P->size)-i && run; i++){				
					index = get_pos_down_losange(index,P->size);
					if (P->p[index]!=1) run=0;
				}
			}
		}
		if (run) t[j] = 1;
		run=1;
	}
	for (j=0; j<P->size; j++){
		if (t[j]){
			index=get_begin_line_losange(h,P->size)+j;
			while (get_hauteur_index_losange(index,P->size) == get_hauteur_index_losange(get_pos_top_losange(index,P->size),P->size)+1){
				P->p[index]=0;
				score++;
				index = get_pos_top_losange(index,P->size);
			}
			P->p[index]=0;
			index=get_begin_line_losange(h,P->size)+j;
			while (get_hauteur_index_losange(index,P->size) == get_hauteur_index_losange(get_pos_down_losange(index,P->size),P->size)-1){
				P->p[index]=0;
				score++;
				index = get_pos_down_losange(index,P->size);
			}
			P->p[index]=0;
		}
	}
	free(t);
	return score;
}

void scroll_losange(plateau * P, int h){
	int i, index;
	h--;
	while (h!=-1){
		for (i=0; i<get_nb_ele_line_losange(h,P->size); i++){
			index=get_begin_line_losange(h,P->size)+i;
			if (P->p[index]){
				P->p[index]=0;
				while (P->p[get_pos_down_losange(index,P->size)]==0 && get_hauteur_index_losange(index,P->size)+1 == get_hauteur_index_losange(get_pos_down_losange(index,P->size),P->size)){
					index = get_pos_down_losange(index,P->size);
				}
				P->p[index]=1;
			}
		}
		h--;
	}
}

int delete_horizontal_losange(plateau * P){
	int nb_ele, i, h, run, score=0;
	for (nb_ele=1, h=0, run=1; h!=get_hauteur_losange(P->size)+1; h++){
		for (i=0; i<nb_ele && run; i++){
			if (P->p[get_begin_line_losange(h,P->size)+i]==0) run=0;
		}
		if (run) {
			for (i=0; i<nb_ele; i++, score++) P->p[get_begin_line_losange(h,P->size)+i]=0;
			scroll_losange(P,h);
		}
		run=1;
		if (h >= get_hauteur_losange(P->size)/2) nb_ele-=2;
		else nb_ele+=2;
	}
	return score;
}

void losange_all_bloc_game(int size, int w, int h){
  	Screen * s;
  	plateau P, C;

  	bloc blocs[20] = {b1,  b2,  b3,  b4,  b5,  b6,  b7,  b8,  b9,  b10, 
  				    b11, b12, b13, b14, b15, b16, b17, b18, b19, b20};
  
  	int t[20] = {9,1,3,2,14,13,7,6,8,0,10,12,11,5,4,16,15,18,17,19};

  	int score = 0, input=-1, health = 3, i, j, count=0, pos;
  	char result[50], str[50];

  	P = create_plateau_losange(size);
  	C = losange_to_matrice(P);
  	s = create_screen(w, h);

  	update_game_screen(s, C);

  	for(j = 0; j*7+15 < P.size+7; j++){
	  	for(i = 0; P.size*2+10+(10*i)+4 < w && count < 20; i++, count++){
	  		printf ("count : %d\n",count);
	  		update_bloc(s, blocs[t[count]], j*7+15, P.size*2+10+(10*i));
	  		sprintf(result, "%.f", (float)count); 
	  		update_string(s, result, j*7+17, P.size*2+11+(10*i));
	  	}
	}
	count++;
	for(j = 0; j*7+P.size+7+5 < h; j++){
		for(i = 0; 3+(10*i)+4 < w && count < 20; i++, count++){
			printf ("count : %d\n",count);
		  	update_bloc(s, blocs[t[count]], j*7+P.size+7+5, 3+(10*i));
		  	sprintf(result, "%.f", (float)count); 
		  	update_string(s, result, j*7+P.size+7+7, 4+(10*i));
		}
	}
  	while(1){
  	  	C = losange_to_matrice(P);
      	update_matrix(s, &C, 6, 4);
	  
	  	update_health(s, P.size, health, 6, 10);
	  
	  	update_score(s, P.size, score);
	  
	  	print_screen(s);
	  	if(health == 0)break;
	  	do{
			printf("Choose a bloc[0 - 19] to set : ");
			scanf("%s",str);
			input = string_to_int(str);
	  	} while(input < 0 || input > 19);

	  	pos = choix_pos_losange(P.size);

	  	if (!verif_losange(pos,P,blocs[input])) health--;
	  	else {
	  		pose_losange(pos,&P,blocs[input]);
	  		score += delete_horizontal_losange(&P);
	  		score += delete_vertical_losange(&P);
	  	}      
  	}
  	printf("Your score : %d\nGame End\n", score);
}

void losange_3bloc_game(int size){
  	Screen * s;
  	plateau P, C;
  	int score = 0, input=-1, health = 3, pos;
  	char str[50];

  	bloc blocs[20] = {b1,  b2,  b3,  b4,  b5,  b6,  b7,  b8,  b9,  b10, 
  				    b11, b12, b13, b14, b15, b16, b17, b18, b19, b20};

  	int t[20] = {9,1,3,2,14,13,7,6,8,0,10,12,11,5,4,16,15,18,17,19};

  	bloc * rand_blocs[3] = {&b1, &b2, &b3};

  	P = create_plateau_losange(size);
  	C = losange_to_matrice(P);
  	s = create_screen(P.size*2+35, P.size+10);

  	update_game_screen(s, C);
  
  	while(1){
  	  	affichage_losange(P);
  	  	C = losange_to_matrice(P);
  	  	clear_string(s, 15, P.size*2+6);
  	  	clear_string(s, 14, P.size*2+6);
  	  	clear_string(s, 13, P.size*2+6);
  	  	clear_string(s, 12, P.size*2+6);
  	  
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

	  	pos = choix_pos_losange(P.size);

	  	if (!verif_losange(pos,P,*rand_blocs[input])) health--;
	  	else {
	  		pose_losange(pos,&P,*rand_blocs[input]);
	  		score += delete_horizontal_losange(&P);
	  		score += delete_vertical_losange(&P);
	  		rand_blocs[input] = &(blocs[t[random_number(20)]]);
	  	}
  	}
  	printf("Your score : %d\nGame End\n", score);
}
