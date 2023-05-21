#ifndef TIMER0_ATTINY10_DEFINES_h                                                // DEFINE che controllano il Timer0
#define TIMER0_ATTINY10_DEFINES_h

#if defined(__AVR_ATtiny10__)

#define MAX_TIMER0_TICKS ( 65536 )                                              // Numero massimo di 'Ticks' che il Timer fa prima di richiamare l'ISR
#define MAX_TIMER0_VALUE ( 65535 )                                              // Massimo Valore che il contatore puo' assumore prima di andare in Overflow

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