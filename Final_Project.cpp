#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <bitset>
#include <iomanip>
#include <string>
#include <cstdint>

// Constants for SHA-256
const std::vector<uint32_t> k = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

// Initial hash values
std::vector<uint32_t> h = {
    0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
    0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
};

// Right rotate function
uint32_t rightRotate(uint32_t value, unsigned int count) {
    return (value >> count) | (value << (32 - count));
}

// Preprocess the input string data
std::vector<uint32_t> preprocess(const std::string& data) {
    std::vector<uint32_t> w(64);
    int numBlocks = (data.length() + 8) / 64 + 1;
    std::vector<uint8_t> paddedData(numBlocks * 64, 0);
    for (size_t i = 0; i < data.length(); ++i) {
        paddedData[i] = data[i];
    }
    // Append the bit '1' to the message
    paddedData[data.length()] = 0x80;
    // Append original length in bits mod (2^64) to message
    uint64_t dataLenBits = static_cast<uint64_t>(data.length()) * 8;
    for (int i = 0; i < 8; ++i) {
        paddedData[paddedData.size() - 1 - i] = (dataLenBits >> (8 * i)) & 0xff;
    }
    // Process each block
    for (int i = 0; i < numBlocks; ++i) {
        for (int j = 0; j < 16; ++j) {
            w[j] = 0;
            for (int k = 0; k < 4; ++k) {
                w[j] |= paddedData[i * 64 + j * 4 + k] << (24 - k * 8);
            }
        }
        for (int j = 16; j < 64; ++j) {
            uint32_t s0 = rightRotate(w[j - 15], 7) ^ rightRotate(w[j - 15], 18) ^ (w[j - 15] >> 3);
            uint32_t s1 = rightRotate(w[j - 2], 17) ^ rightRotate(w[j - 2], 19) ^ (w[j - 2] >> 10);
            w[j] = w[j - 16] + s0 + w[j - 7] + s1;
        }
    }
    return w;
}

// Process each chunk
std::vector<uint32_t> process_chunk(const std::vector<uint32_t>& w, std::vector<uint32_t> h) {
    std::vector<uint32_t> a = h;
    for (int i = 0; i < 64; ++i) {
        uint32_t S1 = rightRotate(a[4], 6) ^ rightRotate(a[4], 11) ^ rightRotate(a[4], 25);
        uint32_t ch = (a[4] & a[5]) ^ (~a[4] & a[6]);
        uint32_t temp1 = a[7] + S1 + ch + k[i] + w[i];
        uint32_t S0 = rightRotate(a[0], 2) ^ rightRotate(a[0], 13) ^ rightRotate(a[0], 22);
        uint32_t maj = (a[0] & a[1]) ^ (a[0] & a[2]) ^ (a[1] & a[2]);
        uint32_t temp2 = S0 + maj;
        a[7] = a[6];
        a[6] = a[5];
        a[5] = a[4];
        a[4] = a[3] + temp1;
        a[3] = a[2];
        a[2] = a[1];
        a[1] = a[0];
        a[0] = temp1 + temp2;
    }
    for (int i = 0; i < 8; i++) {
        h[i] += a[i];
    }
    return h;
}

// Compute SHA-256 hash
std::string sha256(const std::string& data) {
    std::vector<uint32_t> w = preprocess(data);
    std::vector<uint32_t> h = process_chunk(w, ::h);
    std::stringstream ss;
    for (uint32_t i : h) {
        ss << std::hex << std::setfill('0') << std::setw(8) << i;
    }
    return ss.str();
}

int main() {
    // Open and read the entire text from file
    std::ifstream file("BookOfMark.txt");
    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string data = buffer.str();
    file.close();

    // Compute and output the SHA-256 hash
    std::string hash = sha256(data);
    std::cout << "SHA-256 Hash of the Book of Mark: " << hash << std::endl;

    return 0;
}