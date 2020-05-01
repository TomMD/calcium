/*
    Copyright (C) 2020 Fredrik Johansson

    This file is part of Calcium.

    Calcium is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.  See <http://www.gnu.org/licenses/>.
*/

#include "ca_qqbar.h"

int main()
{
    slong iter;
    flint_rand_t state;

    flint_printf("abs....");
    fflush(stdout);

    flint_randinit(state);

    for (iter = 0; iter < 1000; iter++)
    {
        ca_qqbar_t x, y, z, t, u;

        ca_qqbar_init(x);
        ca_qqbar_init(y);
        ca_qqbar_init(z);
        ca_qqbar_init(t);
        ca_qqbar_init(u);

        ca_qqbar_randtest(x, state, 3, 10);
        ca_qqbar_randtest(y, state, 3, 10);

        ca_qqbar_abs(z, x);
        ca_qqbar_abs(t, y);
        ca_qqbar_mul(t, t, z);

        ca_qqbar_mul(u, x, y);
        ca_qqbar_abs(u, u);

        if (!ca_qqbar_equal(t, u) || !ca_qqbar_is_real(t))
        {
            flint_printf("FAIL!\n");
            flint_printf("x = "); ca_qqbar_print(x); flint_printf("\n\n");
            flint_printf("y = "); ca_qqbar_print(y); flint_printf("\n\n");
            flint_printf("z = "); ca_qqbar_print(z); flint_printf("\n\n");
            flint_printf("t = "); ca_qqbar_print(t); flint_printf("\n\n");
            flint_printf("u = "); ca_qqbar_print(t); flint_printf("\n\n");
            flint_abort();
        }

        ca_qqbar_clear(x);
        ca_qqbar_clear(y);
        ca_qqbar_clear(z);
        ca_qqbar_clear(t);
        ca_qqbar_clear(u);
    }

    flint_randclear(state);
    flint_cleanup();
    flint_printf("PASS\n");
    return EXIT_SUCCESS;
}
