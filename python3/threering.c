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

static tr_context *tr_ctx;

static PyObject *
tr_load(PyObject *self, PyObject *args, PyObject *kwds)
{
	char *name = NULL;
	char *kwlist[] = {"dso", NULL};
	tr_dso *dso = NULL;
	PyDsoObject *ptrdo = NULL;

	if (!PyArg_ParseTupleAndKeywords(args, kwds, "s:dso", kwlist, &name))
		return NULL;

	dso = tr_find_module(tr_ctx, name);
	if (!dso) {
		PyErr_SetFromErrno(PyExc_OSError);
		return NULL;
	}

	return NULL;
}

static PyMethodDef tr_functions[] = {
	{"load", (PyCFunction)tr_load, METH_VARARGS|METH_KEYWORDS,
		"Loads a dso, returns an module" },
	{NULL, NULL}
};

static void
tr_free(void *ptr)
{
	PyObject *m = (PyObject *)ptr;
	tr_context *tr_ctx = PyModule_GetState(m);

	tr_context_fini(tr_ctx);
	return;
}

PyModuleDef md = {
	.m_base = PyModuleDef_HEAD_INIT,
	.m_name = "threering",
	.m_doc = "",
	.m_size = -1,
	.m_methods = tr_functions,
	.m_reload = NULL,
	.m_traverse = NULL,
	.m_clear = NULL,
	.m_free = tr_free,
	};

PyMODINIT_FUNC
PyInit_threering(void)
{
	PyObject *m;

	md.m_size = tr_context_size(),

	m = PyModule_Create(&md);
	tr_ctx = PyModule_GetState(m);

	tr_context_init(tr_ctx);

	Py_TYPE(&PyDsoType) = &PyType_Type;
	if (PyType_Ready(&PyDsoType) < 0)
		return NULL;

	/* PJ TODO: add path object */

	return m;
}
