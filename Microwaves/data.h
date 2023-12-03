#ifndef dati_microonde_h
#define dati_microonde_h
//come si sceglie l'intensità di amplificazione? 1x 10x 30x...
/*la sensibilità del ricevitore va regolata all’inizio di ogni misura in modo
da essere il più vicino possibile a metà della scala di misura, scegliendo
opportunamente l’amplificazione e regolando l’offset.*/


//onde stazionarie (orientazione uguale, 30x)
double posizione_riproducibilita = 30.;
double riproducibilita[] = {0.9, 0.9, 0.9};

double posizione[] = {25, 25.5, 26, 26.5, 27, 27.5, 28, 28.5, 29, 29.5, 30, 30.5, 31, 31.5, 32, 32.5, 33, 33.5, 34,  34.5, 35, 35.5, 36, 36.5, 37, 37.5, 38, 38.5, 39, 39.5, 40, 40.5, 41, 41.5, 42, 42.5, 43, 43.5, 44, 44.5, 45, 45.25, 45.5, 45.75, 46, 46.25, 46.5, 46.75, 47, 47.25, 47.50, 47.75, 48, 48.25, 48.5, 48.75, 49, 49.25, 49.5, 49.75, 50 };//devo partire dalla lettura di 1.0
double intensita[] = {0.90, 1.06, 0.86, 0.90, 1.04, 1.04, 0.90, 1.02, 0.84, 0.84 , 0.90, 0.94,  0.82, 0.88, 0.9, 0.8, 0.88, 0.84, 0.78, 0.86 , 0.80 , 0.78, 0.84, 0.78, 0.76, 0.82, 0.74, 0.78, 0.80, 0.72, 0.76, 0.76, 0.68, 0.74, 0.74, 0.66, 0.72, 0.70, 0.64, 0.70, 0.66, 0.64, 0.64,  0.66, 0.70, 0.70, 0.66, 0.64, 0.64, 0.68, 0.70, 0.68, 0.64, 0.62, 0.62, 0.66, 0.68, 0.66, 0.62, 0.60, 0.62 };//*30 traballava
void amplification(double* intensity, int amplify);
//ATTENZIONE abbiamo cambiato l'offset nelle prime misure(fino a posizione= 30 esclusa) perchè la lettura usciva dal range  quindi le misure lette erano -0.08 ma così sono giuste
//cosa succede con il riflettore che avvicino/allontano dal fascio?? il valore dell'intensità oscilla con una ampiezza sempre più grande attorno al punto di partenza

/*
in tutte le misure successive a questa dovrete tenere conto che l’effetto
dell’instaurarsi di un’onda stazionaria rimane, questo vi dà indicazioni su
una possibile ottimizzazione della misura ? mantenere sempre la stessa distanza(?)
*/

//riflessione sulla lastra metallica quadrata (orientazione uguale)
//questa volta abbiamo usato il 10x perchè col 30x rimaneva per troppo tempo sull'angolo e non si capiva il max
int numero_angoli_inc = 5;
int numero_misure_angoli_rifl = 3;
double theta_inc[] = {70., 60., 50., 40., 35.};//per certi angoli di incidenza ne avrò due, uno diretto e uno riflesso
double theta_rifl[][3] = {{67., 68., 68.}, {54., 53., 56. }, {49., 49., 50. }, {41., 40., 41.}, {33., 33., 32.}};
double theta_trasmesso_50[] = {85, 84, 85}; //il 50 sta per l'angolo di incidenza a cui abbiamo trovato il secondo massimo
double theta_trasmesso_40[] = {79, 79, 80};
//segnati anche le intensità se vuoi approfondire(non abbiamo usato il voltimetro perchè la sensibilità è meggiore della stabilità è continuava a traballare)
double intensita_onda_riflessa_metallo[][3] = {{0.64, 0.64, 0.64}, {0.74, 0.72, 0.74}, {0.84, 0.82, 0.82}, {0.66, 0.68, 0.67}, {0.62, 0.64, 0.62}};
double intensita_onda_trasmessa_50 = 0.2;
double intensita_onda_trasmessa_40 = 0.08;

//rifrazione polistirolo vuoto (verificare che l'indice di rifrazione del polistirolo è 1)
//il raggio deve essere rifratto una sola volta (angolo 0gradi tra normale e raggio incidente)
double angolo_al_vertice[2] = {22, 1}; //1= sensibilita goniometro
double max_theta_rifratto_vuoto = 2;

//rifrazione polistirolo riempito con i pellets di styrene
double max_theta_rifratto_styrene[] = {13., 14.};
double intensita_onda_rifratta[] = {0.58, 0.56};//*30
double intensita_onda_riflessa = 0.22;//*30

//polarizzazione
//osserva cosa succede con un giro completo per il Ricevitore, dove non ho segnale?
//regolare i comandi del ricevitore per una deflessione del misuratore quasi a fondo scala(alla fine?)
double distanze_emettitore_ricevitore[] = {50, 70, 90};

double angolo_polarizzatore1[] = {0, 10, 20, 30, 40, 50, 60, 70, 80, 85, 90, 95, 100, 110, 120, 130, 140, 150, 160, 170, 180, 190, 200}; 
double intensita_onda_polarizzata_dist1[] = {0.58, 0.54, 0.50, 0.46, 0.38, 0.28, 0.18, 0.10, 0.02, 0.007, 0.0, 0.005, 0.03, 0.1, 0.2, 0.28, 0.38, 0.46, 0.52, 0.56, 0.58, 0.56, 0.54};//*30
//polarizzazione con griglia orizzontale e coni orizzontali
double intensita_completa_50 = 0.56;//*30 passa il 97%

double angolo_polarizzatore2[] = {0, 10, 20, 30, 40, 50, 60, 70, 80, 85, 90, 95, 100, 110, 120, 130, 140, 150, 160, 170,180}; 
double intensita_onda_polarizzata_dist2[] = {0.94, 0.92, 0.86, 0.80, 0.68, 0.52, 0.38, 0.22, 0.06, 0.02, 0., 0.002, 0.04, 0.20, 0.40, 0.52, 0.68, 0.78, 0.86, 0.92, 0.94 };//*10;
//polarizzazione con griglia orizzontale e coni orizzontali
//double intensita_completa_70 = ;

double angolo_polarizzatore3[] = {0, 10, 20, 30, 40, 50, 60, 70, 80, 85, 90, 95, 100, 110, 120, 130, 140, 150, 160, 170, 180}; 
double intensita_onda_polarizzata_dist3[] = {0.76, 0.74, 0.70, 0.62, 0.54, 0.42, 0.30, 0.16, 0.04, 0.02,  0., 0.002, 0.02, 0.14, 0.28, 0.40, 0.50, 0.60, 0.68, 0.72, 0.74};//*10
//polarizzazione con griglia orizzontale e coni orizzontali
double intensita_completa_90 = 0.18;//*30 passa solo il 70%

//non ho capito cosa dovrei dimostrare???
/*
Si utilizzino i dati raccolti per discutere le due ipotesi: il ricevitore è
sensibile all’ampiezza dell’onda o alla sua intensità.
Forse devo fare un grafico di cos(theta)M_0 e confrontarlo con i punti Mletto in funzione di cos(theta) saranno diversi, quindi M non è direttamente proporzionale a E;
grafica anche cosquadro(theta)M_0 e confrontalo con i tuoi punti, cosa vedi?
*/


//polarizzazione con la griglia(orientazione uguale con la parte larga orizzontale) misure prese a 90cm
double angolo_griglia[] = {0, 45, 90};//angoli rispetto all'orizzontale
double intensita_onda_polarizzata_griglia[] = {0.18 , 0.12 , 0.02 };//*30 orizzontale, obliquo, verticale 
//come la griglia ha modificato l'onda incidente?(si pensi a come si comporta un metallo in presenza di un campo elettrico)
//cosa si può concludere circa la direzione di polarizzazione delle onde prodotte dall’emettitore? quando sono girate sullo zero gradi emettono in verticale e viceversa

//polarizzazione con griglia + Ricevitore ruotato a 90 rispetto il Trasmettitore
double angolo_griglia2[] = {0, 45, 90};
double intensita_onda_polarizzata_griglia2[] = { 0. , 0.14 , 0.};//*30 -90 angolo di cui ho ruotato il ricevitore
//perchè aggiungere un polarizzatore fa aumentare il livello del segnale al rivelatore? forse si riferisce a quando la griglia si trova a 45 e i due coni perpendicolari(rileviamo 0.14 invece di 0)


//polarizzazione con griglia verticale e coni orizzontali(90cm) verifico che ruotando il trasmettitore di 360 non vedo mai segnale: oscilla tra 0  0.20*30

//polarizzazione griglia orizzontale giro di 360 gradi il trasmettitore oscilla tra 0 e  0.56


/*
//polarizzazione con griglia"rotante"
int numero_rotazioni_griglia = 7;
double angolo_griglia_rotante[] = {0, 30, 40, 45, 50, 60, 90}; //rispetto all'asse dei coni che rimarranno sempre perpendicolari tra loro
double intensita_griglia_rotante[] = {}
*/

//angolo di Brewster con lastra di Polyetilene, polarizzazione uguale:parto con orizzontale, 90gradi(lato lungo sulla verticale)
int numero_angoli_inc_Brewster = 9;
double angolo_incidenza_Brewster[] = {25, 28, 30, 35, 40, 50, 52, 55,  60, };
double intensita_onda_riflessa_90[] = {0.02, 0., 0.02,  0.04, 0.08, 0.11, 0., 0.08, 0.36 }; //*10 misuro prima questa

//trovo Brewster solo con quella orizzontale(0)
//occhiali da sole polaroid come funzionano e a cosa servono

//doppia fenditura: dsin(theta) = n lambda
int numero_massimi_fenditura = 2;
int numero_misure_angoli_fenditura = 2;
double ordine_massimo_doppia_fenditura[] = {1, 2};
double angolo_massimo_doppia_fenditura[] = {22, 48}; //misurato tra ricevitore e asse ottico *30  ne avevamo prese due per ognuno ma erano tutti uguali
double intensita_doppia_fenditura[] = {0.46, 0.52, 0.32, 0.18}; //il primo è di ordine 0, non riportato sopra
double d = 7.5;//6cm sulla scheda ma aggiungo 3 della larghezza dei buchi perchè altrimenti non torna una cippa

//bragg
double distanza_bordi_palline = 3;//cm

/*
double intensita[] = {0.42, 0.52, 0.68, 0.72, 0.68, 0.56, 0.40, 0.42, 0.36 0.42, 0.68, 0.76, 0.72, 0.58, 0.48  }//*10
double angolo_bragg[] = {0, 10, 15, 20, 25, 30, 40, 50, 55, 60, 70, 75, 80, 85, 90} //-90
*/
int numero_misure_Bragg = 7;
double intensita_onda_riflessa_Bragg[] = {0.02, 0.12, 0.12, 0.18, 0.18, 0.12, 0.02};//*10
//double angolo_incidenza[] = {30, 35, 37 40, 42,  45, 50};//rispetto alla normale -90
double angolo_incidenza_Bragg[] = {60, 55, 53, 50, 48, 45, 40};



#endif