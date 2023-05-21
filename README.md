# Micro Modulo per Lanterne di Coda FS
Questo micro modulo e' pensato per dotare i modelli in scala delle tipiche *lanterne di coda* usate per segnalamento luminoso di fine convoglio.

**Codice Identificativo Progetto: TFX007**

**Ultima Revisione HardWare: 1.01**

**Ultima Revisione SoftWare: 4.00**

**Alcune Immagini Dimostrative:**

- Modulo Faccia Superiore

<img src="https://github.com/TheFidax/TFX007_MICRO_MODULO_LANTERNE_DI_CODA/blob/main/Images/modulo_sopra.jpg" width="1280">

- Modulo Faccia Inferiore

<img src="https://github.com/TheFidax/TFX007_MICRO_MODULO_LANTERNE_DI_CODA/blob/main/Images/modulo_sotto.jpg" width="1280">

- Modulo Montato su Carrozza Corbellini Hachette e Dimostrazione Lanterne

<img src="https://github.com/TheFidax/TFX007_MICRO_MODULO_LANTERNE_DI_CODA/blob/main/Images/modulo_montato.jpg" width="1280">
<img src="https://github.com/TheFidax/TFX007_MICRO_MODULO_LANTERNE_DI_CODA/blob/main/Images/lanterna_sinistra.jpg" width="1280">
<img src="https://github.com/TheFidax/TFX007_MICRO_MODULO_LANTERNE_DI_CODA/blob/main/Images/lanterna_destra.jpg" width="1280">

------------

## Indice
* [Video Presentazione del Progetto](#video-presentazione-del-progetto)
* [Collegamenti Elettrici](#collegamenti-elettrici)
* [FirmWare](#firmware)
* [HardWare](#hardware)
* [Caratteristiche della Scheda](#caratteristiche-della-scheda)
  - [Micro Dimensioni](#micro-dimensioni)
  - [Ponte di Diodi](#ponte-di-diodi)
  - [Chip Step Down Buck MCP16331](#chip-step-down-buck-mcp16331)
  - [ATtiny10](#attiny10)
  - [Resistori LED incorporati](#resistori-led-incorporati)
  - [Predisposizione Condensatore PowerPack](#predisposizione-condensatore-powerpack)
* [Assemblaggio](#Assemblaggio)
* [Contattami](#Contattami)

------------


## Video Presentazione del Progetto
[![Video Presentazione](https://img.youtube.com/vi/kVVs_6TyThg/0.jpg)](http://www.youtube.com/watch?v=kVVs_6TyThg)

------------

## Collegamenti Elettrici

Nella seguente immagine sono riportati i collegamenti elettrici del Modulo:

<img src="https://github.com/TheFidax/TFX007_MICRO_MODULO_LANTERNE_DI_CODA/blob/main/Images/collegamenti.jpg" width="1280">

*Spiegazione*:
- Rotaie: Queste due piazzole sono destinate alle prese di corrente del rotabile, sono infatti collegate al ponte di diodi interno per l'alimentazione del Modulo.</br>
*Non hanno* un polarita': la connessiore dei fili puo' venire fatta a proprio piacimento.
- Condensatore: Queste piazzole sono pensate per collegare il condensatore esterno (maggiori dettagli nella sezione [Condensatore PowerPack](#predisposizione-condensatore-powerpack)), a queste piazzole e' collegato il circuito di *ricarica lenta* del condensatore.</br>
*Hanno **polarita' ed ESSA VA RISPETTATA***: 
  - La piazzola *Esterna* e' il **GND**
  - La piazzola *Interna* e' il U+ prodotto dal ponte di diodi interno.
- Lanterna Sinistra: Queste piazzole servono collegare Catodo e Anodo del led della lanterna di Sinistra, hanno un resistore da *1k Ohm* incorporato.</br> 
*Hanno **polarita' ed ESSA VA RISPETTATA***: 
  - La piazzola *Interna* e' il **GND**
  - La piazzola *Esterna* e' il **polo positivo** del LED. 
- Lanterna Destra: Queste piazzole servono collegare Catodo e Anodo del led della lanterna di Destra, hanno un resistore da *1k Ohm* incorporato.</br> 
*Hanno **polarita' ed ESSA VA RISPETTATA***: 
  - La piazzola *Interna* e' il **GND**
  - La piazzola *Esterna* e' il **polo positivo** del LED. 

------------

## FirmWare
Il Firmware dedicato e' presente sotto la cartella [FirmWare](https://github.com/TheFidax/TFX007_MICRO_MODULO_LANTERNE_DI_CODA/tree/main/FirmWare), per poterlo caricare è consigliata la seguente [Scheda di Prototipizzazione](xxx) e il programmatore [USBasp](https://www.fischl.de/usbasp/).</br>
Le cifre finali del file .HEX identificano la versione del FirmWare.

**NOTA: *E' INDISPENSABILE* CARICARE IL FIRMWARE *PRIMA* DELL'ASSEMBLAGGIO! Pena l'impossibilita' di programmre il Chip ATtiny10**.

La cartella *.Zip* include il codice sorgente e il progetto comodamente visionabile tramite [MPLAB Express Online](https://www.microchip.com/en-us/development-tools-tools-and-software/mplab-xpress) *senza bisogno di registrazione al sito*.

------------

## HardWare
Il progetto del Micro Modulo e' disponibile qui: https://workspace.circuitmaker.com/Projects/Details/luca-fidanza/Micro-RedLights-Module .</br>
**Viene rilasciato con la seguente Licenza**: https://creativecommons.org/licenses/by-nc-nd/4.0/ .</br>
I **File Gerber**, il **BOM** e il file **Pick and Place** sono nel file **.Zip** disponibile sotto la cartella [HardWare](https://github.com/TheFidax/TFX007_MICRO_MODULO_LANTERNE_DI_CODA/tree/main/HardWare).</br> 

**NOTA**: Lo spessore *consigliato* del PCB per questa scheda è di: **0,6mm**

------------

## Caratteristiche della Scheda
Di seguito sono riportate le caratteristiche della scheda, poi spiegate in dettaglio nei vari paragrafi dedicati.
- [Micro Dimensions](#micro-dimensioni): 11x 11mm
- [MCP16331](#chip-step-down-buck-mcp16331) to power module at 3.3v
- Module can be operate with all systems: [Analog CC, Analog AC and Digital](#ponte-di-diodi)
- [Builtin](#resistori-led-incorporati) 1kOhm lamps resistors
- [Slow charge power pack system](#predisposizione-condensatore-powerpack)
- MINIMUM CLEARANCE: 6mil

------------

### Micro Dimensioni
<img src="https://github.com/TheFidax/TFX007_MICRO_MODULO_LANTERNE_DI_CODA/blob/main/Images/modulo_sopra.jpg" width="1280">

Le dimensioni di questo modulo sono le seguenti (con la scritta TFX in alto):
- Altezza:    11mm
- Larghezza:  11mm
- Spessore:   4,3mm

------------

### Ponte di Diodi
<img src="https://github.com/TheFidax/TFX007_MICRO_MODULO_LANTERNE_DI_CODA/blob/main/Images/graetz.jpg" width="1280">

Il circuito di alimentazione e' realizzato meadiante 4 diodi in configurazione [Ponte di Graetz](https://it.wikipedia.org/wiki/Raddrizzatore#Ponte_di_Graetz).</br>
Tale configurazione permette di *raddrizzare* la tensione captata dalle prese di corrente in Conrente Continua a prescindere del sistema di alimentazione:
- Corrente Continua Analogica (fornisce sempre gli stessi poli in uscita)
- Corrente PWM (raddrizza l'onda quadra fornendo una tensione simil continua)
- Corrente Alternata Analogica (raddrizza l'onda sinusoidale fornendo una tensione simil continua)
- Digitale (raddrizza l'onda quadra fornendo una tensione simil continua)

------------

### Chip Step Down Buck MCP16331
<img src="https://github.com/TheFidax/TFX007_MICRO_MODULO_LANTERNE_DI_CODA/blob/main/Images/modulo_sotto.jpg" width="1280">

L'alimentazione a 3,3 volt e' fornita dal chip [Microchip MCP16331](https://www.microchip.com/wwwproducts/en/MCP16331), un regolatore di tensione di tipo [Step Down Buck](https://it.wikipedia.org/wiki/Convertitore_buck) in gradi di ricevere in ingresso tensioni fino a 50 volt e di fornire in uscita una tensione stabile a 3,3 volt con sviluppo di calore minimo.</br>

------------

### ATtiny10
<img src="https://github.com/TheFidax/TFX007_MICRO_MODULO_LANTERNE_DI_CODA/blob/main/Images/attiny10.jpg" width="1280">

Il lampeggio asincrono e' generato dal chip [ATtiny10](https://www.microchip.com/wwwproducts/en/ATtiny10).</br>
Questo chip opera alla tensione di 3,3v e pilota i led mediante resistori incorporati sul modulo.

**NOTA: Va programmato PRIMA di saldarlo sul modulo!**

------------

### Restori LED Incorporati
<img src="https://github.com/TheFidax/TFX007_MICRO_MODULO_LANTERNE_DI_CODA/blob/main/Images/resistori_led.jpg" width="1280">

Per ridurre al minimo i componenti accessori sul modulo **Sono Gia' Presenti** due resistori da **1kOHm** per i led delle lanterne.

------------

### Predisposizione Condensatore PowerPack
<img src="https://github.com/TheFidax/TFX007_MICRO_MODULO_LANTERNE_DI_CODA/blob/main/Images/predisposizione_powerpack.jpg" width="1280">

Il modulo *prevede* la possibilita' di usare un condensatore esterno come power pack.
**E' gia' presente il circuito di ricarica lenta**.

N.B. Queste piazzole *possono* essere usate per alimentare il modulo da una fonte **in Corrente Continua** esterna, fino a 50 volt.

Tensione condensatore:
- 25 Volt: valore standard **NON** a norma NMRA.
- 35 Volt: Valone **a norma NMRA**.
- 50 volt: Valore **OBBLIGATORIO** per impiego su sistemi in *Corrente Alteranata* **Analogici**.

------------

## Assemblaggio
A causa delle ridotte dimensioni sul PCB **non sono presenti i nomi dei componenti**.

*Per conoscere nomi e ordine di Assemblaggio* fare riferimento al Progetto su CircuitMaker: https://workspace.circuitmaker.com/Projects/Details/luca-fidanza/Micro-RedLights-Module

*Nel caso in cui si volesse la scheda **gia' assemblata** e' possibile contattarmi all'indirizzo mail sottoriportato oppure seguire eventuali aste di pezzi in esubero sul mio profilo **Ebay***: https://www.ebay.it/sch/the_fidax/m.html

------------

## Contattami
Per curiosita' o ulteriori informazioni puo contattarmi al seguente indirizzo email:  	TheFidaxContactsAtgmail.com

**NOTA**: é *Necessario* sostituire 'At' con '@'
