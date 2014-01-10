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

#define _GNU_SOURCE 1
#include <dlfcn.h>
#include <errno.h>
#include <link.h>
#include <stdlib.h>
#include <stdio.h>
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
	tr_dso *dso = calloc(1, sizeof (*dso));
	dso->fd = -1;

	/* steps:
	 * 1) find the dl handle, because we'll need to use this for calls
	 * 2) find the original file the dl handle is to
	 * 3) fish build id out of #2
	 * 4) find debuginfo based on build id
	 * 5) construct dso object
	 * 5.a) construct type objects
	 * 5.b) construct call functions
	 */
	/* #1 dl handle */
	dso->dl_handle = dlopen(name, RTLD_NOW|RTLD_LOCAL);
	if (!dso->dl_handle)
		goto err;

	/* #2 file path - included in the link map */
	int rc = dlinfo(dso->dl_handle, RTLD_DI_LINKMAP, &dso->lm);
	if (rc < 0)
		goto err;

	/* this has a side effect of also giving us dso->elf */
	rc = get_build_id(dso);
	if (rc < 0)
		goto err;

	char *filename = malloc(dso->build_id_size * 2);
	for (size_t i = 1; i < dso->build_id_size; i++)
		sprintf(filename + i*2 -2, "%02x", dso->build_id[i]);
	char *filepath = NULL;

	asprintf(&filepath, "/usr/lib/debug/.build-id/%02x/%s.debug",
		dso->build_id[0], filename);
	free(filename);

	dso->debuginfo_path = filepath;

	return dso;
err:
	if (dso) {
		typeof (errno) saved_errno = errno;
		if (dso->dl_handle)
			dlclose(dso->dl_handle);

		free(dso);
		errno = saved_errno;
	}
	return NULL;
}
