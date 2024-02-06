#ifndef CRYPTO_H
#define CRYPTO_H
#include <string>
#include "arguments.h"
#include "file.h"



class Crypto {
    private:
        enum Mode {BLOCK = 0, STREAM = 1, ENCRYPT = 2, DECRYPT = 3};
        std::string key;
        int cipher_mode;
        int operation_mode;
        size_t BLOCK_SIZE = 16;
        void ReadKey(std::string key_file);
        void BlockEncrypt();
        void BlockDecrypt();
        void StreamEncrypt();
        void StreamDecrypt();
        std::string GetKey();
        void Encrypt();
        void Decrypt();
        std::string XOR(std::string source);
        std::string BlockSWP(std::string xor_str);
        void StreamCrypt();

    public:
        Crypto();
        void DoOperations();

};

#endif