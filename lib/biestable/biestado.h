#ifndef BIESTADO_H
#define BIESTADO_H

typedef struct Biestado Biestado;

typedef struct Biestado_VT
{
    void (*const si)(Biestado *self);
    void (*const no)(Biestado *self);
}Biestado_VT;


struct Biestado{
    const Biestado_VT *vptr;
};

// inline es una sugerencia para el compilador. El compilador lo que hace es agarrar el contenido
// de la funcion inline y lo incrusta directamente donde lo llaman.
inline static void Biestado_si(Biestado *self)
{
    self->vptr->si(self);
}
inline static void Biestado_no(Biestado *self)
{
    self->vptr->no(self);
}




#endif