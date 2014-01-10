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

#include <elf.h>
#include <errno.h>
#include <fcntl.h>
#include <libelf.h>
#include <link.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <threering.h>
#include "threering.h"

int
get_build_id(tr_dso *dso)
{
	dso->fd = open(dso->lm->l_name, O_RDONLY);
	if (dso->fd < 0)
		return -1;

	elf_version(EV_CURRENT);
	dso->elf = elf_begin(dso->fd, ELF_C_READ_MMAP, NULL);
	if (dso->elf == NULL)
		goto err;

	Elf_Scn *scn;
	for (int i = 0; (scn = elf_getscn(dso->elf, i)); i++) {
		GElf_Shdr shdr;
		if (!gelf_getshdr(scn, &shdr))
			goto err;
		if (shdr.sh_type != SHT_NOTE)
			continue;

		Elf_Data *data = elf_rawdata(scn, NULL);
		if (!data)
			continue;

		uint8_t *notes = data->d_buf;
		for (GElf_Nhdr *nhdr = (GElf_Nhdr *)notes;
		     (notes - (uint8_t *)data->d_buf) < (int64_t)shdr.sh_size;
		     notes += sizeof(*nhdr) + nhdr->n_namesz + nhdr->n_descsz) {

			GElf_Nhdr *nhdr = (GElf_Nhdr *)notes;
			char *note = (char *)notes + sizeof(*nhdr);

			if (strncmp(note, ELF_NOTE_GNU, nhdr->n_namesz))
				continue;

			if (nhdr->n_type != NT_GNU_BUILD_ID)
				continue;

			dso->build_id_size = nhdr->n_descsz;
			dso->build_id = malloc(nhdr->n_descsz);
			if (!dso->build_id)
				goto err;

			memcpy(dso->build_id, note+nhdr->n_namesz, nhdr->n_descsz);

			return 0;
		}
	}

	errno = ENOENT;
	return -1;
err:
	if (dso->elf) {
		elf_end(dso->elf);
		dso->elf = NULL;
	}
	if (dso->fd) {
		close(dso->fd);
		dso->fd = -1;
	}
	errno = EINVAL;
	return -1;
}
