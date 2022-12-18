#define ASCII_NUM 48
#define MAX_ARGUMENTS 2
#define OPERATIONS_LOW 1
#define OPERATIONS_MAX 5

typedef enum {
  SUM = 1,
  PRODUCT = 2,
  TRANSPOSE = 3,
  SCALAR = 4,
  DETERMINANT = 5
} operations;

/*matrix control*/
int **mmatrix(int, int);        // make matrix
void fmatrix(int **, int, int); // fill matrix
void ask_input(int *, int *);
void pmatrix(int **, int, int); // print matrix
void freematrix(int **, int);
void fill_matrices(int ***, int ***, int, int, int, int);

/*actual operations*/

int **product_matrix(int **, int **, int, int, int);
/* return pointer to product matrix */

int **sum_matrices(int **, int **, int, int);
/* returns pointer to sum matrix*/

int **transpose_matrix(int **, int, int);
/* returns pointer to the transposed matrix*/

void matrix_scalar(int **, int, int, int);
/* modifies the same matrix*/

int matrix_determinant(int **, int);
/* returns matrix determinant*/
