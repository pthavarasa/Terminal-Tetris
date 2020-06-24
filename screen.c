#ifndef SCREEN_H
#include "screen.h"
#endif

#ifndef TRIANGLE_H
#include "triangle.h"
#endif

#ifndef CERCLE_H
#include "cercle.h"
#endif

int recommanded_size(int w, int h){
	if(w>26)w=26;
	while(w+11 > h)w--;
	return w;
}

int stringToInt(char * c){
    int sign = 1, som = 0, i;
    if (c[0] == '-'){
        sign=-1;
    }
    for (i=0; c[i]; i++){
        if (c[i] >= '0' && c[i] <= '9'){
            som *= 10;
            som += (c[i] - '0');  
        }
    }
    return som * sign;
}

int fetchInput(int min, int max){
    int i, j=0, input;
    char s[100];
    do{
        if(j==0){
            j=1;
        }else{
            printf("Wrong Input, Accept only [%d - %d] : ",min,max);
            j=1;
        }
        scanf ("%s",s);
        seek_to_next_line();
        for (i=0; s[i]; i++){
          if(!(s[i] >= '0' && s[i] <= '9')){
            j = 2;
          }
        }
        input = stringToInt(s);
    } while(input < min || input > max || j == 2);
    return input;
}

char ** string_split(char * str, char delim){
	char ** result;
	int count, count1, i, j;
	char * tmp;
	count = 0;
	count1 = 0;
	tmp = str;
	int str_count[1000];
	while (*tmp){
        if (delim == *tmp)
        	str_count[count++] = count1;
        if(*tmp == 10)break;
        tmp++;
        count1++;
    }
    str_count[count++] = count1;
    tmp = str;
    result = (char**)malloc(sizeof(char*) * count);
    for(i = 0; i < count; i++){
    	result[i] = (char *)malloc(sizeof(char) * str_count[i]+1);
    	for(j = 0; j < str_count[i]; j++){
    		*(*(result+i)+j) = *tmp++;
    	}
    	tmp++;
    	*(*(result+i)+j) = '\0';
    }
    return result;
}


void get_linux_command_output(char * var, char * command){
	FILE *fp;
	fp = popen(command, "r");
	//while(fgets(var, sizeof(var), fp) != NULL)printf("%s",var);
	fgets(var, sizeof(var), fp);
}

void get_terminal_size(int* width, int* height){
	char var[20];
	get_linux_command_output(var, "stty size");
	char ** t = string_split(var, ' ');
	*width = stringToInt(t[1]);
	*height = stringToInt(t[0]);
}

Screen * create_screen(int x, int y){
    Screen * s = (Screen *) malloc(sizeof(Screen));
    char * src = (char *) malloc(sizeof(char) * x * y);
    s->x = x;
    s->y = y;
    int i;
    for(i = 0; i < s->x * s->y; i++) *(src+i) = ' ';
    s->scr = src;
    return s;
}

void print_screen(Screen * s){
  int i;
  system("clear");
  for(i = 0; i < s->x * s->y; i++){
    if(i%s->x == 0){
      printf("\n");
    }
    if(*(s->scr+i) == '*')
      printf("\x1B[31m◼\x1B[0m");
    else if(*(s->scr+i) == '"')
      printf("═");
    else if(*(s->scr+i) == '|')
      printf("║");
    else
      printf("%c",*(s->scr+i));
  }
  printf("\n");
}

int string_count(char * s){
  int i, som;
  som = i = 0;
  while (s[i] != '\0'){
    som++;
    i++;
  }
  return som;
}

int string_to_int(char * s){
	int i, som;
	som = i = 0;
	while (s[i]){
		if (s[i] < 48 || s[i] > 57) return -1;
		som*=10;
		som += s[i]-'0';
		i++;
	}
	return som;
}

void clear_string(Screen * s, int lin, int col){
  int i;
  for(i =0; i < s->x-col; i++){
    s->scr[s->x*lin+col+i] = ' ';
  }
}

void update_string(Screen * s, char * str, int lin, int col){
  int i = 0;
  if(col == -1){
    while(str[i]){
      *(s->scr + s->x * lin + (s->x/2-(string_count(str)/2)) + i) = str[i];
      i++;
    }
    return;
  }
  while(str[i]){
    *(s->scr + s->x * lin + i+ col) = str[i];
    i++;
  }
}

void update_matrix(Screen * s, plateau * p, int lin, int col){
  int i, j, k;
  for(j = 0; j < ((p->forme == 1)?get_hauteur_triangle(p->size):p->size); j++){
    for(i = 0, k = 0; i < p->size*2; i+=2, k++){
      *(s->scr + s->x * (lin+ j) + i + col) = 
        (p->p[j*p->size+k]==DOT)?'.':(p->p[j*p->size+k]==EMPTY)?' ':'*';
      *(s->scr + s->x * (lin + j) + i+1+col) = ' ';
    }
  }
}

void update_bloc(Screen * s, bloc b, int lin, int col){
  int i, j, k;
  for(i = 0, k = 0; i < b.x; i++){
      for(j = b.y-1; j >= 0; j--, k++){
        if (*(b.b + k) == SQUARE) s->scr[(lin-j)*s->x+col+i*2] = '*';
      }
    }
}

/*void update_bloc(Screen * s, bloc b, int lin, int col){
  int i, j, k;
  for(i = 0; i < b.x; i++){
      for(j = b.y-1, k = 0; k < b.y; j--, k++){
        if (*(b.b + (i * b.x) + k) == SQUARE) s->scr[(lin-j)*s->x+col+i*2] = '*';
      }
    }
}*/

void update_game_screen(Screen * s, plateau P){
  int i;
  char alpha[] = {'x', '\0'};
  update_string(s, "----------------------", 0, -1);
  update_string(s, "Welcome", 1, -1);
  update_string(s, "----------------------", 2, -1);
  update_string(s, "\"", 5, 2);
  for(i = 0; i < P.size; i++){
    alpha[0] = 'a'+i;
    update_string(s, alpha, 4, 4 + i*2);
    update_string(s, "\"\"", 5, 3 + i*2);
    update_string(s, "\"\"", ((P.forme == 1)?get_hauteur_triangle(P.size):P.size)+6, 2 + i*2);
    if(i == P.size-1){
      update_string(s, "\"\"", 5, 3 + P.size*2);
      update_string(s, "\"\"\"", ((P.forme == 1)?get_hauteur_triangle(P.size):P.size)+6, 2+ P.size*2);
    }

  }
  for(i = 0; i < ((P.forme == 1)?get_hauteur_triangle(P.size):P.size); i++){
    alpha[0] = 'A'+i;
    update_string(s, alpha, 6 + i, 0);
    update_string(s, "|", 6 + i, 2);
    update_string(s, "|", 6 + i, P.size*2+4);

  }
  update_string(s, "---------------", 7, P.size*2+7);
  update_string(s, "  Score : ", 8, P.size*2+7);
  update_string(s, "---------------", 9, P.size*2+7);

  update_string(s, "1", 17, P.size*2+11);
  update_string(s, "2", 17, P.size*2+21);
  update_string(s, "3", 17, P.size*2+31);  
}

void update_score(Screen * s, int size_plateau, float score){
    char result[50];
    sprintf(result, "%.f", score); 
    update_string(s, result, 8, size_plateau*2+17);
}

void update_health(Screen * s, int plateau_size, int health, int lin, int col){
	int i;
	clear_string(s, lin, plateau_size*2+col);
	for(i = 0; i < health; i++){
		update_string(s, "❤️", lin, plateau_size*2+col+8*i);
	}
}

void src_home(Screen * s, int w, int h){
	update_string(s, "$$$$$$$$\\ $$$$$$$$\\ $$$$$$$$\\ $$$$$$$\\  $$$$$$\\  $$$$$$\\  ", h/2-3, -1);
	update_string(s, "\\__$$  __|$$  _____|\\__$$  __|$$  __$$\\ \\_$$  _|$$  __$$\\ ", h/2-2, -1);
	update_string(s, "   $$ |   $$ |         $$ |   $$ |  $$ |  $$ |  $$ /  \\__|", h/2-1, -1);
	update_string(s, "   $$ |   $$$$$\\       $$ |   $$$$$$$  |  $$ |  \\$$$$$$\\  ", h/2, -1);
	update_string(s, "   $$ |   $$  __|      $$ |   $$  __$$<   $$ |   \\____$$\\ ", h/2+1, -1);
	update_string(s, "   $$ |   $$ |         $$ |   $$ |  $$ |  $$ |  $$\\   $$ |", h/2+2, -1);
	update_string(s, "   $$ |   $$$$$$$$\\    $$ |   $$ |  $$ |$$$$$$\\ \\$$$$$$  |", h/2+3, -1);
	update_string(s, "   \\__|   \\________|   \\__|   \\__|  \\__|\\______| \\______/ ", h/2+4, -1);
	update_string(s, "----------", h/2+6, -1);
	update_string(s, "[1] Start", h/2+7, -1);
	update_string(s, "[0] Help!", h/2+8, -1);
}

void src_size_choose(Screen * s, int w, int h){
	char res[50];
	snprintf(res, sizeof(res), "Your terminal window size is %dx%d.", w, h);
	update_string(s, res, h/2-6, -1);
	snprintf(res, sizeof(res), "The avarage plateau size can be %d to %d.", 9, 26);
	update_string(s, res, h/2-5, -1);
	snprintf(res, sizeof(res), "Recommanded plateau size is %d.", recommanded_size((w-35)/2, h));
	update_string(s, res, h/2-4, -1);
	update_string(s, "(refrush after adjust the window!)", h/2-3, -1);
	update_string(s, "(To play 'All blocs', Full screen must!!)", h/2-2, -1);
	
	update_string(s, "----------", h/2, -1);
	update_string(s, "[7] Refush terminal size", h/2+1, -1);
	update_string(s, "[8] Set recommanded size", h/2+2, -1);
	update_string(s, "[9 - 26] Choose custom size", h/2+3, -1);
}

void src_form_choose(Screen * s, int w, int h){
	update_string(s, "Choose the form of plateau?", h/2-3, -1);
	update_string(s, "\x1B[31m(losange and triangle have some bugs)\x1B[0m so play cercle.", h/2-2, -1);
	update_string(s, "----------", h/2, -1);
	update_string(s, "[0] Losange", h/2+1, -1);
	update_string(s, "[1] Triangle", h/2+2, -1);
	update_string(s, "[2] Cercle", h/2+3, -1);
}

void src_suggestion_choose(Screen * s, int w, int h, int cercle){
	update_string(s, "Choose the game methode?", h/2-3, -1);
	update_string(s, "----------", h/2, -1);
	update_string(s, "[0] All Blocs", h/2+1, -1);
	update_string(s, "[1] Random 3 Blocs X Y", h/2+2, -1);
	if(cercle)update_string(s, "[2] Random 3 Blocs X (animated)", h/2+3, -1);
}

void src_clear(Screen * s, int w, int h){
	int i;
	for(i  = 0; i < w*h; i++)*(s->scr+i) = ' ';
}

int random_number(int max){
  time_t t;
  srand((unsigned) time(&t));
  return rand()%max;
}

