#include <iostream>
#include "TapeEmulator.h"
#include "BubbleTapeSorter.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cout << "Invalid arguments\n" << "Usage: tape_sorter input_tape output_tape" << std::endl;
    }

    TapeEmulator tape(argv[1], argv[2], 16);

    (BubbleTapeSorter(tape))();
}
