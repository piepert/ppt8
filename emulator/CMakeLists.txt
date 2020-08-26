cmake_minimum_required(VERSION 3.16)
project(emulator)

set(CMAKE_CXX_FLAGS "-lsfml-graphics -lsfml-window -lpthread -lsfml-system")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(ppt8e
        main.cpp

        std/std.hpp
        std/std.cpp
        std/curses.hpp
        std/functions.hpp
        std/functions.cpp
        std/tr.hpp

        runtime/runtime.hpp
        runtime/runtime.cpp

        command/command.hpp

        memory/memory.cpp
        memory/memory.hpp

        register/register.cpp
        register/register.hpp

        label/label.cpp
        label/label.hpp

        commands/c_mov_rr.hpp # ok
        commands/c_mov_rv.hpp # ok
        commands/c_mov_mr.hpp # ok
        commands/c_mov_ss.hpp # ok
        commands/c_mov_ms.hpp # ok
        commands/c_mov_sv.hpp # ok
        commands/c_mov_mv.hpp # ok
        commands/c_mov_mm.hpp # ok
        commands/c_mov_imv.hpp # ok
        commands/c_mov_irm.hpp # ok
        commands/c_mov_rm.hpp # ok
        commands/c_mov_imr.hpp # ok
        commands/c_mov_sm.hpp # ok
        commands/c_mov_irs.hpp # ok

        commands/c_call.hpp # ok

        commands/c_mov_axv.hpp # ok
        commands/c_mov_bxv.hpp # ok
        commands/c_mov_cxv.hpp # ok
        commands/c_mov_dxv.hpp # ok
        commands/c_mov_exv.hpp # ok
        commands/c_mov_fxv.hpp # ok
        commands/c_mov_gxv.hpp # ok
        commands/c_mov_hxv.hpp # ok
        commands/c_mov_axr.hpp # ok
        commands/c_mov_bxr.hpp # ok
        commands/c_mov_cxr.hpp # ok
        commands/c_mov_dxr.hpp # ok
        commands/c_mov_exr.hpp # ok
        commands/c_mov_fxr.hpp # ok
        commands/c_mov_gxr.hpp # ok
        commands/c_mov_hxr.hpp # ok

        commands/c_alloc.hpp # ok

        commands/c_int_v.hpp # ok
        commands/c_int_r.hpp # ok
        commands/c_int_s.hpp # ok
        commands/c_int_m.hpp # ok

        commands/c_push8_s.hpp # ok
        commands/c_push8_m.hpp # ok
        commands/c_push8_v.hpp # ok
        commands/c_push16_r.hpp # ok
        commands/c_push16_m.hpp # ok
        commands/c_push16_v.hpp # ok

        commands/c_pop8_s.hpp # ok
        commands/c_pop8_m.hpp # ok
        commands/c_pop16_r.hpp # ok
        commands/c_pop16_m.hpp # ok

        commands/c_ret.hpp # ok

        commands/c_add_rr.hpp # ok
        commands/c_add_rv.hpp # ok
        commands/c_add_rm.hpp # ok
        commands/c_add_mr.hpp # ok
        commands/c_add_mv.hpp # ok
        commands/c_add_rs.hpp # ok
        commands/c_add_ms.hpp # ok
        commands/c_add_sv.hpp # ok

        commands/c_sub_rr.hpp # ok
        commands/c_sub_rv.hpp # ok
        commands/c_sub_rm.hpp # ok
        commands/c_sub_mr.hpp # ok
        commands/c_sub_mv.hpp # ok
        commands/c_sub_rs.hpp # ok
        commands/c_sub_ms.hpp # ok
        commands/c_sub_sv.hpp

        commands/c_mul_rr.hpp # ok
        commands/c_mul_rv.hpp # ok
        commands/c_mul_rm.hpp # ok
        commands/c_mul_mr.hpp # ok
        commands/c_mul_mv.hpp # ok
        commands/c_mul_rs.hpp # ok
        commands/c_mul_ms.hpp # ok
        commands/c_mul_sv.hpp

        commands/c_div_rr.hpp # ok
        commands/c_div_rv.hpp # ok
        commands/c_div_rm.hpp # ok
        commands/c_div_mr.hpp # ok
        commands/c_div_mv.hpp # ok
        commands/c_div_rs.hpp # ok
        commands/c_div_ms.hpp # ok
        commands/c_div_sv.hpp

        commands/c_inc8_s.hpp # ok
        commands/c_inc8_m.hpp # ok
        commands/c_inc16_r.hpp # ok
        commands/c_inc16_m.hpp # ok

        commands/c_dec8_s.hpp # ok
        commands/c_dec8_m.hpp # ok
        commands/c_dec16_r.hpp # ok
        commands/c_dec16_m.hpp # ok

        commands/c_cmp_rm.hpp # ok
        commands/c_cmp_sm.hpp # ok
        commands/c_cmp_mv.hpp # ok
        commands/c_cmp_sv.hpp # ok
        commands/c_cmp_rv.hpp # ok
        commands/c_cmp_mm.hpp # ok
        commands/c_cmp_ss.hpp # ok
        commands/c_cmp_rr.hpp # ok

        commands/c_jmp_v.hpp # ok
        commands/c_jmp_r.hpp # ok
        commands/c_jmp_m.hpp # ok

        commands/c_je_v.hpp # ok
        commands/c_je_r.hpp # ok
        commands/c_je_m.hpp # ok

        commands/c_jl_v.hpp # ok
        commands/c_jl_r.hpp # ok
        commands/c_jl_m.hpp # ok

        commands/c_jg_v.hpp # ok
        commands/c_jg_r.hpp # ok
        commands/c_jg_m.hpp # ok

        commands/c_jn_v.hpp # ok
        commands/c_jn_r.hpp # ok
        commands/c_jn_m.hpp # ok

        commands/c_and_rr.hpp
        commands/c_and_ss.hpp
        commands/c_and_rv.hpp
        commands/c_and_sv.hpp

        commands/c_or_rr.hpp
        commands/c_or_ss.hpp
        commands/c_or_rv.hpp
        commands/c_or_sv.hpp

        commands/c_not_rr.hpp
        commands/c_not_ss.hpp
        commands/c_not_rv.hpp
        commands/c_not_sv.hpp

        commands/c_nand_rr.hpp
        commands/c_nand_ss.hpp
        commands/c_nand_rv.hpp
        commands/c_nand_sv.hpp

        commands/c_nor_rr.hpp
        commands/c_nor_ss.hpp
        commands/c_nor_rv.hpp
        commands/c_nor_sv.hpp

        commands/c_xor_rr.hpp
        commands/c_xor_ss.hpp
        commands/c_xor_rv.hpp
        commands/c_xor_sv.hpp

        commands/c_mov_irr.hpp # ok
        commands/c_mov_irv.hpp # ok
        commands/c_mov_rir.hpp # ok
        commands/c_mov_sir.hpp # ok
        commands/c_mov_mir.hpp # ok

        commands/c_add_ss.hpp # ok
        commands/c_sub_ss.hpp # ok
        commands/c_mul_ss.hpp # ok
        commands/c_div_ss.hpp # ok

        commands/c_mov_axm.hpp # ok
        commands/c_mov_bxm.hpp # ok
        commands/c_mov_cxm.hpp # ok
        commands/c_mov_dxm.hpp # ok
        commands/c_mov_exm.hpp # ok
        commands/c_mov_fxm.hpp # ok
        commands/c_mov_gxm.hpp # ok
        commands/c_mov_hxm.hpp # ok

        commands/_c_nop.hpp # ok

        )