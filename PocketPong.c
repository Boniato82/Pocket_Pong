//Pocket Pong by Boniato82
//	based on Ping Pong Diplomacy for GameBoy. Programmed by jduranmaster a.k.a. Ryoga
//*****************************************

#include <gb/gb.h>
#include <stdio.h>
#include <ctype.h>
#include <gb/console.h>
#include <gb/drawing.h>
#include <rand.h>
#include <gb/hardware.h>

unsigned const char spritetiles[] = {
	//paddle
	0x3c,0x42,0x3c,0x42,0x3c,0x42,0x3c,0x42,
	0x3c,0x42,0x3c,0x42,0x3c,0x42,0x3c,0x42,
	//bola (+16)
	0x7e, 0x7e, 0x7e, 0x00, 0x7e, 0x00, 0x7e, 0x00,
	0x7e, 0x00, 0x7e, 0x00, 0x7e, 0x00, 0x7c, 0x7c,
	//puntuaciones 0 +32
0xff, 0x00, 0xff, 0x00, 0xff, 0x3c, 0xff, 0x3c,
0xff, 0x3c, 0xff, 0x3c, 0xff, 0x3c, 0xff, 0x3c, //+48
0xff, 0x3c, 0xff, 0x3c, 0xff, 0x3c, 0xff, 0x3c,
0xff, 0x3c, 0xff, 0x3c, 0xff, 0x00, 0xff, 0x00,
//1 +64
0x18, 0x00, 0x18, 0x00, 0x18, 0x00, 0x18, 0x00,
0x18, 0x00, 0x18, 0x00, 0x18, 0x00, 0x18, 0x00,
0x18, 0x00, 0x18, 0x00, 0x18, 0x00, 0x18, 0x00,
0x18, 0x00, 0x18, 0x00, 0x18, 0x00, 0x18, 0x00,
//2 +96
0xff, 0x00, 0xff, 0x00, 0x03, 0x00, 0x03, 0x00,
0x03, 0x00, 0x03, 0x00, 0x83, 0x80, 0xff, 0x00,
0xff, 0x00, 0xc0, 0x00, 0xc0, 0x00, 0xc0, 0x00,
0xc0, 0x00, 0xc0, 0x00, 0xff, 0x00, 0xff, 0x00,
//3 +128
0xff, 0x00, 0xff, 0x00, 0x03, 0x00, 0x03, 0x00,
0x03, 0x00, 0x03, 0x00, 0x03, 0x00, 0xff, 0x00,
0xff, 0x00, 0x03, 0x00, 0x03, 0x00, 0x03, 0x00,
0x03, 0x00, 0x03, 0x00, 0xff, 0x00, 0xff, 0x00,
//4 +160
0xff, 0x3c, 0xff, 0x3c, 0xff, 0x3c, 0xff, 0x3c,
0xff, 0x3c, 0xff, 0x3c, 0xff, 0x3c, 0xff, 0x00,
0xff, 0x00, 0xff, 0xfc, 0xff, 0xfc, 0xff, 0xfc,
0xff, 0xfc, 0xff, 0xfc, 0xff, 0xfc, 0xff, 0xfc,
//5 +192
0xff, 0x00, 0xff, 0x00, 0xff, 0x3f, 0xff, 0x3f,
0xff, 0x3f, 0xff, 0x3f, 0xff, 0x3f, 0xff, 0x00,
0xff, 0x00, 0xff, 0xfc, 0xff, 0xfc, 0xff, 0xfc,
0xff, 0xfc, 0xff, 0xfc, 0xff, 0x00, 0xff, 0x00,
//6 +224
0xff, 0x01, 0xff, 0x01, 0xc1, 0x01, 0xc0, 0x00,
0xc0, 0x00, 0xc0, 0x00, 0xc0, 0x00, 0xff, 0x00,
0xff, 0x00, 0xc3, 0x00, 0xc3, 0x00, 0xc3, 0x00,
0xc3, 0x00, 0xe3, 0x20, 0xff, 0x00, 0xff, 0x00,
//7 +256
0xff, 0x00, 0xff, 0x00, 0x07, 0x04, 0x07, 0x04,
0x07, 0x04, 0x07, 0x04, 0x07, 0x04, 0x07, 0x04,
0x07, 0x04, 0x07, 0x04, 0x07, 0x04, 0x07, 0x04,
0x03, 0x00, 0x03, 0x00, 0x03, 0x00, 0x03, 0x00,
//8 +288
0xff, 0x00, 0xff, 0x00, 0xfb, 0x38, 0xc3, 0x00,
0xc3, 0x00, 0xc3, 0x00, 0xff, 0x3c, 0xff, 0x00,
0xff, 0x00, 0xc3, 0x00, 0xc3, 0x00, 0xc3, 0x00,
0xc3, 0x00, 0xc3, 0x00, 0xff, 0x00, 0xff, 0x00,
//9 +320
0xff, 0x00, 0xff, 0x00, 0xff, 0x3c, 0xff, 0x3c,
0xff, 0x3c, 0xff, 0x3c, 0xff, 0x3c, 0xff, 0x00,
0xff, 0x00, 0xff, 0xfc, 0xff, 0xfc, 0xff, 0xfc,
0xff, 0xfc, 0xff, 0xfc, 0xff, 0xfc, 0xff, 0xfc,
//10 +352
0xdf, 0x80, 0xdf, 0x80, 0xdb, 0x8a, 0xdb, 0x8a,
0xdf, 0x8e, 0xdf, 0x8e, 0xdf, 0x8e, 0xdf, 0x8e,
0xdf, 0x8e, 0xdf, 0x8e, 0xdb, 0x8a, 0xdb, 0x8a,
0xdb, 0x8a, 0xdf, 0x8e, 0xdf, 0x80, 0xdf, 0x80,
//red en mitad del campo
0x10, 0x10, 0x30, 0x20, 0x10, 0x00, 0x10, 0x10,
0x52, 0x52, 0x14, 0x04, 0x14, 0x04, 0x10, 0x10
};

//variables globales del programa.
UBYTE counter,y1,y1b,y2,y2b,y3,y3b,y4,y5,y6;
UBYTE ball_pos_x;
UBYTE ball_pos_y;
UBYTE Paddle0_pos_x; //posicion x,y del paddle del jugador
UBYTE Paddle0_pos_y;
UBYTE Paddle1_pos_x;  //posicion x,y del paddle del CPU
UBYTE Paddle1_pos_y;
UBYTE Paddle0b_pos_x; //posicion x,y del paddle extra del jugador
UBYTE Paddle0b_pos_y;
BYTE ball_vector_x1;
BYTE ball_vector_x2;
BYTE ball_vector_y1;
BYTE ball_vector_y2;
UBYTE vector_pointer;
UBYTE game_status;
UBYTE colx;
UBYTE coly;
BYTE temp1;
BYTE temp2;
BYTE* col_table;
BYTE score_p1;
BYTE score_p2;
BYTE score_counter_p1;
BYTE score_counter_p2;
UBYTE Pausa; //para la pausa.
UBYTE Dificultad; //0 = normal mode(CPU solo mueve tras golpear jugador) - 1 = hard mode 
//incremento de la velocidad de la bola.
UBYTE incremento;
BYTE golpea; //determina quién ha golpeado la bola, para el movimiento de la CPU (si golpea ella no se mueve hasta que golpee el jugador)
UBYTE inicio = 0; //determina cómo se inicia la bola tras cada punto ganado.
BYTE controller = 0;
long score = 0;
BYTE randomY1 = 0;
BYTE randomX1 = 0;
BYTE randomX2 = 0;

// funciones del programa.
int REINICIAR_COORDENADAS();
int COLISIONES();
int CONTROLES();
int CARGAR_ELEMENTOS();
int REPINTAR_SPRITES();
int FINAL_JUEGO();
int INICIO_REINICIO();
int MOVIMIENTO_BOLA();

void PLAY_PADDLE_SOUND_EFFECT(void);
void PLAY_UL_WALL_SOUND_EFFECT(void);
void PLAY_LR_WALL_SOUND_EFFECT(void);
void INIT_REGISTERS_SOUND_EFECTS(void);


int main(void){
	UWORD seed = 0;
	seed = DIV_REG;
	seed |= (UWORD)DIV_REG << 8;
	initarand(seed);
	CARGAR_ELEMENTOS();
	//Control del programa.
	while(1) {
		color(BLACK, WHITE, SOLID);
		wait_vbl_done();
		Paddle0_pos_y = y2; //posiciones y de ambos paddles. 
		Paddle1_pos_y = y5;
		set_sprite_tile(7,2+score_counter_p1); //puntuacion player 1
		set_sprite_tile(8,3+score_counter_p1); //puntuacion player 1
		set_sprite_tile(9,2+score_counter_p2); // puntuacion CPU
		set_sprite_tile(10,3+score_counter_p2); // puntuacion CPU
		set_sprite_tile(11,24); //red
		set_sprite_tile(12,24);
		set_sprite_tile(13,24);
		set_sprite_tile(14,24);
		set_sprite_tile(15,24);
		set_sprite_tile(16,24);
		set_sprite_tile(17,24);
		set_sprite_tile(18,24);
		set_sprite_tile(19,24);
		set_sprite_tile(20,24);
		set_sprite_tile(21,24);
		set_sprite_tile(22,24);
		set_sprite_tile(23,24);
		set_sprite_tile(24,24);
		set_sprite_tile(25,24);
		set_sprite_tile(26,24);
		set_sprite_tile(27,24);
		
	//paddle 0. Controlada por el usuario (doble).
	set_sprite_tile(28,0);
	set_sprite_tile(29,0);
	set_sprite_tile(30,0);
	
	//paddle 1. Controlado por la CPU (doble)
	set_sprite_tile(31,0);
	set_sprite_tile(32,0);
	set_sprite_tile(33,0);
		
		CONTROLES();
		FINAL_JUEGO();
		INICIO_REINICIO();
		MOVIMIENTO_BOLA();	
		COLISIONES();
		REPINTAR_SPRITES();
		
	}
}

int CARGAR_ELEMENTOS(){
	OBP0_REG = 0xE0;  //cambiar paleta de Gameboy para que el blanco no sea el color transparente.
	initarand(255); //inicia el RAND aleatorio.
	BGP_REG = 0x27U;
	///// TERMINA EL BLOQUE BITMAP DONDE SE MUESTRA EL TEXTO DEL JUEGO.
	REINICIAR_COORDENADAS();
	
	//fijar las puntuaciones a cero.
	score_p1 = 0;
	score_p2 = 0;
	incremento = 0;
	score_counter_p1 = 0;
	score_counter_p2 = 0;
	golpea = 0;
	Dificultad = 0;
	score = 0;
	Pausa = 0; //desactivado.
	//cargar los sprites.
	SPRITES_8x8;
	//cargar los tiles del paddle.
	set_sprite_data(0, 1, spritetiles);
	//cargar los tiles de la bola.
	set_sprite_data(1, 1, spritetiles+16);
	//cargar los tiles de las puntuaciones. van a ir de 16 en 16, aunque cada número son 32
	set_sprite_data(2, 1, spritetiles+32); //numero 0
	set_sprite_data(3, 1, spritetiles+48);
	set_sprite_data(4, 1, spritetiles+64); //numero 1
	set_sprite_data(5, 1, spritetiles+80);
	set_sprite_data(6, 1, spritetiles+96); //numero 2 
	set_sprite_data(7, 1, spritetiles+112);
	set_sprite_data(8, 1, spritetiles+128); //numero 3
	set_sprite_data(9, 1, spritetiles+144);
	set_sprite_data(10, 1, spritetiles+160); //numero 4
	set_sprite_data(11, 1, spritetiles+176);
	set_sprite_data(12, 1, spritetiles+192); // numero 5
	set_sprite_data(13, 1, spritetiles+208);
	set_sprite_data(14, 1, spritetiles+224); //numero 6
	set_sprite_data(15, 1, spritetiles+240);
	set_sprite_data(16, 1, spritetiles+256); //numero 7
	set_sprite_data(17, 1, spritetiles+272);
	set_sprite_data(18, 1, spritetiles+288) ;//numero 8
	set_sprite_data(19, 1, spritetiles+304);
	set_sprite_data(20, 1, spritetiles+320); //numero 9
	set_sprite_data(21, 1, spritetiles+336);
	set_sprite_data(22, 1, spritetiles+352); //numero 10
	set_sprite_data(23, 1, spritetiles+368);
	//red del campo
	set_sprite_data(24, 1, spritetiles+384);

	//paddle 0. Controlada por el usuario.
	set_sprite_tile(0,0);
	set_sprite_tile(1,0);
	set_sprite_tile(2,0);
	
	//paddle 1. Controlado por la CPU. 
	set_sprite_tile(3,0);
	set_sprite_tile(4,0);
	set_sprite_tile(5,0);
	//bola.
	set_sprite_tile(6,1);
	
	//activar fondos y sprites.
	SHOW_BKG;
	SHOW_SPRITES; 
	enable_interrupts();
	INIT_REGISTERS_SOUND_EFECTS();
	
return 0;	
}
void INIT_REGISTERS_SOUND_EFECTS(void){
	NR52_REG = 0xF8U;
	NR51_REG = 0x00U;
	NR50_REG = 0x77U;//0xFFU;
}

void PLAY_PADDLE_SOUND_EFFECT(void){
    NR10_REG = 0x34U;
	NR11_REG = 0x80U;
	NR12_REG = 0xF0U;
	NR13_REG = 0x0AU;
	NR14_REG = 0xC6U;
	NR51_REG |= 0x11;
}

void PLAY_UL_WALL_SOUND_EFFECT(void){
    NR41_REG = 0x00;//0x1FU;
    NR42_REG = 0xE1;//0xF7U;
    NR43_REG = 0x22;//0x24U;
    NR44_REG = 0xC3;//0x80U;
    NR51_REG = 0x88U;
}

void PLAY_LR_WALL_SOUND_EFFECT(void){
	NR10_REG = 0x04U;
	NR11_REG = 0xFEU;
	NR12_REG = 0xA1U;
	NR13_REG = 0x8FU;
	NR14_REG = 0x86U;
	NR51_REG = 0xF7;
}

int REINICIAR_COORDENADAS(){
	//pos inicial paddle0.
	y1 = 65;
	y2 = 73;
	y3 = 81;
	y1b = 65;
	y2b = 73;
	y3b = 81;
	//pos inicial paddle1.
	y4 = 65;
	y5 = 73;
	y6 = 81;
	//pos inicial bola.
	ball_pos_x=80;
	ball_pos_y=77;
	//inicializar el vector de movimiento.
	ball_vector_x1 = 0;
	ball_vector_x2 = 0;
	ball_vector_y1 = 0;
	ball_vector_y2 = 0;
	vector_pointer = 0;
	game_status = 0;
	return 0;
}


int CONTROLES(){
counter = joypad();	
// movimiento del paddle 0.
		if(counter & J_UP && y1>=21){
			y1-=2;
			y2-=2;
			y3-=2;
			}
		
		if(counter & J_DOWN && y3<=145){
			y1+=2;
			y2+=2;
			y3+=2;
			}
	
	
		// movimiento del paddle 1.
		if(y5 > ball_pos_y && y4 >= 21 && golpea == 0){
			y4-=2;
			y5-=2;
			y6-=2;
		}
		if(y5 < ball_pos_y && y6 <= 145 && golpea == 0){
			y4+=2;
			y5+=2;
			y6+=2;
		}
		if (counter & J_START && game_status == 1){ //poner el juego en pausa pulsando START
				delay(250);
			waitpad(J_START);
			delay(250);	
			}	
		if (counter & J_SELECT && game_status == 1){ //dificultad. 0 = normal mode / 1 = hard mode
			delay(250);
			HIDE_SPRITES;
			switch (Dificultad){
			case 0:
				Dificultad = 1;
				gotoxy(0, 0);
				printf(" \n");
				printf(" \n");
				printf(" \n");
				printf("\n\n    Prepare for");
				printf("\n\n   HARDCORE MODE");
				delay(3500);
				gotoxy(0, 0);
				printf(" \n");
				printf(" \n");
				printf(" \n");
				printf("\n\n                   ");
				printf("\n\n                   ");
				SHOW_SPRITES;
				REPINTAR_SPRITES();
				delay(350);	
				break;
			case 1:
				Dificultad = 0;
				gotoxy(0, 0);
				printf(" \n");
				printf(" \n");
				printf(" \n");
				printf("\n\n      Back to");
				printf("\n\n    NORMAL MODE");
				delay(3000);
				gotoxy(0, 0);
				printf(" \n");
				printf(" \n");
				printf(" \n");
				printf("\n\n                  ");
				printf("\n\n                  ");
				SHOW_SPRITES;
				REPINTAR_SPRITES();	
				delay(350);	
				break;
			}
			delay(250);	
			}			
			return 0;

}

int COLISIONES(){
		//colisiones con paddle del jugador
		if(ball_pos_y >= (y1-8) && ball_pos_y <= (y3+8) && ball_pos_x <= 23){
			
			golpea=0;//golpea el jugador así que se mueve.
			while(temp1!=0 || temp2!=0){
				if(temp1>0){
					temp1--;
					ball_pos_x--;
				}
				if(temp1<0){
					temp1++;
					ball_pos_x++;
				}
				if(temp2>0){
					temp2--;
					ball_pos_y--;
				}
				if(temp2<0){
					temp2++;
					ball_pos_y++;
				}
			}
			PLAY_PADDLE_SOUND_EFFECT();
					do { 
						randomX1 = (rand() % 3) +1;
					} while (randomX1 <= 2 || randomX1 >= 5);
					ball_vector_x1 = randomX1 + (incremento/6); //entre 1 y 3.
				
					do { 
						randomX2 = (rand() % 3) +1;
					} while (randomX2 <= 0 || randomX2 >= 4);
					ball_vector_x2 = randomX2; //1 a 3
				
					do { 
						randomY1 = (rand() % 5) -2;
					} while ((randomY1 <= -4 || randomY1 >= 4));  //
					ball_vector_y1 = randomY1; //entre -3 y 3
				
					if (ball_vector_y1 < 0) ball_vector_y2 = ball_vector_y1 + 1;  //de -1 a 1
					else if (ball_vector_y1 > 0) ball_vector_y2 = ball_vector_y1 - 1;
				incremento++;
	
		}
	
		//colisiones con paddle CPU
		if(ball_pos_y >= (y4-8) && ball_pos_y <= (y6+8) && ball_pos_x >= 148){
			randomX1 = 0;
			randomX2 = 0;
			randomY1 = 0;
			golpea=1;//golpea el CPU así que NO se mueve.
			while(temp1!=0 || temp2!=0){
				if(temp1 > 0){
					temp1--;
					ball_pos_x--;
				}
				if(temp1 < 0){
					temp1++;
					ball_pos_x++;
				}
				if(temp2 > 0){
					temp2--;
					ball_pos_y--;
				}
				if(temp2 < 0){
					temp2++;
					ball_pos_y++;
				}
			}
			PLAY_PADDLE_SOUND_EFFECT();
					do { 
						randomX1 = (rand() % 3) -3;
					} while (randomX1 < -3 || randomX1 > -1);
					ball_vector_x1 = randomX1 - (incremento/6); //entre -1 y -3.
				
					do { 
						randomX2 = (rand() % 3) -3;
					} while (randomX2 < -3 || randomX2 > -1);
					ball_vector_x2 = randomX2; //-1 a -3
				
					do { 
						randomY1 = (rand() % 6) -2;
					} while ((randomY1 < -3 || randomY1 > 3));  //
					ball_vector_y1 = randomY1; //entre -3 y 3
				
					if (ball_vector_y1 < 0) ball_vector_y2 = ball_vector_y1 + 1;  //de -1 a 1
					else if (ball_vector_y1 > 0) ball_vector_y2 = ball_vector_y1 - 1;
				incremento++;
		}
		
		//colisiones con paddle EXTRA CPU
		if((ball_pos_y >= (y5-8) && ball_pos_y <= (y5+8)) && Dificultad == 1 && ball_pos_x >= 90 && ball_pos_x <= 93){
			golpea=1;//golpea el CPU así que NO se mueve.
			while(temp1!=0 || temp2!=0){
				if(temp1 > 0){
					temp1--;
					ball_pos_x--;
				}
				if(temp1 < 0){
					temp1++;
					ball_pos_x++;
				}
				if(temp2 > 0){
					temp2--;
					ball_pos_y--;
				}
				if(temp2 < 0){
					temp2++;
					ball_pos_y++;
				}
			}
			PLAY_PADDLE_SOUND_EFFECT();
			do { 
						randomX1 = (rand() % 3) -3;
					} while (randomX1 < -3 || randomX1 > -1);
					ball_vector_x1 = randomX1 - (incremento/6); //entre -1 y -3.
				
					do { 
						randomX2 = (rand() % 3) -3;
					} while (randomX2 < -3 || randomX2 > -1);
					ball_vector_x2 = randomX2; //-1 a -3
				
					do { 
						randomY1 = (rand() % 5) -2; //que el paddle extra del CPU no golpee tan inclinado.
					} while ((randomY1 < -2 || randomY1 > 2));  //
					ball_vector_y1 = randomY1; //entre -2 y 2
					
					ball_vector_y2 = 0;
				incremento++;
		}
		
		// detección de colisiones.
		// pared izquierda. //CPU gana un punto.
		if(ball_pos_x<20){
			REINICIAR_COORDENADAS();
			score_p2+=2;
			score_counter_p2+=2;
			PLAY_UL_WALL_SOUND_EFFECT();
			incremento = 0;
			golpea = 0;
			controller = 1;	
			score -= 6;  //restamos puntos al total
		}
		// pared derecha. //el jugador gana un punto.
		if(ball_pos_x>150){ 
			REINICIAR_COORDENADAS();
			score_p1+=2;
			score_counter_p1+=2;
			PLAY_UL_WALL_SOUND_EFFECT();
			incremento=0;
			golpea = 0;
			score += 77; //sumamos puntos al total
			controller = 1;
		}
		
		// pared superior.
		if(ball_pos_y < 21){
			ball_pos_y = 21;
			ball_vector_y1--;
			ball_vector_y1=ball_vector_y1 ^ 255;
			ball_vector_y2--;
			ball_vector_y2=ball_vector_y2 ^ 255;
			PLAY_LR_WALL_SOUND_EFFECT();
		}
		
		// pared inferior.
		if(ball_pos_y > 146){
			ball_pos_y = 146;
			ball_vector_y1--;
			ball_vector_y1=ball_vector_y1 ^ 255;
			ball_vector_y2--;
			ball_vector_y2=ball_vector_y2 ^ 255;
			PLAY_LR_WALL_SOUND_EFFECT();
		}
	return 0;
}

int MOVIMIENTO_BOLA(){
		if(vector_pointer==0){
			temp1 = ball_vector_x1;
			temp2 = ball_vector_y1;
			vector_pointer = 1;
		}
		else{
			temp1 = ball_vector_x2;
			temp2 = ball_vector_y2;
			vector_pointer = 0;
		}
		ball_pos_x+=temp1;
		ball_pos_y+=temp2;
return 0;	
}

int REPINTAR_SPRITES(){
//repintar sprite del paddle0 en función de su posición actual.
		move_sprite(0,15,y1);
		move_sprite(1,15,y2);
		move_sprite(2,15,y3);
		if (Dificultad == 1){
			//CPU comparte coordenadas con su otro paddle
			move_sprite(32,98,y5);
		}
		if (Dificultad == 0){
			move_sprite(31,180,160); //CPU
			move_sprite(32,180,160);
			move_sprite(33,180,160);	
		}
		//repintar sprite del paddle1 en función de su posición actual.
		move_sprite(3,153,y4);
		move_sprite(4,153,y5);
		move_sprite(5,153,y6);
		////repintar bola en función de su posición actual.
		move_sprite(6,ball_pos_x,ball_pos_y);
		//repintar puntuaciones.
		move_sprite(7,62,27);
		move_sprite(8,62,35);
		move_sprite(9,102,27);
		move_sprite(10,102,35);
		//pintar la red
		move_sprite(11,82,24);
		move_sprite(12,82,32);
		move_sprite(13,82,40);
		move_sprite(14,82,48);
		move_sprite(15,82,56);
		move_sprite(16,82,64);
		move_sprite(17,82,72);
		move_sprite(18,82,80);
		move_sprite(19,82,88);
		move_sprite(20,82,96);
		move_sprite(21,82,104);
		move_sprite(22,82,112);
		move_sprite(23,82,120);
		move_sprite(24,82,128);
		move_sprite(25,82,136);
		move_sprite(26,82,144);

return 0;
}

int FINAL_JUEGO(){

	if((score_p1 == 20 || score_p2 == 20) || controller == 1){ //fin del juego.
			if((score_counter_p2 == 20 || score_counter_p1 == 20)){	
				HIDE_SPRITES;
				BGP_REG = 0x27U;
				if (score_counter_p1 == 20){
				if ((score_p2 == 0 || score_counter_p2 == 0) && Dificultad == 1) score+=230;
				gotoxy(0,0);
				printf(" \n \n \n \n \n \n");
				printf("     YOU WIN\n");
				printf("     Score: %d", score);

				}
				if (score_counter_p2 == 20){
				gotogxy(0, 0);
				printf(" \n \n \n \n \n \n");
				printf("     YOU LOSE\n");
				printf("     Score: %d", score);
				}
				delay(4000);
				gotoxy(0, 0);
				printf(" \n \n \n \n \n \n");
				printf("                \n");
				printf("                  ");
				REINICIAR_COORDENADAS();
				score=0;
				controller = 0;
			}
			
			if(controller == 1){
				score_p1 = 0;
				score_p2 = 0;
				set_sprite_tile(7,2+score_counter_p1); //puntuacion player 1
				set_sprite_tile(8,3+score_counter_p1); //puntuacion player 1
				set_sprite_tile(9,2+score_counter_p2); // puntuacion CPU
				set_sprite_tile(10,3+score_counter_p2); // puntuacion CPU
						
			}else{
				score_p1 = 0;
				score_p2 = 0;
				incremento = 0;
				score_counter_p1 = 0;
				score_counter_p2 = 0;
				ball_vector_x1 = 1;
				ball_vector_x2 = 1;
				ball_vector_y1 = 1;
				ball_vector_y2 = 1;
				SPRITES_8x8;
				set_sprite_data(0, 1, spritetiles); //paddles
				set_sprite_data(1, 1, spritetiles+16);
				set_sprite_data(2, 1, spritetiles+32); //numero 0
				set_sprite_data(3, 1, spritetiles+48);
				set_sprite_data(4, 1, spritetiles+64); //numero 1
				set_sprite_data(5, 1, spritetiles+80);
				set_sprite_data(6, 1, spritetiles+96); //numero 2 
				set_sprite_data(7, 1, spritetiles+112);
				set_sprite_data(8, 1, spritetiles+128); //numero 3
				set_sprite_data(9, 1, spritetiles+144);
				set_sprite_data(10, 1, spritetiles+160); //numero 4
				set_sprite_data(11, 1, spritetiles+176);
				set_sprite_data(12, 1, spritetiles+192); // numero 5
				set_sprite_data(13, 1, spritetiles+208);
				set_sprite_data(14, 1, spritetiles+224); //numero 6
				set_sprite_data(15, 1, spritetiles+240);
				set_sprite_data(16, 1, spritetiles+256); //numero 7
				set_sprite_data(17, 1, spritetiles+272);
				set_sprite_data(18, 1, spritetiles+288); //numero 8
				set_sprite_data(19, 1, spritetiles+304);
				set_sprite_data(20, 1, spritetiles+320); //numero 9
				set_sprite_data(21, 1, spritetiles+336);
				set_sprite_data(22, 1, spritetiles+352); //numero 10
				set_sprite_data(23, 1, spritetiles+368); 
				//red del campo
				set_sprite_data(24, 1, spritetiles+384);
				set_sprite_data(25, 1, spritetiles); //paddles
				set_sprite_data(26, 1, spritetiles); //paddles
				SHOW_SPRITES;
				game_status = 1;
				controller = 0;
			}
		}

return 0;	
}

int INICIO_REINICIO(){ //cuando empieza la partida o termina una.
if(game_status==0){
			//si el juego ha terminado, se reinicia.
			if(score_counter_p2 == 20 || score_counter_p1 == 20){
				score_counter_p2 = 0;
				score_counter_p1 = 0;
				score_p1 = 0;
				score_p2 = 0;
				incremento= 0;
				golpea = 0;
				score = 0;
			}	
			inicio= rand();
			
			if ( inicio <= 62){	//numero aleatorio para ver hacia dónde se dirige la bola.
				ball_vector_x1 = 1;
				ball_vector_x2 = 1;
				ball_vector_y1 = 1;
				ball_vector_y2 = 1;
				}
			else if (inicio > 62 && inicio <= 124){
				ball_vector_x1 = 1;
				ball_vector_x2 = 1;
				ball_vector_y1 = -1;
				ball_vector_y2 = -1;
				}
			else if (inicio > 124 && inicio<= 186){
				ball_vector_x1 = -1;
				ball_vector_x2 = -1;
				ball_vector_y1 = 1;
				ball_vector_y2 = 1;
				}
			else {
				ball_vector_x1 = -1;
				ball_vector_x2 = -1;
				ball_vector_y1 = -1;
				ball_vector_y2 = -1;
			}
			wait_vbl_done();
			delay(350);
			game_status = 1; //el juego comienza de nuevo.
		}
return 0;	
}
