#include "main.h"

int main(){
	int w, h, input;
	Screen * s;
	get_terminal_size(&w, &h);
	s = create_screen(w, h);
	int plateau_size=7, plateau_form, plateau_methode;
	
	src_home(s, w, h);
	print_screen(s);
	src_clear(s, w, h);
	
	do{
		input = fetchInput(0, 1);
		if (!input) printf ("Sorry, We will update doc very soon!\n");
	} while (!input);
	if(input){
		while(plateau_size == 7){
			get_terminal_size(&w, &h);
			s = create_screen(w, h);
			src_size_choose(s, w, h);
			print_screen(s);
			src_clear(s, w, h);
			plateau_size = fetchInput(7, 26);
			if(plateau_size == 8)plateau_size = recommanded_size((w-35)/2, h);
		}
		
		src_form_choose(s, w, h);
		print_screen(s);
		src_clear(s, w, h);
		plateau_form = fetchInput(0, 2);
		
		src_suggestion_choose(s, w, h, (plateau_form == 2)?1:0);
		print_screen(s);
		src_clear(s, w, h);
		if(plateau_form == 2)plateau_methode = fetchInput(0, 2) ;
			else plateau_methode = fetchInput(0, 1);
	}
	
	input = plateau_form*10+plateau_methode;
	switch(input){
		case 0:
			if(!(plateau_size&1))plateau_size++;
			losange_all_bloc_game(plateau_size, w, h-1);
			break;
		case 1:
			if(!(plateau_size&1))plateau_size++;
			losange_3bloc_game(plateau_size);
			break;
		case 10:
			if(!(plateau_size&1))plateau_size++;
			triangle_all_bloc_game(plateau_size, w, h-1);
			break;
		case 11:
			if(!(plateau_size&1))plateau_size++;
			triangle_3bloc_game(plateau_size);
			break;
		case 20:
			cercle_all_bloc_game(plateau_size, w, h-1);
			break;
		case 21:
			cercle_3bloc_game(plateau_size);
			break;
		case 22:
			cercle_3bloc_animate_game(plateau_size, 100);
			break;
	}
	
	return 0;
}
