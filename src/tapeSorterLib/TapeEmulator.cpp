#include "TapeEmulator.h"
#include <fstream>
#include <utility>
#include <vector>
#include <cassert>
#include <filesystem>
#include <thread>

#define MIN_M 8
#define LOAD_INTERVAL (0.25)
#define TMP_DIR "tmp"
#define TMP_PREFIX "tmp"

TapeEmulator::TapeEmulator(const std::string &input_tape_path, const std::string &output_tape_path, uint64_t m,
                           std::chrono::nanoseconds read_write_delay, std::chrono::nanoseconds move_delay,
                           const std::string &tmp_tapes_location) :
        read_write_delay(read_write_delay), move_delay(move_delay),
        input_tape_path(input_tape_path),
        output_tape_path(output_tape_path),
        max_number_of_elements(m / sizeof(int32_t) / 2),
        tmp_tapes_location(tmp_tapes_location),
        relative_position(0),
        cur_tape({nullptr, 0}), next_tape({nullptr, 0}) {
    if (m < MIN_M)
        throw std::invalid_argument("m must be " + std::to_string(MIN_M) + " or more");
    std::filesystem::create_directories(tmp_tapes_location + "/" + TMP_DIR);
    std::ifstream in(input_tape_path);
    if (!in) {
        throw std::system_error{errno, std::generic_category(), input_tape_path};
    }
    int32_t input;
    uint32_t tmp_file_counter = 0;
    uint64_t i = 0;
    while (!in.eof()) {
        std::ofstream cur(get_tmp_file_name(tmp_file_counter++));
        if (!cur) {
            throw std::system_error{errno, std::generic_category(), get_tmp_file_name(tmp_file_counter - 1)};
        }
        for (i = 0; i < max_number_of_elements && in >> input; i++) {
            cur << input << " ";
        }
    }
    last_tape_num = tmp_file_counter - 1;
    last_tape_size = i;

    if (last_tape_num == 0 && last_tape_size == 0)
        throw std::invalid_argument("Tape is empty\n");

    load_tmp_tape(cur_tape, cur_tape.num);
}

void TapeEmulator::load_tmp_tape(tmp_tape &tmp_tape, uint32_t tape_num) {
    std::ifstream in(get_tmp_file_name(tape_num));
    tmp_tape.array = new int32_t[max_number_of_elements];
    tmp_tape.num = tape_num;
    for (uint64_t i = 0; in >> tmp_tape.array[i]; i++);
}

void TapeEmulator::save_tmp_tape(TapeEmulator::tmp_tape &tmp_tape) {
    if (!tmp_tape.array)
        return;
    std::ofstream out(get_tmp_file_name(tmp_tape.num));
    for (uint64_t i = 0; i < (tmp_tape.num == last_tape_num ? last_tape_size : max_number_of_elements); i++)
        out << tmp_tape.array[i] << " ";
    delete[] tmp_tape.array;
}

std::string TapeEmulator::get_tmp_file_name(uint32_t tape_num) {
    return tmp_tapes_location + "/" + TMP_DIR + "/" + TMP_PREFIX + std::to_string(tape_num);
}

void TapeEmulator::write(int32_t value) {
    std::this_thread::sleep_for(read_write_delay);
    cur_tape.array[relative_position] = value;
}

int32_t TapeEmulator::read() {
    std::this_thread::sleep_for(read_write_delay);
    return cur_tape.array[relative_position];
}

bool TapeEmulator::moveLeft() {
    std::this_thread::sleep_for(move_delay);
    if (cur_tape.num == 0) {
        if (relative_position == 0) {
            return false;
        }
        relative_position--;
        return true;
    }

    if (relative_position <= (uint64_t) ((double) max_number_of_elements * LOAD_INTERVAL) &&
        (next_tape.num != cur_tape.num - 1 || !next_tape.array)) {
        assert(cur_tape.num != 0);
        save_tmp_tape(next_tape);
        load_tmp_tape(next_tape, cur_tape.num - 1);
    }

    if (relative_position-- == 0) {
        assert(next_tape.array);
        assert(next_tape.num == cur_tape.num - 1);
        std::swap(cur_tape, next_tape);
        relative_position = max_number_of_elements - 1;
    }

    return true;
}

bool TapeEmulator::moveRight() {
    std::this_thread::sleep_for(move_delay);
    if (cur_tape.num == last_tape_num) {
        if (relative_position + 1 < last_tape_size) {
            relative_position++;
            return true;
        }
        return false;
    }

    if (relative_position >= (uint64_t) ((double) max_number_of_elements * (1 - LOAD_INTERVAL)) &&
        (next_tape.num != cur_tape.num + 1 || !next_tape.array)) {
        assert(cur_tape.num != last_tape_num);
        save_tmp_tape(next_tape);
        load_tmp_tape(next_tape, cur_tape.num + 1);
    }

    if (++relative_position == max_number_of_elements) {
        assert(next_tape.array);
        assert(next_tape.num == cur_tape.num + 1);
        std::swap(cur_tape, next_tape);
        relative_position = 0;
    }

    return true;
}

TapeEmulator::~TapeEmulator() {
    save_tmp_tape(cur_tape);
    save_tmp_tape(next_tape);
    std::ofstream output(output_tape_path);
    for (uint32_t i = 0; i <= last_tape_num; i++) {
        std::ifstream cur(get_tmp_file_name(i));
        int32_t buf;
        while (cur >> buf) {
            std::this_thread::sleep_for(move_delay);
            std::this_thread::sleep_for(read_write_delay);
            std::this_thread::sleep_for(read_write_delay);
            //delays because it's like move right, read from one tape and write to another
            output << buf << " ";
        }
    }
}
