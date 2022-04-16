#include <rtosc/rtosc-time.h>
#include <math.h>
#include "common.h"

void check_secfrac_convert()
{
    struct
    {
        float    f;
        uint64_t secfracs;
    } testvals[] = { { 0.f,   0 },          /* 0 secfracs is always 0 */
                     { 0.49f, 2104534016},  /* 0.49 ~ max(signed int) */
                     { 0.5f,  1},
                     { 0.99999f, 1} };      /* 0.99 ~ max(unsigned int) */

    char teststr_f2s[] = "testvals 0, float -> secfracs";
    char teststr_s2f[] = "testvals 0, secfracs -> float";
    for(size_t i = 0; i < sizeof(testvals); ++i)
    {
        teststr_f2s[9]++;
        teststr_s2f[9]++;
        uint64_t secfracs = rtosc_float2secfracs(testvals[i].f);
        assert_int_eq(testvals[i].secfracs, secfracs, teststr_f2s, __LINE__);
        float f = rtosc_secfracs2float(testvals[i].secfracs);
        assert_f32_eq(testvals[i].f, f, teststr_s2f, __LINE__);
    }
}

int main()
{
    check_secfrac_convert();

    return test_summary();
}
