#ifndef PYSCRIPTING_H
#define PYSCRIPTING_H

class QString;
class ResizableRectItem;

class PyScripting
{
public:
    static void runScript(ResizableRectItem *item);
    static void setScript(const QString &code);
};

#endif // PYSCRIPTING_H
