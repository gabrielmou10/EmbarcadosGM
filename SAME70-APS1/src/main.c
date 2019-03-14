/**
 * 5 semestre - Eng. da Computação - Insper
 * Rafael Corsi - rafael.corsi@insper.edu.br
 ** APS 1 para a placa SAME70-XPLD
 **
 ** Entrega realizada em parceria com:
 **  - Gabriel Moura
 **  - Nicolas Stegmann
 ** 
 **  - url vídeo
 **/

#include "asf.h"

/********/
/* defines                                                              */
/********/

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

// Configurations Led PC8u

#define LED_PIO           PIOC                  // periferico que controla o LED
#define LED_PIO_ID        12                    // ID do periférico PIOC (controla LED)
#define LED_PIO_IDX       8u                    // ID do LED no PIO
#define LED_PIO_IDX_MASK  (1u << LED_PIO_IDX)   // Mascara para CONTROLARMOS o LED
 
// Configurations of Buzzer , PC17

#define BUTB_PIO			PIOC
#define BUTB_PIO_ID		    12
#define BUTB_PIO_IDX		17
#define BUTB_PIO_IDX_MASK (1u << BUTB_PIO_IDX)

// Configurations of Button Next Song , PC30

#define BUTNEXT_PIO			PIOC
#define BUTNEXT_PIO_ID		12
#define BUTNEXT_PIO_IDX		30
#define BUTNEXT_PIO_IDX_MASK (1u << BUTNEXT_PIO_IDX)

// Configurations of Button Play/Stop , PC30

#define BUTPS_PIO			PIOA
#define BUTPS_PIO_ID		10
#define BUTPS_PIO_IDX		4
#define BUTPS_PIO_IDX_MASK (1u << BUTPS_PIO_IDX)

/********/
/* constants                                                            */
/********/

/********/
/* variaveis globais                                                    */
/********/

/********/
/* prototypes                                                           */
/********/

/********/
/* interrupcoes                                                         */
/********/

/********/
/* funcoes                                                              */
/********/

/**
 * \brief Set a high output level on all the PIOs defined in ul_mask.
 * This has no immediate effects on PIOs that are not output, but the PIO
 * controller will save the value if they are changed to outputs.
 *
 * \param p_pio Pointer to a PIO instance.
 * \param ul_mask Bitmask of one or more pin(s) to configure.
 */
void _pio_set(Pio *p_pio, const uint32_t ul_mask)
{

}


// Função de inicialização do uC
void init(void){
	// Initialize the board clock
	sysclk_init();
	
	// Desativa WatchDog Timer
	WDT->WDT_MR = WDT_MR_WDDIS;
	
	// Ativa o PIO na qual o LED foi conectado
	// para que possamos controlar o LED.
	pmc_enable_periph_clk(LED_PIO_ID);
	// Inicializa o pino do led como saída.
	pio_set_output(LED_PIO, LED_PIO_IDX_MASK, 0, 0, 0);
	
	// Inicializa PIO do Buzzer
	pmc_enable_periph_clk(BUTB_PIO_ID);
	// Inicializa o pino do buzzer como saída.
	pio_set_output(BUTB_PIO, BUTB_PIO_IDX_MASK, 0, 0, 0);
	
	// Inicializa PIO do Botão Next
	pmc_enable_periph_clk(BUTNEXT_PIO_ID);
	// Inicializa o pino do botão next como entrada com um pull-up.
	pio_set_input(BUTNEXT_PIO_ID,BUTNEXT_PIO_IDX_MASK,PIO_DEFAULT);
	pio_pull_up(BUTNEXT_PIO,BUTNEXT_PIO_IDX_MASK,1);
	
	// Inicializa PIO do Botão Play/Stop
	pmc_enable_periph_clk(BUTPS_PIO_ID);
	// Inicializa o pino do botão play/stop como entrada com um pull-up.
	pio_set_input(BUTPS_PIO_ID,BUTPS_PIO_IDX_MASK,PIO_DEFAULT);
	pio_pull_up(BUTNEXT_PIO,BUTNEXT_PIO_IDX_MASK,1);	
}


/********/
/* Main                                                                 */
/********/

// Funcao principal chamada na inicalizacao do uC.
int main(void){

  
  init();
  
	//mario music
  int melodymario[] = {
	  NOTE_E7, NOTE_E7, 0, NOTE_E7,
	  0, NOTE_C7, NOTE_E7, 0,
	  NOTE_G7, 0, 0,  0,
	  NOTE_G6, 0, 0, 0,
	  
	  NOTE_C7, 0, 0, NOTE_G6,
	  0, 0, NOTE_E6, 0,
	  0, NOTE_A6, 0, NOTE_B6,
	  0, NOTE_AS6, NOTE_A6, 0,
	  
	  NOTE_G6, NOTE_E7, NOTE_G7,
	  NOTE_A7, 0, NOTE_F7, NOTE_G7,
	  0, NOTE_E7, 0, NOTE_C7,
	  NOTE_D7, NOTE_B6, 0, 0,
	  
	  NOTE_C7, 0, 0, NOTE_G6,
	  0, 0, NOTE_E6, 0,
	  0, NOTE_A6, 0, NOTE_B6,
	  0, NOTE_AS6, NOTE_A6, 0,
	  
	  NOTE_G6, NOTE_E7, NOTE_G7,
	  NOTE_A7, 0, NOTE_F7, NOTE_G7,
	  0, NOTE_E7, 0, NOTE_C7,
	  NOTE_D7, NOTE_B6, 0, 0
  };
  //Mario main them tempo
  int tempomario[] = {
	  12, 12, 12, 12,
	  12, 12, 12, 12,
	  12, 12, 12, 12,
	  12, 12, 12, 12,
	  
	  12, 12, 12, 12,
	  12, 12, 12, 12,
	  12, 12, 12, 12,
	  12, 12, 12, 12,
	  
	  9, 9, 9,
	  12, 12, 12, 12,
	  12, 12, 12, 12,
	  12, 12, 12, 12,
	  
	  12, 12, 12, 12,
	  12, 12, 12, 12,
	  12, 12, 12, 12,
	  12, 12, 12, 12,
	  
	  9, 9, 9,
	  12, 12, 12, 12,
	  12, 12, 12, 12,
	  12, 12, 12, 12,
  };
  //Underworld melody
  int melodyuw[] = {
	  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,
	  NOTE_AS3, NOTE_AS4, 0,
	  0,
	  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,
	  NOTE_AS3, NOTE_AS4, 0,
	  0,
	  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
	  NOTE_DS3, NOTE_DS4, 0,
	  0,
	  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
	  NOTE_DS3, NOTE_DS4, 0,
	  0, NOTE_DS4, NOTE_CS4, NOTE_D4,
	  NOTE_CS4, NOTE_DS4,
	  NOTE_DS4, NOTE_GS3,
	  NOTE_G3, NOTE_CS4,
	  NOTE_C4, NOTE_FS4, NOTE_F4, NOTE_E3, NOTE_AS4, NOTE_A4,
	  NOTE_GS4, NOTE_DS4, NOTE_B3,
	  NOTE_AS3, NOTE_A3, NOTE_GS3,
	  0, 0, 0
  };
  //Underwolrd tempo
  int tempouw[] = {
	  12, 12, 12, 12,
	  12, 12, 6,
	  3,
	  12, 12, 12, 12,
	  12, 12, 6,
	  3,
	  12, 12, 12, 12,
	  12, 12, 6,
	  3,
	  12, 12, 12, 12,
	  12, 12, 6,
	  6, 18, 18, 18,
	  6, 6,
	  6, 6,
	  6, 6,
	  18, 18, 18, 18, 18, 18,
	  10, 10, 10,
	  10, 10, 10,
	  3, 3, 3
  };
  void buzz (long frequency, long lenght){
	pio_clear(PIOC, LED_PIO_IDX_MASK);    // Coloca 0 no pino do LED
	long delayValue = 1000000 / frequency / 2;
	long numCycles = frequency * length / 1000;	  
	for (long i = 0; i < numCycles; i++) {
		pio_set(BUTB_PIO, BUTB_PIO_IDX_MASK);
		delay_us(delayValue);		
		pio_clear(BUTB_PIO, BUTB_PIO_IDX_MASK);
		delay_us(delayValue);	
	}
	pio_set(PIOC, LED_PIO_IDX_MASK); //liga o led de acordo com os toques
  }
  
  void play (int melody[], int tempo[], int size){
	 for (int thisNote = 0; thisNote < size; thisNote++) {
		 
		 // to calculate the note duration, take one second
		 // divided by the note type.
		 
		 int noteDuration = 1000 / tempo[thisNote];
		 buzz(melody[thisNote], noteDuration);
		 
		 if(pio_get(BUTPS_PIO, PIO_INPUT, BUTPS_PIO_IDX_MASK)){ //se o botao de play for pressionado para a musica
		 }
		 
		 else {
			buzz(0, noteDuration);
			delay_s(1);
			return;
		 }		 
		 
		 // to distinguish the notes, set a minimum time between them.
		 // the note's duration + 30% seems to work well:
		 int pauseBetweenNotes = noteDuration * 1.30;
		 delay_us(pauseBetweenNotes);
		 
		 // stop the tone playing:
		 buzz(0, noteDuration); 
	 }	  
  }
  int song = 1;
  // super loop
  // aplicacoes embarcadas não devem sair do while(1).
  while (1)
  {
	if(pio_get(BUTPS_PIO, PIO_INPUT, BUTPS_PIO_IDX_MASK)){ // se o botão play é pressionado
	}
	else{
		while(!(pio_get(BUTPS_PIO, PIO_INPUT, BUTPS_PIO_IDX_MASK))){
			delay_us(12);
		}
		if(song == 1){
			int size = sizeof(melodymario) / sizeof(int);
			play(melodymario, tempomario, size);
		}
		else if(song == 2){
			int size = sizeof(melodyuw) / sizeof(int);
			play(melodyuw, tempouw, size);
		}
	}
	
	if(pio_get(BUTNEXT_PIO, PIO_INPUT, BUTNEXT_PIO_IDX_MASK)){ // se o botao de next for pressionado troca a musica
	}
	else{
		while(!(pio_get(BUTNEXT_PIO, PIO_INPUT, BUTNEXT_PIO_IDX_MASK)))
		{
			delay_ms(30);
		}
		if(song == 2){
			song = 1;
		}
		else{
			song = 2;
		}
   }
  }
  return 0;
}