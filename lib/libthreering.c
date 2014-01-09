/*
 * Copyright 2014 Red Hat, Inc.
 * All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Author(s): Peter Jones <pjones@redhat.com>
 */

#include <stdlib.h>
#include <string.h>

#include <threering.h>
#include "threering.h"

size_t
tr_context_size(void)
{
	return sizeof (tr_context);
}

int
tr_context_init(tr_context *ctx)
{
	memset(ctx, '\0', sizeof (*ctx));
	return 0;
}

void
tr_context_fini(tr_context *ctx)
{
	memset(ctx, '\0', sizeof (*ctx));
}

tr_dso *
tr_find_module(tr_context *ctx, const char const *name)
{
	return NULL;
}
