#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include "Constantes.h"
#include "Cadena.h"
#include "FuncAux.h"
#include "Asociacion.h"
#include "Pila.h"
#include "Archivo.h"
#include "Directorios.h"
#include "PilaImp.h"


class FileSystem {

public:


	//***************LA INFORMACION ACERCA DE DOCUMENTACION SE ENCUENTRA DETALLADA EN LA LETRA ****************//


	//Constructor por defecto
	FileSystem();

	//Constructor
	FileSystem(unsigned int MAX_RECUPERAR);

	//Destructor
	virtual ~FileSystem();

	//Constructor copia
	FileSystem(const FileSystem &f);

	//Operador de asignaci�n
	FileSystem &operator=(const FileSystem &f);

	TipoRetorno Mkdir(Cadena rutaDirectorio);

	TipoRetorno Rmdir(Cadena rutaDirectorio);

	TipoRetorno CopyDir(Cadena rutaOrigen, Cadena rutaDestino);

	TipoRetorno Dir(Cadena rutaDirectorio, Cadena parametro) const;

	TipoRetorno CreateFile(Cadena rutaArchivo);

	TipoRetorno Delete(Cadena rutaArchivo);

	TipoRetorno Attrib(Cadena rutaArchivo, Cadena parametro);

	TipoRetorno InsertText(Cadena rutaArchivo, unsigned int nroLinea, unsigned int posLinea, Cadena texto);

	TipoRetorno DeleteText(Cadena rutaArchivo, unsigned int nroLinea, unsigned int posLinea, unsigned int k);

	TipoRetorno Type(Cadena rutaArchivo) const;

	TipoRetorno Undelete();

private:
	Directorios* dir;
	Pila<Asociacion<Archivo, Cadena>>* elim;
	int trashSize;
};

#endif 