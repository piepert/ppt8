#include "runtime.hpp"
#include <iostream>

void Runtime::registerName(Name n)
{
    if (!existsNameByValue(n.getValue()))
        this->names.push_back(n);
}

Name* Runtime::getNameByValue(std::string value)
{
    for (Name &n : this->names)
    {
        if (n.getValue() == value)
            return &n;
    }

    return nullptr;
}

bool Runtime::existsNameByValue(std::string value)
{
    for (const Name &n : this->names)
    {
        if (n.getValue() == value)
            return true;
    }

    return false;
}

Runtime::Runtime()
{
    this->registerName(Name("mov", NT_Command));
    this->registerName(Name("int", NT_Command));
    this->registerName(Name("alloc", NT_Command));
    this->registerName(Name("call", NT_Command));
    this->registerName(Name("add", NT_Command));
    this->registerName(Name("sub", NT_Command));
    this->registerName(Name("mul", NT_Command));
    this->registerName(Name("div", NT_Command));
    this->registerName(Name("push", NT_Command));
    this->registerName(Name("pop", NT_Command));
    this->registerName(Name("ret", NT_Command));
    this->registerName(Name("inc", NT_Command));
    this->registerName(Name("dec", NT_Command));
    this->registerName(Name("jmp", NT_Command));
    this->registerName(Name("je", NT_Command));
    this->registerName(Name("jl", NT_Command));
    this->registerName(Name("jg", NT_Command));
    this->registerName(Name("jn", NT_Command));
    this->registerName(Name("and", NT_Command));
    this->registerName(Name("or", NT_Command));
    this->registerName(Name("nand", NT_Command));
    this->registerName(Name("nor", NT_Command));
    this->registerName(Name("xor", NT_Command));
    this->registerName(Name("not", NT_Command));
    this->registerName(Name("cmp", NT_Command));

    this->registerName(Name("ax", NT_Register));
    this->registerName(Name("bx", NT_Register));
    this->registerName(Name("cx", NT_Register));
    this->registerName(Name("dx", NT_Register));
    this->registerName(Name("ex", NT_Register));
    this->registerName(Name("fx", NT_Register));
    this->registerName(Name("gx", NT_Register));
    this->registerName(Name("hx", NT_Register));

    this->registerName(Name("ah", NT_Subregister));
    this->registerName(Name("bh", NT_Subregister));
    this->registerName(Name("ch", NT_Subregister));
    this->registerName(Name("dh", NT_Subregister));
    this->registerName(Name("eh", NT_Subregister));
    this->registerName(Name("fh", NT_Subregister));
    this->registerName(Name("gh", NT_Subregister));
    this->registerName(Name("hh", NT_Subregister));

    this->registerName(Name("al", NT_Subregister));
    this->registerName(Name("bl", NT_Subregister));
    this->registerName(Name("cl", NT_Subregister));
    this->registerName(Name("dl", NT_Subregister));
    this->registerName(Name("el", NT_Subregister));
    this->registerName(Name("fl", NT_Subregister));
    this->registerName(Name("gl", NT_Subregister));
    this->registerName(Name("hl", NT_Subregister));

    this->registerName(Name("mov_rr", NT_Command));
    this->registerName(Name("mov_rv", NT_Command));
    this->registerName(Name("mov_mr", NT_Command));
    this->registerName(Name("mov_ss", NT_Command));
    this->registerName(Name("mov_ms", NT_Command));
    this->registerName(Name("mov_sv", NT_Command));
    this->registerName(Name("mov_mv", NT_Command));
    this->registerName(Name("mov_mm", NT_Command));
    this->registerName(Name("mov_imv", NT_Command));
    this->registerName(Name("mov_irm", NT_Command));
    this->registerName(Name("mov_rm", NT_Command));
    this->registerName(Name("mov_imr", NT_Command));
    this->registerName(Name("mov_sm", NT_Command));
    this->registerName(Name("mov_irs", NT_Command));
    this->registerName(Name("call", NT_Command));
    this->registerName(Name("mov_axv", NT_Command));
    this->registerName(Name("mov_bxv", NT_Command));
    this->registerName(Name("mov_cxv", NT_Command));
    this->registerName(Name("mov_dxv", NT_Command));
    this->registerName(Name("mov_exv", NT_Command));
    this->registerName(Name("mov_fxv", NT_Command));
    this->registerName(Name("mov_gxv", NT_Command));
    this->registerName(Name("mov_hxv", NT_Command));
    this->registerName(Name("mov_axr", NT_Command));
    this->registerName(Name("mov_bxr", NT_Command));
    this->registerName(Name("mov_cxr", NT_Command));
    this->registerName(Name("mov_dxr", NT_Command));
    this->registerName(Name("mov_exr", NT_Command));
    this->registerName(Name("mov_fxr", NT_Command));
    this->registerName(Name("mov_gxr", NT_Command));
    this->registerName(Name("mov_hxr", NT_Command));
    this->registerName(Name("alloc", NT_Command));
    this->registerName(Name("int_v", NT_Command));
    this->registerName(Name("int_r", NT_Command));
    this->registerName(Name("int_s", NT_Command));
    this->registerName(Name("int_m", NT_Command));
    this->registerName(Name("push8_s", NT_Command));
    this->registerName(Name("push8_m", NT_Command));
    this->registerName(Name("push8_v", NT_Command));
    this->registerName(Name("push16_r", NT_Command));
    this->registerName(Name("push16_m", NT_Command));
    this->registerName(Name("push16_v", NT_Command));
    this->registerName(Name("pop8_s", NT_Command));
    this->registerName(Name("pop8_m", NT_Command));
    this->registerName(Name("pop16_r", NT_Command));
    this->registerName(Name("pop16_m", NT_Command));
    this->registerName(Name("ret", NT_Command));
    this->registerName(Name("add_rr", NT_Command));
    this->registerName(Name("add_rv", NT_Command));
    this->registerName(Name("add_rm", NT_Command));
    this->registerName(Name("add_mr", NT_Command));
    this->registerName(Name("add_mv", NT_Command));
    this->registerName(Name("add_rs", NT_Command));
    this->registerName(Name("add_ms", NT_Command));
    this->registerName(Name("add_sv", NT_Command));
    this->registerName(Name("sub_rr", NT_Command));
    this->registerName(Name("sub_rv", NT_Command));
    this->registerName(Name("sub_rm", NT_Command));
    this->registerName(Name("sub_mr", NT_Command));
    this->registerName(Name("sub_mv", NT_Command));
    this->registerName(Name("sub_rs", NT_Command));
    this->registerName(Name("sub_ms", NT_Command));
    this->registerName(Name("sub_sv", NT_Command));
    this->registerName(Name("mul_rr", NT_Command));
    this->registerName(Name("mul_rv", NT_Command));
    this->registerName(Name("mul_rm", NT_Command));
    this->registerName(Name("mul_mr", NT_Command));
    this->registerName(Name("mul_mv", NT_Command));
    this->registerName(Name("mul_rs", NT_Command));
    this->registerName(Name("mul_ms", NT_Command));
    this->registerName(Name("mul_sv", NT_Command));
    this->registerName(Name("div_rr", NT_Command));
    this->registerName(Name("div_rv", NT_Command));
    this->registerName(Name("div_rm", NT_Command));
    this->registerName(Name("div_mr", NT_Command));
    this->registerName(Name("div_mv", NT_Command));
    this->registerName(Name("div_rs", NT_Command));
    this->registerName(Name("div_ms", NT_Command));
    this->registerName(Name("div_sv", NT_Command));
    this->registerName(Name("inc8_s", NT_Command));
    this->registerName(Name("inc8_m", NT_Command));
    this->registerName(Name("inc16_r", NT_Command));
    this->registerName(Name("inc16_m", NT_Command));
    this->registerName(Name("dec8_s", NT_Command));
    this->registerName(Name("dec8_m", NT_Command));
    this->registerName(Name("dec16_r", NT_Command));
    this->registerName(Name("dec16_m", NT_Command));
    this->registerName(Name("cmp_rm", NT_Command));
    this->registerName(Name("cmp_sm", NT_Command));
    this->registerName(Name("cmp_mv", NT_Command));
    this->registerName(Name("cmp_sv", NT_Command));
    this->registerName(Name("cmp_rv", NT_Command));
    this->registerName(Name("jmp_v", NT_Command));
    this->registerName(Name("jmp_r", NT_Command));
    this->registerName(Name("jmp_m", NT_Command));
    this->registerName(Name("je_v", NT_Command));
    this->registerName(Name("je_r", NT_Command));
    this->registerName(Name("je_m", NT_Command));
    this->registerName(Name("jl_v", NT_Command));
    this->registerName(Name("jl_r", NT_Command));
    this->registerName(Name("jl_m", NT_Command));
    this->registerName(Name("jg_v", NT_Command));
    this->registerName(Name("jg_r", NT_Command));
    this->registerName(Name("jg_m", NT_Command));
    this->registerName(Name("jn_v", NT_Command));
    this->registerName(Name("jn_r", NT_Command));
    this->registerName(Name("jn_m", NT_Command));
    this->registerName(Name("and_rr", NT_Command));
    this->registerName(Name("and_ss", NT_Command));
    this->registerName(Name("and_rv", NT_Command));
    this->registerName(Name("and_sv", NT_Command));
    this->registerName(Name("or_rr", NT_Command));
    this->registerName(Name("or_ss", NT_Command));
    this->registerName(Name("or_rv", NT_Command));
    this->registerName(Name("or_sv", NT_Command));
    this->registerName(Name("not_rr", NT_Command));
    this->registerName(Name("not_ss", NT_Command));
    this->registerName(Name("not_rv", NT_Command));
    this->registerName(Name("not_sv", NT_Command));
    this->registerName(Name("nand_rr", NT_Command));
    this->registerName(Name("nand_ss", NT_Command));
    this->registerName(Name("nand_rv", NT_Command));
    this->registerName(Name("nand_sv", NT_Command));
    this->registerName(Name("nor_rr", NT_Command));
    this->registerName(Name("nor_ss", NT_Command));
    this->registerName(Name("nor_rv", NT_Command));
    this->registerName(Name("nor_sv", NT_Command));
    this->registerName(Name("xor_rr", NT_Command));
    this->registerName(Name("xor_ss", NT_Command));
    this->registerName(Name("xor_rv", NT_Command));
    this->registerName(Name("xor_sv", NT_Command));
    this->registerName(Name("mov_irr", NT_Command));
    this->registerName(Name("mov_irv", NT_Command));
    this->registerName(Name("mov_rir", NT_Command));
    this->registerName(Name("mov_sir", NT_Command));
    this->registerName(Name("mov_mir", NT_Command));
    this->registerName(Name("mov_axv", NT_Command));
    this->registerName(Name("mov_bxv", NT_Command));
    this->registerName(Name("mov_cxv", NT_Command));
    this->registerName(Name("mov_dxv", NT_Command));
    this->registerName(Name("mov_exv", NT_Command));
    this->registerName(Name("mov_fxv", NT_Command));
    this->registerName(Name("mov_gxv", NT_Command));
    this->registerName(Name("mov_hxv", NT_Command));
    this->registerName(Name("alloc", NT_Command));
    this->registerName(Name("alloc", NT_Command));
    this->registerName(Name("alloc", NT_Command));
    this->registerName(Name("cmp_mv", NT_Command));
    this->registerName(Name("add_ss", NT_Command));
    this->registerName(Name("sub_ss", NT_Command));
    this->registerName(Name("mul_ss", NT_Command));
    this->registerName(Name("div_ss", NT_Command));

    this->registerName(Name("word", NT_Command));
    this->registerName(Name("@", NT_Command));
}

void Runtime::addVariable(Variable v)
{
    if (!existsVariableByName(v.getName()))
        this->variables.push_back(v);
}

bool Runtime::existsVariableByName(std::string name)
{
    for (const Variable &n : this->variables)
    {
        if (n.getName() == name)
            return true;
    }

    return false;
}

Variable* Runtime::getVariableByName(std::string name)
{
    for (Variable &n : this->variables)
    {
        if (n.getName() == name)
            return &n;
    }

    return nullptr;
}
