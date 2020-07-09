#ifndef DIRECTORIOS_H
#define DIRECTORIOS_H

#include "Constantes.h"
#include "Directorio.h"
#include "NodoAG.h"
#include "ListaOrdImp.h"


class Directorios {

public:

	//Constructor por defecto
	Directorios();

	//Destructor
	virtual ~Directorios();

	//Constructor copia
	Directorios(const Directorios &d);

	//Operador de asignación
	Directorios &operator=(const Directorios &d);

	//PRE:  
	//POS: Agregar el directorio
	void AgregarDirectorio(Cadena ruta);

	//PRE: 
	//POS: Elimina el directorio.
	void EliminarDirectorio(Cadena ruta);

	//PRE: 
	//POS: Retorna true si existe directorio correspondiente a ruta.
	bool ExisteDirectorio(Cadena ruta);

	//PRE: Existe ruta
	//POS: Retorna Directorio correspondiente a la ruta.
	Directorio &BuscarDirectorio(Cadena ruta);

	//PRE: Existe ruta
	//POS: Imprime la jerarquia de directorios a partir de ruta teniendo en cuenta el parametro que indica la visibilidad.
	void Dir(Cadena ruta, Cadena parametro);

	//PRE: 
	//POS: Elimina todos los directorios (y sus archivos) excepto el raiz "/".
	void Vaciar();

	//PRE: 
	//POS: Copia el directorio de origen a destino
	void CopiarDirectorio(Cadena rutaOrigen, Cadena rutaDestino);

	NodoAG<Directorio>*& buscoRuta(NodoAG<Directorio>*& r, Cola<Cadena>* l);

	NodoAG<Directorio>*& ultimoHermano(NodoAG<Directorio>*& r);

	void agregarHijo(NodoAG<Directorio>* r, NodoAG<Directorio>* a);

	void eliminar(NodoAG<Directorio>*& r);

	NodoAG<Directorio>*& CopioNodo(NodoAG<Directorio>* r);

	void DirAux(Cadena ruta, NodoAG<Directorio>*& r, ListaOrd<Cadena>*& l);

	void DirAux1(NodoAG<Directorio>*& p, Cadena* camino, int nivel, ListaOrd<Cadena>*& l);

	void agregarLista (Cadena* camino, int nivel, ListaOrd<Cadena>*& l);

	void mostrarLista(ListaOrd<Cadena>*& l, Cadena parametro);

	int altura(NodoAG<Directorio>*& r);

	Cadena quitarArchivo(Cadena ruta);

	Cadena agarrarUltimo(Cadena ruta);

	bool esSubdirectorio(Cadena ruta1, Cadena ruta2);

private:
	NodoAG<Directorio>* arbol;

};

#endif 