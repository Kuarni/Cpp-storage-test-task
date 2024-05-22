#ifndef TAPESORTER_TAPEEMULATOR_H
#define TAPESORTER_TAPEEMULATOR_H

#include <vector>
#include "Tape.h"

class TapeEmulator : public Tape {
private:
    const uint64_t max_number_of_elements;
    uint64_t relative_position;
    std::string input_tape_path;
    std::string output_tape_path;
    std::string tmp_tapes_location;
    struct tape_pointer {
        int32_t *p;
        uint32_t num;
    };
    tape_pointer cur_tape;
    tape_pointer next_tape;
    uint64_t last_tape_size;
    uint32_t last_tape_num;

    void load_tmp_tape(tape_pointer &tmp_tape, uint32_t tape_num);

    void save_tmp_tape(TapeEmulator::tape_pointer &tmp_tape);

    inline std::string get_tmp_file_name(uint32_t tape_num);
public:
    TapeEmulator(const std::string &input_tape_path, std::string output_tape_path, uint64_t m,
                 std::string tmp_tapes_location = ".");

    void write(int32_t) override;

    int32_t read() override;

    bool moveLeft() override;

    bool moveRight() override;

    ~TapeEmulator();
};

#endif //TAPESORTER_TAPEEMULATOR_H
