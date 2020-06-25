/*
    Copyright (C) 2020 Fredrik Johansson

    This file is part of Calcium.

    Calcium is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.  See <http://www.gnu.org/licenses/>.
*/

#include "ca.h"

void
ca_sqrt(ca_t res, const ca_t x, ca_ctx_t ctx)
{
    if (CA_IS_SPECIAL(x))
    {
        if (x->field & CA_SIGNED_INF)
        {
            ca_sgn(res, x, ctx);
            ca_sqrt(res, res, ctx);
            if (!ca_is_unknown(res, ctx))
                res->field &= CA_SIGNED_INF;
        }
        else
        {
            ca_set(res, x, ctx);
        }
    }
    else
    {
        qqbar_t t;
        qqbar_init(t);

        if (ca_get_qqbar(t, x, ctx))
        {
            qqbar_sqrt(t, t);

            if (qqbar_within_limits(t, ctx->options[CA_OPT_QQBAR_DEG_LIMIT], 0))
                ca_set_qqbar(res, t, ctx);
            else
                _ca_function_fx(res, CA_Sqrt, x, ctx);
        }
        else
        {
            _ca_function_fx(res, CA_Sqrt, x, ctx);
        }

        qqbar_clear(t);
    }
}
