#include <iostream>
using namespace std;

typedef unsigned char byte;

void GF_print(byte gf)
{
  int coef;
  
  printf("%d = %02x = ", gf, gf);
  for(int i=7;i>=0;i++){
    coef = (gf >> i) & 0x01;
    if (coef==1){
      cout << "+" << "x^" << i;
    }
  }
  std::cout << std::endl;
}

byte GF_add(byte gf1, byte gf2) {
    return gf1 ^ gf2;
}

byte GF_xtime(byte gf) {
    int msb;
    byte result;

    msb = (gf >> 7) & 0x01;
    if (msb == 1) {
        result = (gf << 1) ^ 0x1b;
    }
    else {
        result = gf << 1;
    }
    return result;
}

byte GF_mul(byte f, byte g) {
    byte h; 
    int coef; 
    h = 0x00;
    for (int i = 7; i >= 0; i--) {
        coef = (f >> i) & 0x01; 
        h = GF_xtime(h);
        if (coef == 1) {
            h = GF_add(h, g);
        }
    }
    return h;
}

byte GF_inv(byte f) {
    byte f_inv; 
    byte temp; 
    f_inv = 1;
    temp = f;
    for (int i = 0; i < 7; i++) {
        temp = GF_mul(temp, temp);
        f_inv = GF_mul(f_inv, temp);
    }
    return f_inv;
}
#define MATRIX_MAX_SIZE 8 

// GF_Matrix 구조체 사용
struct GF_Matrix {
    byte M[MATRIX_MAX_SIZE][MATRIX_MAX_SIZE];
    int row;
    int col;
};

// GF_Matrix 인스턴스 생성&초기화
GF_Matrix GF_Mat_init() {
    GF_Matrix M;
    M.row = 1;
    M.col = 1;
    M.M[0][0] = 0x01;

    return M;
}

// GF_Matrix 출력
void GF_Mat_print(GF_Matrix Mat) {
    for (int i = 0; i < Mat.row; i++) {
        printf("[");
        for (int j = 0; j < Mat.col; j++) {
            printf(" %02x", Mat.M[i][j]);
        }
        printf(" ]\n");
    }
    printf("\n");
}

// GF_Matrix 곱셈
GF_Matrix GF_Mat_Mul(GF_Matrix A, GF_Matrix B) {
    GF_Matrix AB;
    byte temp;

    AB = GF_Mat_init();
    if (A.col != B.row) {
        cout << "Matrix size error! \n";
        return AB;
    }

    AB.row = A.row;
    AB.col = B.col;
    for (int i = 0; i < AB.row; i++) {
        for (int j = 0; j < AB.col; j++) {
            AB.M[i][j] = 0x00;
            for (int k = 0; k < A.col; k++) {
                temp = GF_mul(A.M[i][k], B.M[k][j]);
                AB.M[i][j] = GF_add(AB.M[i][j], temp);
            }
        }
    }
    return AB;
}

//역행렬 구하기
void GF_Mat_Exchange_Row(GF_Matrix& A, int row1, int row2) {
    byte tmp;
    for (int i = 0; i < A.col; i++) {
        tmp = A.M[row1][i];
        A.M[row1][i] = A.M[row2][i];
        A.M[row2][i] = tmp;
    }
}

void GF_Mat_Scalar_Mul(GF_Matrix& A, byte scalar, int row) {
    byte temp;
    for (int i = 0; i < A.col; i++) {
        temp = GF_mul(scalar, A.M[row][i]);
        A.M[row][i] = temp;
    }
}

void GF_Mat_Row_Add(GF_Matrix& A, byte scalar, int row_src, int row_target) {
    byte temp;
    for (int i = 0; i < A.col; i++) {
        temp = GF_mul(scalar, A.M[row_src][i]);
        A.M[row_target][i] = GF_add(A.M[row_target][i], temp);
    }
}

GF_Matrix GF_Mat_inverse(GF_Matrix A) {
    GF_Matrix AA;
    int pivot_row;

    //[실습] GF(2^8)의 행렬에 대한 역행렬 구하기
    //  Matrix_ver2.cpp의 코드를 수정하여 만들기
    //  (힌트: 연산만 GF(2^8)에 맞게 수정하면 됨)
    //=======================================
    // 행렬 A와 단위행렬 I를 옆으로 붙여 행렬 AA를 만든다. AA = [ A | I ]
    AA.row = A.row;
    AA.col = A.col * 2;
    for (int i = 0; i < A.row; i++) {
        for (int j = 0; j < A.col; j++) {
            AA.M[i][j] = A.M[i][j];
            //[실습7-a] 단위행렬을 오른쪽에 넣기 AA = [ A | I ]
            AA.M[i][j + A.col] = (i == j) ? 0x01 : 0x00;  // GF(2^8) 원소의 1과 0으로
        }
    }

    // Reduced REF(Row Echelon Form) 사다리꼴을 만들어 역행렬을 구한다.
    for (int j = 0; j < A.col; j++) {
        pivot_row = -1;  // 핵심 행(피봇 행)을 찾는다. (초기값 -1로 설정)
        for (int i = j; i < A.row; i++) {
            if (AA.M[i][j] != 0x00) { // [j][j], [j+1][j], [j+2][j] 중 0이 아닌 것
                //[실습7-b] 피봇 행을 설정
                pivot_row = i;
                break;
            }
        }
        if (pivot_row == -1) {  // 피봇 행이 없으면 (모두 0인 경우)
            cout << "Not invertible !" << endl;  // 역행렬 없음
            return A;  // 의미없는 리턴값
        }
        if (pivot_row != j) { // pivot : [0][0] [1][1] [2][2]
            //[실습7-c] -- [j][j]가 피봇이 되도록 행을 교환한다
            GF_Mat_Exchange_Row(AA, j, pivot_row);
        }
        byte temp;
        temp = GF_inv(AA.M[j][j]); // 곱셈의 역원
        GF_Mat_Scalar_Mul(AA, temp, j); // 피봇값이 1이 되도록 조정한다
        for (int i = 0; i < A.row; i++) {
            if ((i != j) && (AA.M[i][j] != 0x00)) {
                //[실습7-d] 피봇행을 기준으로 다른행의 피봇열은 0으로 만든다.
                GF_Mat_Row_Add(AA, AA.M[i][j], j, i);
            }
        }
        //[실습7-e] 단계별 결과를 출력하기
        GF_Mat_print(AA);
    }
    //=======================================
    GF_Matrix Inv;
    Inv.row = A.row;
    Inv.col = A.col;
    for (int i = 0; i < A.row; i++) {
        for (int j = 0; j < A.col; j++) {
            Inv.M[i][j] = AA.M[i][A.col + j];
        }
    }
    return Inv;
}


void Run_GF_matrix_test() {
    byte MixCol[4][4] = { {0x02, 0x03, 0x01, 0x01}, {0x01, 0x02, 0x03, 0x01},
                          {0x01, 0x01, 0x02, 0x03} , {0x03, 0x01, 0x01, 0x02} };
    //byte MixCol[4][4] = { {0x01, 0x00, 0x00, 0x00}, {0x00, 0x01, 0x00, 0x00},
    //                      {0x00, 0x00, 0x01, 0x00} , {0x00, 0x00, 0x00, 0x01} };
    GF_Matrix MC, MC2, MC4, InvMC;
    MC.row = 4;
    MC.col = 4;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            MC.M[i][j] = MixCol[i][j];
    cout << "MixColumn Matrix MC = " << endl;
    GF_Mat_print(MC);

    /*
    MC2 = GF_Mat_Mul(MC, MC);
    cout << "MC^2 = " << endl;
    GF_Mat_print(MC2);

    MC4 = GF_Mat_Mul(MC2, MC2);
    cout << "MC^4 = " << endl;
    GF_Mat_print(MC4);
    */

    cout << "Inverse MixColumn Matrix InvMC = " << endl;
    InvMC = GF_Mat_inverse(MC);
    GF_Mat_print(InvMC);

}
