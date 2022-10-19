// vector_class_step2.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

class CVector { //클래스 벡터 정의
private:
    int mSize; // 벡터의 차원
    double* mVec; // 벡터 배열의 포인터
public:
    CVector() {  // 기본 생성자 1차원 벡터(실수)
        mSize = 1;
        mVec = new double[mSize];
        mVec[0] = 0.0;
    }; // 세미콜론(;) 필요함
    CVector(int size, double arr[]); //CVector myVec(3,arr); CVector myV;
    // Copy Constructor
    CVector (Cvector& cv); //make class variation same with cv f(myVec)
    void ScalarMul(double alpha); //벡터의 상수배
    void Print(); //출력하기
    void Add(CVector vec);
    // Desctructor --> 
    ~CVector() { delete[] mVec; };
};

void CVector::Add(CVector vec)
{
    //Check size
    for(int i=0;i<mSize;i++){
        mVec[i] += vec.mVec[i];
    }
}

void CVector::Print()
{
printf("[");
for (i=0;i<mSize;i++{
printf("%f", mVec[i]); //%5.2f
}
printf("]\n");
}

void CVector::ScalarMul(double alpha) {
for(int i=0;i<mSize;i++){
mVec[i] *= alpha;
}

CVector::CVector(CVector& cv) {
mSize = cv.mSize;
//working who default copy constructor: mVec = cv.mVec;

mVec = new double[mSize];
for(int i=0;i<mSize;i++){
mVec[i]=cv.mVec[i];
}
} 

CVector::CVector(int size, double arr[]) {
    mSize = size;
    mVec = new double[mSize]; 
    for (int i = 0; i < size; i++) {
        mVec[i] = arr[i];
    }
}

void CVector_test(){
CVector vec1;
double arr1[3] = {1.0,2.0,3.0}
CVector vec2(3, arr1);

vec1.Print();
vec2.Print();
vec2.ScalarMul(10.);
vec2.Print();
}



int main()
{
    CVector_test();
