#include <stdio.h>
#include "class.h"
#include <cstring>
#include <string>

Alphabet::Alphabet(){//empty
    this->alph = nullptr;
    this->size = 0;
}

Alphabet::Alphabet(size_t size){ //Alphabet by size
    this->size = size;
    this->alph = new char[size];
    if(size < 94){
        for(int i = ' '; i <= 32 + (char)size; i++){
            this->alph[i - ' ']=i;
        }
    }
    else{
        this->size = 94;
        for(int i = ' '; i <= 32 + (char)size; i++){
            this->alph[i - ' ']=i;
        }
    }

}

Alphabet::Alphabet(const char* str, size_t size){ //Alphabet by ASCII
    this->size = 0;
    this->alph = new char[size];

    for (int i = 0; i < size; i++){
        AddNew(str[i]);
    }
}

Alphabet::~Alphabet(){ // distructor
    if (this->alph != nullptr)
        delete[] this->alph;
        this->size = 0;
}

Alphabet::Alphabet(const Alphabet& al) // copy constructor
{
    this->size = al.size;
    this->alph = new char[al.size];
    for (int i = 0; i < al.size; i++)
        this->alph[i] = al.alph[i];
}

Alphabet& Alphabet::operator =(const Alphabet& al) //copy operator =
{
    if (this != &al) {
        size = al.size;
        delete[] alph;
        alph = new char[size];
        for (int i = 0; i < size; i++)
            alph[i] = al.alph[i];
    }
    return *this;
}

Alphabet::Alphabet(Alphabet&& al) :size(al.size), alph(al.alph) // move constructor
{
    al.alph = nullptr;
    al.size = 0;
}

Alphabet& Alphabet::operator =(Alphabet&& al) // move operator =
{
    if (this != &al) {
        size_t tmp = size;
        size = al.size;
        al.size= tmp;
        char* ptr = alph;
        alph = al.alph;
        al.alph= ptr;
    }
    return *this;
    //
    /*this->size = al.size;
    this->alph = al.alph;

    al.alph = nullptr;
    al.size = 0;
    return *this;*/
}


void Alphabet::SetAlph(char *alph, int size) {
    this->size=size;

    for (int i = 0; i < this->size; i++) {
    this->alph[i] = alph[i];
    }
}
bool Alphabet::isEqual(char s1) const{
    for (int i = 0; i < this->size; i++){
        if(this->alph[i] == s1){
            return true;
        }
    }
    return false;
}

void Alphabet::AddNew(char s1) { //adding for constructor
    if (isEqual(s1) == false){
        this->alph[this->size] = s1;
        this->size++;
    }
}


int Alphabet::FindElement(char s1) const{
    int res = -1;
    for (int i = 0; i < this->size; i++){
        if(s1 == this->alph[i]){
            res = i;
            break;
        }
    }
    return res;
}

char Alphabet::Encoding(int n, char* str) const{
    size_t length = strlen(str);
    char symb;
    //char fin[length];
    for (int i = 0; i < length; i++){
        symb = *str;
        int j = FindElement(symb);
        if (j != -1){
            /*if (j + n < this->size)
                symb = this->alph[j + n];

            else
                symb = this->alph[this->size-j-n+1];*/
            int ind = j+n;
            while (ind < 0) {
                ind += this->size;
            }
            symb = this->alph[ind%this->size];

        }
        else{
            throw std::overflow_error("Alphabet or string is empty.");
        }
        *str = symb;
        str++;
    }
    return *str;
}

Alphabet& Alphabet::operator+=(const Alphabet& other){
    size_t newSize = this->size + other.size;
    size_t size1 = this->size;
    size_t finalsize = this->size;
    char *temp = new char(newSize);
    for (int i = 0; i<size1; i++){
        temp[i] = this->alph[i];
    }
    delete[] this->alph;
    size_t s = size1;
    for (size_t i = size1; i < newSize; i++){
        if (isEqual(other.alph[i-size1]) == false)
        {
            temp[s] = other.alph[i-size1];
            finalsize++;
            s++;
        }
        else continue;
    }
    this->size = finalsize;
    this->alph = new char(finalsize);
    for (int i = 0; i < finalsize; i++){
        this->alph[i]=temp[i];
    }

    return *this;
}

Alphabet& Alphabet::operator+(const char& s1){
    if(this->alph == nullptr){
        this->alph = new char[1];
        this->size = 0;
    }
    if (isEqual(s1) == false){
        if(this->size == 0){
            delete [] this->alph;
            this->alph = new char(1);
            alph[0] = s1;
            this->size++;
        }
        else {
            char *temp = new char(size);
            size_t newSize = this->size + 1;
            for (int i = 0; i<newSize-1; i++){
                temp[i] = this->alph[i];
            }
            delete[] this->alph;
            this->size = newSize;
            this->alph = new char(newSize);
            for (int i = 0; i<newSize-1; i++){
                this->alph[i]=temp[i];
            }
            this->alph[this->size-1]=s1;
            temp = nullptr;
        }
    }
    else throw std::overflow_error("Element already exists.");

    return *this;
}


std::ostream& operator <<(std::ostream& s, const Alphabet& a)
{
    if (a.GetSize() == 0)
        s << "Alphabet is empty";
    else
        for (int i = 0; i < a.GetSize(); i++)
        {
            s<<a.GetElement(i);
        }
    s << std::endl;
    s << "Size: " << a.GetSize();
    s << std::endl;
    return s;
}


std::istream& operator >>(std::istream& s, Alphabet& a){
    size_t size;

    if(!(s >> size)){
        return s;
    }
    a.size = size;

    char symb;
    for (int i = 0; i < size; i++){
        if(s>>symb){
            a+symb;
        }
        else return s;
    }
    return s;
}
