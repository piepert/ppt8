#ifndef EMULATOR_COMMAND_HPP
#define EMULATOR_COMMAND_HPP

#include <cstdint>
#include <vector>

class Runtime;

class Command
{
public:
    virtual uint8_t getOpcode() { return -1; };                    // get opcode of command
    virtual int getLength() { return -1; };                        // how many arguments does it need?
    virtual int run(std::vector<uint8_t> args, Runtime* runtime) { return  0; };
};


#endif //EMULATOR_COMMAND_HPP
