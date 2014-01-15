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
#ifndef THREERING_PRIVATE_H
#define THREERING_PRIVATE_H 1

#include <elf.h>
#include <gelf.h>

struct tr_context {
	int hello;
};

struct tr_dso {
	void *dl_handle;
	struct link_map *lm;

	int fd;
	Elf *elf;

	uint8_t *build_id;
	size_t build_id_size;

	char *debuginfo_path;
	int debuginfo_fd;
};

typedef struct tr_context tr_context;
typedef struct tr_dso tr_dso;

extern int get_build_id(tr_dso *dso);

#endif /* THREERING_PRIVATE_H */
