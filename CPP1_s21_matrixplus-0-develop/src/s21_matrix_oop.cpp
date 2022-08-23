#include "s21_matrix_oop.h"

using namespace s21;

S21Matrix::S21Matrix(int rows, int colums) {
  // std::cout << "S21Matrix " << rows << " " << colums << std::endl;
  this->rows_ = rows;
  this->cols_ = colums;
  if (this->rows_ > 0 && this->cols_ > 0) {
    this->create_matrix();
  } else {
    throw std::out_of_range("S21Matrix - Rows/Cols must be over 0");
  }
}

S21Matrix::S21Matrix(const S21Matrix& another) {
  this->copy_matrix(another);
  // std::cout << "S21Matrix copy " << another.rows_ << " " << another.cols_
            // << std::endl;
}

S21Matrix::S21Matrix(S21Matrix&& another) {
  rows_ = another.rows_;
  cols_ = another.cols_;
  matrix_ = another.matrix_;
  // std::cout << "S21Matrix move " << rows_ << " " << cols_ << std::endl;
  another.matrix_ = nullptr;
  another.rows_ = another.cols_ = 0;
}

S21Matrix::~S21Matrix() {
  // std::cout << "~S21Matrix" << std::endl;
  this->remove_matrix();
}

// get

int S21Matrix::get_cols() const {
  int result = this->cols_;
  return result;
}

int S21Matrix::get_rows() const {
  int result = this->rows_;
  return result;
}

double S21Matrix::get_matr_value(int rows, int colums) const {
  double result;
  if (rows < this->rows_ && colums < this->cols_ && rows >= 0 && colums >= 0) {
    result = this->matrix_[rows][colums];
  } else {
    throw std::out_of_range(
        "get_matr_value - Colims and Rows must be over than 0 and less values of matrix parameters");
  }
  return result;
}

//set

void S21Matrix::set_cols(int colums) {
  if (colums > 0) {
    this->resize_matrix(this->rows_, colums);
  } else {
    throw std::out_of_range("set_cols - Colums must be over than 0");
  }
}

void S21Matrix::set_rows(int rows) {
  if (rows > 0) {
    this->resize_matrix(rows, this->cols_);
  } else {
    throw std::out_of_range("set_rows - Rows must be over than 0");
  }
}

void S21Matrix::set_matr_value(int rows, int colums, double num) {
  if (rows >= 0 && colums >= 0 && rows < this->rows_ && colums < this->cols_) {
    this->matrix_[rows][colums] = num;
  } else {
    throw std::out_of_range(
        "set_matr_value - Colims and Rows must be over than 0 and less values of matrix parameters");
  }
}

void S21Matrix::create_matrix() {
  if (this->rows_ > 0 && this->cols_ > 0) {
    this->matrix_ = new double*[this->rows_]();
    for (int i = 0; i < this->rows_; i++) {
      this->matrix_[i] = new double[this->cols_]();
    }
  }
}

void S21Matrix::remove_matrix() {
  if (this->check_matrix()) {
    for (int i = 0; i < this->rows_; i++) {
      delete[] this->matrix_[i];
      this->matrix_[i] = nullptr;
    }
    delete[] this->matrix_;
    this->matrix_ = nullptr;
  }
  this->rows_ = 0;
  this->cols_ = 0;
}



void S21Matrix::copy_matrix(const S21Matrix& another) {
  this->rows_ = another.rows_;
  this->cols_ = another.cols_;
  create_matrix();
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      this->matrix_[i][j] = another.matrix_[i][j];
    }
  }
}

void S21Matrix::resize_matrix(int rows, int colums) {
  if (this->rows_ != rows || this->cols_ != colums) {
    S21Matrix tmp(*this);
    this->remove_matrix();
    this->rows_ = rows;
    this->cols_ = colums;
    this->create_matrix();
    for (int i = 0; i < std::min(this->rows_, tmp.rows_); i++) {
      for (int j = 0; j < std::min(this->cols_, tmp.cols_); j++) {
        this->matrix_[i][j] = tmp.matrix_[i][j];
      }
    }
    tmp.remove_matrix();
  }
}

bool S21Matrix::eq_matrix(const S21Matrix& other) {
  bool result = false;
  if (this->checkSize_matrix(other)) {
    bool flag = false;
    for (int i = 0; i < this->rows_; i++) {
      if (flag) break;
      for (int j = 0; j < this->cols_; j++) {
        if (fabs(this->matrix_[i][j] - other.matrix_[i][j]) < EPS) {
          result = true;
        } else {
          result = false;
          flag = true;
          break;
        }
      }
    }
  }
  return result;
}

void S21Matrix::sum_matrix(const S21Matrix& other) {
  if (this->checkSize_matrix(other)) {
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < this->cols_; j++) {
        this->matrix_[i][j] += other.matrix_[i][j];
      }
    }
  } else {
    throw std::invalid_argument("sum_matrix - Matrixs should have equal size");
  }
}

void S21Matrix::sub_matrix(const S21Matrix& other) {
  if (this->checkSize_matrix(other)) {
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < this->cols_; j++) {
        this->matrix_[i][j] -= other.matrix_[i][j];
      }
    }
  } else {
    throw std::invalid_argument("sub_matrix - Matrixs should have equal size");
  }
}

void S21Matrix::mul_number(const double num) {
  if (this->check_matrix()) {
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < this->cols_; j++) {
        this->matrix_[i][j] *= num;
      }
    }
  } else {
    throw std::invalid_argument("mul_number - Matrix should be really");
  }
}

void S21Matrix::mul_matrix(const S21Matrix& other) {
  if (this->check_matrix() && other.check_matrix()) {
    if (this->cols_ != other.rows_ || this->matrix_ == other.matrix_) {
      throw std::invalid_argument(
          "mul_matrix - Columns matrix A should be equal rows matrix B");
    } else {
      S21Matrix tmp(*this);
      this->remove_matrix();
      this->rows_ = tmp.rows_;
      this->cols_ = other.cols_;
      this->create_matrix();
      for (int i = 0; i < tmp.rows_; i++) {
        for (int j = 0; j < other.cols_; j++) {
          for (int r = 0; r < tmp.cols_; r++) {
            this->matrix_[i][j] += tmp.matrix_[i][r] * other.matrix_[r][j];
          }
        }
      }
      tmp.remove_matrix();
    }
  } else {
    throw std::invalid_argument("mul_matrix - Matrixs should be really");
  }
}

S21Matrix S21Matrix::transpose() {
  if (this->check_matrix()) {
    S21Matrix tmp(*this);
    this->remove_matrix();
    this->rows_ = tmp.cols_;
    this->cols_ = tmp.rows_;
    this->create_matrix();
    for (int i = 0; i < tmp.rows_; i++) {
      for (int j = 0; j < tmp.cols_; j++) {
        this->matrix_[j][i] = tmp.matrix_[i][j];
      }
    }
    tmp.remove_matrix();
  } else {
    throw std::invalid_argument("transpose - Matrix should be really");
  }
  return *this;
}

void S21Matrix::get_minor(int row, int column) {
  S21Matrix tmp(*this);
  this->remove_matrix();
  this->rows_ = tmp.rows_ - 1;
  this->cols_ = tmp.cols_ - 1;
  this->create_matrix();
  int z = 0;
  for (int i = 0; i < tmp.rows_; i++) {
    if (i != row) {
      int k = 0;
      for (int j = 0; j < tmp.cols_; j++) {
        if (j != column) {
          this->matrix_[z][k] = tmp.matrix_[i][j];
          k++;
        }
      }
      z++;
    }
  }
  tmp.remove_matrix();
}

double S21Matrix::determinant() {
  double determ = 0.0;
  if (this->checkSquare_matrix()) {
    if (this->rows_ == 1) {
      determ = this->matrix_[0][0];
    } else if (this->rows_ == 2) {
      determ += (this->matrix_[0][0] * this->matrix_[1][1] -
                 this->matrix_[1][0] * this->matrix_[0][1]);
    } else {
      int minus = -1;
      for (int i = 0; i < this->rows_; i++) {
        S21Matrix minor(*this);
        minor.get_minor(i, 0);
        minus *= -1;
        determ += (minus * this->matrix_[i][0] * minor.determinant());
      }
    }
  } else {
    throw std::invalid_argument("determinant - Matrix should be square");
  }
  return determ;
}

S21Matrix S21Matrix::calc_complements() {
  S21Matrix tmp(*this);
  if (this->checkSquare_matrix()) {
    if (this->rows_ == 1) {
      tmp.matrix_[0][0] = 1;
    } else {
      for (int i = 0; i < this->rows_; i++) {
        for (int j = 0; j < this->cols_; j++) {
          S21Matrix minor(*this);
          minor.get_minor(i, j);
          double number = minor.determinant();
          tmp.matrix_[i][j] = ((i + j) % 2 == 1 ? -1 : 1) * number;
          minor.remove_matrix();
        }
      }
    }
  } else {
    tmp.remove_matrix();
    throw std::invalid_argument("Matrix should be square");
  }
  return tmp;
}

S21Matrix S21Matrix::inverse_matrix() {
  S21Matrix tmp(this->calc_complements());
  double determinant = this->determinant();
  if (determinant != 0.0) {
    tmp.transpose();
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < this->cols_; j++) {
        tmp.matrix_[i][j] = (double)tmp.matrix_[i][j] / (double)determinant;
      }
    }
  } else {
    throw std::invalid_argument(
        "Matrix should be square or determinant should be not equal 0");
  }

  return tmp;
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) {
  S21Matrix result(*this);
  result.sum_matrix(other);
  return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) {
  S21Matrix result(*this);
  result.sub_matrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) {
  S21Matrix result(*this);
  result.mul_matrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const double number) {
  S21Matrix result(*this);
  result.mul_number(number);
  return result;
}

bool S21Matrix::operator==(const S21Matrix& other) {
  return this->eq_matrix(other);
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  if (other.matrix_ != this->matrix_) {
    this->remove_matrix();
    this->copy_matrix(other);
  }
  return *this;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  this->sum_matrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  this->sub_matrix(other);
  return *this;
}
S21Matrix S21Matrix::operator*=(const S21Matrix& other) {
  this->mul_matrix(other);
  return *this;
}
S21Matrix S21Matrix::operator*=(const double num) {
  this->mul_number(num);
  return *this;
}

double S21Matrix::operator()(int rows, int colums) {
  return this->get_matr_value(rows, colums);
}

// void S21Matrix::print_matrix() const {
//   for (int i = 0; i < this->rows_; i++) {
//     for (int j = 0; j < this->cols_; j++) {
//       std::cout.setf(std::ios::left);
//       std::cout.width(5);
//       std::cout << get_matr_value(i,j);
//     }
//     std::cout << std::endl;
//   }
// }

// void S21Matrix::fill_matrix(double num) {
//   for (int i = 0; i < this->rows_; i++) {
//     for (int j = 0; j < this->cols_; j++) {
//       this->matrix_[i][j] = num;
//       num++;
//     }
//   }
// }

bool S21Matrix::check_matrix() const {
  bool result = false;
  if (this->rows_ > 0 && this->cols_ > 0 && this->matrix_ != nullptr) {
    result = true;
  }
  return result;
}

bool S21Matrix::checkSize_matrix(const S21Matrix& other) const {
  bool result = false;
  if (this->check_matrix() && other.check_matrix()) {
    if (this->rows_ == other.rows_ && this->cols_ == other.cols_) {
      result = true;
    }
  }
  return result;
}

bool S21Matrix::checkSquare_matrix() const {
  bool result = false;
  if (this->check_matrix()) {
    if (this->rows_ == this->cols_) {
      result = true;
    }
  }
  return result;
}
