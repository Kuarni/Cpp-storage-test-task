#ifndef TAPESORTER_BUBBLETAPESORTER_H
#define TAPESORTER_BUBBLETAPESORTER_H

#include "Tape.h"
#include "TapeSorter.h"

class BubbleTapeSorter : public TapeSorter {
public:
    BubbleTapeSorter(Tape &tape) : TapeSorter(tape) {};

    void operator()() override;
};

#endif //TAPESORTER_BUBBLETAPESORTER_H
