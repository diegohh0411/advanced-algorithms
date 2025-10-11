// Diego Hernández Herrera, A01198786

#include <iostream>

#include "kmp.h"
#include "manacher.h"
#include "files.h"
#include "lcs.h"
#include "common.h"

int main() {
    auto [mcodes, transmissions] = readFiles();

    KmpManager(mcodes, transmissions);
    ManacherManager(transmissions);
    LcsManager(transmissions);

    return 0;
}