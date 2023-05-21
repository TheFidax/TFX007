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
