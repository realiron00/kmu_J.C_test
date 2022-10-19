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

    // Desctructor --> 
    ~CVector() { delete[] mVec; };
};

CVector::CVector(CVector& cv) {
mSize = cv.mSize;
//mVec = cv.mVec;

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





int main()
{
    std::cout << "Hello World!\n";
