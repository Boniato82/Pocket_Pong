/*Pocket Pong by Boniato82
//	based on Ping Pong Diplomacy for GameBoy. Programmed by jduranmaster
*/

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
0x52, 0x52, 0x14, 0x04, 0x14, 0x04, 0x10, 0x10,
	//flecha de pantalla de inicio
0x00, 0x00, 0x18, 0x00, 0x0c, 0x00, 0x7e, 0x00,
0x7e, 0x00, 0x0c, 0x00, 0x18, 0x00, 0x00, 0x00
};

//variables globales del programa.
UINT8 EmpiezaJuego;
UINT8 presionado; //para usar con los controles.
UINT8 y1,y2,y3,y4,y5,y6;
UINT8 ball_pos_x;
UINT8 ball_pos_y;
UINT8 Paddle0_pos_x; //posicion x,y del paddle del jugador
UINT8 Paddle0_pos_y;
UINT8 Paddle1_pos_x;  //posicion x,y del paddle del CPU
UINT8 Paddle1_pos_y;
INT8 ball_vector_x1;
INT8 ball_vector_y1;
UINT8 game_status;
UINT8 score_counter_p1;
UINT8 score_counter_p2;
UINT8 Pausa; 
INT8 Dificultad; //0 = normal mode 1 = hardcore mode 
UINT8 incremento; //incremento de la velocidad del vector x de la bola.
INT8 golpea; //determina quién ha golpeado la bola, para el movimiento de la CPU (si golpea ella no se mueve hasta que golpee el jugador)
UINT8 inicio_direccion; //determina la dirección de la bola tras cada punto ganado.
UINT8 inicio_y; //determina la posición Y de la bola tras cada punto ganado.
INT16 score;
UINT16 seed; //semilla para numeros aleatorios.
UINT8 i; //numero para los for

// funciones del programa.
void REINICIAR_COORDENADAS(void);
void COLISIONES(void);
void CONTROLES(void);
void CARGAR_ELEMENTOS(void);
void CARGAR_SPRITES(void);
void REPINTAR_SPRITES(void);
void FINAL_JUEGO(void);
void INICIO_REINICIO(void);
void MOVIMIENTO_BOLA(void);
void PLAY_PADDLE_SOUND_EFFECT(void);
void PLAY_UL_WALL_SOUND_EFFECT(void);
void PLAY_LR_WALL_SOUND_EFFECT(void);
void INIT_REGISTERS_SOUND_EFECTS(void);
void LIMPIA_PANTALLA(void);
void SET_SPRITES(void);
void PULSA_SELECT(void);
void PANTALLA_INICIAL(void);
void OCULTAR_SPRITES(void);

void main(void){
	CARGAR_ELEMENTOS();
	CARGAR_SPRITES();
	SET_SPRITES();
	PANTALLA_INICIAL();
	//Control del programa.
	while(1) {
		color(BLACK, WHITE, SOLID);
		wait_vbl_done();
		Paddle0_pos_y = y2; //posiciones y de ambos paddles. 
		Paddle1_pos_y = y5;
		SET_SPRITES();
		CONTROLES();
		FINAL_JUEGO();
		INICIO_REINICIO();
		MOVIMIENTO_BOLA();	
		COLISIONES();
		REPINTAR_SPRITES();	
	}
}

void CARGAR_ELEMENTOS(void){
	seed = 0;
	inicio_direccion = 0; //determina cómo se inicia la bola tras cada punto ganado.
	inicio_y = 0;
	score = 0;
	seed = DIV_REG;
	EmpiezaJuego = 0;
	ball_pos_y = 0;
	seed |= (UINT16)DIV_REG << 8;
	initarand(seed);
	OBP0_REG = 0xE0;  //cambiar paleta de Gameboy para que el blanco no sea el color transparente.
	initarand(255); //inicia el RAND aleatorio.
	BGP_REG = 0x27U;
	REINICIAR_COORDENADAS();
	
	//fijar las puntuaciones a cero.
	incremento = 0;
	score_counter_p1 = 0;
	score_counter_p2 = 0;
	golpea = 0;
	Dificultad = 0;
	score = 0;
	Pausa = 0; //desactivado.
	//cargar los sprites.
	SPRITES_8x8;
	//activar fondos y sprites.
	SHOW_BKG;
	SHOW_SPRITES; 
	enable_interrupts();
	INIT_REGISTERS_SOUND_EFECTS();
}

void CARGAR_SPRITES(void){
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
	//flecha de selección PANTALLA_INICIO
	set_sprite_data(25, 1, spritetiles+400);

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
	
	
}

void SET_SPRITES(void){
	set_sprite_tile(7,2+(score_counter_p1*2)); //puntuacion player 1
	set_sprite_tile(8,3+(score_counter_p1*2)); //puntuacion player 1
	set_sprite_tile(9,2+(score_counter_p2*2)); // puntuacion CPU
	set_sprite_tile(10,3+(score_counter_p2*2)); // puntuacion CPU
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
	//paddle 1. Controlado por la CPU (doble)
	set_sprite_tile(28,0);
	set_sprite_tile(29,0);
	set_sprite_tile(30,0);
	//flecha SELECT
	set_sprite_tile(31,25);
}

void PANTALLA_INICIAL(void){
	score_counter_p1 = 0;
	score_counter_p2 = 0;
	i = 0;
	Dificultad = 0;
	do
{
		gotoxy(0, 0);
		puts(" \n");
		puts(" \n");
		puts(" \n");
		puts("    POCKET PONG\n\n\n");
		puts("    Normal mode\n");
		puts("   Hardcore mode");
		if (Dificultad == 0) move_sprite(31,28,96);	//pintar la flecha de la Dificultad
		else move_sprite(31,20,112);
		if (joypad() & J_SELECT){
			switch (Dificultad){
			case 0:
				Dificultad = 1;
				move_sprite(31,20,112);
			break;
			case 1:
				Dificultad = 0; //dificultad normal
				move_sprite(31,28,96);
			break;
		}
		delay(250);		
		}
		if (joypad() & J_START) {
			EmpiezaJuego = 1;
			switch (Dificultad){
				case 0: //normal
				for (i= 0; i<5; i++ ) {
					gotoxy(0, 0);
					puts(" \n");
					puts(" \n");
					puts(" \n");
					puts("    POCKET PONG\n\n\n");
					puts("                      \n");
					delay(140);
					gotoxy(0, 0);
					puts(" \n");
					puts(" \n");
					puts(" \n");
					puts("    POCKET PONG\n\n\n");
					puts("    Normal mode\n");
					delay(140);
				}	
				break;
				case 1:
				for (i= 0; i<5; i++ ) {
					gotoxy(0, 0);
					puts(" \n");
					puts(" \n");
					puts(" \n");
					puts("    POCKET PONG\n\n\n");
					puts("    Normal mode\n");
					puts("                 ");
					delay(140);
					gotoxy(0, 0);
					puts(" \n");
					puts(" \n");
					puts(" \n");
					puts("    POCKET PONG\n\n\n");
					puts("\n");
					puts("   Hardcore mode");
					delay(140);
				}
				break;	
		}
	}
} 
while (EmpiezaJuego != 1); //esperamos a que se haya pulsado start
move_sprite(31,0,0); //ocultamos la flecha.
LIMPIA_PANTALLA();
}

void INIT_REGISTERS_SOUND_EFECTS(void){
	NR52_REG = 0xF8U;
	NR51_REG = 0x00U;
	NR50_REG = 0x77U;
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
    NR41_REG = 0x00;
    NR42_REG = 0xE1;
    NR43_REG = 0x22;
    NR44_REG = 0xC3;
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

void REINICIAR_COORDENADAS(void){
	gotoxy(0,0);
	//pos inicial paddle0.
	y1 = 65;
	y2 = 73;
	y3 = 81;
	//pos inicial paddle1.
	y4 = 65;
	y5 = 73;
	y6 = 81;
	//pos inicial bola.
	do {
			inicio_y = rand();
			} while (inicio_y > 140);
			ball_pos_y	= inicio_y;
	ball_pos_x = 81;
	//inicializar el vector de movimiento.
	ball_vector_x1 = 2;
	ball_vector_y1 = 1;
	game_status = 0;
}

void CONTROLES(void){
presionado = joypad();	

		//reiniciar el juego (RESET) a la pantalla de título si pulsamos los 3 botones a la vez
		if((joypad() & J_A) && (joypad() & J_B) && (joypad() & J_SELECT))
		{	
				REINICIAR_COORDENADAS();
				score=0;
				incremento = 0;
				score_counter_p1 = 0;
				score_counter_p2 = 0;
				ball_vector_x1 = 2;
				ball_vector_y1 = 1;
				SPRITES_8x8;
				EmpiezaJuego = 0;
				OCULTAR_SPRITES();
				delay(500);
				SHOW_SPRITES;
				Dificultad = 0;
				PANTALLA_INICIAL();
				CARGAR_SPRITES();
				REPINTAR_SPRITES();
				
		}
			
		// movimiento del paddle 0.
		if(presionado & J_UP && y1>=21){
			y1-=2;
			y2-=2;
			y3-=2;
			if(presionado & J_A){
				y1-=3;
				y2-=3;
				y3-=3;
			}
		}
		if(presionado & J_DOWN && y3<=145){
			y1+=2;
			y2+=2;
			y3+=2;
			if(presionado & J_A){
				y1+=3;
				y2+=3;
				y3+=3;
			}
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
		
		if (presionado & J_START && game_status == 1){ //poner el juego en pausa pulsando START
				delay(250);
			waitpad(J_START);
			delay(250);	
			}		
}

void COLISIONES(void){
		//colisiones con paddle del jugador
		if(ball_pos_y >= (y1-8) && ball_pos_y <= (y3+8) && ball_pos_x <= 23){
			
			golpea=0;//golpea el jugador así que se mueve.
			PLAY_PADDLE_SOUND_EFFECT();
					ball_vector_x1 = 2;
					ball_vector_x1 += (incremento/6);		
					do { 
						ball_vector_y1 = (rand() % 5) -2;
					} while ((ball_vector_y1 < -2 || ball_vector_y1 > 2) || ball_vector_y1 == 0); //Y entre -2 y 2; 
				incremento++;
	
		}
	
		//colisiones con paddle CPU
		if(ball_pos_y >= (y4-8) && ball_pos_y <= (y6+8) && ball_pos_x >= 148){
			golpea=1;//golpea el CPU así que NO se mueve.
			PLAY_PADDLE_SOUND_EFFECT();
					ball_vector_x1 = -2;
					ball_vector_x1 -= (incremento/6); 
					do { 
						ball_vector_y1 = (rand() % 5) -2;
					} while ((ball_vector_y1 < -2 || ball_vector_y1 > 2 || ball_vector_y1 == 0)); //Y entre -2 y 2
				incremento++;
		}
		
		//colisiones con paddle EXTRA CPU
		if((ball_pos_y >= (y5-8) && ball_pos_y <= (y5+8)) && Dificultad == 1 && ball_pos_x >= 90 && ball_pos_x <= 93){
			golpea=1;//golpea el CPU así que NO se mueve.
			PLAY_PADDLE_SOUND_EFFECT();
					ball_vector_x1 = -2;
					ball_vector_x1 -= (incremento/6);
				
					do { 
						ball_vector_y1 = (rand() % 5) -2;
					} while ((ball_vector_y1 < -2 || ball_vector_y1 > 2 || ball_vector_y1 == 0)); //Y entre -2 y 2
				incremento++;
		}

		// pared izquierda. //CPU gana un punto.
		if(ball_pos_x<5){
			PLAY_UL_WALL_SOUND_EFFECT();
			REINICIAR_COORDENADAS();
			score_counter_p2++;
			incremento = 0;
			golpea = 0;
			gotoxy(0,0);
		}
		
		// pared derecha. //el jugador gana un punto.
		if(ball_pos_x>160){ 
			PLAY_UL_WALL_SOUND_EFFECT();
			REINICIAR_COORDENADAS();
			score_counter_p1++;
			incremento=0;
			golpea = 0;			
			gotoxy(0,0);
		}
		
		// pared superior.
		if(ball_pos_y < 21){
			ball_pos_y = 21;
			ball_vector_y1--;
			ball_vector_y1=ball_vector_y1 ^ 255;
			PLAY_LR_WALL_SOUND_EFFECT();
		}
		
		// pared inferior.
		if(ball_pos_y > 146){
			ball_pos_y = 146;
			ball_vector_y1--;
			ball_vector_y1=ball_vector_y1 ^ 255;
			PLAY_LR_WALL_SOUND_EFFECT();
		}
}

void MOVIMIENTO_BOLA(void){
		ball_pos_x+= ball_vector_x1;
		ball_pos_y+= ball_vector_y1;
}

void REPINTAR_SPRITES(void){
		//repintar sprite del paddle0 en función de su posición actual.
		move_sprite(0,15,y1);
		move_sprite(1,15,y2);
		move_sprite(2,15,y3);
		if (Dificultad == 1){
			//CPU comparte coordenadas con su otro paddle
			move_sprite(29,98,y5);
		}
		if (Dificultad == 0){
			move_sprite(28,0,0); //CPU extra fuera de la pantalla
			move_sprite(29,0,0);
			move_sprite(30,0,0);	
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
}

void FINAL_JUEGO(void){

	if(score_counter_p1 == 10 || score_counter_p2 == 10){ //fin del juego.
				HIDE_SPRITES;
				BGP_REG = 0x27U;
				score = ((score_counter_p1*100) - (score_counter_p2*9));
				if (score <= 0) score = 0;
				if (score_counter_p1 == 10){
					gotoxy(0,0);
					printf(" \n \n \n \n \n \n");
					printf("     YOU WIN\n\n");
					printf("     Score:%d", (UINT16)score);

				}
				if (score_counter_p2 == 10){
					gotogxy(0, 0);
					printf(" \n \n \n \n \n \n");
					printf("     YOU LOSE\n\n");
					printf("     Score:%d", (UINT16)score);
				}
				delay(4000);
				gotoxy(0, 0);
				printf(" \n \n \n \n \n \n");
				printf("                \n\n");
				printf("                  ");
				REINICIAR_COORDENADAS();
				score=0;
				incremento = 0;
				score_counter_p1 = 0;
				score_counter_p2 = 0;
				ball_vector_x1 = 2;
				ball_vector_y1 = 1;
				SPRITES_8x8;
				EmpiezaJuego = 0;
				Dificultad = 0;
				OCULTAR_SPRITES();
				SHOW_SPRITES;
				PANTALLA_INICIAL();
				CARGAR_SPRITES();
				REPINTAR_SPRITES();
	}
}

void INICIO_REINICIO(void){ //cuando empieza la partida o termina una.
if(game_status==0){
			//si el juego ha terminado, se reinicia.
			if(score_counter_p2 == 20 || score_counter_p1 == 20){
				score_counter_p2 = 0;
				score_counter_p1 = 0;
				incremento= 0;
				golpea = 0;
				score = 0;
			}	
			inicio_direccion = rand();
			
			if ( inicio_direccion <= 62){	//numero aleatorio para ver hacia dónde se dirige la bola.
				ball_vector_x1 = 1;
				ball_vector_y1 = 1;
				}
			else if (inicio_direccion > 62 && inicio_direccion <= 124){
				ball_vector_x1 = 1;
				ball_vector_y1 = -1;
				}
			else if (inicio_direccion > 124 && inicio_direccion <= 186){
				ball_vector_x1 = -1;
				ball_vector_y1 = 1;
				}
			else {
				ball_vector_x1 = -1;
				ball_vector_y1 = -1;
			}
			delay(350);
			wait_vbl_done();
			game_status = 1; //el juego comienza de nuevo.
		}	
}

void LIMPIA_PANTALLA(void) {
	gotoxy(0,0); 
      printf("\n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n \n");
    gotoxy(0,0);  
}

void OCULTAR_SPRITES(void) { //oculta todos los sprites menos la flecha para la pantalla de inicio.
	i = 0;
	for (i=0; i != 31; i++){
	move_sprite(i,0,0);	//asignamos coordenadas 0,0 a cada sprite.
	}
	wait_vbl_done();
}
