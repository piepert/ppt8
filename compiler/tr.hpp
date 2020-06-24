#ifndef COMPILER_TR_HPP
#define COMPILER_TR_HPP

#include <vector>
#include <string>
#include <iostream>
#include "token.hpp"

const std::vector<std::vector<std::string>> MNEMONIC_PATTERNS = { // ALLOC NOT INCLUDED
    { "mov_rr", "mov r,r" },
    { "mov_rv", "mov r,wordvv" },
    { "mov_mr", "mov @vv,r" },
    { "mov_ss", "mov s,s" },
    { "mov_ms", "mov @vv,s" },
    { "mov_sv", "mov s,v" },
    { "mov_mv", "mov @vv,v" },
    { "mov_mm", "mov @vv,@vv" },
    { "mov_imv", "mov @@vv,v" },
    { "mov_irm", "mov @r,@vv" },
    { "mov_rm", "mov r,@vv" },
    { "mov_imr", "mov @@vv,r" },
    { "mov_sm", "mov s,@vv" },
    { "mov_irs", "mov @r,s" },
    { "call", "call wordvv" },
    { "mov_axv", "mov ax,wordvv" },
    { "mov_bxv", "mov bx,wordvv" },
    { "mov_cxv", "mov cx,wordvv" },
    { "mov_dxv", "mov dx,wordvv" },
    { "mov_exv", "mov ex,wordvv" },
    { "mov_fxv", "mov fx,wordvv" },
    { "mov_gxv", "mov gx,wordvv" },
    { "mov_hxv", "mov hx,wordvv" },
    { "mov_axr", "mov ax,r" },
    { "mov_bxr", "mov bx,r" },
    { "mov_cxr", "mov cx,r" },
    { "mov_dxr", "mov dx,r" },
    { "mov_exr", "mov ex,r" },
    { "mov_fxr", "mov fx,r" },
    { "mov_gxr", "mov gx,r" },
    { "mov_hxr", "mov hx,r" },
    { "int_v", "int v" },
    { "int_r", "int r" },
    { "int_s", "int s" },
    { "int_m", "int @vv" },
    { "push8_s", "push s" },
    { "push8_m", "push @vv" },
    { "push8_v", "push v" },
    { "push16_r", "push r" },
    { "push16_m", "push word@vv" },
    { "push16_v", "push wordvv" },
    { "pop8_s", "pop s" },
    { "pop8_m", "pop @vv" },
    { "pop16_r", "pop r" },
    { "pop16_m", "pop word@vv" },
    { "ret", "ret" },
    { "add_rr", "add r,r" },
    { "add_rv", "add r,wordvv" },
    { "add_rm", "add r,@vv" },
    { "add_mr", "add @vv,r" },
    { "add_mv", "add @vv,v" },
    { "add_rs", "add r,s" },
    { "add_ms", "add @vv,s" },
    { "add_sv", "add s,v" },
    { "sub_rr", "sub r,r" },
    { "sub_rv", "sub r,wordvv" },
    { "sub_rm", "sub r,@vv" },
    { "sub_mr", "sub @vv,r" },
    { "sub_mv", "sub @vv,v" },
    { "sub_rs", "sub r,s" },
    { "sub_ms", "sub @vv,s" },
    { "sub_sv", "sub s,v" },
    { "mul_rr", "mul r,r" },
    { "mul_rv", "mul r,wordvv" },
    { "mul_rm", "mul r,@vv" },
    { "mul_mr", "mul @vv,r" },
    { "mul_mv", "mul @vv,v" },
    { "mul_rs", "mul r,s" },
    { "mul_ms", "mul @vv,s" },
    { "mul_sv", "mul s,v" },
    { "div_rr", "div r,r" },
    { "div_rv", "div r,wordvv" },
    { "div_rm", "div r,@vv" },
    { "div_mr", "div @vv,r" },
    { "div_mv", "div @vv,v" },
    { "div_rs", "div r,s" },
    { "div_ms", "div @vv,s" },
    { "div_sv", "div s,v" },
    { "inc8_s", "inc s" },
    { "inc8_m", "inc @vv" },
    { "inc16_r", "inc r" },
    { "inc16_m", "inc word@vv" },
    { "dec8_s", "dec s" },
    { "dec8_m", "dec @vv" },
    { "dec16_r", "dec r" },
    { "dec16_m", "dev word@vv" },
    { "cmp_rm", "cmp r,@vv" },
    { "cmp_sm", "cmp s,@vv" },
    { "cmp_mv", "cmp @vv,v" },
    { "cmp_sv", "cmp s,v" },
    { "cmp_rv", "cmp r,wordvv" },
    { "jmp_v", "jmp wordvv" },
    { "jmp_r", "jmp r" },
    { "jmp_m", "jmp @vv" },
    { "je_v", "je wordvv" },
    { "je_r", "je r" },
    { "je_m", "je @vv" },
    { "jl_v", "jl wordvv" },
    { "jl_r", "jl register" },
    { "jl_m", "jl @vv" },
    { "jg_v", "jg wordvv" },
    { "jg_r", "jg r" },
    { "jg_m", "jg @vv" },
    { "jn_v", "jn wordvv" },
    { "jn_r", "jn r" },
    { "jn_m", "jn @vv" },
    { "and_rr", "and r,r" },
    { "and_ss", "and s,s" },
    { "and_rv", "and r,wordvv" },
    { "and_sv", "and s,v" },
    { "or_rr", "or r,r" },
    { "or_ss", "or s,s" },
    { "or_rv", "or r,wordvv" },
    { "or_sv", "or s,v" },
    { "not_r", "not r" },
    { "not_s", "not s" },
    { "nand_rr", "nand r,r" },
    { "nand_ss", "nand s,s" },
    { "nand_rv", "nand r,wordvv" },
    { "nand_sv", "nand s,v" },
    { "nor_rr", "nor r,r" },
    { "nor_ss", "nor s,s" },
    { "nor_rv", "nor r,wordvv" },
    { "nor_sv", "nor s,v" },
    { "xor_rr", "xor r,r" },
    { "xor_ss", "xor s,s" },
    { "xor_rv", "xor r,wordvv" },
    { "xor_sv", "xor s,v" },
    { "mov_irr", "mov @r,r" },
    { "mov_irv", "mov @r,v" },
    { "mov_rir", "mov r,@r" },
    { "mov_sir", "mov s,@r" },
    { "mov_mir", "mov @vv,@r" },
    { "cmp_mm", "cmp @vv,@vv" },
    { "add_ss", "add s,s" },
    { "sub_ss", "sub s,s" },
    { "mul_ss", "mul s,s" },
    { "div_ss", "div s,s" },
    { "mov_axm", "mov ax,word@vv" },
    { "mov_bxm", "mov bx,word@vv" },
    { "mov_cxm", "mov cx,word@vv" },
    { "mov_dxm", "mov dx,word@vv" },
    { "mov_exm", "mov ex,word@vv" },
    { "mov_fxm", "mov fx,word@vv" },
    { "mov_gxm", "mov gx,word@vv" },
    { "mov_hxm", "mov hx,word@vv" },
    { "cmp_mm", "cmp @vv,@vv" },
    { "cmp_ss", "cmp s,s" },
    { "cmp_rr", "cmp r,r" }
};

std::string get_mnemonic_for_pattern(std::vector<Token> pattern)
{
    if (pattern.size() == 0)
        return "null";

    std::string p = pattern[0].getValue()+" ";
    int rc = 0;

    for (int i = 1; i < pattern.size(); i++)
    {
        if (pattern[i].getType().getPattern() == "r" && rc <= 0)
        {
            p += pattern[i].getValue();
            rc++;
        }
        else
            p += pattern[i].getType().getPattern();
    }

    if (pattern.size() == 1)
        p = pattern[0].getValue();

    for (int i = 0; i < MNEMONIC_PATTERNS.size(); i++)
    {
        if (MNEMONIC_PATTERNS[i][1] == p)
            return MNEMONIC_PATTERNS[i][0];
    }

    p = pattern[0].getValue()+" ";

    for (int i = 1; i < pattern.size(); i++)
        p += pattern[i].getType().getPattern();

    if (pattern.size() == 1)
        p = pattern[0].getValue();

    for (int i = 0; i < MNEMONIC_PATTERNS.size(); i++)
    {
        if (MNEMONIC_PATTERNS[i][1] == p)
            return MNEMONIC_PATTERNS[i][0];
    }

    return "null";
}

#endif //COMPILER_TR_HPP
