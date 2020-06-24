#include"cercle.h"

int get_dots(int size){
  return ((int)size/10)+2;
}

int get_upper_pos(plateau p, int pos){
  int upper = pos - p.size;
  if(p.p[upper] == EMPTY || upper < 0 || upper > p.size*p.size-1)return EMPTY;
  return upper;

}
int get_lower_pos(plateau p, int pos){
  int upper = pos + p.size;
  if(p.p[upper] == EMPTY || upper < 0 || upper > p.size*p.size-1)return EMPTY;
  return upper;

}
int get_left_pos(plateau p, int pos){
  int i;
  int upper = pos - 1;
  if(p.p[upper] == EMPTY || upper < 0 || upper > p.size*p.size-1)return EMPTY;
  for(i = 0; i < p.size; i++){
    if(pos == p.size*i)return EMPTY;
  }
  return upper;

}
int get_right_pos(plateau p, int pos){
  int i;
  int upper = pos + 1;
  if(p.p[upper] == EMPTY || upper < 0 || upper > p.size*p.size-1)return EMPTY;
  for(i = 0; i < p.size; i++){
    if(pos == p.size*i+p.size-1)return EMPTY;
  }
  return upper;

}

plateau create_cercle(plateau P){
  int dots, i, j, size;
  size = P.size;
  dots = get_dots(size);
  for(j = 0; j < dots; j++){
    for(i = 0; i < dots-j; i++){
      P.p[j*size+i] = EMPTY;
      P.p[j*size+(size - dots) + i+j] = EMPTY;
      P.p[size*(size - (j+1)) + i] = EMPTY;
      P.p[size*(size - (j+1))+(size - dots + i+j)] = EMPTY;
    }
  }

  return P;
}


plateau create_plateau(int size, int forme){
	plateau P;
  int i;
	P.size = size;
	P.forme = forme;
	P.p = malloc(sizeof(int) * size * size);
  for(i = 0; i < size*size; i++)P.p[i]=DOT;
  P = create_cercle(P);
  /*
  P.p[50] = SQUARE;
  P.p[get_upper_pos(P, 50)] = SQUARE;
  P.p[get_lower_pos(P, 50)] = SQUARE;
  P.p[get_left_pos(P, 50)] = SQUARE;
  P.p[get_right_pos(P, 50)] = SQUARE;
  */
	return P;
}



void affichage_circle(plateau P){
  int i,j;
  for(i = 0; i < P.size; i++){
    if(!i){
      printf("   ");
      for(j = 0; j < P.size; j++)
        printf("%c ",(int)'a'+j);
      printf("\n\n");
    }
    printf("%c  ",(int)'A'+i);
    for(j = i*P.size; j < i*P.size+P.size; j++){
      if(P.p[j] == DOT)
        printf(DOTSYMBOL);
      else if(P.p[j] == EMPTY)
        printf("  ");
      else
        printf(SQUARESYMBOL);
    }
    printf("\n");
  }
}

void seek_to_next_line(){
    int c;
    while( (c = fgetc( stdin )) != EOF && c != '\n' );
}

int get_user_pos(int size){
  char h, v;
  printf("Type horizontal letter[a - %c] : ", 'a'+size-1);
  scanf("%c",&h);
  seek_to_next_line();
  if(!(h >= 'a' && (int)h <= (int)'a'+size-1)){
    //printf("\x1B[31mError horizontal letter are between a - %c !\x1B[0m \n", 'a'+size-1);
    return -1;
  }
  printf("Type vertical letter[A - %c] : ", 'A'+size-1);
  scanf("%c",&v);
  seek_to_next_line();
  if(!(v >= 'A' && (int)v <= (int)'A'+size-1)){
    //printf("\x1B[31mError vertical letter are between A - %c !\x1B[0m \n", 'A'+size-1);
    return -1;
  }
  return ((int)v-(int)'A') * size + ((int)h-(int)'a');
}

int get_user_pos_horizontal(int size){
  char h;
  printf("Type horizontal letter[a - %c] : ", 'a'+size-1);
  scanf("%c",&h);
  seek_to_next_line();
  if(!(h >= 'a' && (int)h <= (int)'a'+size-1)){
    //printf("\x1B[31mError horizontal letter are between a - %c !\x1B[0m \n", 'a'+size-1);
    return -1;
  }
  return ((int)h-(int)'a');
}

int append_bloc(plateau * p, bloc b, int pos){
  int i, j, k, verified;
  verified = 1;
  for(i = 0, k = 0; i < b.x; i++){
    for(j = b.y-1; j >= 0; j--, k++){
      if((pos-(p->size*j))+i <= 0)
        verified = 0;
      else if(*(b.b + k) == SQUARE && !(p->p[(pos-(p->size*j))+i] == DOT))
        verified = 0;
    }
  }
  if(verified){
    for(i = 0, k = 0; i < b.x; i++){
      for(j = b.y-1; j >= 0; j--, k++){
        if(*(b.b + k) == SQUARE)
          p->p[(pos-(p->size*j))+i] = SQUARE;
      }
    }
  }else{
    //printf("\x1B[31mError u can't append bloc in unautorised area!\x1B[0m \n");
    return 0;
  }
  return 1;
}

void my_delay(int i){
    clock_t start,end;
    start=clock();
    while(((end=clock())-start)<=((i*CLOCKS_PER_SEC)/1000));
}

int bloc_area_verify(plateau * p, bloc b, int pos, int pos_tmp){
    int i, j, k, verified;
    verified = 1;
	for(i = 0, k = 0; i < b.x; i++){
		for(j = 0; j < b.y; j++, k++){
			if(p->p[pos_tmp-(p->size*j)+i] == SQUARE && 
					p->p[pos-(p->size*j)+i] == DOT){
				break;
			}else if(p->p[pos_tmp-(p->size*j)+i] == DOT){
				continue;
			}else{
				verified = 0;
			}
		}
	}
	return verified;
}

void bloc_area_clear(plateau * p, bloc b, int pos){
	int i, j, k;
	for(i = 0, k = 0; i < b.x; i++){
      for(j = b.y-1; j >= 0; j--, k++){
        if(*(b.b + k) == SQUARE)
          p->p[(pos-(p->size*j))+i] = DOT;
      }
    }
}

int append_bloc_animate(Screen * s, plateau * p, bloc b, int pos, int animation_delay){
  int i, j, k, verified, pos_tmp;
  printf("start = %d\n", pos);
  pos = pos+p->size*(b.y-1);
  printf("pos_a = %d\n", pos);
  for(i = 0, k = 0; i < b.x; i++){
		for(j = b.y-1; j >= 0; j--, k++){
		  if((pos-(p->size*j))+i <= 0)
			verified = 0;
		  else if(*(b.b + k) == SQUARE && !(p->p[(pos-(p->size*j))+i] == DOT))
			verified = 0;
		}
	}
  while(1){
	  if(verified){
		for(i = 0, k = 0; i < b.x; i++){
		  for(j = b.y-1; j >= 0; j--, k++){
		    if(*(b.b + k) == SQUARE)
		      p->p[(pos-(p->size*j))+i] = SQUARE;
		  }
		}
		update_matrix(s, p, 6, 4);
		print_screen(s);
		my_delay(animation_delay);
		pos_tmp = pos;
		pos = get_lower_pos(*p, pos);
		verified = bloc_area_verify(p, b, pos, pos_tmp);
		if(verified)bloc_area_clear(p, b, pos_tmp); else break;
	  }else{
		//printf("\x1B[31mError u can't append bloc in unautorised area!\x1B[0m \n");
		return 0;
	  }
  }
  return 1;
}

void print_bloc(bloc b){
  int i, j;
  for(i = 0; i < b.y; i++){
    for(j = 0; j < b.x; j++){
      if(*(b.b + (j*2)+ i) == DOT)
        printf("  ");
      else if(*(b.b + (j*2)+ i) == EMPTY)
        printf("  ");
      else
        printf(SQUARESYMBOL);
    }
    printf("\n");
  }
}

int verify_vertical(plateau p, int pos){
  int tmp = pos;
  while(pos != -1 && p.p[pos] != EMPTY){
    if(p.p[pos] == DOT)return 0;
    pos = get_upper_pos(p, pos);
  }
  pos = tmp;
  while(pos != -1 && p.p[pos] != EMPTY){
    if(p.p[pos] == DOT)return 0;
    pos = get_lower_pos(p, pos);
  }
  return 1;
}

int verify_horizontal(plateau p, int pos){
  int tmp = pos;
  while(pos != -1 && p.p[pos] != EMPTY){
    if(p.p[pos] == DOT)return 0;
    pos = get_left_pos(p, pos);
  }
  pos = tmp;
  while(pos != -1 && p.p[pos] != EMPTY){
    if(p.p[pos] == DOT)return 0;
    pos = get_right_pos(p, pos);
  }
  return 1;
}

void cancel_vertical(plateau * p, int pos){
  int tmp = pos;
  while(pos != -1 && p->p[pos] != EMPTY){
    p->p[pos] = DOT;
    pos = get_upper_pos(*p, pos);
  }
  pos = tmp;
  while(pos != -1 && p->p[pos] != EMPTY){
    p->p[pos] = DOT;
    pos = get_lower_pos(*p, pos);
  }
}

void cancel_horizontal(plateau * p, int pos){
  int tmp = pos;
  while(pos != -1 && p->p[pos] != EMPTY){
    p->p[pos] = DOT;
    pos = get_left_pos(*p, pos);
  }
  pos = tmp;
  while(pos != -1 && p->p[pos] != EMPTY){
    p->p[pos] = DOT;
    pos = get_right_pos(*p, pos);
  }
}

void shift_blocs(plateau * p, int pos){
  int i, tmp;
  for(i = 0; i < p->size; i ++){
    if(p->p[pos+i] == DOT){
      tmp = pos+i;
      while((tmp = get_upper_pos(*p, tmp)) != -1){
      	if(p->p[tmp] == SQUARE){
		    p->p[get_lower_pos(*p, tmp)] = SQUARE;
		    p->p[tmp] = DOT;
		 }
      }
    }
  }
}

/*
int cancel_plateau_lc(plateau * P, int pos, int x, int y){
  int i, j, count, shift;
  count = shift = 0;
  for(i = 0; i < x; i++){
    for(j = 0; j < y; j++){
      if(verify_vertical(*P, (pos - P->size*j)+i)){
        cancel_vertical(P, (pos - P->size*j)+i);
        count++;
      }
      if(verify_horizontal(*P, (pos - P->size*j)+i)){
        cancel_horizontal(P, (pos - P->size*j)+i);
        count++;
        shift = 1;
      }
    }
  }
  if(shift)shift_blocs(P, pos);
  return count;
}
*/

int cancel_plateau(plateau * P){
  int i, count, shift, pos;
  count = shift = 0;
  for(i = 0; i < P->size; i++){
  	//printf("%d\n", P->size*(P->size/2) + i);
		if(verify_vertical(*P, P->size*(P->size/2) + i)){
			cancel_vertical(P, P->size*(P->size/2) + i);
			count++;
		}
		if(verify_horizontal(*P, P->size/2+(P->size*i))){
			cancel_horizontal(P, P->size/2+(P->size*i));
			count++;
			shift = 1;
			pos = P->size*i;
		}
  }
  if(shift)shift_blocs(P, pos);
  return count;
}

void cercle_3bloc_game(int size){
  Screen * s;
  plateau P;
  P = create_plateau(size,2);
  s = create_screen(P.size*2+35, P.size+10);

  bloc blocs[20] = {b1,  b2,  b3,  b4,  b5,  b6,  b7,  b8,  b9,  b10, 
  				    b11, b12, b13, b14, b15, b16, b17, b18, b19, b20};

  bloc * rand_blocs[3] = {&b1, &b2, &b3};

  update_game_screen(s, P);
  
  
  int score = 0, input, health = 3;
  while(1){
  	  clear_string(s, 15, P.size*2+10);
  	  clear_string(s, 14, P.size*2+10);
  	  clear_string(s, 13, P.size*2+10);
  	  clear_string(s, 12, P.size*2+10);
  	  
      update_matrix(s, &P, 6, 4);
	  update_bloc(s, *rand_blocs[0], 15, P.size*2+10);
	  update_bloc(s, *rand_blocs[1], 15, P.size*2+20);
	  update_bloc(s, *rand_blocs[2], 15, P.size*2+30);
	  
	  update_health(s, P.size, health, 6, 10);
	  
	  //clear_string(s, 21, P.size*2+7);
	  //update_string(s, "Choose a bloc to set[1 - 3] : ", 21, P.size*2+7);
	  update_score(s, P.size, score);
	  
	  print_screen(s);
	  if(health == 0)break;
	  printf("Choose a bloc[1 - 3] to set : ");
	  input = fetchInput(1, 3)-1;
      int pos = get_user_pos(P.size);
      if(pos >= 0){
		  if(append_bloc(&P, *(rand_blocs[input]), pos)){
		  	clear_string(s, 23, P.size*2+7); // error msg clear
		    score += cancel_plateau(&P)*100;
		    rand_blocs[input] = &(blocs[random_number(20)]);
		  }else{
		  	update_string(s, "\x1B[31mWrong Cordination!\x1B[0m", 23, P.size*2+7);
		  	health--;
		  }
      }else{
      	update_string(s, "\x1B[31mWrong Cordination!\x1B[0m", 23, P.size*2+7);
      	health--;
      }
      

	  //update_string(s, "\x1B[31mMessage Error !\x1B[0m", 23, P.size*2+7);
	  //clear_string(s, 27, 0);
  }
  printf("Your score : %d\nGame End\n", score);
  //return 0;
}

void cercle_all_bloc_game(int size, int w, int h){
  Screen * s;
  plateau P;
  P = create_plateau(size,2);
  s = create_screen(w, h);

  int t[20] = {9,1,3,2,14,13,7,6,8,0,10,12,11,5,4,16,15,18,17,19};

  bloc blocs[20] = {b1,  b2,  b3,  b4,  b5,  b6,  b7,  b8,  b9,  b10, 
  				    b11, b12, b13, b14, b15, b16, b17, b18, b19, b20};

  update_game_screen(s, P);
  
  
  int score = 0, input, health = 3, i, j, count=0;
  char result[50];
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
		  	update_bloc(s, blocs[t[count]], j*7+P.size+7+5, 3+(10*i));
		  	sprintf(result, "%.f", (float)count); 
		  	update_string(s, result, j*7+P.size+7+7, 4+(10*i));
		  }
	  }
  while(1){
  	  
      update_matrix(s, &P, 6, 4);
      /*
      for(i = 0, j = 0;i < 12; i+=3, j++){
      	  update_bloc(s, blocs[i], j*7+15, P.size*2+10);
		  update_bloc(s, blocs[i+1], j*7+15, P.size*2+20);
		  update_bloc(s, blocs[i+2], j*7+15, P.size*2+30);
      }
      */
	  
	  update_health(s, P.size, health, 6, 10);
	  
	  //clear_string(s, 21, P.size*2+7);
	  //update_string(s, "Choose a bloc to set[1 - 3] : ", 21, P.size*2+7);
	  update_score(s, P.size, score);
	  
	  print_screen(s);
	  if(health == 0)break;
	  printf("Choose a bloc[0 - 19] to set : ");
	  input = fetchInput(0, 19);
      int pos = get_user_pos(P.size);
      if(pos >= 0){
		  if(append_bloc(&P, blocs[input], pos)){
		  	clear_string(s, 23, P.size*2+7); // error msg clear
		    score += cancel_plateau(&P)*100;
		  }else{
		  	update_string(s, "\x1B[31mWrong Cordination!\x1B[0m", 23, P.size*2+7);
		  	health--;
		  }
      }else{
      	update_string(s, "\x1B[31mWrong Cordination!\x1B[0m", 23, P.size*2+7);
      	health--;
      }
      

	  //update_string(s, "\x1B[31mMessage Error !\x1B[0m", 23, P.size*2+7);
	  //clear_string(s, 27, 0);
  }
  printf("Your score : %d\nGame End\n", score);
  //return 0;
}

void cercle_3bloc_animate_game(int size, int animation_delay){
  Screen * s;
  plateau P;
  P = create_plateau(size,2);
  s = create_screen(P.size*2+35, P.size+10);

  bloc blocs[20] = {b1,  b2,  b3,  b4,  b5,  b6,  b7,  b8,  b9,  b10, 
  				    b11, b12, b13, b14, b15, b16, b17, b18, b19, b20};

  bloc * rand_blocs[3] = {&b1, &b2, &b3};

  update_game_screen(s, P);
  
  
  int score = 0, input, health = 3;
  while(1){
  	  clear_string(s, 15, P.size*2+10);
  	  clear_string(s, 14, P.size*2+10);
  	  clear_string(s, 13, P.size*2+10);
  	  clear_string(s, 12, P.size*2+10);
  	  
      update_matrix(s, &P, 6, 4);
	  update_bloc(s, *rand_blocs[0], 15, P.size*2+10);
	  update_bloc(s, *rand_blocs[1], 15, P.size*2+20);
	  update_bloc(s, *rand_blocs[2], 15, P.size*2+30);
	  
	  update_health(s, P.size, health, 6, 10);
	  
	  //clear_string(s, 21, P.size*2+7);
	  //update_string(s, "Choose a bloc to set[1 - 3] : ", 21, P.size*2+7);
	  update_score(s, P.size, score);
	  
	  print_screen(s);
	  if(health == 0)break;
	  printf("Choose a bloc[1 - 3] to set : ");
	  input = fetchInput(1, 3)-1;
      int pos = get_user_pos_horizontal(P.size);
      if(pos >= 0){
		  if(append_bloc_animate(s, &P, *(rand_blocs[input]), pos, animation_delay)){
		  	clear_string(s, 23, P.size*2+7); // error msg clear
		    score += cancel_plateau(&P)*100;
		    rand_blocs[input] = &(blocs[random_number(20)]);
		  }else{
		  	update_string(s, "\x1B[31mWrong Cordination!\x1B[0m", 23, P.size*2+7);
		  	health--;
		  }
      }else{
      	update_string(s, "\x1B[31mWrong Cordination!\x1B[0m", 23, P.size*2+7);
      	health--;
      }
      

	  //update_string(s, "\x1B[31mMessage Error !\x1B[0m", 23, P.size*2+7);
	  //clear_string(s, 27, 0);
  }
  printf("Your score : %d\nGame End\n", score);
  //return 0;
}


