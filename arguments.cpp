#include "arguments.h"
#include "file.h"


Arguments::Arguments(int argc, char* argv[]) {
    program_name = argv[0];
    if(argc != EXPECTED_ARGUMENTS) {
        std::cout << "Usage: " << program_name << " <B|S> <input_file> <output_file> <key_file> <E|D>\n";
        exit(1);
    }

    cipher_mode = argv[1];
    input_file = argv[2];
    output_file = argv[3];
    key_file = argv[4];
    mode = argv[5];

    Validate();
}

void Arguments::Validate() {
    if(cipher_mode != "B" && cipher_mode != "S") {
        std::cout << "Invalid cipher mode entered. Only <B>lock and <S>tream modes are supported.\n";
        exit(1);
    } else if(!File::Exists(input_file)) {
        std::cout << "Could not open input file: " << input_file << "\n";
        exit(1);
    } else if(!File::Exists(key_file)) {
        std::cout << "Could not open key file: " << key_file << "\n";
        exit(1);
    } else if(mode != "E" && mode != "D") {
        std::cout << "Invalid operation mode entered. Only <E>ncryption and <D>ecrypion are supported.\n";
        exit(1);
    }
}

std::string Arguments::GetKeyFilename() {
    return key_file;
}

std::string Arguments::GetInputFilename() {
    return input_file;
}

std::string Arguments::GetOutputFilename() {
    return output_file;
}
bool Arguments::IsBlockMode() {
    return(Arguments::cipher_mode == "B");
}

bool Arguments::IsEncryptMode() {
    return(Arguments::mode == "E");
}