#ifndef TABLE_EXCEPTION
#define TABLE_EXCEPTION

#include <cstring>

class TableException : public std::exception {
private:
    char msg[256];
public:
    TableException(const char* msg) {
        strcpy(this->msg, msg);
    }
    const char* what() {
        return msg;
    }
};

#endif
