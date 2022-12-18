#define WORD_LENGTH 6 // 5chars + '\0'
#define YES 'S'
#define NO 'N'
#define FALSE 0
#define TRUE 1
#define MAX_GAMES 8
#define MIN_GAMES 1
#define TRIES_PER_GAME 6
#define START_SCORE 5000
#define WIN_SCORE 2000
#define HIGHEST_SCORE 10000
#define LOWEST_SCORE 0
#define PENALTY 500
#define WELL_PLACED_LETTER 100
#define WRONG_PLACED_LETTER 50
#define EXTERNAL_FILE "palabras.txt"
// reemplazar string por el path del archivo a utilizar
void getWordInLine(char *, int, char *); // funcion provista
                                         // utilidades
int set_score(char[], char[]);
void reset_tracking(char[]);
void print_feedback(char[], char[], char[]);
void clean_stdin();
void capitalize_word(char[]);
int user_won(char[]);
int get_file_lines(char[]);
// estadisticas
void print_mean(int[], int);
void print_higher_score(int[], int);
void print_lower_score(int[], int);
