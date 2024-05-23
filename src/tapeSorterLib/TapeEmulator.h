#ifndef TAPESORTER_TAPEEMULATOR_H
#define TAPESORTER_TAPEEMULATOR_H

#include <vector>
#include <chrono>
#include "Tape.h"

class TapeEmulator : public Tape {
private:
    const std::chrono::nanoseconds read_write_delay;
    const std::chrono::nanoseconds move_delay;
    const uint64_t max_number_of_elements;
    uint64_t relative_position;
    std::string input_tape_path;
    std::string output_tape_path;
    std::string tmp_tapes_location;
    struct tmp_tape {
        int32_t *array;
        uint32_t num;
    };
    tmp_tape cur_tape;
    tmp_tape next_tape;
    uint64_t last_tape_size;
    uint32_t last_tape_num;

    void load_tmp_tape(tmp_tape &tmp_tape, uint32_t tape_num);

    void save_tmp_tape(TapeEmulator::tmp_tape &tmp_tape);

    inline std::string get_tmp_file_name(uint32_t tape_num);

public:
    TapeEmulator(const std::string &input_tape_path, std::string output_tape_path, uint64_t m,
                 std::chrono::nanoseconds read_write_delay = std::chrono::nanoseconds(0),
                 std::chrono::nanoseconds move_delay = std::chrono::nanoseconds(0),
                 std::string tmp_tapes_location = ".");

    void write(int32_t) override;

    int32_t read() override;

    bool moveLeft() override;

    bool moveRight() override;

    ~TapeEmulator();
};

#endif //TAPESORTER_TAPEEMULATOR_H
