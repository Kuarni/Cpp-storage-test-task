#include "BubbleTapeSorter.h"

void BubbleTapeSorter::operator()() {
    int counter, direction = 1;
    do {
        counter = 0;
        auto prev = tape.read();
        while (move(direction)) {
            auto cur = tape.read();
            if (direction > 0 ? cur < prev : cur > prev) {
                tape.write(prev);
                move(-direction);
                tape.write(cur);
                move(direction);
                counter++;
            } else
                prev = cur;
        }
        direction *= -1;
    } while (counter);
}
