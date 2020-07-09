#ifndef PRUEBASPROPIAS_H
#define PRUEBASPROPIAS_H

#include "Prueba.h"
#include "ConductorPrueba.h"
#include "InterfazDelSistemaImp.h"
#include "ListaPosImp.h"
#include "Asociacion.h"
#include "Cadena.h"
#include "Directorio.h"
#include "Archivo.h"
#include "Cola.h"
#include "ColaImp.h"
#include "PilaImp.h"
#include "Directorios.h"

class PruebasPropias : public Prueba
{

public:
	PruebasPropias(ConductorPrueba* conductor);
	virtual ~PruebasPropias();
	virtual void correrPruebaConcreta();

protected:
	virtual const char* getNombre() const;

private:

	void FormarRedBasica(InterfazDelSistema* interfaz);
};

#endif