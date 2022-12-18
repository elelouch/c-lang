#include "header.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int row1, col1;
  int row2, col2;
  int **matrix1;
  int **matrix2;
  int **matrix_result;
  int choice, scalar;

  if (argc > MAX_ARGUMENTS) {
    printf("Too many arguments \n");
    return EXIT_FAILURE;
  } else if (argc < MAX_ARGUMENTS) {
    printf("Too few arguments \n");
    return EXIT_FAILURE;
  }
  choice = ((int)argv[1][0]) - ASCII_NUM;
  /*Since number chars 0-9 have values between 48-57 respectively
   * I just cast the char from the input and then use it*/
  if (choice < OPERATIONS_LOW || choice > OPERATIONS_MAX) {
    printf("Option not available, check the following: \n");
    printf("1) Sum two matrices\n");
    printf("2) Product between two matrices\n");
    printf("3) Transpose a matrix\n");
    printf("4) Scalar product\n");
    printf("5) Get the determinant of a matrix\n");
  }

  switch (choice) {
  case PRODUCT:
    printf("You choose product between matrices!\n");

    printf("First matrix rows amount and second matrix columns amount must be "
           "the same in order to get the product matrix\n");
    do {
      printf("---------First matrix size--------\n");
      ask_input(&row1, &col1);
      printf("---------Second matrix size--------\n");
      ask_input(&row2, &col2);
    } while (col1 != row2);

    fill_matrices(&matrix1, &matrix2, row1, row2, col1, col2);

    matrix_result = product_matrix(matrix1, matrix2, row1, col2, row2);
    printf("First matrix : \n");
    pmatrix(matrix1, row1, col1);
    printf("Second matrix : \n");
    pmatrix(matrix2, row2, col2);
    printf("Result matrix : \n");
    pmatrix(matrix_result, row1, col2);

    freematrix(matrix1, row1);
    freematrix(matrix2, row2);
    freematrix(matrix_result, row1);

    break;
  case SUM:
    printf("You choose sum between matrices!\n");
    /* ask input*/
    do {
      printf("---------First matrix size--------\n");
      ask_input(&row1, &col1);
      printf("---------Second matrix size--------\n");
      ask_input(&row2, &col2);
    } while (!(col1 == col2 && row1 == row2));

    /*create and fill both matrices*/
    matrix1 = mmatrix(row1, col1);
    matrix2 = mmatrix(row2, col2);
    printf("\n\n");
    fmatrix(matrix1, row1, col1);
    fmatrix(matrix2, row2, col2);

    /*save the pointer to the sum matrix in matrix result*/
    matrix_result = sum_matrices(matrix1, matrix2, row1, col1);
    printf("First matrix : \n");
    pmatrix(matrix1, row1, col1);
    printf("Second matrix : \n");
    pmatrix(matrix2, row2, col2);
    printf("Result matrix : \n");
    pmatrix(matrix_result, row1, col2);

    freematrix(matrix1, row1);
    freematrix(matrix2, row2);
    freematrix(matrix_result, row1);
    break;
  case SCALAR:
    printf("You choose scalar of a matrix!\n");

    ask_input(&row1, &col1);
    matrix1 = mmatrix(row1, col1);
    fmatrix(matrix1, row1, col1);
    printf("Insert a scalar number: ");
    if (scanf("%d", &scalar) != 1)
      printf("failed to assign a number");
    matrix_scalar(matrix1, row1, col1, scalar);

    printf("Result matrix : \n");
    pmatrix(matrix1, row1, col1);
    freematrix(matrix1, row1);

    break;
  case DETERMINANT:
    printf("You choose determinant of a matrix\n");
    printf("Insert a square matrix size to calculate the determinant: \n");
    do {
      scanf("%d", &row1);
    } while (row1 < 0);

    matrix1 = mmatrix(row1, row1);
    fmatrix(matrix1, row1, row1);
    printf("the matrix determinant is : %d \n",
           matrix_determinant(matrix1, row1));
    pmatrix(matrix1, row1, row1);
    freematrix(matrix1, row1);
    break;

  case TRANSPOSE:
    ask_input(&row1, &col1);
    matrix1 = mmatrix(row1, col1);
    fmatrix(matrix1, row1, col1);
    matrix2 = transpose_matrix(matrix1, row1, col1);
    pmatrix(matrix2, row1, col1);
    freematrix(matrix1, row1);
    freematrix(matrix2, col1);
    /* since a transposed matrix of a MxN matrix has
     * NxM sice, I use col1 as rows to free the matrices*/

    break;
  }
  return EXIT_SUCCESS;
}

int **mmatrix(int row, int col) {
  int **new_matrix = (int **)malloc(row * sizeof(int *));
  if (new_matrix == NULL) {
    printf("Not enough memory \n");
    return new_matrix;
  }
  int i;
  for (i = 0; i < row; i++) {
    *(new_matrix + i) = (int *)calloc(col, sizeof(int));
    if (*(new_matrix + i) == NULL) {
      printf("Not enough memory \n");
      return new_matrix;
    }
  }
  return new_matrix;
}
void fmatrix(int **matrix, int row, int col) {
  int i, j;
  printf("Fill the matrix!\n");
  for (i = 0; i < row; i++) {
    for (j = 0; j < col; j++) {
      pmatrix(matrix, row, col);
      printf("(%d,%d)th element: ", i + 1, j + 1);
      scanf("%d", *(matrix + i) + j);
      printf("\n");
    }
  }
}
int **product_matrix(int **matrix1, int **matrix2, int row, int col,
                     int index) {
  int **new_matrix = mmatrix(row, col);
  int i, j, k;
  if (new_matrix == NULL) {
    printf("Not enough memory\n");
    return new_matrix;
  }

  /*for the (i,j)th element of MxN matrix, we have to
   * sum the products of the ith rows between the jth rows.
   * Thus, each (i,j)th element of the result matrix(C = A.B) is defined as
   * Cij = Ai1B1j + Ai2B2j + ... + AikBkj */

  for (i = 0; i < row; i++) {
    for (j = 0; j < col; j++) {
      for (k = 0; k < index; k++) {
        new_matrix[i][j] += matrix1[i][k] * matrix2[k][j];
      }
    }
  }
  return new_matrix;
}
void ask_input(int *row, int *col) {
  printf("Insert [rows],then followed by a space the [cols] of the matrix \n");
  scanf("%d %d", row, col);
}
void pmatrix(int **matrix, int row, int col) {
  int i, j;
  for (i = 0; i < row; i++) {
    for (j = 0; j < col; j++) {
      printf("%d ", matrix[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}
void freematrix(int **matrix, int rows) {
  int i;
  for (i = 0; i < rows; i++) {
    free(*(matrix + i));
  }
  free(matrix);
}
int **sum_matrices(int **matrix1, int **matrix2, int row, int col) {
  int **new_matrix = (int **)malloc(sizeof(int *) * row);
  int i, j;
  if (new_matrix == NULL) {
    printf("Not enough memory");
  }
  for (i = 0; i < row; i++) {
    *(new_matrix + i) = (int *)calloc(row, sizeof(int));
    if (*(new_matrix + i) == NULL) {
      printf("Not enough memory");
    }
  }

  for (i = 0; i < row; i++) {
    for (j = 0; j < col; j++) {
      *(*(new_matrix + i) + j) = *(*(matrix1 + i) + j) + *(*(matrix2 + i) + j);
    }
  }
  return new_matrix;
}
int **transpose_matrix(int **matrix, int row, int col) {
  int **new_matrix = (int **)malloc(sizeof(int *) * col);
  int i, j;
  if (new_matrix == NULL) {
    printf("Not enough memory");
  }
  for (i = 0; i < row; i++) {
    *(new_matrix + i) = (int *)calloc(row, sizeof(int));
    if (*(new_matrix + i) == NULL) {
      printf("Not enough memory");
    }
  }
  for (i = 0; i < row; i++) {
    for (j = 0; j < col; j++) {
      *(*(new_matrix + j) + i) = *(*(matrix + i) + j);
    }
  }
  return new_matrix;
}
void fill_matrices(int ***matrix1, int ***matrix2, int row1, int col1, int row2,
                   int col2) {
  printf("---------First matrix elements--------\n");
  *matrix1 = mmatrix(row1, col1);
  fmatrix(*matrix1, row1, col1);
  printf("---------Second matrix elements--------\n");
  *matrix2 = mmatrix(row2, col2);
  fmatrix(*matrix2, row2, col2);
}
int matrix_determinant(int **matrix, int size) {
  int i, j, k;
  int **minor = mmatrix(size, size);
  int result = 0;
  if (size == 2) {
    return matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1];
  }

  for (i = 0; i < size; i++) {
    for (j = 0; j < size; j++) {
      for (k = 0; k < size; k++) {
        if (j != 0 && k != i) {
          if (k > i) {
            minor[j - 1][k - 1] = matrix[j][k];
          } else {
            minor[j - 1][k] = matrix[j][k];
          }
        }
      }
    }
    result +=
        (int)pow((-1), i) * matrix[0][i] * matrix_determinant(minor, size - 1);
  }
  freematrix(minor, size - 1);
  return result;
}
void matrix_scalar(int **matrix, int row, int col, int scalar) {
  int i, j;
  for (i = 0; i < row; i++) {
    for (j = 0; j < col; j++) {
      matrix[i][j] *= scalar;
    }
  }
}
