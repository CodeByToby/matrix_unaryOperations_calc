//=====================================================//
// TYTUL: Problem B - operacje na macierzach           //
//                                                     //
// AUTOR: Tobiasz Sleziona                             //
// SZKOŁA/WYDZIAŁ: Politechnika Opolska, WEAiI (1 rok) //
// DATA UKONCZENIA: 16 kwietnia 2023                   //
//=====================================================//

#include <iostream>
#include <vector> // vector
#include <fstream> // ifstream, ofstream

#define INPUT_FILE argv[1]
#define OUTPUT_FILE argv[2]
#define INDEX_X X.x*i + X.y*j + X.c*(len-1)
#define INDEX_Y Y.x*i + Y.y*j + Y.c*(len-1)

using namespace std;

struct index {
    short x;
    short y;
    bool c; // whether len-1 is present as a constant in the index
};

inline void swapIndexes(index & A, index & B) {
    index temp;
    temp = A; A = B; B = temp;
}
inline void reverseIndex(index & A) {
    A.x *= -1; A.y *= -1;
    A.c = (A.c == false)? true : false;
}

/*************************************************************/
/***************** CLASS DEFINITION START ********************/
/*************************************************************/

class matrix {
    private:
        unsigned int len {}; // matrix side length (<=300)
        unsigned int size {}; // matrix total character size (<=len^2=90000)

        index X {1,0,false}; // index x to be used for the final transform
        index Y {0,1,false}; // index y to be used for the final transform

        vector<vector<char>> mtx; // matrix vector of vectors
        vector<char> ops; // operations vector

        void transform(void); // perform the final operation on the matrix
    public:
        void assign(ifstream*); // assign values to the object using stdin
        void process(void); // combine the operations into one single operation

        void print(ofstream*); // output to file
        void print(void); // output to stdout
};

void matrix::assign(ifstream* inFile) {
    *inFile >> len;
    size = len*len;

/* MATRIX */
    // resize the mtx matrix
    mtx.resize(len);
    for (int i=0; i<len; i++)
        mtx[i].resize(len);

    // assign values to mtx vector
    for (int i=0; i<len; i++)
        for (int j=0; j<len; j++)
            *inFile >> mtx[i][j];

/* OPERATIONS */
    // assign values to ops vector
    char ch{}; // temporary char value
    for (int i=0; ch !='&'; ++i) {
        *inFile >> ch;
        ops.push_back(ch);
    }
}
void matrix::process(void) {
    for (char ch : ops) {
        switch (ch) {
            case 'T': // TRANSPONATE -- A(i, j) -> B(j, i)
                swapIndexes(X,Y); // [i][j] to [j][i] and vice-versa
                break;

            case 'D': // REVERSE TRANSPONATE -- A(i, j) -> B(-j-n-1, -i-n-1)
                swapIndexes(X,Y);
                reverseIndex(X); // [i] to [-i-n-1] and vice-versa
                reverseIndex(Y); // [j] to [-i-n-1] and vice-versa
                break;

            case 'H': // HORIZONTAL MIRROR -- A(i, j) -> B(i, -j-n-1)
                reverseIndex(Y);
                break;

            case 'V': // VERTICAL MIRROR -- A(i, j) -> B(-i-n-1, j)
                reverseIndex(X);          
                break;

            case 'A': case 'Z':  // 90 DEGREES TO THE LEFT -- A(i, j) -> B(j, -i-n-1)
                swapIndexes(X,Y);
                reverseIndex(Y);
                break;

            case 'B': case 'Y': // 180 DEGREES TO THE LEFT -- A(i, j) -> B(-i-n-1, -j-n-1)
                reverseIndex(X);
                reverseIndex(Y);         
                break;

            case 'C': case 'X': // 270 DEGREES TO THE LEFT -- A(i, j) -> B(-j-n-1, i)
                swapIndexes(X,Y);
                reverseIndex(X);
                break;     
        }
    }
    transform();
}
void matrix::transform(void) {
    char mtxTemp[len][len] {}; // create a temporary matrix for performing the operation

    // perform operation on the matrix and put it in the temporary matrix
    for (int i=0; i<len; i++)
        for (int j=0; j<len; j++)
            mtxTemp[INDEX_X][INDEX_Y] = mtx[i][j];

    // update the final matrix
    for (int i=0; i<len; i++)
        for (int j=0; j<len; j++)
            mtx[i][j] = mtxTemp[i][j];
}

void matrix::print(void) {
    for (int i=0; i<len; i++) {
        for (int j=0; j<len; j++)
            cout << mtx[i][j];
        cout << '\n';
    }
}
void matrix::print(ofstream* outFile) {
    for (int i=0; i<len; i++) {
        for (int j=0; j<len; j++)
            *outFile << mtx[i][j];
        *outFile << '\n';
    }
}

/*************************************************************/
/****************** CLASS DEFINITION END *********************/
/*************************************************************/

int main(int argc, char *argv[])
{
    if (argc != 3) { cerr << "Nieprawidlowa liczba argumentow!\n"; return -1; }

    /*************************************************************/

    ifstream input;
    input.open(INPUT_FILE);
    if (!input) { cerr << "Nie udalo sie otworzyc pliku z danymi wejsciowymi!\n"; return -2; }

    unsigned int testCount; // total number of tests/matrixes to process

    input >> testCount;
    matrix matrixes[testCount]; // array of objects of class matrix

    for (int i=0; i<testCount; i++)
        matrixes[i].assign(&input);

    input.close();

    /*************************************************************/

    ofstream output;
    output.open(OUTPUT_FILE);
    if (!output) { cerr << "Nie udalo sie otworzyc pliku z danymi wyjsciowymi!\n"; return -3; }

    for (int i=0; i<testCount; ++i) {
        matrixes[i].process();
        matrixes[i].print(&output);
    }

    output.close();

    return 0;
}