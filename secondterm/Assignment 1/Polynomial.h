/* @Author

* Student Name: Ömer Faruk Davarcı
* Student ID: 150160048      */

#include <new>
using namespace std;

class Polynomial{
  private:
    int degree;
    int *coefficient;
  public:
    //constructor
    Polynomial(): degree(0), coefficient(NULL) {
    };
    //destructor
    ~Polynomial(){
      delete []coefficient;
    };
    //get degree of poly
    int getDegree()const{
      return degree;
    }
    //allocate memory
    void allocateMemory(){
      int size = degree + 1;
      coefficient = new int[size];
    };
    //set coefficients and degree
    Polynomial(int s, int *arr): degree(s), coefficient(arr){
      this->allocateMemory();
      for (int i = 0; i <= s; i++){
        coefficient[i] = arr[i];
      }
    };
    //copy constructor
    Polynomial(const Polynomial &p){
        degree = p.degree;
        allocateMemory();
        for (int i = 0; i <= degree; i++) {
          coefficient[i] = p.coefficient[i];
        }
    };
    // () overload
    Polynomial operator()(int a, int *p){
      Polynomial result(a,p);
      return result;
    };
    //multiplication overload
    Polynomial operator*(const Polynomial &polyAdded){
      int p[degree+polyAdded.degree+1];
      for (int i = 0; i < degree+polyAdded.degree+1; i++) {
        p[i] = 0;
      }//i am doing this because when i initialize zero, some c++ versions does not
      for (int i = 0; i <= degree; i++) {
        for (int j = 0; j <= polyAdded.degree; j++) {
          int a = coefficient[i] * polyAdded.coefficient[j];
          p[i+j] += a;
        }
      }
      Polynomial result(degree+polyAdded.degree,p);
      return result;
    };
    //addition overload
    Polynomial operator+(const Polynomial &polyAdded){
      if (degree > polyAdded.degree) {
        int p[degree+1];
        for (int i = 0; i <= polyAdded.degree; i++) {
          p[i] = coefficient[i] + polyAdded.coefficient[i];
        }
        for (int i = polyAdded.degree+1; i <= degree; i++) {
          p[i] = coefficient[i];
        }
        Polynomial result(degree,p);
        return result;
      }else{
        int p[polyAdded.degree+1];
        for (int i = 0; i <= degree; i++) {
          p[i] = coefficient[i] + polyAdded.coefficient[i];
        }
        for (int i = degree+1; i <= polyAdded.degree; i++) {
          p[i] = polyAdded.coefficient[i];
        }
        Polynomial result(polyAdded.degree,p);
        return result;
      }
    };
    //display overload
    friend ostream& operator<<(ostream& , const Polynomial&);
};

ostream& operator<<(ostream& os, const Polynomial& poly)
{
  for (int i = poly.degree; i >= 0 ; i--) {
    if (i == 0) {
      os << poly.coefficient[i];
    }else if (i == 1) {
      if (poly.coefficient[i] == 1) {
        os << "x" << " + ";
      }else{
        os << poly.coefficient[i] << "x" << " + ";
      }
    }else{
      if (poly.coefficient[i] == 1) {
        os << "x^" << i << " + ";
      }else{
        os << poly.coefficient[i] << "x^" << i << " + ";
      }
    }
  }
 return os;
}
