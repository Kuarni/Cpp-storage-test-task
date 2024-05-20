#ifndef TAPESORTER_TAPEEMULATOR_H
#define TAPESORTER_TAPEEMULATOR_H

#include <vector>
#include "Tape.h"

class TapeEmulator : public Tape {
private:
    std::vector<int32_t> tape;
    size_t position;
    std::string tape_name;
    std::string tapes_location;

    void readTape();

    void saveTape();

public:
    TapeEmulator(std::string tapeName, std::string tapesLocation = ".");

    void write(int32_t value) override;

    int32_t read() override;

    bool moveLeft() override;

    bool moveRight() override;

    std::string getTapeName() override;

    void changeTape(std::string name) override;

    ~TapeEmulator();
};

#endif //TAPESORTER_TAPEEMULATOR_H
