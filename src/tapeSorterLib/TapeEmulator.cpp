#include "TapeEmulator.h"
#include <fstream>
#include <vector>

void TapeEmulator::readTape() {
    position = 0;
    std::ifstream in(tapes_location + "/" + tape_name);
    int32_t input;
    while (in >> input) {
        tape.push_back(input);
    }
}

void TapeEmulator::saveTape() {
    std::ofstream out(tapes_location + "/" + tape_name);
    for (int32_t i: tape) {
        out << i << " ";
    }
    tape.clear();
}

TapeEmulator::TapeEmulator(std::string tapeName, std::string tapesLocation) : tape_name(tapeName),
                                                                              tapes_location(tapesLocation) {
    readTape();
}

void TapeEmulator::write(int32_t value) {
    tape[position] = value;
}

int32_t TapeEmulator::read() {
    return tape[position];
}

bool TapeEmulator::moveLeft() {
    if (position > 0) {
        position--;
        return true;
    }
    return false;
}

bool TapeEmulator::moveRight() {
    if (position < tape.size() - 1) {
        position++;
        return true;
    }
    return false;
}

std::string TapeEmulator::getTapeName() {
    return {tape_name};
}

void TapeEmulator::changeTape(std::string name) {
    saveTape();
    tape_name = name;
    readTape();
}

TapeEmulator::~TapeEmulator() {
    saveTape();
}
