#include "Directorios.h"

#ifndef DIRECTORIOS_CPP
#define DIRECTORIOS_CPP

Directorios::Directorios()
{
	Directorio raiz = Directorio(".");
	this->arbol = new NodoAG<Directorio>(raiz, NULL, NULL);
}

Directorios::~Directorios()
{
	this->Vaciar();
}

Directorios::Directorios(const Directorios &d)
{
	this->arbol = d.arbol;
}

Directorios &Directorios::operator=(const Directorios &d)
{
	if (this != &d)
	{
		this->arbol = d.arbol;
		assert(false);
	}
	return *this;
}

void Directorios::AgregarDirectorio(Cadena ruta)
{
	Cola<Cadena>* cola = ruta.split();
	Cola<Cadena>* split = ruta.split();
	Cadena nombre;
	while (!(cola->EsVacia()))
		nombre = cola->Desencolar();
	Directorio* nuevo =new Directorio(nombre);
	while (cola->CantidadElementos() < (ruta.split()->CantidadElementos()-1))
		cola->Encolar(split->Desencolar());
	NodoAG<Directorio>* dires = new NodoAG<Directorio>(*nuevo, NULL, NULL);
	NodoAG<Directorio>*& agregoCon = this->buscoRuta(this->arbol, cola);
	agregarHijo(agregoCon, dires);
}

void Directorios::EliminarDirectorio(Cadena ruta)
{
	NodoAG<Directorio>*& aux = buscoRuta(this->arbol, ruta.split());
	NodoAG<Directorio>* p = aux;
	aux = aux->sh;
	p->sh = NULL;
	eliminar(p);
}

bool Directorios::ExisteDirectorio(Cadena ruta)
{
	bool ret = false;
	if (buscoRuta(this->arbol, ruta.split())!=NULL)
		ret = true;
	return ret;
}

Directorio &Directorios::BuscarDirectorio(Cadena ruta)
{
	return buscoRuta(this->arbol, ruta.split())->dato;
}

void Directorios::Dir(Cadena ruta, Cadena parametro)
{
	ListaOrd<Cadena>* ordenada = new ListaOrdImp<Cadena>();
	DirAux(ruta, this->arbol, ordenada);
	mostrarLista(ordenada, parametro);
}

void Directorios::Vaciar()
{
	Cadena string;
	Cadena raiz = "./";
	while (this->arbol->ph) {
		string = this->arbol->ph->dato.GetNombre();
		EliminarDirectorio(raiz + string);
	}
}

void Directorios::CopiarDirectorio(Cadena rutaOrigen, Cadena rutaDestino)
{
	NodoAG<Directorio>* nodo = buscoRuta(this->arbol, rutaOrigen.split());
	NodoAG<Directorio>* copia = CopioNodo(nodo);
	agregarHijo(buscoRuta(this->arbol, rutaDestino.split()), copia);
}

NodoAG<Directorio>*& Directorios::buscoRuta(NodoAG<Directorio>*& r, Cola<Cadena>* l)
{
	Cola<Cadena>* aux = l->Clon();
	if (r == NULL || aux->EsVacia()) {
		return r;
	}
	else {
		if (r->dato.GetNombre() == aux->Principio()) {
			Cadena basura = aux->Desencolar();
			if (aux->EsVacia()) {
				return r;
			}
			else {
				return buscoRuta(r->ph, aux);
			}
		}
		else
			return buscoRuta(r->sh, aux);
	}
}

NodoAG<Directorio>*& Directorios::ultimoHermano(NodoAG<Directorio>*& r)
{
	if (r->sh == NULL) {
		return r;
	}
	else {
		return ultimoHermano(r->sh);
	}
}

void Directorios::agregarHijo(NodoAG<Directorio>* r, NodoAG<Directorio>* a)
{
	if (r->ph != NULL)
		ultimoHermano(r->ph)->sh = a;
	else
		r->ph = a;
}

void Directorios::eliminar(NodoAG<Directorio>*& r)
{
	if (r) {
		eliminar(r->ph);
		eliminar(r->sh);
		delete r;
	}
}

NodoAG<Directorio>*& Directorios::CopioNodo(NodoAG<Directorio>* r) {
	NodoAG<Directorio>* ret;
	if (r->ph != NULL)
		ret = new NodoAG<Directorio>(r->dato, CopioNodo(r->ph), NULL);
	else
		ret = new NodoAG<Directorio>(r->dato, NULL, NULL);
	return ret;
}

void Directorios::DirAux(Cadena ruta, NodoAG<Directorio>*& r, ListaOrd<Cadena>*& l) {
	Cadena* camino = new Cadena[altura(r) + 1];
	NodoAG<Directorio>*& p = buscoRuta(r, ruta.split());
	ruta.eliminarDesdeHasta(0, 0);
	DirAux1(p, camino, 0, l);
}

void Directorios::DirAux1(NodoAG<Directorio>*& p, Cadena* camino, int nivel, ListaOrd<Cadena>*& l){
	if (p != NULL) {
		camino[nivel] = p->dato.GetNombre();
		agregarLista(camino, nivel, l);
		DirAux1(p->ph, camino, nivel+1, l);
		if (nivel>1)
			DirAux1(p->sh, camino, nivel, l);
	}
}

void Directorios::agregarLista(Cadena* camino, int nivel, ListaOrd<Cadena>*& l) {
	Cadena concat = "";
	for (int i = 0; i < nivel+1; i++)
		concat = concat + "/" + camino[i];
	concat.eliminarDesdeHasta(0, 0);
	l->AgregarOrd(concat);
}

void Directorios::mostrarLista(ListaOrd<Cadena>*& l, Cadena parametro) {
	Cadena ruta = "";
	Cadena imprimo = "";
	while (!l->EsVacia()) {
		ruta = l->Minimo();
		imprimo = ruta;
		cout << imprimo << endl;
		l->BorrarMinimo();
		BuscarDirectorio(ruta).ListarArchivos(imprimo, parametro);
	}

}

int Directorios::altura(NodoAG<Directorio>*& r) {
	if (r != NULL) {
		if (altura(r->ph) + 1 > altura(r->sh))
			return altura(r->ph) + 1;
		else
			return altura(r->sh);
	}
	else
		return 0;
}

Cadena Directorios::quitarArchivo(Cadena ruta) {
	Cola<Cadena>* rutaDirectorioAux = ruta.split();
	Cadena dirAux;//Directorio que hay que validar que exista.
	dirAux = rutaDirectorioAux->Desencolar();
	for (int i = 1; i < ruta.split()->CantidadElementos() - 1; i++) {
		dirAux = dirAux + "/" + rutaDirectorioAux->Desencolar();
	}
	return dirAux;
}

Cadena Directorios::agarrarUltimo(Cadena ruta) {
	Cola<Cadena>* nombreArchivoAux = ruta.split();
	Cadena archivo = "";
	while (!nombreArchivoAux->EsVacia()) {
		archivo = nombreArchivoAux->Desencolar();
	}
	return archivo;
}

bool Directorios::esSubdirectorio(Cadena ruta1, Cadena ruta2) {
	return ruta2.Contains(ruta1);
}

#endif