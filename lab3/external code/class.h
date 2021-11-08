#include <iostream>
#include <limits>
#ifndef class_h
#define class_h


template <class T>
bool get(T &a)
{
    while (!(std::cin >> a))
    {
        if (std::cin.eof())
            return false;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return true;
}

std::string getstr();

class Alphabet{
private:
    size_t size;
    char *alph;
public:
    Alphabet(); //empty of Steps'
    Alphabet(size_t size); //size of Steps'
    Alphabet(const char* str, size_t size); //constructor of Steps'
    ~Alphabet(); //destructor
    Alphabet(const Alphabet& alph); //copy constructor
    Alphabet(Alphabet&& al); // Move constructor
    Alphabet& operator =(const Alphabet&); //copy operator
    Alphabet& operator =(Alphabet&& al); // moving operator



    const char* GetAlph() const { return this->alph;} // returning pointer on array (remember, when u use it)


    void SetAlph(char alph[], int size);
    void SetSize(size_t size) { this->size=size;}
    size_t GetSize() const {return size;}
    char GetElement(int index) const {return alph[index];}


    Alphabet Potok(std::iostream& in);
    void Union(char *alph1, int size1, int size2);
    char Encoding(int n, char *str) const;
    bool isEqual(char s1) const;
    void AddNew(char s1);
    int FindElement(char s1) const;
    friend std::ostream& operator <<(std::ostream&, const Alphabet&);
    friend std::istream& operator >>(std::istream&, Alphabet&);

    Alphabet& operator +=(const Alphabet&);
    Alphabet& operator +(const char& s1);


};



#endif /* class_h */
