/*Pocket Pong by Boniato82
//
*/

#include <gb/gb.h>
#include <stdio.h>
#include <stdint.h>
#include <ctype.h>
#include <gbdk/console.h>
#include <gb/drawing.h>
#include <rand.h>
#include "gb/hardware.h"

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

//DATOS DE X_PONG
const unsigned char Sprites_Paddles[32] = { //32 elementos (separados por comas ",")
	//paddle izquierda-derecha
0x3c,0x42,0x3c,0x42,0x3c,0x42,0x3c,0x42,
0x3c,0x42,0x3c,0x42,0x3c,0x42,0x3c,0x42,
	//paddle arriba-abajo
0xff,0xff,0x00,0xff,0xff,0x00,0xff,0x00,
0xff,0x00,0xff,0x00,0xff,0x00,0x00,0xff,
};

const unsigned char Sprites_Bola[16] = {
0x7e,0x7e,0x7e,0x00,0x7e,0x00,0x7e,0x00,
0x7e,0x00,0x7e,0x00,0x7e,0x00,0x7c,0x7c
};

const unsigned char Sprites_Numeros[336] = {
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
0xff, 0xfc, 0xff, 0xfc, 0xff, 0xfc, 0xff, 0xfc
};

//Datos de SQUASH PONG
const unsigned char SP_Sprites_Paddles[32] = { //32 elementos (separados por comas ",")
	//paddle jugador
0xff,0xc3,0xff,0xc3,0xff,0xc3,0xff,0xc3,
0xff,0xc3,0xff,0xc3,0xff,0xc3,0xff,0xc3,
	//paddle cpu
0x00,0x3c,0x00,0x3c,0x00,0x3c,0x00,0x3c,
0x00,0x3c,0x00,0x3c,0x00,0x3c,0x00,0x3c
};
const unsigned char SP_Sprites_Numeros[320] = {
0xff, 0x00, 0xff, 0x00, 0xff, 0x3c, 0xff, 0x3c,
0xff, 0x3c, 0xff, 0x3c, 0xff, 0x3c, 0xff, 0x3c, 
0xff, 0x3c, 0xff, 0x3c, 0xff, 0x3c, 0xff, 0x3c,
0xff, 0x3c, 0xff, 0x3c, 0xff, 0x00, 0xff, 0x00,
//1 +32
0x18, 0x00, 0x18, 0x00, 0x18, 0x00, 0x18, 0x00,
0x18, 0x00, 0x18, 0x00, 0x18, 0x00, 0x18, 0x00,
0x18, 0x00, 0x18, 0x00, 0x18, 0x00, 0x18, 0x00,
0x18, 0x00, 0x18, 0x00, 0x18, 0x00, 0x18, 0x00,
//2 +64
0xff, 0x00, 0xff, 0x00, 0x03, 0x00, 0x03, 0x00,
0x03, 0x00, 0x03, 0x00, 0x83, 0x80, 0xff, 0x00,
0xff, 0x00, 0xc0, 0x00, 0xc0, 0x00, 0xc0, 0x00,
0xc0, 0x00, 0xc0, 0x00, 0xff, 0x00, 0xff, 0x00,
//3 +96
0xff, 0x00, 0xff, 0x00, 0x03, 0x00, 0x03, 0x00,
0x03, 0x00, 0x03, 0x00, 0x03, 0x00, 0xff, 0x00,
0xff, 0x00, 0x03, 0x00, 0x03, 0x00, 0x03, 0x00,
0x03, 0x00, 0x03, 0x00, 0xff, 0x00, 0xff, 0x00,
//4 +128
0xff, 0x3c, 0xff, 0x3c, 0xff, 0x3c, 0xff, 0x3c,
0xff, 0x3c, 0xff, 0x3c, 0xff, 0x3c, 0xff, 0x00,
0xff, 0x00, 0xff, 0xfc, 0xff, 0xfc, 0xff, 0xfc,
0xff, 0xfc, 0xff, 0xfc, 0xff, 0xfc, 0xff, 0xfc,
//5 +160
0xff, 0x00, 0xff, 0x00, 0xff, 0x3f, 0xff, 0x3f,
0xff, 0x3f, 0xff, 0x3f, 0xff, 0x3f, 0xff, 0x00,
0xff, 0x00, 0xff, 0xfc, 0xff, 0xfc, 0xff, 0xfc,
0xff, 0xfc, 0xff, 0xfc, 0xff, 0x00, 0xff, 0x00,
//6 +192
0xff, 0x01, 0xff, 0x01, 0xc1, 0x01, 0xc0, 0x00,
0xc0, 0x00, 0xc0, 0x00, 0xc0, 0x00, 0xff, 0x00,
0xff, 0x00, 0xc3, 0x00, 0xc3, 0x00, 0xc3, 0x00,
0xc3, 0x00, 0xe3, 0x20, 0xff, 0x00, 0xff, 0x00,
//7 +224
0xff, 0x00, 0xff, 0x00, 0x07, 0x04, 0x07, 0x04,
0x07, 0x04, 0x07, 0x04, 0x07, 0x04, 0x07, 0x04,
0x07, 0x04, 0x07, 0x04, 0x07, 0x04, 0x07, 0x04,
0x03, 0x00, 0x03, 0x00, 0x03, 0x00, 0x03, 0x00,
//8 +256
0xff, 0x00, 0xff, 0x00, 0xfb, 0x38, 0xc3, 0x00,
0xc3, 0x00, 0xc3, 0x00, 0xff, 0x3c, 0xff, 0x00,
0xff, 0x00, 0xc3, 0x00, 0xc3, 0x00, 0xc3, 0x00,
0xc3, 0x00, 0xc3, 0x00, 0xff, 0x00, 0xff, 0x00,
//9 +288
0xff, 0x00, 0xff, 0x00, 0xff, 0x3c, 0xff, 0x3c,
0xff, 0x3c, 0xff, 0x3c, 0xff, 0x3c, 0xff, 0x00,
0xff, 0x00, 0xff, 0xfc, 0xff, 0xfc, 0xff, 0xfc,
0xff, 0xfc, 0xff, 0xfc, 0xff, 0xfc, 0xff, 0xfc
};

//funciones comunes de todos los juegos
void PLAY_PADDLE_SOUND_EFFECT(void);
void PLAY_UL_WALL_SOUND_EFFECT(void);
void PLAY_LR_WALL_SOUND_EFFECT(void);
void INIT_REGISTERS_SOUND_EFECTS(void);
void LIMPIA_TEXTO(void);
void LIMPIA_TEXTO2(void);
void MENU_SELECCION_JUEGO(void);
void RESET_JUEGO(void);
void INTRO(void); //logo de Boniato82
void OCULTAR_SPRITES(void);
void PP_REINICIAR_COORDENADAS(void); // funciones del juego Pocket Pong.
void PP_COLISIONES(void);
void PP_CONTROLES(void);
void PP_CARGAR_ELEMENTOS(void);
void PP_CARGAR_SPRITES(void);
void PP_REPINTAR_SPRITES(void);
void PP_FINAL_JUEGO(void);
void PP_INICIO_REINICIO(void);
void PP_MOVIMIENTO_BOLA(void);
void PP_SET_SPRITES(void);
void PP_PANTALLA_INICIAL(void);
void X_REINICIAR_COORDENADAS(void); //funciones del juego X_Pong
void X_COLISIONES(void);
void X_CONTROLES(void);
void X_CARGAR_ELEMENTOS(void);
void X_CARGAR_SPRITES(void);
void X_REPINTAR_SPRITES(void);
void X_FINAL_JUEGO(void);
void X_INICIO_REINICIO(void);
void X_MOVIMIENTO_BOLA(void);
void X_SET_SPRITES(void);
void X_PANTALLA_INICIAL(void);
void SP_REINICIAR_COORDENADAS(void); //funciones del juego Squash Pong
extern void SP_COLISIONES(void);
extern void SP_CONTROLES(void);
extern void SP_CARGAR_ELEMENTOS(void);
extern void SP_CARGAR_SPRITES(void);
extern void SP_REPINTAR_SPRITES(void);
extern void SP_FINAL_JUEGO(void);
extern void SP_INICIO_REINICIO(void);
extern void SP_MOVIMIENTO_BOLA(void);
extern void SP_SET_SPRITES(void);
extern void SP_PANTALLA_INICIAL(void);


//variables comunes de todos los juegos
uint8_t ball_pos_x;
uint8_t ball_pos_y;
int8_t ball_vector_x1,ball_vector_y1;
uint8_t Pausa; 
uint8_t game_status;
uint8_t EmpiezaJuego;
uint8_t Dificultad; //dificultad de los juegos
uint8_t incremento; //incremento de la velocidad del vector x de la bola.
int8_t golpea; //determina quién ha golpeado la bola, para el movimiento de la CPU (si golpea ella no se mueve hasta que golpee el jugador)
uint8_t inicio_direccion; //determina la dirección de la bola tras cada punto ganado.
uint8_t inicio_y; //determina la posición Y de la bola tras cada punto ganado.
uint8_t i; //numero para los for
uint16_t seed; //semilla para numeros aleatorios.
uint8_t juego; //1 = Pocket Pong, 2=4x Pong, 3=Sqash Pong
uint8_t presionado; //para usar con los controles.

//variables globales del juego Pocket Pong
uint8_t SeleccionaJuego;
uint8_t Accion;
uint8_t y1,y2,y3,y4,y5,y6;
uint8_t PP_Paddle0_pos_x; //posicion x,y del paddle del jugador
uint8_t PP_Paddle0_pos_y;
uint8_t PP_Paddle1_pos_x;  //posicion x,y del paddle del CPU
uint8_t PP_Paddle1_pos_y;
uint16_t score_counter_p1;
uint16_t score_counter_p2;
uint16_t score;

//variables y constantes del juego X_Pong
const unsigned char Sprites_Paddles[32];
const unsigned char Sprites_Numeros[336];
const unsigned char Sprites_Bola[16];
const unsigned char Sprites_Flecha[16];
uint8_t x1,x2,x3; //coordenadas x de paddle arriba-abajo
uint8_t vidas; 
uint8_t Puntua1; //unidades
uint8_t Puntua2; //decenas
uint8_t Puntuacion_Final;
uint8_t golpeo_pala; //si golpeo la misma pala para ni repetir puntos (0=inicio juego, 1=norte, 2=sur, 3=este, 4=oeste)

//variables y constantes del juego Squash Pong
uint8_t presionado; //para usar con los controles.
uint8_t y1CPU,y2CPU; //coordenadas Paddle CPU
uint8_t xCPU;
uint8_t EmpiezaJuego;
uint8_t vidas; 
int8_t ball_vector_x1,ball_vector_y1;
uint8_t score_Player;
uint8_t score_CPU;
uint8_t inicio_direccion; //determina la dirección de la bola tras cada punto ganado.
uint8_t inicio_y; //determina la posición Y de la bola tras cada punto ganado.
uint8_t i; //numero para los for


void main(void){ //FUNCION PRINCIPAL, EL PROGRAMA EMPIEZA AQUI
	PP_CARGAR_ELEMENTOS();
	PP_CARGAR_SPRITES();
	PP_SET_SPRITES();
	INTRO();
	MENU_SELECCION_JUEGO();
	
}
void PP_CARGAR_ELEMENTOS(void){
	seed = 0;
	inicio_direccion = 0; //determina cómo se inicia la bola tras cada punto ganado.
	inicio_y = 0;
	seed = DIV_REG;
	Accion = 0;
	SeleccionaJuego = 0;
	ball_pos_y = 0;
	seed |= (uint16_t)DIV_REG << 8;
	initarand(seed);
	OBP0_REG = 0xE0;  //cambiar paleta de Gameboy para que el blanco no sea el color transparente.
	initarand(255); //inicia el RAND aleatorio.
	BGP_REG = 0x27U;
	PP_REINICIAR_COORDENADAS();
	
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

void PP_CARGAR_SPRITES(void){
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

}

void PP_SET_SPRITES(void){
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
	//flecha
	set_sprite_tile(31,25);
}
void MENU_SELECCION_JUEGO(void){	
	SeleccionaJuego=0;	
	juego = 1; //juego Pocket Pong por defecto
do
{
		gotoxy(0, 0);
		puts(" \n");
		puts("  SELECT YOUR GAME\n\n\n\n");
		puts("    Pocket Pong\n");
		puts("       4X Pong\n");
		puts("     Squash Pong");
		if (juego == 1) move_sprite(31,32,72);	//pintar la flecha de selección
		else if (juego == 2) move_sprite(31,56,88);
		else if (juego == 3) move_sprite(31,40,104);
		if (joypad() & J_DOWN){
			switch (juego){
			case 1:
				juego = 2; //cambia a 4x Pong
				move_sprite(31,56,88);
			break;
			case 2:
				juego = 3; //cambia a Sqash Pong
				move_sprite(31,40,104);
			break;			
		}
		delay(275);		
		}
		if (joypad() & J_UP){
			switch (juego){
			case 2:
				juego = 1; //cambia a Pocket Pong
				move_sprite(31,32,72);
			break;	
			case 3:
				juego = 2; //cambia a 4X Pong
				move_sprite(31,56,88);
			break;				
		}
		delay(275);		
		}
		if (joypad() & J_START || joypad() & J_A){
			SeleccionaJuego = 1;
				break;
		}
	}

while (SeleccionaJuego == 0); //esperamos a que se haya pulsado start
move_sprite(31,0,0); //ocultamos la flecha.
LIMPIA_TEXTO();

//seleccionamos el juego
switch (juego) {
			case 1: //Pocket Pong
				PP_CARGAR_ELEMENTOS();
				PP_CARGAR_SPRITES();
				PP_PANTALLA_INICIAL();
				
				while(1) {
					wait_vbl_done();	
					//color(BLACK, WHITE, SOLID);
					PP_Paddle0_pos_y = y2; //posiciones y de ambos paddles. 
					PP_Paddle1_pos_y = y5;	
					PP_SET_SPRITES();
					PP_CONTROLES();
					PP_FINAL_JUEGO();
					PP_INICIO_REINICIO();
					PP_MOVIMIENTO_BOLA();	
					PP_COLISIONES();
					PP_REPINTAR_SPRITES();	
					}
			break;
			case 2: //4X PONG
				X_PANTALLA_INICIAL();
				X_CARGAR_ELEMENTOS();
				X_CARGAR_SPRITES();
			while(1) {
					wait_vbl_done();
					X_SET_SPRITES();
					X_CONTROLES(); //Juego.c
					X_MOVIMIENTO_BOLA(); //Juego.c
					X_COLISIONES(); //Juego.c
					X_FINAL_JUEGO(); //Final.c
					X_INICIO_REINICIO(); //Final.c
					X_REPINTAR_SPRITES(); //Juego.c	
					} 
			break;	
			case 3: //SQUASH PONG
				SP_CARGAR_ELEMENTOS();
				SP_CARGAR_SPRITES();
				SP_PANTALLA_INICIAL();
				
			while(1) {
				wait_vbl_done();
				SP_SET_SPRITES();
				SP_CONTROLES(); //Juego.c
				SP_MOVIMIENTO_BOLA(); //Juego.c
				SP_COLISIONES(); //Juego.c
				SP_FINAL_JUEGO(); //Final.c
				SP_INICIO_REINICIO(); //Final.c
				SP_REPINTAR_SPRITES(); //Juego.c	 
				}
			break;			
		}

}

void PP_PANTALLA_INICIAL(void){
	Accion=0;	
	score_counter_p1 = 0;
	score_counter_p2 = 0;
	i = 0;
	Dificultad = 0; //modo classic por defecto
	do
{
		gotoxy(0, 0);
		puts(" \n");
		puts(" \n");
		puts("    POCKET PONG\n\n\n\n");
		puts("*------------------*");
		puts("| Classic  Hardcore|");
		puts("|     Ultimate     |");
		puts("*------------------*");
		if (Dificultad == 0) move_sprite(31,16,104);	//pintar la flecha de la Dificultad
		else if (Dificultad == 1) move_sprite(31,88,104);
		else if (Dificultad == 2) move_sprite(31,48,120);
		if (joypad() & J_RIGHT){
			Dificultad = 1; //cambia a hardcore
			move_sprite(31,88,104);	
			delay(275);		
		}
		if (joypad() & J_LEFT || joypad() & J_UP){
			Dificultad = 0; //cambia a classic
				move_sprite(31,16,104);	
				delay(275);	
		}
		if (joypad() & J_DOWN){
			Dificultad = 2; //cambia a ultimate
			move_sprite(31,48,120);
			delay(275);	
		}
		if (joypad() & J_SELECT){
			switch (Dificultad){
			case 0:
				Dificultad = 1; //cambia a hardcore
				move_sprite(31,88,104);
			break;
			case 1:
				Dificultad = 2; //cambia a ultimate
				move_sprite(31,48,120);
			break;
			case 2:
				Dificultad = 0; //cambia a classic
				move_sprite(31,16,104);
			break;
				
		}
		delay(275);		
		}
		if (joypad() & J_B) { //volver al menú de selección
		Accion = 0;
		juego = 1;
		SeleccionaJuego = 0;
		move_sprite(31,0,0); //ocultamos la flecha.
		LIMPIA_TEXTO();
		MENU_SELECCION_JUEGO();
		}
		if (joypad() & J_START || joypad() & J_A) {
			Accion = 1;
			switch (Dificultad){
				case 0: //classsic
				for (i= 0; i<5; i++ ) {
					gotoxy(0, 0);
					puts(" \n");
					puts(" \n");
					puts("    POCKET PONG\n\n\n\n");
					puts("                       ");
					puts("                       ");
					puts("                       ");
					puts("                       ");
					delay(140);
					gotoxy(0, 0);
					puts(" \n");
					puts(" \n");
					puts("    POCKET PONG\n\n\n\n\n\n");
					puts("  Classic");
					delay(140);
				}	
				break;
				case 1: //hardcore
				for (i= 0; i<5; i++ ) {
					gotoxy(0, 0);
					puts(" \n");
					puts(" \n");
					puts("    POCKET PONG\n\n\n\n");
					puts("                       ");
					puts("                       ");
					puts("                       ");
					puts("                       ");
					delay(140);
					gotoxy(0, 0);
					puts(" \n");
					puts(" \n");
					puts("    POCKET PONG\n\n\n\n\n\n");
					puts("           Hardcore");
					delay(140);
				}
				break;	
				case 2: //ultimate
				for (i= 0; i<5; i++ ) {
					gotoxy(0, 0);
					puts(" \n");
					puts(" \n");
					puts("    POCKET PONG\n\n\n\n");
					puts("                       ");
					puts("                       ");
					puts("                       ");
					puts("                       ");
					delay(140);
					gotoxy(0, 0);
					puts(" \n");
					puts(" \n");
					puts("    POCKET PONG\n\n\n\n\n\n");
					puts("                \n");
					puts("      Ultimate");
					delay(140);
				}
				break;
		}
	}
} 
while (Accion != 1); //esperamos a que se haya pulsado start
if (Dificultad == 2){ //si elegimos hardcore, CPU tiene ya 9 puntos de ventaja sobre 10.
score_counter_p2 = 9;
}
move_sprite(31,0,0); //ocultamos la flecha.
LIMPIA_TEXTO2();
}

void PP_REINICIAR_COORDENADAS(void){
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
			ball_pos_y = inicio_y;
	ball_pos_x = 81;
	//inicializar el vector de movimiento.
	ball_vector_x1 = 2;
	ball_vector_y1 = 1;
	game_status = 0;
}

void PP_CONTROLES(void){
presionado = joypad();	

		//reiniciar el juego (RESET) a la pantalla de título si pulsamos los 3 botones a la vez
		if(joypad() & J_A && joypad() & J_B && joypad() & J_SELECT && joypad() & J_START)
		{	
				PP_REINICIAR_COORDENADAS();
				score=0;
				incremento = 0;
				score_counter_p1 = 0;
				score_counter_p2 = 0;
				ball_vector_x1 = 2;
				ball_vector_y1 = 1;
				SPRITES_8x8;
				Accion = 0;
				OCULTAR_SPRITES();
				delay(750);
				SHOW_SPRITES;
				Dificultad = 0;
				PP_PANTALLA_INICIAL();
				PP_CARGAR_SPRITES();
				PP_REPINTAR_SPRITES();
				
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
				delay(275);
			waitpad(J_START);
			delay(275);	
			}		
}

void PP_COLISIONES(void){
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
			PP_REINICIAR_COORDENADAS();
			score_counter_p2++;
			incremento = 0;
			golpea = 0;
			gotoxy(0,0);
		}
		
		// pared derecha. //el jugador gana un punto.
		if(ball_pos_x>160){ 
			PLAY_UL_WALL_SOUND_EFFECT();
			PP_REINICIAR_COORDENADAS();
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

void PP_MOVIMIENTO_BOLA(void){
		ball_pos_x+= ball_vector_x1;
		ball_pos_y+= ball_vector_y1;
}

void PP_REPINTAR_SPRITES(void){
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

void PP_FINAL_JUEGO(void){

	if(score_counter_p1 == 10 || score_counter_p2 == 10){ //fin del juego.
				HIDE_SPRITES;
				BGP_REG = 0x27U;
				score = ((score_counter_p1*75) - (score_counter_p2*9));
				if (score <= 0) score = 0;
				if (score_counter_p1 == 10){
					gotoxy(0,0);
					printf(" \n \n \n \n \n \n");
					printf("     YOU WIN\n\n");
					printf("     Score:%d", score);

				}
				if (score_counter_p2 == 10){
					gotogxy(0, 0);
					printf(" \n \n \n \n \n \n");
					printf("     YOU LOSE\n\n");
					printf("     Score:%d", score);
				}
				delay(4000);
				gotoxy(0, 0);
				LIMPIA_TEXTO();
				PP_REINICIAR_COORDENADAS();
				score=0;
				incremento = 0;
				score_counter_p1 = 0;
				score_counter_p2 = 0;
				ball_vector_x1 = 2;
				ball_vector_y1 = 1;
				SPRITES_8x8;
				Accion = 0;
				Dificultad = 0;
				OCULTAR_SPRITES();
				SHOW_SPRITES;
				PP_PANTALLA_INICIAL();
				PP_CARGAR_SPRITES();
				PP_REPINTAR_SPRITES();
	}
}

void PP_INICIO_REINICIO(void){ //cuando empieza la partida o termina una.
if(game_status==0){
			//si el juego ha terminado, se reinicia.
			if(score_counter_p2 == 20 || score_counter_p1 == 20){
				score_counter_p2 = 0;
				score_counter_p1 = 0;
				incremento= 0;
				golpea = 0;
				Dificultad = 0;
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
			delay(375);
			wait_vbl_done();
			game_status = 1; //el juego comienza de nuevo.
		}	
}


//FUNCIONES ESPECIFICAS DE 4X PONG
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
void X_CARGAR_ELEMENTOS(void){
	seed = 0;
	inicio_direccion = 0; //determina cómo se inicia la bola tras cada punto ganado.
	inicio_y = 0;
	seed = DIV_REG;
	EmpiezaJuego = 0;
	vidas = 3;
	ball_pos_y = 70;
	seed |= (uint16_t)DIV_REG << 8;
	OBP0_REG = 0xE0;  //cambiar paleta de Gameboy para que el blanco no sea el color transparente.
	initarand(seed); //inicia el RAND aleatorio.
	BGP_REG = 0x27U;
	X_REINICIAR_COORDENADAS();
	
	//fijar las puntuaciones a cero.
	incremento = 0;
	Puntua1 = 0;
	Puntua2 = 0;
	golpea = 0;
	Dificultad = 0;
	Puntuacion_Final = 0;
	Pausa = 0; //desactivado.
	SPRITES_8x8;
	SHOW_SPRITES; 
	enable_interrupts();
	INIT_REGISTERS_SOUND_EFECTS();
}

void X_CARGAR_SPRITES(void){
	//paddle izquierda-derecha
	set_sprite_data(0, 1, Sprites_Paddles);
	//paddle arriba-abajo
	set_sprite_data(1, 1, Sprites_Paddles+16);
	//bola.
	set_sprite_data(2, 1, Sprites_Bola);
	//cargar los tiles de las puntuaciones. van a ir de 16 en 16, aunque cada número son 32
	set_sprite_data(4, 1, Sprites_Numeros); //numero 0
	set_sprite_data(5, 1, Sprites_Numeros+16);
	set_sprite_data(6, 1, Sprites_Numeros+32); //numero 1
	set_sprite_data(7, 1, Sprites_Numeros+48);
	set_sprite_data(8, 1, Sprites_Numeros+64); //numero 2 
	set_sprite_data(9, 1, Sprites_Numeros+80);
	set_sprite_data(10, 1, Sprites_Numeros+96); //numero 3
	set_sprite_data(11, 1, Sprites_Numeros+112);
	set_sprite_data(12, 1, Sprites_Numeros+128); //numero 4
	set_sprite_data(13, 1, Sprites_Numeros+144);
	set_sprite_data(14, 1, Sprites_Numeros+160); // numero 5
	set_sprite_data(15, 1, Sprites_Numeros+176);
	set_sprite_data(16, 1, Sprites_Numeros+192); //numero 6
	set_sprite_data(17, 1, Sprites_Numeros+208);
	set_sprite_data(18, 1, Sprites_Numeros+224); //numero 7
	set_sprite_data(19, 1, Sprites_Numeros+240);
	set_sprite_data(20, 1, Sprites_Numeros+256) ;//numero 8
	set_sprite_data(21, 1, Sprites_Numeros+272);
	set_sprite_data(22, 1, Sprites_Numeros+288); //numero 9
	set_sprite_data(23, 1, Sprites_Numeros+304);
}

void X_SET_SPRITES(void){
	//paddle izquierdo.
	set_sprite_tile(0,0);
	set_sprite_tile(1,0);
	set_sprite_tile(2,0);
	//paddle derecho. 
	set_sprite_tile(3,0);
	set_sprite_tile(4,0);
	set_sprite_tile(5,0);
	//paddle arriba.
	set_sprite_tile(6,1);
	set_sprite_tile(7,1);
	set_sprite_tile(8,1);
	//paddle abajo.
	set_sprite_tile(9,1);
	set_sprite_tile(10,1);
	set_sprite_tile(11,1);
	//bola.
	set_sprite_tile(12,2);
	
	set_sprite_tile(14,4+(Puntua2*2)); //puntuacion decenas
	set_sprite_tile(15,5+(Puntua2*2)); //puntuacion decenas
	set_sprite_tile(16,4+(Puntua1*2)); // puntuacion unidades
	set_sprite_tile(17,5+(Puntua1*2)); // puntuacion unidades
}


void X_PANTALLA_INICIAL(void){
	Accion = 0;		
	Puntua1 = 0;
	Puntua2 = 0;
	uint8_t a = 0;
	Dificultad = 0; //modo facil por defecto
do 
{
		gotoxy(0, 0);
		puts(" \n");
		puts(" \n");
		puts("      4X PONG\n\n\n\n");
		puts("*------------------*");
		puts("| Easy     Normal  |");
		puts("|     Hardcore     |");
		puts("*------------------*");
		if (Dificultad == 0)
		{
			move_sprite(31,16,104);	//pintar la flecha de la Dificultad
		}
		else if (Dificultad == 1) 
		{
			move_sprite(31,88,104);
		}
		else if (Dificultad == 2) 
		{
			move_sprite(31,48,120);
		}

		if (joypad() & J_RIGHT){
			Dificultad = 1; //cambia a normal
			move_sprite(31,88,104);	
			delay(275);		
		}
		if (joypad() & J_LEFT || joypad() & J_UP){
			Dificultad = 0; //cambia a easy
			move_sprite(31,16,104);
				delay(275);	
		}
		if (joypad() & J_DOWN){
			Dificultad = 2; //cambia a hardcore
			move_sprite(31,48,120);
			delay(275);	
		}		

		if (joypad() & J_SELECT){
			switch (Dificultad){
			case 0:
				Dificultad = 1; //cambia a normal
				move_sprite(31,88,104);
			break;
			case 1:
				Dificultad = 2; //cambia a hardcore
				move_sprite(31,48,120);
			break;
			case 2:
				Dificultad = 0; //cambia a easy
				move_sprite(31,16,104);
			break;
				
		}
		delay(275);
		}
		if (joypad() & J_B) { //volver al menú de selección
		Accion = 0;
		juego = 1;
		SeleccionaJuego = 0;
		move_sprite(31,0,0); //ocultamos la flecha.
		LIMPIA_TEXTO();
		MENU_SELECCION_JUEGO();
		}
		if (joypad() & J_START || joypad() & J_A) {
			EmpiezaJuego = 1;
			switch (Dificultad){
				case 0: //easy
				for (a= 0; a<5; a++ ) {
					gotoxy(0, 0);
					puts(" \n");
					puts(" \n");
					puts("      4X PONG\n\n\n\n");
					puts("                       ");
					puts("                       ");
					puts("                       ");
					puts("                       ");
					delay(140);
					gotoxy(0, 0);
					puts(" \n");
					puts(" \n");
					puts("      4X PONG\n\n\n\n\n\n");
					puts("  Easy");
					delay(140);
				}	
				break;
				case 1: //normal
				for (a= 0; a<5; a++ ) {
					gotoxy(0, 0);
					puts(" \n");
					puts(" \n");
					puts("      4X PONG\n\n\n\n");
					puts("                       ");
					puts("                       ");
					puts("                       ");
					puts("                       ");
					delay(140);
					gotoxy(0, 0);
					puts(" \n");
					puts(" \n");
					puts("      4X PONG\n\n\n\n\n\n");
					puts("           Normal");
					delay(140);
				}
				break;	
				case 2: //hardcore
				for (a= 0; a<5; a++ ) {
					gotoxy(0, 0);
					puts(" \n");
					puts(" \n");
					puts("      4X PONG\n\n\n\n");
					puts("                       ");
					puts("                       ");
					puts("                       ");
					puts("                       ");
					delay(140);
					gotoxy(0, 0);
					puts(" \n");
					puts(" \n");
					puts("      4X PONG\n\n\n\n\n\n");
					puts("                \n");
					puts("      Hardcore");
					delay(140);
				}
				break;
		}
	}
} 
while (EmpiezaJuego != 1); //esperamos a que se haya pulsado start

move_sprite(31,0,0); //ocultamos la flecha.
LIMPIA_TEXTO();
}

void X_REINICIAR_COORDENADAS(void){
	gotoxy(0,0);
	//pos inicial paddles izquierda-derecha
	y1 = 65;
	y2 = 73;
	y3 = 81;
	//pos inicial paddles arriba-abajo
	x1 =70;
	x2 =78;
	x3 =86;
	//pos inicial bola.
	ball_pos_y = 72;
	ball_pos_x = 81;
	//inicializar el vector de movimiento.
	ball_vector_x1 = (rand() % 3) -1; //entre 1 y -1 
	ball_vector_y1 = (rand() % 3) -1;
	
	game_status = 0;
}

void X_CONTROLES(void){
presionado = joypad();
		
		// movimiento del paddle izquierda - derecha.
		if(presionado & J_UP && y1>=22){
			y1-=2;
			y2-=2;
			y3-=2;
			if(presionado & J_A){
				y1-=3;
				y2-=3;
				y3-=3;
			}
		}
		if(presionado & J_DOWN && y3<=143){
			y1+=2;
			y2+=2;
			y3+=2;
			if(presionado & J_A){
				y1+=3;
				y2+=3;
				y3+=3;
			}
			}
	
		// movimiento del paddle arriba - abajo.
		if(presionado & J_LEFT && x1>=23){
			x1-=2;
			x2-=2;
			x3-=2;
			if(presionado & J_A){
				x1-=3;
				x2-=3;
				x3-=3;
			}
		}
		if(presionado & J_RIGHT && x3<=145){
			x1+=2;
			x2+=2;
			x3+=2;
			if(presionado & J_A){
				x1+=3;
				x2+=3;
				x3+=3;
			}
			}

		
		if (presionado & J_START && game_status == 1){ //poner el juego en pausa pulsando START
				delay(275);
			waitpad(J_START);
			delay(275);	
			}		
}

void X_COLISIONES(void){
		//colisiones con paddle izquierdo
		if(ball_pos_y >= (y1-8) && ball_pos_y <= (y3+8) && ball_pos_x <= 23){
			PLAY_PADDLE_SOUND_EFFECT();
					do { 
						ball_vector_y1 = (rand() % 3) -1; // numeros entre -1 y 1 
					} while (ball_vector_y1 == 0); //Y entre -1 y 1; 					
					if (Dificultad ==0) ball_vector_x1 = 1;
					else if (Dificultad ==1) ball_vector_x1 = 2; 				
					else if (Dificultad ==2) ball_vector_x1 = 2 +(incremento/50);		
					
				incremento++;
		if (golpeo_pala != 4){
		Puntua1++;	
		if (Puntua1 > 9){
			Puntua1 = 0;
			Puntua2++;
		}
		Puntuacion_Final++;
		}
		golpeo_pala=4;
		}
	
		//colisiones con paddle derecho
		if(ball_pos_y >= (y1-8) && ball_pos_y <= (y3+8) && ball_pos_x >= 146){
			PLAY_PADDLE_SOUND_EFFECT();
					do { 
						ball_vector_y1 = (rand() % 3) -1;  // numeros entre -1 y 1 
					} while (ball_vector_y1 == 0); //Y entre -2 y 2; 					
					if (Dificultad ==0) ball_vector_x1 = -1;
					else if (Dificultad ==1) ball_vector_x1 = -2;
					else if (Dificultad ==2) ball_vector_x1 = -2 -(incremento/50); 
					
				incremento++;
		if (golpeo_pala != 3){
		Puntua1++;
		
		if (Puntua1 > 9){
			Puntua1 = 0;
			Puntua2++;
		}
		Puntuacion_Final++;
		}
		golpeo_pala=3;
		}
		
		//colisiones con paddle arriba
		if(ball_pos_x >= (x1-8) && ball_pos_x <= (x3+8) && ball_pos_y <= 28){
			PLAY_PADDLE_SOUND_EFFECT();
					do { 
						ball_vector_x1 = (rand() % 3) -1;  // numeros entre -1 y 1 
					} while (ball_vector_x1 == 0); //x entre -2 y 2
					if (Dificultad ==0) ball_vector_y1 = 1;
					else if (Dificultad ==1)  ball_vector_y1 = 2;
					else if (Dificultad ==2) ball_vector_y1 = 2 +(incremento/50); 
			
				incremento++;
				
		if (golpeo_pala != 1){
		Puntua1++;
		if (Puntua1 > 9){
			Puntua1 = 0;
			Puntua2++;
		}
		Puntuacion_Final++;
		}
		golpeo_pala=1;
		}
		
		
		//colisiones con paddle abajo
		if(ball_pos_x >= (x1-8) && ball_pos_x <= (x3+8) && ball_pos_y >= 140){
			PLAY_PADDLE_SOUND_EFFECT();
					do { 
						ball_vector_x1 = (rand() % 3) -1;  // numeros entre -1 y 1 
					} while (ball_vector_x1 == 0); //x entre -2 y 2					
					if (Dificultad ==0) ball_vector_y1 = -1;
					else if (Dificultad ==1)  ball_vector_y1 = -2;
					else if (Dificultad == 2) ball_vector_y1 = -2 -(incremento/50); 
					
				incremento++;
				
		if (golpeo_pala != 2){
		Puntua1++;
		
		if (Puntua1 > 9){
			Puntua1 = 0;
			Puntua2++;
		}
		Puntuacion_Final++;
		}
		golpeo_pala=2;
		}

		// pared izquierda. pierdes
		if(ball_pos_x<4){
			PLAY_UL_WALL_SOUND_EFFECT();
			X_REINICIAR_COORDENADAS();
			vidas--;
			incremento = 0;
			golpea = 0;
			gotoxy(0,0);
		}
		
		// pared derecha. 
		if(ball_pos_x>168){ 
			PLAY_UL_WALL_SOUND_EFFECT();
			X_REINICIAR_COORDENADAS();
			vidas--;
			incremento=0;
			golpea = 0;			
			gotoxy(0,0);
		}
		
		// pared superior.
		if(ball_pos_y < 4){
			PLAY_UL_WALL_SOUND_EFFECT();
			X_REINICIAR_COORDENADAS();
			vidas--;
			incremento = 0;
			golpea = 0;
			gotoxy(0,0);
		}
		
		// pared inferior.
		if(ball_pos_y > 152){
			PLAY_UL_WALL_SOUND_EFFECT();
			X_REINICIAR_COORDENADAS();
			vidas--;
			incremento = 0;
			golpea = 0;
			gotoxy(0,0);
		}
}

void X_MOVIMIENTO_BOLA(void){
		ball_pos_x+= ball_vector_x1;
		ball_pos_y+= ball_vector_y1;
}

void X_REPINTAR_SPRITES(void){
		//repintar sprite del paddle izquierdo en función de su posición actual.
		move_sprite(0,13,y1); 
		move_sprite(1,13,y2);
		move_sprite(2,13,y3);
		//repintar sprite del paddle derecho en función de su posición actual.
		move_sprite(3,155,y1);
		move_sprite(4,155,y2);
		move_sprite(5,155,y3);
		//repintar sprite del paddle arriba en función de su posición actual.
		move_sprite(6,x1,20);
		move_sprite(7,x2,20);
		move_sprite(8,x3,20);
		//repintar sprite del paddle abajo en función de su posición actual.
		move_sprite(9,x1,145);
		move_sprite(10,x2,145);
		move_sprite(11,x3,145);
		////repintar bola en función de su posición actual.
		move_sprite(12,ball_pos_x,ball_pos_y);
		//repintar puntuaciones.
		move_sprite(14,76,74);
		move_sprite(15,76,82);
		move_sprite(16,87,74);
		move_sprite(17,87,82);
		gotoxy(0,0); //texto con las vidas
		printf("\n\n\n\n\n\n\n\n\n\n");
		printf("      Lives:%u", vidas);
	
}



void X_FINAL_JUEGO(void){

	if(Puntuacion_Final == 100 || vidas == 0){ //fin del juego.
				BGP_REG = 0x27U;
				if (Puntuacion_Final == 100){
					gotoxy(0,0);
					printf(" \n \n \n \n \n");
					printf("        WOW!\n");
					printf(" YOU HAVE MADE IT!\n\n");

				}
				if (vidas == 0){
					X_REPINTAR_SPRITES(); //pintamos los sprites para que score sea actualizado
					move_sprite(12,0,0); //ocultamos la bola
					puts("\n");
					puts("      YOU LOSE");
				}
				delay(4000);
				X_REINICIAR_COORDENADAS();
				Puntuacion_Final=0;
				incremento = 0;
				Puntua1 = 0;
				Puntua2 = 0;
				ball_vector_x1 = 2;
				ball_vector_y1 = 1;
				SPRITES_8x8;
				EmpiezaJuego = 0;
				Dificultad = 0;
				vidas = 3;
				OCULTAR_SPRITES();
				LIMPIA_TEXTO();
				SHOW_SPRITES;
				X_PANTALLA_INICIAL();
				X_CARGAR_SPRITES();
				X_REPINTAR_SPRITES();
	}
}

void X_INICIO_REINICIO(void){ //cuando empieza la partida o termina una.
if(game_status==0){
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
			delay(375);
			wait_vbl_done();
			game_status = 1; //el juego comienza de nuevo.
		}	
}

//FUNCIONES ESPECIFICAS DE SQUASH PONG
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
void SP_CARGAR_ELEMENTOS(void){
	seed = 0;
	inicio_direccion = 0; //determina cómo se inicia la bola tras cada punto ganado.
	inicio_y = 0;
	seed = DIV_REG;
	EmpiezaJuego = 0;
	vidas = 3;
	golpea = 0;
	ball_pos_y = 70;
	seed |= (uint16_t)DIV_REG << 8;
	OBP0_REG = 0xE0;  //cambiar paleta de Gameboy para que el blanco no sea el color transparente.
	initarand(seed); //inicia el RAND aleatorio.
	BGP_REG = 0x27U;
	SP_REINICIAR_COORDENADAS();
	
	//fijar las puntuaciones a cero.
	incremento = 0;
	score_Player = 0;
	score_CPU = 0;
	golpea = 0;
	Dificultad = 0;
	Puntuacion_Final = 0;
	Pausa = 0; //desactivado.
	SPRITES_8x8;
	SHOW_SPRITES; 
	enable_interrupts();
	INIT_REGISTERS_SOUND_EFECTS();
}

void SP_CARGAR_SPRITES(void){
	//paddle jugador
	set_sprite_data(0, 1, SP_Sprites_Paddles);
	//paddle CPU
	set_sprite_data(1, 1, SP_Sprites_Paddles+16);
	//bola.
	set_sprite_data(2, 1, Sprites_Bola);
	//cargar los tiles de las puntuaciones. van a ir de 16 en 16, aunque cada número son 32
	set_sprite_data(4, 1, SP_Sprites_Numeros); //numero 0
	set_sprite_data(5, 1, SP_Sprites_Numeros+16);
	set_sprite_data(6, 1, SP_Sprites_Numeros+32); //numero 1
	set_sprite_data(7, 1, SP_Sprites_Numeros+48);
	set_sprite_data(8, 1, SP_Sprites_Numeros+64); //numero 2 
	set_sprite_data(9, 1, SP_Sprites_Numeros+80);
	set_sprite_data(10, 1, SP_Sprites_Numeros+96); //numero 3
	set_sprite_data(11, 1, SP_Sprites_Numeros+112);
	set_sprite_data(12, 1, SP_Sprites_Numeros+128); //numero 4
	set_sprite_data(13, 1, SP_Sprites_Numeros+144);
	set_sprite_data(14, 1, SP_Sprites_Numeros+160); // numero 5
	set_sprite_data(15, 1, SP_Sprites_Numeros+176);
	set_sprite_data(16, 1, SP_Sprites_Numeros+192); //numero 6
	set_sprite_data(17, 1, SP_Sprites_Numeros+208);
	set_sprite_data(18, 1, SP_Sprites_Numeros+224); //numero 7
	set_sprite_data(19, 1, SP_Sprites_Numeros+240);
	set_sprite_data(20, 1, SP_Sprites_Numeros+256) ;//numero 8
	set_sprite_data(21, 1, SP_Sprites_Numeros+272);
	set_sprite_data(22, 1, SP_Sprites_Numeros+288); //numero 9
	set_sprite_data(23, 1, SP_Sprites_Numeros+304);
}

void SP_SET_SPRITES(void){
	//paddle jugador.
	set_sprite_tile(0,0);
	set_sprite_tile(1,0);
	//paddle CPU
	set_sprite_tile(2,1);
	set_sprite_tile(3,1);
	//bola.
	set_sprite_tile(4,2);
	//flecha SELECT
	set_sprite_tile(5,3);
	if (Dificultad == 0){
	//puntuacion
	set_sprite_tile(7,4+(score_Player*2)); //puntuacion player 1
	set_sprite_tile(8,5+(score_Player*2)); //puntuacion player 1
	set_sprite_tile(9,4+(score_CPU*2)); // puntuacion CPU
	set_sprite_tile(10,5+(score_CPU*2)); // puntuacion CPU
	}
	else{
	set_sprite_tile(7,4+(Puntua2*2)); //puntuacion decenas
	set_sprite_tile(8,5+(Puntua2*2)); //puntuacion decenas
	set_sprite_tile(9,4+(Puntua1*2)); // puntuacion unidades
	set_sprite_tile(10,5+(Puntua1*2)); // puntuacion unidades
		
	}
		
}

void SP_PANTALLA_INICIAL(void){
	score_Player = 0;
	score_CPU = 0;
	uint8_t a = 0;
	Dificultad = 0; //modo facil por defecto
do 
{
		gotoxy(0, 0);
		puts(" \n");
		puts(" \n");
		puts("    SQUASH PONG\n\n\n\n");
		puts("*------------------*");
		puts("| Vs CPU     Solo  |");
		puts("*------------------*");
		if (Dificultad == 0)
		{
			move_sprite(31,16,104);	//pintar la flecha de la Dificultad
		}
		else if (Dificultad == 1) 
		{
			move_sprite(31,104,104);
		}

		if (joypad() & J_RIGHT){
			Dificultad = 1; //cambia a Hard
				move_sprite(31,104,104);
				delay(275);
				}

		if (joypad() & J_LEFT){
				Dificultad = 0; //cambia a Normal
				move_sprite(31,16,104);
				delay(275);
				}

		if (joypad() & J_B) { //volver al menú de selección
		Accion = 0;
		juego = 1;
		SeleccionaJuego = 0;
		move_sprite(31,0,0); //ocultamos la flecha.
		LIMPIA_TEXTO();
		MENU_SELECCION_JUEGO();
		}
		if (joypad() & J_START || joypad() & J_A) {
			EmpiezaJuego = 1;
			switch (Dificultad){
				case 0: //easy
				for (a= 0; a<5; a++ ) {
					gotoxy(0, 0);
					puts(" \n");
					puts(" \n");
					puts("    SQUASH PONG\n\n\n\n");
					puts("                       ");
					puts("                       ");
					puts("                       ");
					puts("                       ");
					delay(140);
					gotoxy(0, 0);
					puts(" \n");
					puts(" \n");
					puts("    SQUASH PONG\n\n\n\n\n\n");
					puts("  Vs CPU");
					delay(140);
				}	
				break;
				case 1: //normal
				for (a= 0; a<5; a++ ) {
					gotoxy(0, 0);
					puts(" \n");
					puts(" \n");
					puts("    SQUASH PONG\n\n\n\n");
					puts("                       ");
					puts("                       ");
					puts("                       ");
					puts("                       ");
					delay(140);
					gotoxy(0, 0);
					puts(" \n");
					puts(" \n");
					puts("    SQUASH PONG\n\n\n\n\n\n");
					puts("             Solo");
					delay(140);
				}
				break;	
		}
	}
} 
while (EmpiezaJuego != 1); //esperamos a que se haya pulsado start

move_sprite(31,0,0); //ocultamos la flecha.
LIMPIA_TEXTO();
}

void SP_REPINTAR_SPRITES(void){
		//repintar sprite del paddle jugador en función de su posición actual.
		move_sprite(0,13,y1); 
		move_sprite(1,13,y2);
		////repintar bola en función de su posición actual.
		move_sprite(4,ball_pos_x,ball_pos_y);
		//repintar sprite del paddle cpu en función de su posición actual.	
		if (Dificultad == 0){
			move_sprite(2,13-xCPU,y1CPU);
			move_sprite(3,13-xCPU,y2CPU);
			//repintar puntuaciones.
			move_sprite(7,80,27);
			move_sprite(8,80,35);
			move_sprite(9,80,108);
			move_sprite(10,80,116);
			gotoxy(0,0); //texto con las vidas
			printf("\n\n\n\n");
			printf("       Player");
			printf("\n\n\n\n\n\n\n\n\n\n");
			printf("        CPU");
		}
		else if (Dificultad == 1){
		//repintar puntuaciones.
			move_sprite(7,76,74);
			move_sprite(8,76,82);
			move_sprite(9,87,74);
			move_sprite(10,87,82);
			gotoxy(0,0); //texto con las vidas
			printf("\n\n\n\n\n\n\n\n\n\n");
			printf("      Lives:%u", vidas);
		}
}

void SP_CONTROLES(void){
presionado = joypad();	

		//reiniciar el juego (RESET) a la pantalla de título si pulsamos los 3 botones a la vez
		if((joypad() & J_A) && (joypad() & J_B) && (joypad() & J_SELECT))
		{	
				SP_REINICIAR_COORDENADAS();
				Puntuacion_Final=0;
				incremento = 0;
				score_Player = 0;
				score_CPU = 0;
				ball_vector_x1 = 2;
				ball_vector_y1 = 1;
				SPRITES_8x8;
				EmpiezaJuego = 0;
				vidas = 3;
				OCULTAR_SPRITES();
				delay(750);
				LIMPIA_TEXTO();
				SHOW_SPRITES;
				Dificultad = 0;
				SP_PANTALLA_INICIAL();
				SP_CARGAR_SPRITES();
				SP_REPINTAR_SPRITES();
				
		}
			
		// movimiento del paddle izquierda - derecha.
		if(presionado & J_UP && y1>=22){
			y1-=2;
			y2-=2;
			if(presionado & J_A){
				y1-=3;
				y2-=3;
			}
		}
		if(presionado & J_DOWN && y2<=143){
			y1+=2;
			y2+=2;
			if(presionado & J_A){
				y1+=3;
				y2+=3;
			}
			}
		if (Dificultad == 0){ //si jugamos modo Vs. CPU
			// movimiento del paddle CPU respecto a la bola
			if (golpea == 0){
				if(y2CPU > ball_pos_y && y1CPU >= 21){
					y1CPU-=2;
					y2CPU-=2;
				}
				else if(y2CPU < ball_pos_y && y2CPU <= 145){
					y1CPU+=2;
					y2CPU+=2;
				}
			}
			else if (golpea == 1 && ball_pos_x <= 80){
				if(y2CPU > ball_pos_y && y1CPU >= 21){
					y1CPU+=2;
					y2CPU+=2;
				}
				else if(y2CPU < ball_pos_y && y2CPU <= 145){
					y1CPU-=2;
					y2CPU-=2;
				}
			
			}
		}
		//poner el juego en pausa pulsando START
		if (presionado & J_START && game_status == 1){ 
				delay(275);
			waitpad(J_START);
			delay(275);	
			}		
}

void SP_MOVIMIENTO_BOLA(void){
		ball_pos_x += ball_vector_x1;
		ball_pos_y += ball_vector_y1;
}

void SP_COLISIONES(void){
		//colisiones con paddle jugador
		if (Dificultad == 0){
			if(golpea == 1 && ball_pos_y >= (y1-8) && ball_pos_y <= (y2+8) && ball_pos_x <= 23){
				PLAY_PADDLE_SOUND_EFFECT();
						if (Dificultad ==0) ball_vector_x1 = 2;
						else if (Dificultad ==1) ball_vector_x1 = 2;
						ball_vector_x1 += (incremento/5);					
						if (ball_vector_x1 < 4){
						do { 
							ball_vector_y1 = (rand() % 5) -2;
						} while ((ball_vector_y1 < -2 || ball_vector_y1 > 2) || ball_vector_y1 == 0); //Y entre -2 y 2; 
						}
						else if (ball_vector_x1 > 4){
						do { 
							ball_vector_y1 = (rand() % 9) -4;
						} while ((ball_vector_y1 < -4 || ball_vector_y1 > 4 || ball_vector_y1 == 0)); //Y entre -2 y 2
						}
					incremento++;
				golpea = 0; //golpea el jugador, CPU se mueve.
				xCPU = 0;
			}
		}
		else if (Dificultad == 1){
			if(ball_pos_y >= (y1-8) && ball_pos_y <= (y2+8) && ball_pos_x <= 23){
				PLAY_PADDLE_SOUND_EFFECT();
						ball_vector_x1 = 2;
						ball_vector_x1 += (incremento/5);					
						if (ball_vector_x1 < 4){
						do { 
							ball_vector_y1 = (rand() % 5) -2;
						} while ((ball_vector_y1 < -2 || ball_vector_y1 > 2) || ball_vector_y1 == 0); //Y entre -2 y 2; 
						}
						else if (ball_vector_x1 > 4){
						do { 
							ball_vector_y1 = (rand() % 9) -4;
						} while ((ball_vector_y1 < -4 || ball_vector_y1 > 4 || ball_vector_y1 == 0)); //Y entre -2 y 2
						}
					incremento++;
					Puntuacion_Final++;
					Puntua1++;
					if (Puntua1 > 9){
						Puntua1 = 0;
						Puntua2++;
					}
				golpea = 0; //golpea el jugador, CPU se mueve.
				xCPU = 0;
			}
		}
	
		//colisiones con paddle CPU
		if (Dificultad == 0){
			if(golpea == 0){ 
				if (ball_pos_y >= (y1CPU-8) && ball_pos_y <= (y2CPU+8) && ball_pos_x <= 23){
				PLAY_PADDLE_SOUND_EFFECT();
						if (Dificultad ==0) ball_vector_x1 = 2;
						else if (Dificultad ==1) ball_vector_x1 = 2;
						ball_vector_x1 += (incremento/5);
						if (ball_vector_x1 < 4){
						do { 
							ball_vector_y1 = (rand() % 5) -2;
						} while ((ball_vector_y1 < -2 || ball_vector_y1 > 2 || ball_vector_y1 == 0)); //Y entre -2 y 2
						}
						else if (ball_vector_x1 > 4){
						do { 
							ball_vector_y1 = (rand() % 9) -4;
						} while ((ball_vector_y1 < -4 || ball_vector_y1 > 4 || ball_vector_y1 == 0)); //Y entre -2 y 2
						}
					incremento++;
				golpea = 1; //golpea el CPU y no se mueve más hasta que sea 0
			}
			}
			if(golpea == 1){
			
			
			}
			
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

		
		// pared derecha. 
		if(ball_pos_x>160){ 
			ball_pos_x = 160;
			ball_vector_x1--;
			ball_vector_x1=ball_vector_x1 ^ 255;
			PLAY_LR_WALL_SOUND_EFFECT();
		}
		
		// pared superior.
		if(ball_pos_y < 10){
			PLAY_UL_WALL_SOUND_EFFECT();
			SP_REINICIAR_COORDENADAS();
			vidas--;
			incremento = 0;
			gotoxy(0,0);
		}
		//pared izquierda (punto)
		if(ball_pos_x<5){
			PLAY_UL_WALL_SOUND_EFFECT();
			SP_REINICIAR_COORDENADAS();
			if (Dificultad == 0)
			{
				if (golpea == 0) score_Player++;
				else score_CPU++;
			}
			else if (Dificultad == 1)
				vidas--;
			incremento = 0;
			gotoxy(0,0);
		}
	
}

void SP_REINICIAR_COORDENADAS(void){
	gotoxy(0,0);
	//pos inicial paddle jugador	
	y1 = 65;
	y2 = 73;
	//pos inicial paddle CPU
		y1CPU = 30;
		y2CPU = 38;
		uint8_t xCPU = 0;

	//pos inicial bola.
	ball_pos_y = 80;
	ball_pos_x = 50;
	//inicializar el vector de movimiento.
	ball_vector_x1 = 3; 
	ball_vector_y1 = (rand() % 5) -2;
	
	game_status = 0;
}

void SP_INICIO_REINICIO(void){ //cuando empieza la partida o termina una.
if(game_status==0){
			ball_vector_x1 = 3;
			delay(375);
			wait_vbl_done();
			game_status = 1; //el juego comienza de nuevo.
		}	
}

void SP_FINAL_JUEGO(void){
	if (Dificultad == 0) //si juegas contra la CPU
	{
		if(score_Player == 10 || score_CPU == 10){ //fin del juego.
				HIDE_SPRITES;
				BGP_REG = 0x27U;
				if (score_Player == 10){
					gotoxy(0,0);
					printf(" \n \n \n \n \n \n");
					printf("     YOU WIN\n\n");

				}
				if (score_CPU == 10){
					gotogxy(0, 0);
					printf(" \n \n \n \n \n \n");
					printf("     YOU LOSE\n\n");
				}
				delay(4000);
				gotoxy(0, 0);
				printf(" \n \n \n \n \n \n");
				printf("                \n\n");
				printf("                  ");
				SP_REINICIAR_COORDENADAS();
				incremento = 0;
				score_Player = 0;
				score_CPU = 0;
				ball_vector_x1 = 2;
				ball_vector_y1 = 1;
				SPRITES_8x8;
				EmpiezaJuego = 0;
				Dificultad = 0;
				OCULTAR_SPRITES();
				LIMPIA_TEXTO();
				SHOW_SPRITES;
				SP_PANTALLA_INICIAL();
				SP_CARGAR_SPRITES();
				SP_REPINTAR_SPRITES();				
	}
	
	
	}
	else {
	if(Puntuacion_Final == 100 || vidas == 0){ //si juegas solo
				BGP_REG = 0x27U;
				if (Puntuacion_Final == 100){
					gotoxy(0,0);
					printf(" \n \n \n \n \n");
					printf("        WOW!\n");
					printf(" YOU HAVE MADE IT!\n\n");

				}
				if (vidas == 0){
					SP_REPINTAR_SPRITES(); //pintamos los sprites para que score sea actualizado
					gotogxy(0, 0);
					printf("\n      YOU LOSE");
				}
				delay(4000);
				gotoxy(0, 0);
				printf(" \n \n \n \n \n");
				printf("                \n\n");
				printf("                    ");
				printf("                    ");
				printf("                    ");
				printf("                    ");
				SP_REINICIAR_COORDENADAS();
				Puntuacion_Final=0;
				incremento = 0;
				score_Player = 0;
				score_CPU = 0;
				Puntua1 = 0;
				Puntua2 = 0;
				ball_vector_x1 = 2;
				ball_vector_y1 = 1;
				SPRITES_8x8;
				EmpiezaJuego = 0;
				Dificultad = 0;
				vidas = 3;
				OCULTAR_SPRITES();
				LIMPIA_TEXTO();
				SHOW_SPRITES;
				SP_PANTALLA_INICIAL();
				SP_CARGAR_SPRITES();
				SP_REPINTAR_SPRITES();	
	}
	}
}



//FUNCIONES COMUNES
////////////////////////////////////////
///////////////////////////////////////
////////////////////////////////////////
///////////////////////////////////////
//////////////////////////////////////
void INTRO(void){
	gotoxy(0,7);
	printf("     with love\n");
	gotoxy(0,8);
	printf("                  fr");
	gotoxy(0,8);
	delay(50);
	printf("               ");
	gotoxy(0,8);
	printf("                from");
	gotoxy(0,8);
	delay(50);
	printf("                ");
	gotoxy(0,8);
	printf("              from B");
	gotoxy(0,8);
	delay(50);
	printf("              ");
	gotoxy(0,8);
	printf("            from Bon");
	gotoxy(0,8);
	delay(50);
	printf("                ");
	gotoxy(0,8);
	printf("          from Bonia");
	gotoxy(0,8);
	delay(50);
	printf("                               ");
	gotoxy(0,8);
	printf("        from Boniato");
	gotoxy(0,8); 
	delay(50);
	printf("                               ");
	gotoxy(0,8);
	printf("      from Boniato82   ");
	printf("                               ");
	gotoxy(0,8);
	printf("   from Boniato82   ");
	delay(2500);
	gotoxy(0,7);
	printf("                          ");
	gotoxy(0,6);
	printf("     with love");
	gotoxy(0,8);
	printf("   from Boniato82");
	delay(30);
	gotoxy(0,6);
	printf("                          ");
	gotoxy(0,8);
	printf("                        ");
	gotoxy(0,5);
	printf("     with love");
	gotoxy(0,9);
	printf("   from Boniato82");
	delay(30);
	gotoxy(0,5);
	printf("                        ");
	gotoxy(0,9);
	printf("                    ");
	gotoxy(0,4);
	printf("     with love");
	gotoxy(0,10);
	printf("   from Boniato82");
	delay(30);
	gotoxy(0,4);
	printf("                          ");
	gotoxy(0,10);
	printf("                          ");
	gotoxy(0,3);
	printf("     with love");
	gotoxy(0,11);
	printf("   from Boniato82");
	delay(30);
	gotoxy(0,3);
	printf("                    ");
	gotoxy(0,11);
	printf("                    ");
	gotoxy(0,2);
	printf("     with love");
	gotoxy(0,12);
	printf("   from Boniato82");
	delay(30);
	gotoxy(0,2);
	printf("                         ");
	gotoxy(0,12);
	printf("                          ");
	gotoxy(0,1);
	printf("     with love");
	gotoxy(0,13);
	printf("   from Boniato82");
	delay(30);
	gotoxy(0,1);
	printf("                    ");
	gotoxy(0,13);
	printf("                    ");
	gotoxy(0,0);
	printf("     with love");
	gotoxy(0,14);
	printf("   from Boniato82");
	delay(30);
	gotoxy(0,0);
	printf("                        ");
	gotoxy(0,14);
	printf("                        ");
	gotoxy(0,15);
	printf("   from Boniato82");
	delay(30);
	gotoxy(0,15);
	printf("                    ");
	gotoxy(0,16);
	printf("   from Boniato82");
	delay(30);
	gotoxy(0,16);
	printf("                          ");
	gotoxy(0,17);
	printf("   from Boniato82");
	delay(30);
	gotoxy(0,17);
	printf("                        ");
	
}

//LIMPIEZA DE PANTALLA
void LIMPIA_TEXTO(void) {
	fill_rect(0, 0, 160, 144, 0); //ocultamos texto, que se considera parte del background dibujando un rectángulo negro en toda la pantalla
	wait_vbl_done();
}
void LIMPIA_TEXTO2(void) {
	gotoxy(0,0); 
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
   	gotoxy(0,0);  
}


void OCULTAR_SPRITES(void) { //oculta todos los sprites menos la flecha para la pantalla de inicio.
	i = 0;
	for (i=0; i != 31; i++){
	move_sprite(i,0,0);	//asignamos coordenadas 0,0 a cada sprite.
	}
	wait_vbl_done();
}


//ELEMENTOS DE SONIDO
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

