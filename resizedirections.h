#ifndef RESIZEDIRECTIONS_H
#define RESIZEDIRECTIONS_H

struct ResizeDirections
{
    enum { HorzNone, Left, Right } horizontal;
    enum { VertNone, Top, Bottom } vertical;
    bool any() { return horizontal || vertical; }
};

#endif // RESIZEDIRECTIONS_H

