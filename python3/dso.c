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

#include <Python.h>

#include <threering.h>
#include "threering.h"

static void
dso_dealloc(PyObject *obj)
{
	;
}

static int
dso_init(PyObject *self, PyObject *args, PyObject *kwds)
{
	return 0;
}

static PyObject *
dso_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
	return NULL;
}

PyTypeObject PyDsoType = {
	.tp_name = "dso",
	.tp_basicsize = sizeof (PyDsoObject),
	.tp_dealloc = (destructor)dso_dealloc,
	.tp_getattro = PyObject_GenericGetAttr,
	.tp_setattro = PyObject_GenericSetAttr,
	.tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
	.tp_doc = "",
	.tp_methods = NULL,
	.tp_members = NULL,
	.tp_getset = NULL,
	.tp_init = dso_init,
	.tp_alloc = PyType_GenericAlloc,
	.tp_new = dso_new,
	.tp_free = PyObject_Del,
};

