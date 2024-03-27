#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>

#define OUTPUT_FILE "A.in"

using namespace std;

int main(void) {
    const unsigned int TEST_COUNT = 20;
    const unsigned int MAX_OPS = 100000;
    const unsigned int MAX_LEN = 300;
    const char possibleOps[] = {'T','D','H','V','A','Z','B','Y','C','Z'};

    srand(time(nullptr)); // use current time as seed for random generator

    ofstream output;
    output.open(OUTPUT_FILE);
    
    if (!output) { // if cannot open output file
        cerr << "Nie udalo sie otworzyc pliku!\n"; return -1;
    }

    output << TEST_COUNT << '\n';
    for (int i=0; i<TEST_COUNT; ++i)
    { 
        /* SIDE-LENGTH */
        
        int len = rand() % MAX_LEN + 1; // 1 to MAX_LEN
        output << len << '\n';

        /* MATRIX */
        
        for (int j=0; j<len; ++j) {
            for (int k=0; k<len; ++k)
                output << char(rand() % 25 + 97); // 97 to 112 (small letters)
            output << '\n';
        }

        /* OPERATIONS */
        
        int ops = rand() % MAX_OPS + 1; // 1 to MAX_OPS
        for (int j=0; j<ops; ++j) {
            int op_index = rand() % sizeof(possibleOps)/sizeof(char); // 0 to (length of possibleOps)
            output << possibleOps[op_index];
        }
        output << '&' << '\n';
    }

    output.close();
}