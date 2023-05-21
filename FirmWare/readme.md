# FirmWare TFX007

------------

# main.c

```c
#define F_CPU   8000000                                                         // Frequenza di funzionamento

////////////////////////////////////////////////////////////////////////////////
/* Librerie */

#include <avr/sleep.h>                                                          // Libreria per la gestione della modalita' Sleep
#include <avr/interrupt.h>                                                      // ISR per gli interrupt
#include <util/delay.h>                                                         // Libreria per la funzione _delay_ms
#include <stdint.h>                                                             // Tipi di dati uintxx_t in C

#include "Lights_Timing.h"                                                      // libreria con i valori (in mS) di accensione e spegimento lanterne
#include "TIMER0_ATTINY10_DEFINES.h"                                            // comandi rapidi Timer0

////////////////////////////////////////////////////////////////////////////////

/* Tempistiche Timer */
// Durata del 'Tick' = 256 (256 cicli per un 1 tick del timer) / 8000000 = 3,2 x 10^-5 S = 32 * 10^-6 uS
#define TICKS_TIMING            ( 32 )
// Calcola il numero Ticks partendo da un generico tempo in mS: T=XmS = X * 10^-3 -> n' Tick = ( (X * (10^(-3))) / (32 * 10^(-6)) )
// Lavoro SOLO in positivo quindi: n' Tick = ( (X * (10^(3))) / (32 ) )
#define TICKS_GENERIC_MS(x)     ( ((uint32_t)x * 1000 ) / TICKS_TIMING )
#define TICKS_T_ON              TICKS_GENERIC_MS(T_ON)  //( 625 )
#define TICKS_T_OFF             TICKS_GENERIC_MS(T_OFF) //( 20625 ) 

/* Comandi 'rapidi' */
#define LANT1_ON    ( PORTB |= (1 << PORTB0) )
#define LANT1_OFF   ( PORTB &= ~( 1 << PORTB0) )
#define LANT2_ON    ( PORTB |= (1 << PORTB1) )
#define LANT2_OFF   ( PORTB &= ~( 1 << PORTB1) )

////////////////////////////////////////////////////////////////////////////////
/* Prototipi */

uint8_t getRandom(void);                                                        // Restituisce un valore random usando l'ADC sul pin lasciato fluttante

////////////////////////////////////////////////////////////////////////////////
/* Variabili Globali */ 

static uint32_t asyncDelayTicks;                                                // Variabile che tiene memoria dei 'ticks' di sfasamento tra le due lanterne

////////////////////////////////////////////////////////////////////////////////
/* MAIN */

int main() {    
    /* SETUP */
    
    CCP = 0xD8;                                                                 // Abilito la modifica dei registri protetti (dal datasheet)
    CLKPSR = 0b0000;                                                            // Imposto il 'prescaler' a 1 : frequenza 8MHz
    
    asyncDelayTicks = TICKS_GENERIC_MS(2 * getRandom());                        // Calcolo un valore 'random' di 'ticks' come sfasamento tra le due lanterne

    ADCSRA = 0;                                                                 // Disabilito l' ADC
    PRR = (1<<PRADC);                                                           // Abilito la possibilita' di risparmiare energia dal modulo ADC
           
    DDRB = 0b0011;                                                              // Imposto i pin PB1 e PB0 come OUTPUT
                                                                                // Lascio un riscontro visivo per indicare che il modulo e' pronto
    LANT1_ON;                                                                   // Accendo la lanterna 1
    LANT2_ON;                                                                   // Accendo la lanterna 2
        
                                                                                // Imposto il Timer0 per gestire il lampeggio
    TIMER0_DISABLE_OVERFLOW_INTERRUPT;                                          // Disattivo il timer
    TIMER0_RESET_CCONTROLS_REGISTERS;                                           // Eseguo il Reset dei registri di controllo
    TIMER0_ENABLE_OVERFLOW_INTERRUPT;                                           // Attivo l' ISR per Overflow
    TIMER0_SET_COUNTER_REGISTER(MAX_TIMER0_COUNTER);                            // Imposto il contatore del Timer al massimo -> Attivo subito l'ISR

    sei();                                                                      // Abilito gli interrupt globali
        
    set_sleep_mode(SLEEP_MODE_IDLE);                                            // Imposto la modalita' di Sleep come IDLE
    sleep_enable();                                                             // Abilito il MCU a poter andare nella modalita' 'Sleep'
    
    TIMER0_SET_PRESCALER_256;                                                   // Imposto il prescaler a 256 (impostando il prescaler si avvia anche il Timer)
    /* FINE SETUP */

    
    /* LOOP */
    while(1) {                                                                  // Non faccio niente perche' e' tutto gestito dal Timer0
        sleep_cpu();                                                            // Mando l'MCU in modalita' 'Sleep'
    }
    /* FINE LOOP */
    
    return 0;                                                                   // Fine del Main
}

ISR(TIM0_OVF_vect) {
    static uint8_t nextPhase = 0;                                               // Contatore per tenere traccia della fase di lampeggio

    sleep_disable();                                                            // Impedisco al MCU di poter andare in modalita' 'Sleep'

    switch(nextPhase) {
        case 0: {                                                               // Fase 0: Tutte le lanterne spente -> Devi accendere la Laterna di Sinistra
            LANT1_ON;                                                           // Accendo la Lanterna 1
            ++nextPhase;                                                        // Incremento il contatore
            
            TIMER0_SET_COUNTER_REGISTER((uint16_t)(MAX_TIMER0_COUNTER - TICKS_T_ON));
            break;
        }
        case 1: {                                                               // Fase 1: Lanterna Sinistra accesa, la devo spegnere
            LANT1_OFF;                                                          // Spengo la Lanterna 1
            ++nextPhase;                                                        // Incremento il contatore
            
            TIMER0_SET_COUNTER_REGISTER((uint16_t)(MAX_TIMER0_COUNTER - asyncDelayTicks));
            break;
        }
        case 2: {                                                               // Fase 2: Tutte le Lanterne Spente -> Devo Accendere la Lanterna Destra
            LANT2_ON;                                                           // Accendo la Lanterna 2
            ++nextPhase;                                                        // Incremento il contatore
            
            TIMER0_SET_COUNTER_REGISTER((uint16_t)(MAX_TIMER0_COUNTER - TICKS_T_ON));
            break;
        }
        case 3: {                                                               // Fase 3: Lanterna Destra accesa, la devo spegnere
            LANT2_OFF;                                                          // Spengo la Lanterna 2
            nextPhase = 0;                                                      // Azzero il contatore
            
            TIMER0_SET_COUNTER_REGISTER((uint16_t)(MAX_TIMER0_COUNTER - (TICKS_T_OFF - asyncDelayTicks)));
            break;
        }
    }

    sleep_enable();                                                             // Abilito il MCU a poter andare nella modalita' 'Sleep'
}

uint8_t getRandom(void) {                                                       // Funzione che restituisce un numero random
#define ITERATIONS  10                                                          // Numero di volte che esegue la lettura per ricavare un valore medio
    uint16_t value = 0;                                                         // Variabile contenente il valore random calcolato
    
    ADMUX = 0b00000010;                                                         // Imposto l'ADC per leggere il valore dal pin PB2
    ADCSRA = 1<<ADEN | 1<<ADPS0;                                                // Abilito il modulo ADC per conversione singola

    for(uint8_t i = 0; i < ITERATIONS; ++i){                                    // Faccio la lettura 10 volte
        uint8_t temp;                                                           // Variabile di supporto dove salgo il valore convertito dall'ADC (ADC a 8bit su ATtiny10)
        ADCSRA = ADCSRA | 1<<ADSC;                                              // Avvio la conversione
        while (ADCSRA & 1<<ADSC);                                               // Attendo che la conversione venga eseguits
        temp = ADCL;                                                            // Salvo il valore convertito dal registro ADCL

        value += temp;                                                          // Sommo tutti i risultato della conversione
        
        _delay_ms(5);                                                           // Attendo 5mS tra una conversione e l'altra 
    }
    
    value /= ITERATIONS;                                                        // Eseguo la Media matematica dei valori trovati
    
    return (uint8_t)value;                                                      // Restituisco il valore random  a 8bit (il valore restituito dall'ADC e' campionato su 8bit)
}
```

------------

# Lights_Timing.h

```c
#ifndef LIGHTS_TIMING_h                                                         // Header contenenti i 'Tempi' del lampeggio
#define	LIGHTS_TIMING_h

/*  I Tempi sono estratti basandosi sul numero dei Frame di un filmato a 50fps
 *  Tempo Lanterna Spenta   =   33 frame    x   1/50S (50fps)   = 0,66S = 660mS
 *  Tempo Lanterna Accesa   =   1 frame     x   1/50S (50fps)   = 0,02S = 20mS
 *
 *  1000mS = 1S
  */

#define     T_OFF       660                                                     // Millisecondi per cui la lanterna resta SPENTA
#define     T_ON        20                                                      // Millisecondi per cui la lanterna resta ACCESA

#endif	/* LIGHTS_TIMING_h */
```

------------

# TIMER_ATTINY10_DEFINES.h

```c
#ifndef TIMER0_ATTINY10_DEFINES_h                                                // DEFINE che controllano il Timer0
#define TIMER0_ATTINY10_DEFINES_h

#if defined(__AVR_ATtiny10__)

#define MAX_TIMER0_COUNTER ( 65536 )
      /*
      * Esegue un reset dei registri del Counter del Timer
      * Input:
      *   - Nulla
      * Restituisce:
      *   - Nulla
      */
#define TIMER0_RESET_COUNTER_REGISTER       ( TCNT0H = TCNT0L = 0 )
      /*
      * Imposta un valore nei registri del Counter del Timer
      * Input:
      *   - il valore da impostare
      * Restituisce:
      *   - Nulla
      */
#define TIMER0_SET_COUNTER_REGISTER(x)       TCNT0H = (((int)x)>>8); TCNT0L = (((int)x) & 0xFF)
      /*
      * Imposta un valore nei registri del Output Compare Register del Timer
      * Input:
      *   - il valore da impostare
      * Restituisce:
      *   - Nulla
      */
#define TIMER0_SET_OUTPUT_COMPARE_REGISTER(x)       OCR0AH = (((int)x)>>8); OCR0AL = (((int)x) & 0xFF)
      /*
      * Esegue un reset dei registri di controllo del Timer
      * Input:
      *   - Nulla
      * Restituisce:
      *   - Nulla
      */
#define TIMER0_RESET_CCONTROLS_REGISTERS    ( TCCR0A = TCCR0B = 0x00 )
      /*
      * Esegue un reset del Prescaler del Timer3 con conseguenza fermata del Timer
      * Input:
      *   - Nulla
      * Restituisce:
      *   - Nulla
      */
#define TIMER0_RESET_PRESCALER              ( TCCR0B &= ~( (1 << CS00) | (1 << CS01) | (1 << CS02) ) )
      /*
      * Imposta il Prescaler del Timer a 1
      * Input:
      *   - Nulla
      * Restituisce:
      *   - Nulla
      */
#define TIMER0_SET_PRESCALER_1              ( TCCR0B |= (1 << CS00) )
      /*
      * Imposta il Prescaler del Timer a 8
      * Input:
      *   - Nulla
      * Restituisce:
      *   - Nulla
      */
#define TIMER0_SET_PRESCALER_8              ( TCCR0B |= (1 << CS01) )
      /*
      * Imposta il Prescaler del Timer a 64
      * Input:
      *   - Nulla
      * Restituisce:
      *   - Nulla
      */
#define TIMER0_SET_PRESCALER_64              ( TCCR0B |= (1 << CS00) | (1 << CS01) )
      /*
      * Imposta il Prescaler del Timer a 256
      * Input:
      *   - Nulla
      * Restituisce:
      *   - Nulla
      */
#define TIMER0_SET_PRESCALER_256             ( TCCR0B = (1 << CS02) )
      /*
      * Imposta il Prescaler del Timer a 1024
      * Input:
      *   - Nulla
      * Restituisce:
      *   - Nulla
      */
#define TIMER0_SET_PRESCALER_1024            ( TCCR0B |= (1 << CS00) | (1 << CS02) )
      /*
      * Enable Timer/Counter, Overflow Interrupt 
      * Input:
      *   - Nulla
      * Restituisce:
      *   - Nulla
      */
#define TIMER0_ENABLE_OVERFLOW_INTERRUPT     ( TIMSK0 = (1 << TOIE0) )
      /*
      * Disable Timer/Counter, Overflow Interrupt 
      * Input:
      *   - Nulla
      * Restituisce:
      *   - Nulla
      */
#define TIMER0_DISABLE_OVERFLOW_INTERRUPT   ( TIMSK0 &= ~( (1 << TOIE0) ) )
      /*
      * Enable Timer/Counter, Output Compare B Match Interrupt Interrupt 
      * Input:
      *   - Nulla
      * Restituisce:
      *   - Nulla
      */
#define TIMER0_ENABLE_OUTPUT_COMPARE_A_INTERRUPT     TCCR0A = (1<<COM0A0); ( TIMSK0 = (1 << OCIE0A) )
      /*
      * Disable Timer/Counter, Output Compare B Match Interrupt Interrupt 
      * Input:
      *   - Nulla
      * Restituisce:
      *   - Nulla
      */
#define TIMER0_DISABLE_OUTPUT_COMPARE_A_INTERRUPT     TCCR0A &= ~( (1 << COM0A0) ); ( TIMSK0 &= ~( (1 << OCIE0A) ) )
      /*
      * Enable Timer/Counter, Output Compare B Match Interrupt Interrupt 
      * Input:
      *   - Nulla
      * Restituisce:
      *   - Nulla
      */
#define TIMER0_ENABLE_OUTPUT_COMPARE_B_INTERRUPT     TCCR0B = (1<<COM0B0); ( TIMSK0 = (1 << OCIE0B) )
      /*
      * Disable Timer/Counter, Output Compare B Match Interrupt Interrupt 
      * Input:
      *   - Nulla
      * Restituisce:
      *   - Nulla
      */
#define TIMER0_DISABLE_OUTPUT_COMPARE_B_INTERRUPT     TCCR0B &= ~( (1 << COM0B0) ); ( TIMSK0 &= ~( (1 << OCIE0B) ) )

#else

#error "Compatibile SOLO CON ATTINY10"

#endif

#endif
```
