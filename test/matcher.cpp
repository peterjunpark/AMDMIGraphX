#include <migraph/matcher.hpp>
#include <migraph/iterator_for.hpp>
#include <test.hpp>
#include <basic_ops.hpp>

namespace match = migraph::match;

template <class M>
migraph::match::matcher_result find_match(migraph::program& p, M&& m)
{
    migraph::match::matcher_result result;
    for(auto ins : migraph::iterator_for(p))
    {
        result = migraph::match::match_instruction(p, ins, m);
        if(result.result != p.end())
            return result;
    }
    return result;
}

void match1()
{
    migraph::program p;
    auto l = p.add_literal(1);
    auto m = match::standard_shape();
    auto r = find_match(p, m);
    EXPECT(bool{r.result == l});
}

void match_name1()
{
    migraph::program p;
    auto one = p.add_literal(1);
    auto two = p.add_literal(2);
    auto sum = p.add_instruction(sum_op{}, one, two);
    p.add_instruction(pass_op{}, sum);
    auto m = match::name("sum");
    auto r = find_match(p, m);
    EXPECT(bool{r.result == sum});
}

void match_name2()
{
    migraph::program p;
    auto one = p.add_literal(1);
    auto two = p.add_literal(2);
    auto sum = p.add_instruction(sum_op{}, one, two);
    p.add_instruction(pass_op{}, sum);
    auto m = match::name("min");
    auto r = find_match(p, m);
    EXPECT(bool{r.result == p.end()});
}

void match_name3()
{
    migraph::program p;
    auto one = p.add_literal(1);
    auto two = p.add_literal(2);
    auto sum = p.add_instruction(sum_op{}, one, two);
    p.add_instruction(pass_op{}, sum);
    auto m = match::name("sum")(match::standard_shape());
    auto r = find_match(p, m);
    EXPECT(bool{r.result == sum});
}

void match_arg1()
{
    migraph::program p;
    auto one = p.add_literal(1);
    auto two = p.add_literal(2);
    auto sum = p.add_instruction(sum_op{}, one, two);
    p.add_instruction(pass_op{}, sum);
    auto m = match::name("sum")(match::arg(0)(match::name("@literal")), match::standard_shape());
    auto r = find_match(p, m);
    EXPECT(bool{r.result == sum});
}

void match_arg2()
{
    migraph::program p;
    auto one = p.add_literal(1);
    auto two = p.add_literal(2);
    auto sum = p.add_instruction(sum_op{}, one, two);
    p.add_instruction(pass_op{}, sum);
    auto m = match::name("sum")(match::arg(0)(match::name("sum")), match::standard_shape());
    auto r = find_match(p, m);
    EXPECT(bool{r.result == p.end()});
}

void match_arg3()
{
    migraph::program p;
    auto one = p.add_literal(1);
    auto two = p.add_literal(2);
    auto sum = p.add_instruction(sum_op{}, one, two);
    p.add_instruction(pass_op{}, sum);
    auto m = match::name("sum")(match::arg(1)(match::name("@literal")), match::standard_shape());
    auto r = find_match(p, m);
    EXPECT(bool{r.result == sum});
}

void match_arg4()
{
    migraph::program p;
    auto one  = p.add_literal(1);
    auto two  = p.add_literal(2);
    auto sum  = p.add_instruction(sum_op{}, one, two);
    auto pass = p.add_instruction(pass_op{}, sum);
    auto m    = match::name("pass")(match::arg(0)(match::name("sum")), match::standard_shape());
    auto r    = find_match(p, m);
    EXPECT(bool{r.result == pass});
}

void match_arg5()
{
    migraph::program p;
    auto one = p.add_literal(1);
    auto two = p.add_literal(2);
    auto sum = p.add_instruction(sum_op{}, one, two);
    p.add_instruction(pass_op{}, sum);
    auto m = match::name("pass")(match::arg(1)(match::name("sum")), match::standard_shape());
    auto r = find_match(p, m);
    EXPECT(bool{r.result == p.end()});
}

void match_arg6()
{
    migraph::program p;
    auto one = p.add_literal(1);
    auto two = p.add_literal(2);
    auto sum = p.add_instruction(sum_op{}, one, two);
    p.add_instruction(pass_op{}, sum);
    auto m = match::name("sum")(match::arg(0)(match::name("@literal")));
    auto r = find_match(p, m);
    EXPECT(bool{r.result == sum});
}

void match_arg7()
{
    migraph::program p;
    auto one = p.add_literal(1);
    auto two = p.add_literal(2);
    auto sum = p.add_instruction(sum_op{}, one, two);
    p.add_instruction(pass_op{}, sum);
    auto m = match::name("sum")(match::arg(0)(match::name("@literal")),
                                match::arg(1)(match::name("@literal")));
    auto r = find_match(p, m);
    EXPECT(bool{r.result == sum});
}

void match_args1()
{
    migraph::program p;
    auto one = p.add_literal(1);
    auto two = p.add_literal(2);
    auto sum = p.add_instruction(sum_op{}, one, two);
    p.add_instruction(pass_op{}, sum);
    auto m = match::name("sum")(match::args(match::name("@literal"), match::name("@literal")),
                                match::standard_shape());
    auto r = find_match(p, m);
    EXPECT(bool{r.result == sum});
}

void match_args2()
{
    migraph::program p;
    auto one = p.add_literal(1);
    auto two = p.add_literal(2);
    auto sum = p.add_instruction(sum_op{}, one, two);
    p.add_instruction(pass_op{}, sum);
    auto m = match::name("sum")(match::args(match::name("@literal"), match::name("sum")),
                                match::standard_shape());
    auto r = find_match(p, m);
    EXPECT(bool{r.result == p.end()});
}

void match_args3()
{
    migraph::program p;
    auto one = p.add_literal(1);
    auto two = p.add_literal(2);
    auto sum = p.add_instruction(sum_op{}, one, two);
    p.add_instruction(pass_op{}, sum);
    auto m = match::name("sum")(match::args(match::name("@literal")), match::standard_shape());
    auto r = find_match(p, m);
    EXPECT(bool{r.result == p.end()});
}

void match_args4()
{
    migraph::program p;
    auto one  = p.add_literal(1);
    auto two  = p.add_literal(2);
    auto sum1 = p.add_instruction(sum_op{}, one, two);
    auto sum2 = p.add_instruction(sum_op{}, sum1, two);
    p.add_instruction(pass_op{}, sum2);
    auto m = match::name("sum")(match::args(match::name("sum"), match::name("@literal")),
                                match::standard_shape());
    auto r = find_match(p, m);
    EXPECT(bool{r.result == sum2});
}

void match_args5()
{
    migraph::program p;
    auto one = p.add_literal(1);
    auto two = p.add_literal(2);
    auto sum = p.add_instruction(sum_op{}, one, two);
    p.add_instruction(pass_op{}, sum);
    auto m = match::name("sum")(match::args(match::name("sum"), match::name("@literal")),
                                match::standard_shape());
    auto r = find_match(p, m);
    EXPECT(bool{r.result == p.end()});
}

void match_args6()
{
    migraph::program p;
    auto one  = p.add_literal(1);
    auto two  = p.add_literal(2);
    auto sum  = p.add_instruction(sum_op{}, one, two);
    auto pass = p.add_instruction(pass_op{}, sum);
    auto m    = match::name("pass")(match::args(match::name("sum")), match::standard_shape());
    auto r    = find_match(p, m);
    EXPECT(bool{r.result == pass});
}

void match_args7()
{
    migraph::program p;
    auto one  = p.add_literal(1);
    auto two  = p.add_literal(2);
    auto sum  = p.add_instruction(sum_op{}, one, two);
    auto pass = p.add_instruction(pass_op{}, sum);
    auto m    = match::name("pass")(match::args(match::name("sum")(match::args(
                                     match::name("@literal"), match::name("@literal")))),
                                 match::standard_shape());
    auto r    = find_match(p, m);
    EXPECT(bool{r.result == pass});
}

void match_all_of1()
{
    migraph::program p;
    auto one = p.add_literal(1);
    auto two = p.add_literal(2);
    auto sum = p.add_instruction(sum_op{}, one, two);
    p.add_instruction(pass_op{}, sum);
    auto m = match::name("sum")(match::all_of(match::arg(0)(match::name("@literal")),
                                              match::arg(1)(match::name("@literal"))));
    auto r = find_match(p, m);
    EXPECT(bool{r.result == sum});
}

void match_all_of2()
{
    migraph::program p;
    auto one = p.add_literal(1);
    auto two = p.add_literal(2);
    auto sum = p.add_instruction(sum_op{}, one, two);
    p.add_instruction(pass_op{}, sum);
    auto m = match::name("sum")(
        match::all_of(match::arg(0)(match::name("sum")), match::arg(1)(match::name("@literal"))));
    auto r = find_match(p, m);
    EXPECT(bool{r.result == p.end()});
}

void match_any_of1()
{
    migraph::program p;
    auto one = p.add_literal(1);
    auto two = p.add_literal(2);
    auto sum = p.add_instruction(sum_op{}, one, two);
    p.add_instruction(pass_op{}, sum);
    auto m = match::name("sum")(
        match::any_of(match::arg(0)(match::name("sum")), match::arg(1)(match::name("@literal"))));
    auto r = find_match(p, m);
    EXPECT(bool{r.result == sum});
}

void match_any_of2()
{
    migraph::program p;
    auto one = p.add_literal(1);
    auto two = p.add_literal(2);
    auto sum = p.add_instruction(sum_op{}, one, two);
    p.add_instruction(pass_op{}, sum);
    auto m = match::name("sum")(
        match::any_of(match::arg(0)(match::name("sum")), match::arg(1)(match::name("sum"))));
    auto r = find_match(p, m);
    EXPECT(bool{r.result == p.end()});
}

void match_none_of1()
{
    migraph::program p;
    auto one = p.add_literal(1);
    auto two = p.add_literal(2);
    auto sum = p.add_instruction(sum_op{}, one, two);
    p.add_instruction(pass_op{}, sum);
    auto m = match::name("sum")(
        match::none_of(match::arg(0)(match::name("sum")), match::arg(1)(match::name("sum"))));
    auto r = find_match(p, m);
    EXPECT(bool{r.result == sum});
}

void match_none_of2()
{
    migraph::program p;
    auto one = p.add_literal(1);
    auto two = p.add_literal(2);
    auto sum = p.add_instruction(sum_op{}, one, two);
    p.add_instruction(pass_op{}, sum);
    auto m = match::name("sum")(match::none_of(match::arg(0)(match::name("@literal")),
                                               match::arg(1)(match::name("@literal"))));
    auto r = find_match(p, m);
    EXPECT(bool{r.result == p.end()});
}

void match_bind1()
{
    migraph::program p;
    auto one  = p.add_literal(1);
    auto two  = p.add_literal(2);
    auto sum  = p.add_instruction(sum_op{}, one, two);
    auto pass = p.add_instruction(pass_op{}, sum);
    auto m    = match::name("pass")(
                 match::args(match::name("sum")(match::args(match::name("@literal").bind("one"),
                                                            match::name("@literal").bind("two")))
                                 .bind("sum")),
                 match::standard_shape())
                 .bind("pass");
    auto r = find_match(p, m);
    EXPECT(bool{r.instructions.at("one") == one});
    EXPECT(bool{r.instructions.at("two") == two});
    EXPECT(bool{r.instructions.at("sum") == sum});
    EXPECT(bool{r.instructions.at("pass") == pass});
    EXPECT(bool{r.result == pass});
}

struct match_find_sum
{
    migraph::instruction_ref ins;
    auto matcher() const { return match::name("sum"); }

    void apply(migraph::program&, match::matcher_result r) const { EXPECT(bool{r.result == ins}); }
};

struct match_find_literal
{
    migraph::instruction_ref ins;
    auto matcher() const { return match::name("@literal"); }

    void apply(migraph::program&, match::matcher_result r) const
    {
        EXPECT(bool{r.result != ins});
        EXPECT(r.result->name() == "@literal");
    }
};

void match_finder()
{
    migraph::program p;
    auto one = p.add_literal(1);
    auto two = p.add_literal(2);
    auto sum = p.add_instruction(sum_op{}, one, two);
    p.add_instruction(pass_op{}, sum);
    match::find_matches(p, match_find_sum{sum}, match_find_literal{sum});
}

int main()
{
    match1();
    match_name1();
    match_name2();
    match_name3();

    match_arg1();
    match_arg2();
    match_arg3();
    match_arg4();
    match_arg5();
    match_arg6();
    match_arg7();

    match_args1();
    match_args2();
    match_args3();
    match_args4();
    match_args5();
    match_args6();
    match_args7();

    match_all_of1();
    match_all_of2();

    match_any_of1();
    match_any_of2();

    match_none_of1();
    match_none_of2();

    match_bind1();

    match_finder();
}