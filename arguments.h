#ifndef ARGUMENTS_H
#define ARGUMENTS_H

#include <iostream>
#include <string>

class Arguments {
    private:
        const int EXPECTED_ARGUMENTS = 6;
        void Validate();
        static inline std::string program_name, cipher_mode, input_file, output_file, key_file, mode;
    public:
        Arguments(int argc, char* argv[]);
        static std::string GetKeyFilename();
        static std::string GetInputFilename();
        static std::string GetOutputFilename();
        static bool IsBlockMode();
        static bool IsEncryptMode();
};



#endif