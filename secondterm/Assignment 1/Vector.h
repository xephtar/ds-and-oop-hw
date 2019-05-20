/* @Author

* Student Name: Ömer Faruk Davarcı
* Student ID: 150160048      */
#include <new>
using namespace std;

class VectorX{
  private:
    int size;
    int *value;
  public:
    //constructor
    VectorX(): size(0), value(NULL) {
      this->allocateMemory();
    };
    //destructor
    ~VectorX(){
      delete []value;
    };
    //get size of vector
    int getSize()const{
      return size;
    }
    //allocate memory
    void allocateMemory(){
      this->value = new int[this->size];
    }
    //set value and size
    VectorX(int s, int *arr): size(s), value(arr){
      this->allocateMemory();
      for (int i = 0; i < s; i++){
        value[i] = arr[i];
      }
    };
    //copy constructor
    VectorX(const VectorX &v){
      size = v.size;
      this->allocateMemory();
      for (int i = 0; i < size; i++){
        value[i] = v.value[i];
      }
    };
    //() overload function
    VectorX operator()(int a, int *p){
      VectorX result(a,p);
      return result;
    };
    // multiplication overload for scalars
    VectorX operator*(const int scalar){
      VectorX vect(size,value);
      for (int i = 0; i < size; i++) {
        vect.value[i] = value[i] * scalar;
      }
      return vect;
    };
    // multiplication overload for vetoral
    int operator*(const VectorX& vectAdded){
      VectorX vect(size,value);
      for (int i = 0; i < size; i++) {
        vect.value[i] = value[i] * vectAdded.value[i];
      }
      int result = 0;
      for (int i = 0; i < size; i++) {
        result += vect.value[i];
      }
      return result;
    };
    // addition overload
    VectorX operator+(const VectorX& vectAdded){
      VectorX vectResult(this->size,this->value);
      for (int i = 0; i < this->size; i++) {
        vectResult.value[i] = this->value[i] + vectAdded.value[i];
      }
      return vectResult;
    };
    //display overload
    friend ostream& operator<<(ostream& , const VectorX&);
};

ostream& operator<<(ostream& out, const VectorX& vect)
{
 out << "(";
 for (int i = 0; i < vect.size; i++) {
     if (i == vect.size - 1) {
       out << vect.value[i];
     }else{
       out << vect.value[i] << ", ";
     }
   }
 out << ")";
 return out;
}
