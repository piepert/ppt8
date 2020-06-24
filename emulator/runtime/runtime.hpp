#ifndef EMULATOR_RUNTIME_HPP
#define EMULATOR_RUNTIME_HPP

#include <stack>
#include <cstdint>
#include <vector>
#include <string>

#include "../memory/memory.hpp"
#include "../register/register.hpp"
#include "../command/command.hpp"

class Runtime
{
private:
    std::stack<uint8_t> stack;
    std::vector<Command*> commands;
    Memory memory;

    Register reg_ax;
    Register reg_bx;
    Register reg_cx;
    Register reg_dx;
    Register reg_ex;
    Register reg_fx;
    Register reg_gx;
    Register reg_hx;

public:
    int PROGRAMM_INDEX = 0;
    bool DEBUG = false;
    std::string PROGRAMM_CODE;

    Runtime();

    Memory* getMemory();
    std::stack<uint8_t>* getStack();

    Register* getAX();
    Register* getBX();
    Register* getCX();
    Register* getDX();
    Register* getEX();
    Register* getFX();
    Register* getGX();
    Register* getHX();

    void raiseException(std::string string);
    void addCommand(Command* command);

    bool existsCommand(uint8_t opcode);
    std::vector<Command*>* getCommands();
    Command* getCommand(uint8_t opcode);

    Register* getRegisterByID(uint8_t id);
    uint8_t getSubRegisterByID(uint8_t id);
    void setSubRegisterByID(uint8_t id, uint8_t value);

    void push8bit(uint8_t i);
    void push16bitSplittet(uint16_t i);
};


#endif //EMULATOR_RUNTIME_HPP
