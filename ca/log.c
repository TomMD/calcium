/*
    Copyright (C) 2020 Fredrik Johansson

    This file is part of Calcium.

    Calcium is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.  See <http://www.gnu.org/licenses/>.
*/

#include "ca.h"

/* log(exp(z)) -- http://fungrim.org/entry/a3a253/ */
void
ca_log_exp(ca_t res, const ca_t z, ca_ctx_t ctx)
{
    ca_t t, pi;

    if (CA_IS_SPECIAL(z))
        flint_abort();

    ca_init(t, ctx);
    ca_init(pi, ctx);

    ca_pi(pi, ctx);

    ca_im(t, z, ctx);
    ca_div(t, t, pi, ctx);
    ca_sub_ui(t, t, 1, ctx);
    ca_div_ui(t, t, 2, ctx);

    ca_ceil(t, t, ctx);

    if (ca_check_is_zero(t, ctx) == T_TRUE)
    {
        ca_set(res, z, ctx);
    }
    else
    {
        ca_t pi_i;

        ca_init(pi_i, ctx);
        ca_pi_i(pi_i, ctx);

        ca_mul(t, t, pi_i, ctx);
        ca_mul_ui(t, t, 2, ctx);

        ca_sub(res, z, t, ctx);
        ca_clear(pi_i, ctx);
    }

    ca_clear(t, ctx);
    ca_clear(pi, ctx);
}

void
ca_log(ca_t res, const ca_t x, ca_ctx_t ctx)
{
    truth_t is_zero;
    ca_ext_ptr ext;

    if (CA_IS_SPECIAL(x))
    {
        if (ca_check_is_infinity(x, ctx) == T_TRUE)
            ca_pos_inf(res, ctx);
        else if (ca_check_is_undefined(x, ctx) == T_TRUE)
            ca_undefined(res, ctx);
        else
            ca_unknown(res, ctx);
        return;
    }

    is_zero = ca_check_is_zero(x, ctx);

    if (is_zero == T_TRUE)
    {
        ca_neg_inf(res, ctx);
        return;
    }

    if (is_zero == T_UNKNOWN)
    {
        ca_unknown(res, ctx);
        return;
    }

    if (ca_check_is_one(x, ctx) == T_TRUE)
    {
        ca_zero(res, ctx);
        return;
    }

    ext = ca_is_gen_as_ext(x, ctx);

    if (ext != NULL && CA_EXT_HEAD(ext) == CA_Exp)
    {
        /* log(exp(z)) */
        ca_log_exp(res, CA_EXT_FUNC_ARGS(ext), ctx);
        return;
    }

    _ca_make_field_element(res, _ca_ctx_get_field_fx(ctx, CA_Log, x), ctx);
    fmpz_mpoly_q_gen(CA_MPOLY_Q(res), 0, CA_MCTX_1(ctx));
}

