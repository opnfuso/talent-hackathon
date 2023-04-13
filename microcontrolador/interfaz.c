/*
 * LCD328p.c
 *
 * Created: 10/04/2023 06:06:40 p. m.
 * Author : duoco
 */ 

//Uso de la señal de reloj interna del micro
#define F_CPU 1000000

//Librerias
#include <avr/io.h>
#include <util/delay.h>

// DEFINICIONES DE APOYO
#define I	0
#define D	1

// DECLARACION DE INSTRUCCIONES
#define LINEA1		0x80
#define LINEA2		0xC0
#define LINEA3		0x94
#define LINEA4		0xD4
#define CLEAR		0x01

// DECLARACION DE FUNCIONES BÁSICAS
void LCD_Inicio();
void Escribir(uint8_t type, uint8_t inst_data);
void Inicializacion();
void Imprimir (char *A);

//PROGRAMA PRINCIPAL
int main(void)
{
	/* Replace with your application code */
	
	DDRD&=~(0x0F<<DDRD);	// Se establece el nibble menos significativo del puerto D para entrada de datos
	
	Inicializacion();
	
	Escribir(I, CLEAR);
	Escribir(I, LINEA1);
	Imprimir("- - - - - - - - - - ");
	Escribir(I, LINEA2 + 8);
	Imprimir("HOLA");
	Escribir(I, LINEA3);
	Imprimir("INICIANDO SISTEMA");
	Escribir(I, LINEA4);
	Imprimir("- - - - - - - - - - ");
	_delay_ms(800);
	Escribir(I, LINEA3);
	Imprimir("INICIANDO SISTEMA.");
	_delay_ms(800);
	Escribir(I, LINEA3);
	Imprimir("INICIANDO SISTEMA..");
	Escribir(I, LINEA3);
	Imprimir("INICIANDO SISTEMA...");
	_delay_ms(800);
	
	Escribir(I, CLEAR);
	Escribir(I, LINEA1 + 5);
	Imprimir("VROVCOR-TM");
	Escribir(I, LINEA2 + 2);
	Imprimir("EQUIPO RoboMinds");
	Escribir(I, LINEA3 + 2);
	Imprimir("TALENT HACKATHON");
	Escribir(I, LINEA4 + 8);
	Imprimir("2023");
	_delay_ms(2500);
	
	Escribir(I, CLEAR);
	Escribir(I, LINEA1 + 3);
	Imprimir("ALEJANDRO A.D.");
	Escribir(I, LINEA2 + 2);
	Imprimir("MIREL ISAAC L.B.");
	Escribir(I, LINEA3);
	Imprimir("MARIO ALEJANDRO Q.G");
	Escribir(I, LINEA4);
	Imprimir("GUILLERMO ISAAC V.C");
	_delay_ms(2000);
	Escribir(I, CLEAR);
	
	Escribir(I, LINEA1 + 5);
	Imprimir("VROVCOR-TM");
	Escribir(I, LINEA2);
	Imprimir("CAMARA:");
	
	while (1)
	{
		switch(PIND&(0x0F<<PORTD)) //Datos recibido de la tarjeta de control
		{
			case 0x00:				
			Escribir(I, LINEA3);
			Imprimir("E.V:|||DETENIDO|||");
			break;
			
			case 0x01:			
			Escribir(I, LINEA3);
			Imprimir("E.V: --AVANZANDO--");
			break;
			
			case 0x02:			
			Escribir(I, LINEA3);
			Imprimir("E.V: RETROCEDIENDO");
			break;
			
			case 0x03:			
			Escribir(I, LINEA3);
			Imprimir("E.V: GIRANDO >->->");
			break;
			
			case 0x04:			
			Escribir(I, LINEA3);
			Imprimir("E.V: GIRANDO <-<-<");
			break;
			
			case 0x05:			
			Escribir(I, LINEA4);
			Imprimir(">>>CAMINO LIBRE<<<");
			break;
			
			case 0x06:			
			Escribir(I, LINEA4);
			Imprimir("OBSTACULO ADELANTE");
			break;
			
			case 0x07:			
			Escribir(I, LINEA4);
			Imprimir("OBSTACULO ATRAS   ");
			break;
			
			case 0x08:			
			Escribir(I, LINEA2);
			Imprimir("CAMARA: DESACTIVADA");
			break;
			
			case 0x09:			
			Escribir(I, LINEA2);
			Imprimir("CAMARA: ACTIVADA   ");
			break;
			
			default:
			Escribir(I, LINEA1 + 5);
			Imprimir("VROVCOR-TM");
			Escribir(I, LINEA2);
			Imprimir("CAMARA:");
			Escribir(I, LINEA3);
			Imprimir("E.V:");
			Escribir(I, LINEA4);
			Imprimir("");
			break;
		}
	}
}


/*ESTRUCTURACION DE FUNCIONES*/

void LCD_Inicio()
{
	PORTB &=~ (1<<PORTB0);
	_delay_us(50);
	PORTB |=  (1<<PORTB0);
}

void Escribir(uint8_t type, uint8_t inst_data)
{
	if (type)
	PORTB |=  (1<<PORTB1);
	else
	PORTB &=~ (1<<PORTB1);

	PORTD = (PIND & 0x0F) | (inst_data & 0xF0);
	LCD_Inicio();
	PORTD = (PIND & 0x0F) | ((inst_data<<4) & 0xF0);
	LCD_Inicio();
	_delay_ms(2);
}

void Inicializacion()
{
	DDRB  |=  (1<<DDB0) | (1<<DDB1);
	DDRD  |=  0xF0;
	
	PORTB &=~ ((1<<PORTB0) | (1<<PORTB0));
	
	PORTD  = (PIND & 0x0F) | 0x30;

	_delay_ms(50);
	LCD_Inicio();
	_delay_ms(50);
	LCD_Inicio();
	_delay_ms(50);
	LCD_Inicio();
	_delay_ms(50);

	PORTD = (PIND & 0x0F) | 0x20;
	
	LCD_Inicio();
	_delay_ms(50);

	Escribir(I, 0x2C);
	Escribir(I, 0x08);
	Escribir(I, 0x01);
	Escribir(I, 0x06);
	
	Escribir(I, 0x0C);
}

void Imprimir (char *A)
{
	while(*A)
	{
		Escribir(D, *A);
		A++;
	}
}
