#ifndef EMULATOR_RUNTIME_HPP
#define EMULATOR_RUNTIME_HPP

#include <stack>
#include <cstdint>
#include <vector>
#include <string>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "../memory/memory.hpp"
#include "../register/register.hpp"
#include "../command/command.hpp"

#define RT_CMD_MEM_SIZE 256

class Runtime
{
private:
    sf::Uint8* screen;
    int screen_width;
    int screen_height;

    std::stack<uint8_t> stack;
    std::vector<Command*> commands;
    Command* command_mem[256];
    Command* nop_command;
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
    bool WAIT_FOR_KEY_PRESS;
    sf::Keyboard::Key INPUT_BUFFER;
    bool KEY_IS_PRESSED = false;
    bool SHIFT_PRESSED = false;
    bool CTRL_PRESSED = false;
    sf::RenderWindow* window;

    uint16_t SCREEN_WIDTH;
    uint16_t SCREEN_HEIGHT;

    Runtime(int screen_width, int screen_height);

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
    Command* getCommand(uint8_t opcode, bool iterate=false);

    Register* getRegisterByID(uint8_t id);
    uint8_t getSubRegisterByID(uint8_t id);
    void setSubRegisterByID(uint8_t id, uint8_t value);

    void push8bit(uint8_t i);
    void push16bitSplittet(uint16_t i);

    int getPixelState(int x, int y);
    int getPixelSize();

    void setPixelState(int x, int y, uint8_t state);
    void clearPixels();

    sf::Uint8* getPixelStates();
};


#endif //EMULATOR_RUNTIME_HPP
