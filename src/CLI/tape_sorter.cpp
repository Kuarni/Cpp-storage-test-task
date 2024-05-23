#include <iostream>
#include "TapeEmulator.h"
#include "BubbleTapeSorter.h"
#include "ini.h"

void run_algo(const std::string& input_tape, const std::string& output_tape, uint64_t m,
             uint64_t read_write_delay, uint64_t move_delay) {
    TapeEmulator tape(input_tape, output_tape, m, std::chrono::nanoseconds(read_write_delay),
                      std::chrono::nanoseconds(move_delay));

    (BubbleTapeSorter(tape))();
}

int main(int argc, char *argv[]) {
    if (argc < 3 || argc > 4) {
        std::cout << "Invalid arguments\n" << "Usage: tape_sorter input_tape output_tape [config_path]" << std::endl;
        return EINVAL;
    }

    const std::string config_path = argc == 4 ? argv[3] : "configs/config.ini";

    ini::File config = ini::open(config_path);
    auto read_write_delay = config["delays"].get<uint64_t>("read_write");
    auto move_delay = config["delays"].get<uint64_t>("move");
    auto m = config["memory_limit"].get<uint64_t>("m");

    run_algo(argv[1], argv[2], m, read_write_delay, move_delay);

    return 0;
}
