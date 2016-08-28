#include "pyscripting.h"
#include "resizablerectitem.h"
#include <Python.h>

static bool initialized = false;
static ResizableRectItem *pthis;
static PyObject* pythonSetColor(PyObject *self, PyObject *args)
{
    Q_UNUSED(self);
    int a, r, g, b;
    PyArg_ParseTuple(args, "iiii", &r, &g, &b, &a);
    pthis->setBrush(QColor(r, g, b, a));
    Py_RETURN_NONE;
}

static PyObject* pythonSetPos(PyObject *self, PyObject *args)
{
    Q_UNUSED(self);
    double x, y;
    PyArg_ParseTuple(args, "dd", &x, &y);
    pthis->setPos(x, y);
    Py_RETURN_NONE;
}

static PyObject* pythonPos(PyObject *self, PyObject *args)
{
    Q_UNUSED(self);
    Q_UNUSED(args);
    QPointF pos = pthis->pos();
    return Py_BuildValue("dd", pos.x(), pos.y());
}

static PyObject* pythonSetRect(PyObject *self, PyObject *args)
{
    Q_UNUSED(self);
    double x, y, w, h;
    PyArg_ParseTuple(args, "dddd", &x, &y, &w, &h);
    pthis->setRect(x, y, w, h);
    Py_RETURN_NONE;
}

static PyObject* pythonRect(PyObject *self, PyObject *args)
{
    Q_UNUSED(self);
    Q_UNUSED(args);
    QRectF r = pthis->rect();
    return Py_BuildValue("dddd", r.x(), r.y(), r.width(), r.height());
}

static PyMethodDef methods[] = {
    { "setColor", pythonSetColor, METH_VARARGS, "set the color of the current rect item" },
    { "setPos", pythonSetPos, METH_VARARGS, "set the position of the current rect item" },
    { "pos", pythonPos, METH_NOARGS, "get the position of the current rect item" },
    { "setRect", pythonSetRect, METH_VARARGS, "set the rectangle of the current rect item" },
    { "rect", pythonRect, METH_NOARGS, "get the rectangle of the current rect item" },
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
