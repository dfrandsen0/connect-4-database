#include <string>
#include <vector>
#include <cstdint>
#include <cstring>
#include <stdexcept>
#include <iostream>

#include "config.h"
#include "coder.h"

using namespace std;

static const string base64_chars =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789+/";

static inline bool is_base64(unsigned char c) {
    return (isalnum(c) || c == '+' || c == '/');
}    

string Coder::encode(char** state) {
    vector<uint8_t> bytes;
    uint32_t bit_buffer = 0;
    int bit_count = 0;

    // Step 1: Encode column heights (3 bits per column)
    int heights[NUM_COLUMNS] = {0};
    for (int col = 0; col < NUM_COLUMNS; ++col) {
        int height = 0;
        for (int row = 0; row < NUM_ROWS; ++row) {
            if (state[col][row] != 0) {
                height++;
            }
        }
        heights[col] = height;

        bit_buffer |= (height & 0x7) << bit_count;
        bit_count += 3;
        while (bit_count >= 8) {
            bytes.push_back(bit_buffer & 0xFF);
            bit_buffer >>= 8;
            bit_count -= 8;
        }
    }

    // Step 2: Encode disc data (1 bit per disc)
    for (int col = 0; col < NUM_COLUMNS; ++col) {
        for (int row = 0; row < heights[col]; ++row) {
            uint8_t bit = (state[col][row] == 2) ? 1 : 0;
            bit_buffer |= (bit << bit_count);
            bit_count++;
            if (bit_count >= 8) {
                bytes.push_back(bit_buffer & 0xFF);
                bit_buffer >>= 8;
                bit_count -= 8;
            }
        }
    }

    // Flush remaining bits
    if (bit_count > 0) {
        bytes.push_back(bit_buffer & 0xFF);
    }

    //cerr << bytes.size() << endl;
    return string(reinterpret_cast<char*>(bytes.data()), bytes.size());
}

string Coder::base64_encode(string input) {
    string output;
    int i = 0;
    unsigned char char_array_3[3];
    unsigned char char_array_4[4];

    size_t len = input.size();
    const char* bytes_to_encode = input.data();

    while (len--) {
        char_array_3[i++] = *(bytes_to_encode++);
        if (i == 3) {
            char_array_4[0] =  (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] =   char_array_3[2] & 0x3f;

            for (i = 0; i < 4; ++i)
                output += base64_chars[char_array_4[i]];
            i = 0;
        }
    }

    if (i) {
        for (int j = i; j < 3; ++j) {
            char_array_3[j] = 0;
        }

        char_array_4[0] =  (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
        char_array_4[3] =   char_array_3[2] & 0x3f;

        for (int j = 0; j < i + 1; ++j) {
            output += base64_chars[char_array_4[j]];
        }
    }

    return output;
}

string Coder::base64_decode(string encoded_string) {
    while (encoded_string.size() % 4 != 0) {
        encoded_string += '=';
    }

    int in_len = encoded_string.size();
    int i = 0, j = 0, in_ = 0;
    unsigned char char_array_4[4], char_array_3[3];
    std::string ret;

    while (in_len-- && (encoded_string[in_] != '=') && is_base64(encoded_string[in_])) {
        char_array_4[i++] = encoded_string[in_]; in_++;
        if (i == 4) {
            for (i = 0; i < 4; i++)
                char_array_4[i] = base64_chars.find(char_array_4[i]);

            char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
            char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
            char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

            for (i = 0; i < 3; i++) ret += char_array_3[i];
            i = 0;
        }
    }

    if (i) {
        for (j = i; j < 4; j++) char_array_4[j] = 0;

        for (j = 0; j < 4; j++) char_array_4[j] = base64_chars.find(char_array_4[j]);

        char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
        char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
        char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

        for (j = 0; j < i - 1; j++) ret += char_array_3[j];
    }

    return ret;
}

void Coder::decode(string encoded, char** state) {
    const uint8_t* data = reinterpret_cast<const uint8_t*>(encoded.data());
    size_t data_size = encoded.size();

    uint64_t bit_buffer = 0;
    int bit_count = 0;
    size_t byte_index = 0;

    auto get_bits = [&](int count) -> uint32_t {
        while (bit_count < count && byte_index < data_size) {
            bit_buffer |= (uint64_t)data[byte_index++] << bit_count;
            bit_count += 8;
        }

        if (bit_count < count) {throw runtime_error("Not enough bits");}
        uint32_t result = (bit_buffer & ((1ULL << count) - 1));
        bit_buffer >>= count;
        bit_count -= count;
        return result;
    };

    int heights[NUM_COLUMNS];

    // Step 1: Read column heights
    for (int col = 0; col < NUM_COLUMNS; ++col) {
        heights[col] = get_bits(3);
    }

    // Step 2: Read disc data
    for (int col = 0; col < NUM_COLUMNS; ++col) {
        for (int row = 0; row < heights[col]; ++row) {
            uint8_t bit = get_bits(1);
            state[col][row] = (bit == 1) ? 2 : 1;
        }
        for (int row = heights[col]; row < NUM_ROWS; ++row) {
            state[col][row] = 0;
        }
    }
}
