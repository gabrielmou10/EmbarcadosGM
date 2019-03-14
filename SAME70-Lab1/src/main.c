/**
 * 5 semestre - Eng. da Computa��o - Insper
 * Rafael Corsi - rafael.corsi@insper.edu.br
 *
 * Projeto 0 para a placa SAME70-XPLD
 *
 * Objetivo :
 *  - Introduzir ASF e HAL
 *  - Configuracao de clock
 *  - Configuracao pino In/Out
 *
 * Material :
 *  - Kit: ATMEL SAME70-XPLD - ARM CORTEX M7
 */

/********/
/* includes                                                             */
/********/

#include "asf.h"

/********/
/* defines                                                              */
/********/

// Configura��es do led

#define LED_PIO           PIOC                  // periferico que controla o LED
#define LED_PIO_ID        12                    // ID do perif�rico PIOC (controla LED)
#define LED_PIO_IDX       8u                    // ID do LED no PIO
#define LED_PIO_IDX_MASK  (1u << LED_PIO_IDX)   // Mascara para CONTROLARMOS o LED

// Configuracoes do botao 

#define BUT_PIO			PIOA
#define BUT_PIO_ID		10  
#define BUT_PIO_IDX		11
#define BUT_PIO_IDX_MASK (1u << BUT_PIO_IDX)

/********/
/* constants                                                            */
/********/

/********/
/* variaveis globais                                                    */
/********/

/********/
/* prototypes                                                           */
/********/

void init(void);

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


// Fun��o de inicializa��o do uC
void init(void){
	// Initialize the board clock
	sysclk_init();
	
	// Desativa WatchDog Timer
	WDT->WDT_MR = WDT_MR_WDDIS;
	
	// Ativa o PIO na qual o LED foi conectado
	// para que possamos controlar o LED.
	pmc_enable_periph_clk(LED_PIO_ID);
	
	// Inicializa PC8 como sa�da.
	pio_set_output(LED_PIO, LED_PIO_IDX_MASK, 0, 0, 0);
	
	// Inicializa PIO do botao
	pmc_enable_periph_clk(BUT_PIO_ID);
	
	// configura pino ligado ao bot�o como entrada com um pull-up.
	pio_set_input(BUT_PIO,BUT_PIO_IDX_MASK,PIO_DEFAULT);
	
	pio_pull_up(BUT_PIO,BUT_PIO_IDX_MASK,1);


}


/********/
/* Main                                                                 */
/********/

// Funcao principal chamada na inicalizacao do uC.
int main(void)
{
  init();

  // super loop
  // aplicacoes embarcadas n�o devem sair do while(1).
  while (1)
  {
	if(pio_get(BUT_PIO, PIO_INPUT, BUT_PIO_IDX_MASK)){
		pio_set(PIOC, LED_PIO_IDX_MASK); // Coloca 1 no pino LED
	}
	else{
		pio_clear(PIOC, LED_PIO_IDX_MASK);    // Coloca 0 no pino do LED
	}

  }
  return 0;
}