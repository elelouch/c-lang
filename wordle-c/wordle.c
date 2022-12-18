#define _GNU_SOURCE
#include "./header.h"
#include <ctype.h> //importada para toupper
#include <stdio.h>
#include <stdlib.h>
#include <string.h> //la importe para strcpy y strchr
#include <time.h>   //la importe para pid

int main() {

  char guess[WORD_LENGTH], guess_feedback[WORD_LENGTH - 1], enigma[WORD_LENGTH];

  /*en enigma se almacenara la palabra a
    adivinar ,en guess el intento y guess_feedback
    tendra el feedback de cada intento*/

  char wanna_play;
  char keep_playing;
  int total_games;       /*cantidad de partidas*/
  int scores[MAX_GAMES]; /*Este array tendra la puntuacion de cada
                           partida donde cada partida esta representada
                           por el numero de la partida, menos uno.*/
  char tracking[WORD_LENGTH - 1] = {'-'};

  /*cada numero representara la posicion de cada
    letra de la palabra de una partida,al acertar/a
    divinar un caracter se completara con '.'
    al final de la partida se seteara todo a '-'
    de nuevo*/

  int i, j;

  srand(time(NULL));
  /*cambio la seed*/

  /* Presentacion del juego*/
  printf("\v\t\tBIENVENIDO A WORDLE\v\n");
  printf("En Wordle nos encargamos de adivinar una palabra de 5 letras!\n\n");

  printf("En este programa las letras no se repiten y ademas, solo se tendran "
         "en cuenta las primeras "
         "5 de su intento.\n Cada devolucion de un intento tendra el siguiente "
         "formato: "
         "\n");
  printf(" + : Si la letra es correcta y esta bien posicionada. \n * : Si la "
         "letra es correcta pero esta mal posicionada. \n - : Si la letra es "
         "incorrecta.\n\n");
  printf("Usted tendra 6 intentos por partida.\n");

  printf("Quiere participar de una sesion de juego?(S)i/(N)o :");

  do {
    scanf(" %c", &wanna_play);
    wanna_play = toupper(wanna_play);
  } while (!(wanna_play == YES || wanna_play == NO));
  /*si wanna_play es igual a N o a S, salgo del loop*/

  if (wanna_play == NO) {
    printf("Para que inicio el programa?\n");
    return EXIT_SUCCESS;
  }

  printf("Ingrese la cantidad de partidas(max. 8): ");
  do {
    scanf("%d", &total_games);
  } while (total_games > MAX_GAMES || total_games < MIN_GAMES);

  for (i = 0; i < total_games; i++) {
    getWordInLine(EXTERNAL_FILE, rand() % get_file_lines(EXTERNAL_FILE) + 1,
                  enigma);
    scores[i] = START_SCORE;
    /*cada partida comienza con 5000*/

    printf("\n\t\t------Partida %d de %d------\n", i + 1, total_games);
    for (j = 0; j < TRIES_PER_GAME; j++) {
      printf("\n\t\tIntento #%d: ", j + 1);
      scanf("%5s", guess); /*Se leeran solo los primeros 5 char*/
      clean_stdin();
      /*Para no renegar con basura que queda en el buffer*/

      capitalize_word(guess);
      print_feedback(guess_feedback, enigma, guess);
      /* printea un feedback y ademas guess_feedback la ultima jugada*/
      scores[i] += set_score(tracking, guess_feedback);

      /*set_score obtendra la puntuacion de cada jugada y
        ademas se le pasara el tracking para checkear si el
        usuario gano o no con user_won*/

      if (user_won(guess_feedback)) {

        /*si el usuario gana seteo el score de esa
          partida a 10000*/

        if (j == 0) {
          scores[i] = HIGHEST_SCORE;
        }
        printf("Ganaste!");
        break;
      }
    }
    if (j == TRIES_PER_GAME) {
      /* si hizo 6 intentos y no gano, pierde*/
      scores[i] = LOWEST_SCORE;
    }
    printf("\n\nLa palabra era: %s\n\n", enigma);
    printf("Puntaje de la partida : %d\n", scores[i]);
    reset_tracking(tracking);

    if (total_games > 1 && i != total_games - 1) {
      /* si tiene mas de un juego y si no es la
       * ultima partida, consultar para seguir jugando*/
      printf("Desea seguir jugando? (S)i/(N)o:");
      scanf(" %c", &keep_playing);
      keep_playing = toupper(keep_playing);
    }
    if (keep_playing == NO) {
      /*si el usuario sale antes,
       * +1 al contador de partidas ya que el loop no llegara
       * al final y no se sumara 1 a i
       * de esta manera llevo mejor el contador de partidas*/
      i++;
      break;
    }
  }
  // recordar que i son los juegos jugados

  printf("\t\t\n-----ESTADISTICAS-----\n");

  print_mean(scores, i);
  print_higher_score(scores, i);
  print_lower_score(scores, i);
  return EXIT_SUCCESS;
}

void reset_tracking(char A[]) {
  int i;
  for (i = 0; i < WORD_LENGTH - 1; i++) {
    A[i] = '-';
  }
}

void getWordInLine(char *fileName, int lineNumber, char *p) {
  FILE *fp;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  fp = fopen(fileName, "r");
  if (fp == NULL)
    exit(EXIT_FAILURE);

  int i = 1;
  while ((read = getline(&line, &len, fp)) != -1) {
    if (i == lineNumber) {
      strcpy(p, line);
      fclose(fp);
      p[5] = '\0';
      /*Aca tuve que agregar a este amigo
       * porque al parecer el puntero a p[5] me quedaba colgando, y tomaba
       * toda la stream que introducia en guess. Generando que tenga
       * una copia de guess en enigma, por tanto tenia ambas palabras
       * con un overflow en enigma. Es lo que pude deducir con los printf
       * las direcciones de memoria de cada uno. Eran una sucesion de
       * direcciones, como un array.*/
      return;
    }
    i++;
  }
}

int set_score(char tracking[], char guess_feedback[]) {
  /*recibira tracking para ver que letras fueron
   adivinadas ya, si la letra fue adivinada, no
   contara en el puntaje porque se marco previamen
   te en tracking. Tambien recibira el intento de la
   jugada actual.*/

  int guess_score = 0, i;

  for (i = 0; i < WORD_LENGTH - 1; i++) {
    if (guess_feedback[i] == '+' && tracking[i] != '.') {
      /* si la pega y es nueva, suma 100 y es marcada en tracking*/
      tracking[i] = '.';
      guess_score += WELL_PLACED_LETTER;
    } else if (guess_feedback[i] == '*' && tracking[i] != '.') {
      /* si casi la pega y es nueva, suma 50 y es
       * marcada en tracking*/
      tracking[i] = '.';
      guess_score += WRONG_PLACED_LETTER;
    }
  }
  if (user_won(guess_feedback)) {
    return WIN_SCORE;
  } else {
    return guess_score - PENALTY;
  }
}

void print_feedback(char feedback[], char word[], char guess[]) {
  int i = 0, j;
  printf("\n\t\t\t");
  for (j = 0; j < (int)strlen(guess); j++) {
    printf("%c ", guess[j]);
  }
  printf("\n\t\t\t");
  while (i < WORD_LENGTH - 1) {
    // loopeo por toda la string de manera que:
    if (word[i] == guess[i]) {
      /*si encuentro caracteres iguales en la misma
        posicion de la  palabra a adivinar y el
        intento,  printeo + y completo  feedback[i]*/

      feedback[i] = '+';
      printf("+ ");
    } else if (strchr(word, guess[i]) != NULL) {

      /*si encuentro que el caracter i del intento, se
        encuentra en la palabra a adivinar, printeo * y
        completo feedback[i]*/

      feedback[i] = '*';
      printf("* ");
    } else {
      //  /* si definitivamente el caracter no esta en la palabra a adivinar,
      //     printeo '-' y lo pongo en la misma posicion*/
      feedback[i] = '-';
      printf("- ");
    }
    i++;
  }
  printf("\n");
}

int user_won(char guess_feedback[]) {

  /*si detecta una seguidilla de 5 '+' en el
    intento actual, el usuario
    gana y devuelve 1, si no devuelve 0*/

  int i, count = 0;
  for (i = 0; i < WORD_LENGTH - 1; i++) {
    if (guess_feedback[i] == '+') {
      count++;
    }
  }
  if (count >= 5)
    return TRUE;
  return FALSE;
}

void print_mean(int scores[], int games) {
  // printea el promedio
  int i;
  float total = 0;
  for (i = 0; i < games; i++) {
    total += scores[i];
  }
  printf("El puntaje promedio de %d partida(s) fue %.3f\n", games,
         total / games);
}
void print_higher_score(int scores[], int games) {
  int i, greater_num = 0;
  for (i = 0; i < games; i++) {
    if (scores[i] > greater_num) {
      greater_num = scores[i];
      break;
    }
  }
  printf("El puntaje mas alto del juego fue %d en la partida %d\n", greater_num,
         i + 1);
}
void print_lower_score(int scores[], int games) {
  int i, lowest_num = scores[0];
  int game = 1;
  /* guarda en que juego se obtuvo el menor puntaje, inizializado
     en 1 porque si no se llegara a encontrar algun puntaje mayor
     que el primero , tendria basura dentro*/
  for (i = 0; i < games; i++) {
    if (scores[i] < lowest_num) {
      lowest_num = scores[i];
      game = i + 1;
    }
  }
  printf("El puntaje mas bajo del juego fue %d en la partida %d\n", lowest_num,
         game);
}
void capitalize_word(char guess[]) {
  int i;
  for (i = 0; i < strlen(guess); i++) {
    guess[i] = toupper(guess[i]);
  }
}
void clean_stdin(void) {
  while (getchar() != '\n')
    ;
  /* mientras c sea distinto de \n y EOF, sigue tomando caracteres*/
}

int get_file_lines(char file_name[]) {
  FILE *fp;           // puntero a un archivo
  int line_count = 0; // contador de lineas, cuenta cada '\n' del archivo
  char file_char;

  fp = fopen(file_name, "r"); // abro el archivo para leer nomas
  if (fp == NULL) {           // si falla, devolviendo null, sale de la funcion.
    return EXIT_FAILURE;
  }
  while ((file_char = fgetc(fp)) != EOF) {
    /*fgetc lee el siguiente caracter de fp y lo devuelve como un
      unsigned char casteado a int o EOF al final de linea o en un
      error*/
    /*aca a medida que leo los caracteres del puntero fp, los asigno a
      file_char y los comparo, si no es el final de linea, el loop
      continua. Luego lo comparo con el caracter de nueva linea,
      si encuentra que tienen el mismo valor, le sumo uno a la cuenta de
      lineas del archivo.*/
    if (file_char == '\n')
      line_count++;
  }
  fclose(fp); // cierro el archivo para evitar tener basura
  return line_count;
}
