#ifndef CPP_STORAGE_TEST_TASK_TAPESORTER_H
#define CPP_STORAGE_TEST_TASK_TAPESORTER_H

#include "Tape.h"

class TapeSorter {
protected:
    Tape &tape;

    bool move(long long n) {
        bool last = false;
        if (n < 0)
            while (n++ && (last = tape.moveLeft()));
        else
            while (n-- && (last = tape.moveRight()));
        return last;
    }

public:
    TapeSorter(Tape &tape) : tape(tape) {};

    virtual void operator()() = 0;
};

#endif //CPP_STORAGE_TEST_TASK_TAPESORTER_H
