
#include "verify_program.hpp"
#include <migraphx/program.hpp>
#include <migraphx/generate.hpp>
#include <migraphx/operators.hpp>

struct test_log : verify_program<test_log>
{
    migraphx::program create_program() const
    {
        migraphx::program p;
        auto* mm = p.get_main_module();
        migraphx::shape s{migraphx::shape::float_type, {6}};
        auto x = mm->add_instruction(migraphx::op::abs{}, mm->add_parameter("x", s));
        mm->add_instruction(migraphx::op::log{}, x);
        return p;
    }
};