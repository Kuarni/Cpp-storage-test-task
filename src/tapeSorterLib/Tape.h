#ifndef CPP_STORAGE_TEST_TASK_TAPE_H
#define CPP_STORAGE_TEST_TASK_TAPE_H

#include <cstdint>
#include <string>

class Tape {
public:
    virtual void write(int32_t) = 0;

    virtual int32_t read() = 0;

    virtual bool moveLeft() = 0;

    virtual bool moveRight() = 0;
};

#endif //CPP_STORAGE_TEST_TASK_TAPE_H