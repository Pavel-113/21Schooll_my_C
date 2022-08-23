#include "s21_matrix.h"

int is_correct(matrix_t *A);
int is_correct_x(matrix_t *A, matrix_t *B);
matrix_t get_minor(matrix_t *A, int n, int m);

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int error = 1;
  if (result != NULL) {
    result->columns = columns;
    result->rows = rows;

    if (rows > 0 && columns > 0) {
      result->matrix = (double **)calloc(rows, sizeof(double *));
      for (int i = 0; i < result->rows; i++) {
        result->matrix[i] = (double *)calloc(result->columns, sizeof(double));
      }
      error = 0;
    }
  }
  return error;
}

void s21_remove_matrix(matrix_t *A) {
  if (A != NULL) {
    if (A->rows > 0 && A->columns > 0) {
      if (A->matrix != NULL) {
        for (int i = 0; i < A->rows; i++) {
          free(A->matrix[i]);
        }
        free(A->matrix);
      }
    }
    A->matrix = NULL;
    A->columns = 0;
    A->rows = 0;
  }
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int result = FAILURE;
  if (is_correct_x(A, B) == 2 && A->rows == B->rows &&
      A->columns == B->columns) {
    result = SUCCESS;
    for (int i = 0; i < A->rows && result == SUCCESS; i++) {
      for (int j = 0; j < A->columns && result == SUCCESS; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > EPS) {
          result = FAILURE;
        }
      }
    }
  }
  return result;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = is_correct_x(A, B);
  if (error == 2 && A->rows == B->rows && A->columns == B->columns) {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
      }
    }
    error = 0;
  } else {
    result->matrix = NULL;
    result->columns = 0;
    result->rows = 0;
  }
  return error;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = is_correct_x(A, B);
  if (error == 2 && A->rows == B->rows && A->columns == B->columns) {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
      }
    }
    error = 0;
  } else {
    result->matrix = NULL;
    result->columns = 0;
    result->rows = 0;
  }
  return error;
}
int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int error = is_correct(A);
  if (error == 2) {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
    error = 0;
  } else {
    result->matrix = NULL;
    result->columns = 0;
    result->rows = 0;
  }
  return error;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = is_correct_x(A, B);
  if (error == 2 && A->columns == B->rows) {
    s21_create_matrix(A->rows, B->columns, result);
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        result->matrix[i][j] = 0;
        for (int k = 0; k < A->columns; k++) {
          result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
        }
      }
    }
    error = 0;
  } else {
    result->matrix = NULL;
    result->columns = 0;
    result->rows = 0;
  }
  return error;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int error = is_correct(A);
  if (error == 2) {
    s21_create_matrix(A->columns, A->rows, result);
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        result->matrix[i][j] = A->matrix[j][i];
      }
    }
    error = 0;
  } else {
    result->matrix = NULL;
    result->columns = 0;
    result->rows = 0;
  }
  return error;
}

matrix_t get_minor(matrix_t *A, int n, int m) {
  matrix_t M;
  if (A->columns > 1 && A->rows > 1) {
    s21_create_matrix(A->rows - 1, A->columns - 1, &M);
    int ii = 0;
    for (int i = 0; i < M.rows; i++) {
      if (ii == n) ii = ii + 1;
      int jj = 0;
      for (int j = 0; j < M.columns; j++) {
        if (j == m) jj = jj + 1;
        M.matrix[i][j] = A->matrix[ii][jj];
        jj++;
      }
      ii++;
    }
  } else {
    s21_create_matrix(0, 0, &M);
  }
  return M;
}

int s21_determinant(matrix_t *A, double *result) {
  int error = is_correct(A);
  if (error == 2 && A->columns == A->rows) {
    if (A->columns == 1) {
      *result = A->matrix[0][0];
    } else if (A->columns == 2) {
      *result =
          A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
    } else {
      for (int i = 0; i < A->columns; i++) {
        double resM = 0.0;
        matrix_t M = get_minor(A, i, 0);
        int MINUS = (i % 2) == 0 ? 1 : -1;
        s21_determinant(&M, &resM);
        *result += MINUS * A->matrix[i][0] * resM;
        s21_remove_matrix(&M);
      }
    }
    error = 0;
  } else {
    *result = NAN;
  }
  return error;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int error = is_correct(A);
  if (error == 2 && A->columns == A->rows) {
    if (A->columns == 1) {
      s21_create_matrix(1, 1, result);
      result->matrix[0][0] = 1;
    } else {
      s21_create_matrix(A->columns, A->rows, result);
      for (int i = 0; i < result->rows; i++) {
        for (int j = 0; j < result->columns; j++) {
          double resM = 0.0;
          matrix_t M = get_minor(A, i, j);
          int MINUS = ((i + j) % 2) == 0 ? 1 : -1;
          s21_determinant(&M, &resM);
          result->matrix[i][j] = MINUS * resM;
          s21_remove_matrix(&M);
        }
      }
    }
    error = 0;
  } else {
    result->matrix = NULL;
    result->columns = 0;
    result->rows = 0;
  }
  return error;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int error = is_correct(A);
  if (error == 2 && A->columns == A->rows) {
    double res = 0.0;
    s21_determinant(A, &res);
    if (res != 0) {
      matrix_t A_comp;
      s21_calc_complements(A, &A_comp);
      s21_transpose(&A_comp, result);
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = result->matrix[i][j] / res;
        }
      }
      s21_remove_matrix(&A_comp);
      error = 0;
    } else {
      result->matrix = NULL;
      result->columns = 0;
      result->rows = 0;
    }
  } else {
    result->matrix = NULL;
    result->columns = 0;
    result->rows = 0;
  }
  return error;
}

int is_correct(matrix_t *A) {
  int result = 1;
  if (A != NULL) {
    if (A->rows > 0 && A->columns > 0 && A->matrix != NULL) {
      result = 2;
    }
  }
  return result;
}

int is_correct_x(matrix_t *A, matrix_t *B) {
  int result = 1;
  if (A != NULL && B != NULL) {
    if ((A->rows > 0 && A->columns > 0 && A->matrix != NULL) &&
        (B->rows > 0 && B->columns > 0 && B->matrix != NULL)) {
      result = 2;
    }
  }
  return result;
}
