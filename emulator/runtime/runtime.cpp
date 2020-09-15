#include <iostream>
#include <SFML/Graphics/RectangleShape.hpp>
#include "runtime.hpp"
#include "../commands/c_int_r.hpp"
#include "../commands/c_int_v.hpp"
#include "../commands/c_int_m.hpp"
#include "../commands/c_int_s.hpp"
#include "../commands/c_alloc.hpp"
#include "../commands/c_mov_axv.hpp"
#include "../commands/c_jmp_v.hpp"
#include "../commands/c_jmp_m.hpp"
#include "../commands/c_jmp_r.hpp"
#include "../commands/c_mov_bxv.hpp"
#include "../commands/c_mov_cxv.hpp"
#include "../commands/c_mov_dxv.hpp"
#include "../commands/c_mov_exv.hpp"
#include "../commands/c_mov_fxv.hpp"
#include "../commands/c_mov_gxv.hpp"
#include "../commands/c_mov_hxv.hpp"
#include "../commands/c_mov_fxr.hpp"
#include "../commands/c_mov_gxr.hpp"
#include "../commands/c_mov_hxr.hpp"
#include "../commands/c_mov_irm.hpp"
#include "../commands/c_mov_imr.hpp"
#include "../commands/c_mov_irs.hpp"
#include "../commands/c_mov_imv.hpp"
#include "../commands/c_mov_mm.hpp"
#include "../commands/c_mov_mr.hpp"
#include "../commands/c_mov_ms.hpp"
#include "../commands/c_mov_mv.hpp"
#include "../commands/c_mov_rr.hpp"
#include "../commands/c_mov_ss.hpp"
#include "../commands/c_mov_rv.hpp"
#include "../commands/c_mov_sm.hpp"
#include "../commands/c_mov_sv.hpp"
#include "../commands/c_call.hpp"
#include "../commands/c_ret.hpp"
#include "../commands/c_push8_s.hpp"
#include "../commands/c_push8_v.hpp"
#include "../commands/c_push8_m.hpp"
#include "../commands/c_push16_r.hpp"
#include "../commands/c_push16_m.hpp"
#include "../commands/c_push16_v.hpp"
#include "../commands/c_pop8_s.hpp"
#include "../commands/c_pop8_m.hpp"
#include "../commands/c_pop16_r.hpp"
#include "../commands/c_pop16_m.hpp"
#include "../commands/c_je_r.hpp"
#include "../commands/c_je_v.hpp"
#include "../commands/c_je_m.hpp"
#include "../commands/c_jl_r.hpp"
#include "../commands/c_jl_v.hpp"
#include "../commands/c_jl_m.hpp"
#include "../commands/c_jg_r.hpp"
#include "../commands/c_jg_v.hpp"
#include "../commands/c_jg_m.hpp"
#include "../commands/c_jn_r.hpp"
#include "../commands/c_jn_v.hpp"
#include "../commands/c_jn_m.hpp"
#include "../commands/c_dec8_s.hpp"
#include "../commands/c_dec8_m.hpp"
#include "../commands/c_dec16_r.hpp"
#include "../commands/c_dec16_m.hpp"
#include "../commands/c_inc8_s.hpp"
#include "../commands/c_inc8_m.hpp"
#include "../commands/c_inc16_r.hpp"
#include "../commands/c_inc16_m.hpp"
#include "../commands/c_cmp_rm.hpp"
#include "../commands/c_cmp_sm.hpp"
#include "../commands/c_cmp_mv.hpp"
#include "../commands/c_cmp_sv.hpp"
#include "../commands/c_cmp_rv.hpp"
#include "../commands/c_cmp_rr.hpp"
#include "../commands/c_cmp_ss.hpp"
#include "../commands/c_cmp_mm.hpp"
#include "../commands/c_mov_mir.hpp"
#include "../commands/c_mov_sir.hpp"
#include "../commands/c_mov_rir.hpp"
#include "../commands/c_mov_irr.hpp"
#include "../commands/c_mov_irv.hpp"
#include "../commands/c_add_rr.hpp"
#include "../commands/c_add_ss.hpp"
#include "../commands/c_add_rv.hpp"
#include "../commands/c_add_rm.hpp"
#include "../commands/c_add_mr.hpp"
#include "../commands/c_add_mv.hpp"
#include "../commands/c_add_rs.hpp"
#include "../commands/c_add_ms.hpp"
#include "../commands/c_add_sv.hpp"
#include "../commands/c_sub_rr.hpp"
#include "../commands/c_sub_ss.hpp"
#include "../commands/c_sub_rv.hpp"
#include "../commands/c_sub_rm.hpp"
#include "../commands/c_sub_mr.hpp"
#include "../commands/c_sub_mv.hpp"
#include "../commands/c_sub_rs.hpp"
#include "../commands/c_sub_ms.hpp"
#include "../commands/c_sub_sv.hpp"
#include "../commands/c_mul_rr.hpp"
#include "../commands/c_mul_ss.hpp"
#include "../commands/c_mul_rv.hpp"
#include "../commands/c_mul_rm.hpp"
#include "../commands/c_mul_mr.hpp"
#include "../commands/c_mul_mv.hpp"
#include "../commands/c_mul_rs.hpp"
#include "../commands/c_mul_ms.hpp"
#include "../commands/c_mul_sv.hpp"
#include "../commands/c_div_rr.hpp"
#include "../commands/c_div_ss.hpp"
#include "../commands/c_div_rv.hpp"
#include "../commands/c_div_rm.hpp"
#include "../commands/c_div_mr.hpp"
#include "../commands/c_div_mv.hpp"
#include "../commands/c_div_rs.hpp"
#include "../commands/c_div_ms.hpp"
#include "../commands/c_div_sv.hpp"
#include "../commands/c_mov_axr.hpp"
#include "../commands/c_mov_bxr.hpp"
#include "../commands/c_mov_cxr.hpp"
#include "../commands/c_mov_dxr.hpp"
#include "../commands/c_mov_exr.hpp"
#include "../commands/c_mov_rm.hpp"
#include "../commands/_c_nop.hpp"

Memory *Runtime::getMemory()
{
    return &this->memory;
}

std::stack<uint8_t> *Runtime::getStack()
{
    return &this->stack;
}

Register *Runtime::getAX()
{
    return &this->reg_ax;
}

Register *Runtime::getBX()
{
    return &this->reg_bx;
}

Register *Runtime::getCX()
{
    return &this->reg_cx;
}

Register *Runtime::getDX()
{
    return &this->reg_dx;
}

Register *Runtime::getEX()
{
    return &this->reg_ex;
}

Register *Runtime::getFX()
{
    return &this->reg_fx;
}

Register *Runtime::getGX()
{
    return &this->reg_gx;
}

Register *Runtime::getHX()
{
    return &this->reg_hx;
}

void Runtime::addCommand(Command *command)
{
    this->commands.push_back(command);
}

bool Runtime::existsCommand(uint8_t opcode)
{
    if (opcode < RT_CMD_MEM_SIZE)
        return true;

    for (Command *x : this->commands)
    {
        if (x->getOpcode() == opcode)
            return true;
    }

    return false;
}

std::vector<Command *> *Runtime::getCommands()
{
    return &commands;
}

Command *Runtime::getCommand(uint8_t opcode, bool iterate)
{
    if (!iterate)
        return this->command_mem[opcode];

    for (Command *x : this->commands)
    {
        if (x->getOpcode() == opcode)
            return x;
    }

    return this->nop_command;
}

Runtime::Runtime(int screen_width, int screen_height)
{
    this->reg_ax = Register();
    this->reg_bx = Register();
    this->reg_cx = Register();
    this->reg_dx = Register();
    this->reg_ex = Register();
    this->reg_fx = Register();
    this->reg_gx = Register();
    this->reg_hx = Register();

    this->memory = Memory();
    this->nop_command = new NOP();

    this->commands.push_back(new Int_R());
    this->commands.push_back(new Int_V());
    this->commands.push_back(new Int_M());
    this->commands.push_back(new Int_S());

    this->commands.push_back(new Alloc());

    this->commands.push_back(new Mov_AXV());
    this->commands.push_back(new Mov_BXV());
    this->commands.push_back(new Mov_CXV());
    this->commands.push_back(new Mov_DXV());
    this->commands.push_back(new Mov_EXV());
    this->commands.push_back(new Mov_FXV());
    this->commands.push_back(new Mov_GXV());
    this->commands.push_back(new Mov_HXV());

    this->commands.push_back(new Mov_AXR());
    this->commands.push_back(new Mov_BXR());
    this->commands.push_back(new Mov_CXR());
    this->commands.push_back(new Mov_DXR());
    this->commands.push_back(new Mov_EXR());
    this->commands.push_back(new Mov_FXR());
    this->commands.push_back(new Mov_GXR());
    this->commands.push_back(new Mov_HXR());

    this->commands.push_back(new Mov_IRM());
    this->commands.push_back(new Mov_IMR());
    this->commands.push_back(new Mov_IRS());
    this->commands.push_back(new Mov_IMV());
    this->commands.push_back(new Mov_MM());
    this->commands.push_back(new Mov_MR());
    this->commands.push_back(new Mov_MS());
    this->commands.push_back(new Mov_MV());
    this->commands.push_back(new Mov_RR());
    this->commands.push_back(new Mov_RV());
    this->commands.push_back(new Mov_SM());
    this->commands.push_back(new Mov_SS());
    this->commands.push_back(new Mov_SV());
    this->commands.push_back(new Mov_RM());

    this->commands.push_back(new Mov_MIR());
    this->commands.push_back(new Mov_SIR());
    this->commands.push_back(new Mov_RIR());
    this->commands.push_back(new Mov_IRR());
    this->commands.push_back(new Mov_IRV());

    this->commands.push_back(new Jmp_R());
    this->commands.push_back(new Jmp_V());
    this->commands.push_back(new Jmp_M());

    this->commands.push_back(new Call());
    this->commands.push_back(new Ret());

    this->commands.push_back(new Push8_S());
    this->commands.push_back(new Push8_V());
    this->commands.push_back(new Push8_M());
    this->commands.push_back(new Push16_R());
    this->commands.push_back(new Push16_M());
    this->commands.push_back(new Push16_V());

    this->commands.push_back(new Pop8_S());
    this->commands.push_back(new Pop8_M());
    this->commands.push_back(new Pop16_R());
    this->commands.push_back(new Pop16_M());

    this->commands.push_back(new Je_R());
    this->commands.push_back(new Je_V());
    this->commands.push_back(new Je_M());

    this->commands.push_back(new Jl_R());
    this->commands.push_back(new Jl_V());
    this->commands.push_back(new Jl_M());

    this->commands.push_back(new Jg_R());
    this->commands.push_back(new Jg_V());
    this->commands.push_back(new Jg_M());

    this->commands.push_back(new Jn_R());
    this->commands.push_back(new Jn_V());
    this->commands.push_back(new Jn_M());

    this->commands.push_back(new Dec8_S());
    this->commands.push_back(new Dec8_M());
    this->commands.push_back(new Dec16_R());
    this->commands.push_back(new Dec16_M());

    this->commands.push_back(new Inc8_S());
    this->commands.push_back(new Inc8_M());
    this->commands.push_back(new Inc16_R());
    this->commands.push_back(new Inc16_M());

    this->commands.push_back(new Cmp_RM());
    this->commands.push_back(new Cmp_SM());
    this->commands.push_back(new Cmp_MV());
    this->commands.push_back(new Cmp_SV());
    this->commands.push_back(new Cmp_RV());
    this->commands.push_back(new Cmp_RR());
    this->commands.push_back(new Cmp_SS());
    this->commands.push_back(new Cmp_MM());

    this->commands.push_back(new Add_RR());
    this->commands.push_back(new Add_SS());
    this->commands.push_back(new Add_RV());
    this->commands.push_back(new Add_RM());
    this->commands.push_back(new Add_MR());
    this->commands.push_back(new Add_MV());
    this->commands.push_back(new Add_RS());
    this->commands.push_back(new Add_MS());
    this->commands.push_back(new Add_SV());

    this->commands.push_back(new Sub_RR());
    this->commands.push_back(new Sub_SS());
    this->commands.push_back(new Sub_RV());
    this->commands.push_back(new Sub_RM());
    this->commands.push_back(new Sub_MR());
    this->commands.push_back(new Sub_MV());
    this->commands.push_back(new Sub_RS());
    this->commands.push_back(new Sub_MS());
    this->commands.push_back(new Sub_SV());

    this->commands.push_back(new Mul_RR());
    this->commands.push_back(new Mul_SS());
    this->commands.push_back(new Mul_RV());
    this->commands.push_back(new Mul_RM());
    this->commands.push_back(new Mul_MR());
    this->commands.push_back(new Mul_MV());
    this->commands.push_back(new Mul_RS());
    this->commands.push_back(new Mul_MS());
    this->commands.push_back(new Mul_SV());

    this->commands.push_back(new Div_RR());
    this->commands.push_back(new Div_SS());
    this->commands.push_back(new Div_RV());
    this->commands.push_back(new Div_RM());
    this->commands.push_back(new Div_MR());
    this->commands.push_back(new Div_MV());
    this->commands.push_back(new Div_RS());
    this->commands.push_back(new Div_MS());
    this->commands.push_back(new Div_SV());

    for (int i = 0; i < RT_CMD_MEM_SIZE; i++)
    {
        this->command_mem[i] = getCommand(i, true);
    }

    this->PROGRAMM_INDEX = 0;
    this->DEBUG = false;
    this->WAIT_FOR_KEY_PRESS = false;
    this->INPUT_BUFFER = sf::Keyboard::Key();
    this->screen = new sf::Uint8[screen_height * screen_width * 4];
    this->SCREEN_WIDTH = screen_width;
    this->SCREEN_HEIGHT = screen_height;

    for(int i = 0; i < screen_width*screen_height*4; i += 4)
    {
        this->screen[i] = 0;
        this->screen[i+1] = 0;
        this->screen[i+2] = 0;
        this->screen[i+3] = 255;
    }

    this->screen_width = screen_width;
    this->screen_height = screen_height;
}

Register *Runtime::getRegisterByID(uint8_t id)
{
    switch (id)
    {
        case 1:
            return &this->reg_ax;
        case 2:
            return &this->reg_bx;
        case 3:
            return &this->reg_cx;
        case 4:
            return &this->reg_dx;
        case 5:
            return &this->reg_ex;
        case 6:
            return &this->reg_fx;
        case 7:
            return &this->reg_gx;
        case 8:
            return &this->reg_hx;
    }

    this->raiseException("GIVEN REGISTER ID WRONG");
    return 0;
}

void Runtime::raiseException(std::string string)
{
    std::cout << std::endl << std::endl << string << std::endl << "Press enter to exit." << std::endl;
    ppt8_std::get_char();
    exit(1);
}

uint8_t Runtime::getSubRegisterByID(uint8_t id)
{
    switch (id)
    {
        case 1:
            return this->reg_ax.getHigher8bit();
        case 2:
            return this->reg_bx.getHigher8bit();
        case 3:
            return this->reg_cx.getHigher8bit();
        case 4:
            return this->reg_dx.getHigher8bit();
        case 5:
            return this->reg_ex.getHigher8bit();
        case 6:
            return this->reg_fx.getHigher8bit();
        case 7:
            return this->reg_gx.getHigher8bit();
        case 8:
            return this->reg_hx.getHigher8bit();
        case 9:
            return this->reg_ax.getLower8bit();
        case 10:
            return this->reg_bx.getLower8bit();
        case 11:
            return this->reg_cx.getLower8bit();
        case 12:
            return this->reg_dx.getLower8bit();
        case 13:
            return this->reg_ex.getLower8bit();
        case 14:
            return this->reg_fx.getLower8bit();
        case 15:
            return this->reg_gx.getLower8bit();
        case 16:
            return this->reg_hx.getLower8bit();
    }

    return 0;
}

void Runtime::setSubRegisterByID(uint8_t id, uint8_t value)
{
    if (DEBUG)
    {
        std::cout << "((SET " << (int) id << " TO " << (int) value << "))" << std::endl;
        int a = (id-8 < 0 ? id : id-8);
        int b = (id+8 > 16 ? id : id+8);

        std::cout << "((B " << a << "=" << (int) this->getSubRegisterByID(a) << " | " << b << "=" << (int) this->getSubRegisterByID(b) << "))" << std::endl;
    }

    switch (id)
    {
        case 1:
            this->reg_ax.setValueHigher8bit(value);
            break;
        case 2:
            this->reg_bx.setValueHigher8bit(value);
            break;
        case 3:
            this->reg_cx.setValueHigher8bit(value);
            break;
        case 4:
            this->reg_dx.setValueHigher8bit(value);
            break;
        case 5:
            this->reg_ex.setValueHigher8bit(value);
            break;
        case 6:
            this->reg_fx.setValueHigher8bit(value);
            break;
        case 7:
            this->reg_gx.setValueHigher8bit(value);
            break;
        case 8:
            this->reg_hx.setValueHigher8bit(value);
            break;
        case 9:
            this->reg_ax.setValueLower8bit(value);
            break;
        case 10:
            this->reg_bx.setValueLower8bit(value);
            break;
        case 11:
            this->reg_cx.setValueLower8bit(value);
            break;
        case 12:
            this->reg_dx.setValueLower8bit(value);
            break;
        case 13:
            this->reg_ex.setValueLower8bit(value);
            break;
        case 14:
            this->reg_fx.setValueLower8bit(value);
            break;
        case 15:
            this->reg_gx.setValueLower8bit(value);
            break;
        case 16:
            this->reg_hx.setValueLower8bit(value);
            break;
    }

    if (this->DEBUG)
    {
        int a = (id-8 < 0 ? id : id-8);
        int b = (id+8 > 16 ? id : id+8);

        std::cout << "((E " << a << "=" << (int) this->getSubRegisterByID(a) << " | " << b << "=" << (int) this->getSubRegisterByID(b) << "))" << std::endl;
    }
}

void Runtime::push8bit(uint8_t i)
{
    this->stack.push(i);
}

void Runtime::push16bitSplittet(uint16_t i)
{
    this->stack.push(ppt8_std::get_higher_8bit_from_16bit(i));
    this->stack.push(ppt8_std::get_lower_8bit_from_16bit(i));
}

int Runtime::getPixelState(int x, int y)
{
    if (y >= this->screen_height || y < 0)
        return 0;

    if (x >= this->screen_width || x < 0)
        return 0;

    return screen[(y*this->screen_width + x) * 4];
}

void Runtime::setPixelState(int x, int y, uint8_t state)
{
    if (y >= this->screen_height || y < 0)
        return;

    if (x >= this->screen_width || x < 0)
        return;

    screen[(y*this->screen_width + x) * 4] = state;
    screen[(y*this->screen_width + x) * 4 + 1] = state;
    screen[(y*this->screen_width + x) * 4 + 2] = state;
    screen[(y*this->screen_width + x) * 4 + 3] = state;
}

sf::Uint8* Runtime::getPixelStates()
{
    return this->screen;
}

void Runtime::clearPixels()
{
    /*
    sf::RectangleShape rect;
    rect.setPosition(0, 0);
    rect.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
    rect.setFillColor(sf::Color::Black);

    window->draw(rect);
    */

    for(int i = 0; i < screen_width*screen_height*4; i += 4)
    {
        this->screen[i] = 0;
        this->screen[i+1] = 0;
        this->screen[i+2] = 0;
        this->screen[i+3] = 255;
    }
}

int Runtime::getPixelSize()
{
    return window->getSize().x / this->screen_width;
}
