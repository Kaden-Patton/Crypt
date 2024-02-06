#include "file.h"
#include "arguments.h"
#include "crypto.h"

int main(int argc, char *argv[]) {
    Arguments args(argc, argv);
    Crypto crypt;
    crypt.DoOperations();
    return 0;
}