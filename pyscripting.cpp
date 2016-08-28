#include "pyscripting.h"
#include "resizablerectitem.h"
#include <Python.h>

static bool initialized = false;
static ResizableRectItem *pthis;
static PyObject* setColorCallback(PyObject *self, PyObject *args)
{
    Q_UNUSED(self);
    int a, r, g, b;
    PyArg_ParseTuple(args, "iiii", &r, &g, &b, &a);
    pthis->setBrush(QColor(r, g, b, a));
    Py_RETURN_NONE;
}

static PyObject* setPosCallback(PyObject *self, PyObject *args)
{
    Q_UNUSED(self);
    double x, y;
    PyArg_ParseTuple(args, "dd", &x, &y);
    pthis->setPos(x, y);
    Py_RETURN_NONE;
}

static PyObject* getPosCallback(PyObject *self, PyObject *args)
{
    Q_UNUSED(self);
    Q_UNUSED(args);
    QPointF pos = pthis->pos();
    return Py_BuildValue("dd", pos.x(), pos.y());
}

static PyMethodDef methods[] = {
    { "setColor", setColorCallback, METH_VARARGS, "set the color of the current rect item" },
    { "setPos", setPosCallback, METH_VARARGS, "set the position of the current rect item" },
    { "pos", getPosCallback, METH_NOARGS, "get the position of the current rect item" },
    { 0, 0, 0, 0 }
};

static QString pythonCode;

void PyScripting::runScript(ResizableRectItem *item)
{
    if (!initialized) {
        Py_Initialize();
        initialized = true;
        Py_InitModule("item", methods);
        PyRun_SimpleString("import item\n");
    }

    pthis = item;
    PyRun_SimpleString(pythonCode.toUtf8().data());
}

void PyScripting::setScript(const QString &code)
{
    pythonCode = code;
}
