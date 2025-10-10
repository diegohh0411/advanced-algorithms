// Diego Hernández Herrera, A01198786

#include <iostream>

#include "kmp.h"
#include "manacher.h"
#include "files.h"

int main() {
    auto [mcodes, transmissions] = readFiles();

    KmpManager(mcodes, transmissions);
    ManacherManager(transmissions);

    return 0;
}