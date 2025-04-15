#ifndef CODER_H_
#define CODER_H_

#include <string>

using namespace std;



class Coder {
public:
    static string encode(char** state);
    static string base64_encode(string input);
    static void decode(string encoded, char** state);
    static string base64_decode(string encoded_string);
};

#endif