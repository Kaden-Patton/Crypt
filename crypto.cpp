#include "crypto.h"
#include "arguments.h"

Crypto::Crypto() {
    key = "";
    ReadKey(Arguments::GetKeyFilename());
    cipher_mode = Arguments::IsBlockMode() ? Mode::BLOCK : Mode::STREAM;
    operation_mode = Arguments::IsEncryptMode() ? Mode::ENCRYPT : Mode::DECRYPT;
}

void Crypto::ReadKey(std::string key_file) {
    key = File::Read(key_file);
    BLOCK_SIZE = key.length();
}

std::string Crypto::GetKey() {
    return key;
}

void Crypto::DoOperations() {
    switch(operation_mode) {
        case Mode::ENCRYPT:
            Crypto::Encrypt();
            break;
        case Mode::DECRYPT:
            Crypto::Decrypt();
            break;
        default:
            break;
    }
}

void Crypto::Encrypt() {
    switch(cipher_mode) {
        case Mode::BLOCK:
            Crypto::BlockEncrypt();
            break;

        case Mode::STREAM:
            Crypto::StreamEncrypt();
            break;
        
        default:
            break;
    }
}

void Crypto::Decrypt() {
       switch(cipher_mode) {
        case Mode::BLOCK:
            Crypto::BlockDecrypt();
            break;

        case Mode::STREAM:
            Crypto::StreamDecrypt();
            break;
        
        default:
            break;
    } 
}

void Crypto::BlockEncrypt() {
    std::string plaintext = File::ReadBlock(Arguments::GetInputFilename(), BLOCK_SIZE);
    std::string xor_plaintext = Crypto::XOR(plaintext);
    std::string swapped_plaintext = Crypto::BlockSWP(xor_plaintext);
    File::Write(Arguments::GetOutputFilename(), swapped_plaintext);
}

void Crypto::BlockDecrypt() {
    std::string ciphertext = File::Read(Arguments::GetInputFilename());
    std::string swapped_ciphertext = Crypto::BlockSWP(ciphertext);
    std::string xored_ciphertext = Crypto::XOR(swapped_ciphertext);
    std::string output_string = "";
    output_string.append(File::RemovePadding(xored_ciphertext));
    File::Write(Arguments::GetOutputFilename(), output_string);
}

std::string Crypto::XOR(std::string source) {
    std::string xor_str = "";
    for(size_t i = 0; i < source.length(); i++) {
        char temp = source[i] ^ key[i % BLOCK_SIZE];
        xor_str += temp;
    }
    return xor_str;
}

std::string Crypto::BlockSWP(std::string xor_str) {
    if(xor_str.empty()) {
        return "";
    }
    auto start = xor_str.begin();
    auto end = xor_str.end() - 1;
    int i = 0;
    while(start != end) {
        if(key[i % BLOCK_SIZE] % 2 == 1) {
            char temp = *start;
            *start = *end;
            *end = temp;
            start++;
            end--;
        } else {
            start++;
        }
        i++; 
    }
    return xor_str;
}

void Crypto::StreamEncrypt() {
    Crypto::StreamCrypt(); 
}

void Crypto::StreamDecrypt() {
    Crypto::StreamCrypt();
}

void Crypto::StreamCrypt() {
    std::string input = File::Read(Arguments::GetInputFilename());
    std::string output = Crypto::XOR(input);
    File::Write(Arguments::GetOutputFilename(), output);
}
