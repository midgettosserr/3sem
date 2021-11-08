#include <iostream>
#include <fstream>
#include "class.h"
#include <cstring>

using namespace std;

//программа для шифрования/дешифрования текстовых файлов

bool encode(string filenameIn, string filenameOut, const Alphabet& a, int n){
        ifstream fileIn(filenameIn);
        ofstream fileOut(filenameOut);
        if (!fileIn.is_open() || !fileOut.is_open()) {
                return false;
        }
        string str;
        while (getline(fileIn, str)){
                char *cstr = new char[str.size() + 1];
                strcpy(cstr, str.c_str());
                a.Encoding(n, cstr);
                fileOut << cstr << endl;
                delete [] cstr;
        }
        fileIn.close();
        fileOut.close();
        return true;
}

int main(){
        Alphabet a(94);
        int key;
        cout << "Input key: ";
        get(key);

        string filenameIn, filenameOut;
        cout << "Input filename: ";
        cin >> filenameIn;
        cout << "Input filename for result file: ";
        cin >> filenameOut;

        int type;

        do {
                cout << "1 - Encode, 2 - Decode" << endl;
                get(type);

        } while (type != 1 && type != 2);

        if (type == 2){
                key = -key;
        }
        try {
                if (encode(filenameIn, filenameOut, a, key))
                        cout << "Result has been written to file " << filenameOut << endl;
                else
                        cout << "Can't open the file " << filenameIn << " or create the file " << filenameOut << endl;
        }
        catch (exception e) {
                cout << "Text contains symbols that are not in the alphabet" << endl;
                cout << "The alphabet is: " << a << endl;
        }
        return 0;
}
