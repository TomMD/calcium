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
ca_ctx_init(ca_ctx_t ctx)
{
    slong i;
    qqbar_t onei;

    ctx->mctx = flint_malloc(CA_NVARS_MAX * sizeof(fmpz_mpoly_ctx_struct));
    for (i = 0; i < CA_NVARS_MAX; i++)
        fmpz_mpoly_ctx_init(ctx->mctx + i, i + 1, ORD_LEX);
    ctx->mctx_len = CA_NVARS_MAX;

    /* Always create QQ, QQ(i) */

    ctx->fields = (ca_field_struct *) flint_malloc(2 * sizeof(ca_field_struct));
    ctx->fields_len = 2;
    ctx->fields_alloc = 2;

    ca_field_init_qq(ctx->fields);

    qqbar_init(onei);
    qqbar_i(onei);
    ca_field_init_nf(ctx->fields + 1, onei);
    qqbar_clear(onei);
}
