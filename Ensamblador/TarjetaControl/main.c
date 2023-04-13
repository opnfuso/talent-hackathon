/*
 * DEC1.4.6.c
 *
 * Created: 10/04/2023 01:58:42 p. m.
 * Author : duoco
 */ 

//Uso de la señal de reloj interna del micro
#define F_CPU 1000000 // 1MHz

//Librerias
#include <avr/io.h>
#include <util/delay.h>

void MOTOR1A();	// Declaracion de la funcion para el avance del motor 1
void MOTOR1R();	// Declaracion de la funcion para el avance en reversa del motor 1
void MOTOR2A();	// Declaracion de la funcion para el avance del motor 2
void MOTOR2R();	// Declaracion de la funcion para el avance en reversa del motor 2
void MOTOR3A();	// Declaracion de la funcion para el avance del motor 3
void MOTOR3R();	// Declaracion de la funcion para el avance en reversa del motor 3
void MOTOR4A();	// Declaracion de la funcion para el avance del motor 4
void MOTOR4R();	// Declaracion de la funcion para el avance en reversa del motor 4

void MOTOR1S();	// Declaracion de la funcion para poner en STOP al motor 1
void MOTOR2S();	// Declaracion de la funcion para poner en STOP al motor 1
void MOTOR3S();	// Declaracion de la funcion para poner en STOP al motor 1
void MOTOR4S();	// Declaracion de la funcion para poner en STOP al motor 1

void AVANCE();		// Declaracion de la funcion para poner en avance al vehiculo
void REVERSA();		// Declaracion de la funcion para poner en reversa al vehiculo
void GDERECHA();	// Declaracion de la funcion para girar hacia la derecha
void GIZQUIERDA();	// Declaracion de la funcion para girar hacia la izquierda
void ALTO_TOTAL();	// Declaracion de la funcion para poner en alto al vehiculo
void LUCESTP();		// Declaracion de la funcion para en encedido de la luces traseras
void LUCES();		// Declaracion de la funcion para en encedido de la luces delantera

//------------------------------------------RGB---------------------------------------------
void LUZ_ROJA();		//Declaracion de la funcion para la luz de color rojo
void LUZ_VERDE();		//Declaracion de la funcion para la luz de color verde
void LUZ_AZUL();		//Declaracion de la funcion para la luz de color azul
void LUZ_AMARILLA();	//Declaracion de la funcion para la luz de color amarillo
void LUZ_MORADA();		//Declaracion de la funcion para la luz de color morado
void LUZ_CIAN();		//Declaracion de la funcion para la luz de color cian
void LUZ_BLANCA();		//Declaracion de la funcion para la luz de color blanco
void LUZ_APAGADA();		//Declaracion de la funcion para apagar RGB
void SEC_RGB();         //Declaracion de la funcion para secuencia de prueba RGB
void RGB();             //Declaracion de la funcion para control las luces RGB
//--------------------------------------Brazo robotico--------------------------------------
void EJEH_D();	// Declaracion de la funcion para el giro del eje horizontal a la derecha
void EJEH_I();	// Declaracion de la funcion para el giro del eje horizontal a la izquierda

void EJEV_D();	// Declaracion de la funcion para el giro del eje vertical a la derecha
void EJEV_I();	// Declaracion de la funcion para el giro del eje vertical a la derecha

int A=0;	// Declaracion e inicializacion de la variable A en 0
int B=0;	// Declaracion e inicializacion de la variable B en 0
int C=0;	// Declaracion e inicializacion de la variable C en 0

int main(void)
{

	DDRB&=~(0x0F<<DDRB);	// Se establece el nibble menos significativo del puerto B para entrada de datos
	DDRB&=~(1<<DDB4);		// Señal de control 1
	DDRB&=~(1<<DDB5);		// Señal de control 2
	DDRD|=(1<<DDD7);		// Señal de activacion de las luces preventivas de reversa
	DDRD|=(1<<DDD6);		// Señal de activacion de las luces delanteras
	
	DDRD|=(1<<DDD5);		// Señal de activacion del color rojo del RGB
	DDRD|=(1<<DDD4);		// Señal de activacion del color verde del RGB
	DDRD|=(1<<DDD3);		// Señal de activacion del color azul del RGB
	DDRD|=(1<<DDD2);		// Señal de activacion del modulo de luces de la camara
	
	DDRA|=(1<<DDA0);		// Señal de control 1 para el motor 1
	DDRA|=(1<<DDA1);		// Señal de control 2 para el motor 1
	DDRA|=(1<<DDA2);		// Señal de control 1 para el motor 2
	DDRA|=(1<<DDA3);		// Señal de control 2 para el motor 2
	DDRA|=(1<<DDA4);		// Señal de control 1 para el motor 3
	DDRA|=(1<<DDA5);		// Señal de control 2 para el motor 3
	DDRA|=(1<<DDA6);		// Señal de control 1 para el motor 4
	DDRA|=(1<<DDA7);		// Señal de control 2 para el motor 4
	
	PORTB |= (1 << PB6) | (1 << PB7);	// Habilitar pull-up en PB6 y PB7
	DDRB &= ~(1 << PB6) & ~(1 << PB7);	// Configurar PB6 y PB7 como entradas
	
	DDRC |= 0x0F;	// Se establece el nibble menos significativo del puerto C para salida de datos
		
	/* Replace with your application code */
	while (1) //Siempre que 1=1
	{
		LUCESTP();	//Luces preventivas de reversa
		
		switch(PINB&(0x0F<<PORTB)) //Datos recibidos del decodificador de tonos
		{
			case 0:				// Tecla D
			ALTO_TOTAL();
			break;
	
			case 1:				// Tecla 1
			GIZQUIERDA();		// Giro a la izquierda
			break;
			
			case 2:				// Tecla 2
			AVANCE();			// Avance del vehiculo
			break;

			case 3:				// Tecla 3
			GDERECHA();			//Giro a la derecha
			break;
			
			case 4:				// Tecla 4
			EJEH_D();
			break;
			
			case 5:				// Tecla 5
			ALTO_TOTAL();
			break;

			case 6:				// Tecla 6
			EJEH_I();
			break;
			
			case 7:				// Tecla 7
			EJEV_D();
			break;
			
			case 8:				// Tecla 8
			REVERSA();			//Avance en reversa del vehiculo
			LUCESTP();			//Luces preventivas de reversa
			break;
			
			case 9:				// Tecla 9
			EJEV_I();
			break;
			
			case 10:			// Tecla 0
			LUCES();
			break;
			
			case 11:			// Tecla *
			RGB();
			break;
			
			case 12:			// Tecla #
			ALTO_TOTAL();
			break;

			case 13:			// Tecla A
			ALTO_TOTAL();
			break;
			
			case 14:			// Tecla B
			ALTO_TOTAL();
			break;
			
			case 15:			// Tecla C
			ALTO_TOTAL();
			break;

			default:			// Si no se cumple ninguna condicion
			ALTO_TOTAL();
			break;
		}
		
	}
}

void MOTOR1A()
{
	PORTA|=(1<<PORTA0);		//1
	PORTA&=~(1<<PORTA1);	//0
}

void MOTOR1R()
{
	PORTA&=~(1<<PORTA0);	//0
	PORTA|=(1<<PORTA1);		//1
}

void MOTOR2A()
{
	PORTA|=(1<<PORTA2);		//1
	PORTA&=~(1<<PORTA3);	//0
}

void MOTOR2R()
{
	PORTA&=~(1<<PORTA2);	//0
	PORTA|=(1<<PORTA3);		//1
}

void MOTOR3A()
{
	PORTA|=(1<<PORTA4);		//1
	PORTA&=~(1<<PORTA5);	//0
}

void MOTOR3R()
{
	PORTA&=~(1<<PORTA4);	//0
	PORTA|=(1<<PORTA5);		//1
}

void MOTOR4A()
{
	PORTA|=(1<<PORTA6);		//1
	PORTA&=~(1<<PORTA7);	//0
}

void MOTOR4R()
{
	PORTA&=~(1<<PORTA6);	//0
	PORTA|=(1<<PORTA7);		//1
}

void MOTOR1S()
{
	PORTA&=~(1<<PORTA0);	//0
	PORTA&=~(1<<PORTA1);	//0
}

void MOTOR2S()
{
	PORTA&=~(1<<PORTA2);	//0
	PORTA&=~(1<<PORTA3);	//0
}

void MOTOR3S()
{
	PORTA&=~(1<<PORTA4);	//0
	PORTA&=~(1<<PORTA5);	//0
}

void MOTOR4S()
{
	PORTA&=~(1<<PORTA6);	//0
	PORTA&=~(1<<PORTA7);	//0
}

void AVANCE()
{
	PORTC = (PORTC & 0xF0) | 0x01;
	if(PINB & (1<<PORTB4))	//Si el infrarrojo delantero no detecta obstaculo
	{
		PORTC = (PORTC & 0xF0) | 0x05;
		MOTOR1A();			//Avance del vehiculo
		MOTOR2A();
		
		MOTOR3S();
		MOTOR4S();
	}
	else					//Si el infrarrojo delantero detecta obstaculo
	{
		PORTC = (PORTC & 0xF0) | 0x06;
		_delay_ms(50);
		ALTO_TOTAL();		//Parar el avance del vehiculo
	}
}

void REVERSA()
{
	PORTC = (PORTC & 0xF0) | 0x02;
	
	if(PINB & (1<<PORTB5))	//Si el infrarrojo trasero no detecta obstaculo
	{
		PORTC = (PORTC & 0xF0) | 0x05;
		MOTOR1R();			//El vehiculo sigue en reversa.
		MOTOR2R();
	}
	else					//Si el infrarrojo trasero detecta obstaculo
	{
		PORTC = (PORTC & 0xF0) | 0x07;
		_delay_ms(50);
		ALTO_TOTAL();		//Parar el avance del vehiculo
	}
	
}

void GDERECHA()
{
	PORTC = (PORTC & 0xF0) | 0x03;
	MOTOR1A();
	MOTOR2R();
	
	MOTOR3S();
	MOTOR4S();
}

void GIZQUIERDA()
{
	PORTC = (PORTC & 0xF0) | 0x04;
	MOTOR1R();
	MOTOR2A();
	
	MOTOR3S();
	MOTOR4S();
}

void SEN_IR()
{
	if(PINB & (1<<PORTB4))	//Si el infrarrojo delantero no detecta obstaculo
	{
		PORTC |= 0x05;
		_delay_ms(50);
		
	}
	else					//Si el infrarrojo delantero detecta obstaculo
	{
		PORTC |= 0x06;
		_delay_ms(50);
	}
		
	if(PINB & (1<<PORTB5))	//Si el infrarrojo trasero no detecta obstaculo
	{
		PORTC |= 0x05;
		_delay_ms(50);
	}
	else					//Si el infrarrojo trasero detecta obstaculo
	{
		PORTC |= 0x07;
		_delay_ms(50);
	}
		
}

void ALTO_TOTAL()
{
	MOTOR1S();
	MOTOR2S();
	MOTOR3S();
	MOTOR4S();
	PORTC = (PORTC & 0xF0) | 0x00;
}

void LUCESTP()
{
	if((PINB&(0x0F<<PORTB))==8)	//Si se presiona la tecla 8
	{
		PORTD|=(1<<PORTD7);		//Encendido de luces traseras preventivas
	}
	else
	{
		PORTD&=~(1<<PORTD7);	//Apagado de luces traseras preventivas
	}
}

void LUCES()
{
	while ((PINB&(0x0F<<PORTB))==10)
	{
		_delay_ms(1500);		//Retardo de 1.5s
		A=(PINB&(0x0F<<PORTB));	//Se guarda en la variable A el valor recibido del decodificador

		switch(A)
		{
			case 11:				// Tecla *
			PORTD|=(1<<PORTD6);		//Encendido de luces delanteras
			break;
			
			case 12:				// Tecla #
			PORTD|=(1<<PORTD2);		//Encendido de luces de la camara
			break;
			
			case 5:					// Tecla 5
			PORTD&=~(1<<PORTD2);	//Apagado de luces de la camara
			break;
			
			default:				// Si no se cumple ninguna condicion
			PORTD&=~(1<<PORTD6);	//Apagado de luces delanteras
			
			break;
		}
		
		ALTO_TOTAL();	//Alto total del vehiculo
	}
}

void EJEH_D()
{
	if(PINB & (1<<PORTB6))	//Si el sensor esta desactivado
	{
		MOTOR3A();
	}
	else			//Si el sensor se activa
	{
		MOTOR3S();		//Parar el giro hacia adelante
	}
	
	MOTOR1S();
	MOTOR2S();
	MOTOR4S();
}

void EJEH_I()
{
	if(PINB & (1<<PORTB7))	//Si el sensor esta desactivado
	{
		MOTOR3R();
	}
	else			//Si el sensor se activa
	{
		MOTOR3S();		//Parar el giro hacia adelante
	}
	
	MOTOR1S();
	MOTOR2S();
	MOTOR4S();
}

void EJEV_D()
{
	MOTOR4A();
	
	MOTOR1S();
	MOTOR2S();
	MOTOR3S();
}

void EJEV_I()
{
	MOTOR4R();
	
	MOTOR1S();
	MOTOR2S();
	MOTOR3S();
}

void LUZ_AZUL()
{
	PORTD|=(1<<PORTD5);		// Azul encendido
	PORTD&=~(1<<PORTD4);	// Rojo apagado
	PORTD&=~(1<<PORTD3);	// Verde apagado
}

void LUZ_ROJA()
{
	PORTD&=~(1<<PORTD5);	// Azul apagado
	PORTD|=(1<<PORTD4);		// Rojo encendido
	PORTD&=~(1<<PORTD3);	// Verde apagado
}

void LUZ_VERDE()
{
	PORTD&=~(1<<PORTD5);	// Azul apagado
	PORTD&=~(1<<PORTD4);	// Rojo apagado
	PORTD|=(1<<PORTD3);		// Verde encendido
}

void LUZ_MORADA()
{
	PORTD|=(1<<PORTD5);		// Azul encendido
	PORTD|=(1<<PORTD4);		// Rojo encendido
	PORTD&=~(1<<PORTD3);	// Verde apagado
}

void LUZ_CIAN()
{
	PORTD|=(1<<PORTD5);		// Azul encendido
	PORTD&=~(1<<PORTD4);	// Rojo apagado
	PORTD|=(1<<PORTD3);		// Verde encendido
}

void LUZ_AMARILLA()
{
	PORTD&=~(1<<PORTD5);	// Azul apagado
	PORTD|=(1<<PORTD4);		// Rojo encendido
	PORTD|=(1<<PORTD3);		// Verde encendido
}

void LUZ_BLANCA()
{
	PORTD|=(1<<PORTD5);		// Azul encendido
	PORTD|=(1<<PORTD4);		// Rojo encendido
	PORTD|=(1<<PORTD3);		// Verde encendido
}

void SEC_RGB()
{
	LUZ_ROJA();
	_delay_ms(1200);		//Retardo de 1.5s
	LUZ_VERDE();
	_delay_ms(1200);		//Retardo de 1.5s
	LUZ_AZUL();
	_delay_ms(1200);		//Retardo de 1.5s
	LUZ_AMARILLA();
	_delay_ms(1200);		//Retardo de 1.5s
	LUZ_MORADA();
	_delay_ms(1200);		//Retardo de 1.5s
	LUZ_CIAN();
	_delay_ms(1200);		//Retardo de 1.5s
	LUZ_BLANCA();
	_delay_ms(1200);		//Retardo de 1.5s
}

void LUZ_APAGADA()
{
	PORTD&=~(1<<PORTD5);		// Rojo apagado
	PORTD&=~(1<<PORTD4);		// Verde apagado
	PORTD&=~(1<<PORTD3);		// Azul apagado
}


void RGB()
{
	while ((PINB&(0x0F<<PORTB))==11)
	{
		_delay_ms(1500);		//Retardo de 1.5s
		B=(PINB&(0x0F<<PORTB));	//Se guarda en la variable B el valor recibido del decodificador
		
		switch(B)
		{
			case 1:				// Tecla 1
			LUZ_ROJA();			// Encendido de la luz roja
			break;
			
			case 2:				// Tecla 2
			LUZ_VERDE();		// Encendido de la luz verde
			
			case 3:				// Tecla 3
			LUZ_AZUL();			// Encendido de la luz azul
			break;
			
			case 4:				// Tecla 4
			LUZ_AMARILLA();		// Encendido de la luz amarilla
			break;
			
			case 5:				// Tecla 5
			LUZ_MORADA();		// Encendido de la luz morada
			break;
			
			case 6:				// Tecla 6
			LUZ_CIAN();			// Encendido de la luz cian
			break;
			
			case 7:				// Tecla 7
			LUZ_BLANCA();		// Encendido de la luz blanca
			break;
			
			case 8:				// Tecla 8
			SEC_RGB();			// Secuencia de encendido de luces RGB
			break;
			
			case 9:				// Tecla 9
			LUZ_APAGADA();		//Apagado de luces delanteras
			break;
			
			default:			// Si no se cumple ninguna condicion
			LUZ_APAGADA();		//Apagado de luces RGB
			break;
		}
		
		ALTO_TOTAL();	//Alto total del vehiculo
		_delay_ms(3000);		//Retardo de 1.5s
		
	}
}
