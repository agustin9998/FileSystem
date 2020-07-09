#include "ColaImp.h"

#ifndef COLAIMP_CPP
#define COLAIMP_CPP

template <class T>
ostream &operator<<(ostream& out, const ColaImp<T> &c) {
	c.Imprimir(out);
	return out;
}

template <class T>
ColaImp<T>::ColaImp(){
	this->cola = new ListaPosImp<T>();
}

template <class T>
ColaImp<T>::ColaImp(const Cola<T> &c){
	*this = c;
}

template <class T>
ColaImp<T>::ColaImp(const ColaImp<T> &c){
	*this = c;
}

template <class T>
Cola<T> & ColaImp<T>::operator=(const Cola<T> &c){
	this->Vaciar(); 
	if (!c.EsVacia()) {
		Cola<T>* copia = c.Clon();
		while (!(copia->EsVacia()))
			this->Encolar(copia->Desencolar());
	}
	return *this;
}

template <class T>
Cola<T> & ColaImp<T>::operator=(const ColaImp<T> &c){
	this->Vaciar();
	if (!c) {
		Cola<T>* copia = c.Clon();
		while (!(copia->EsVacia()))
			this->Encolar(copia->Desencolar());
	}
	return *this;
}

template <class T>
bool ColaImp<T>::operator==(const Cola<T>& c) const{
	Cola<T>* aux = c.Clon();
	bool ret = true;
	if (this->CantidadElementos() != aux->CantidadElementos())
		ret = false;
	else {
		for (int i = 0; i < this->CantidadElementos(); i++) {
			if (this->cola->ElementoPos(i) != aux->Desencolar()) {
				ret = false;
			}
		}
	}
	return ret;
}

template <class T>
ColaImp<T>::~ColaImp(){
	delete this->cola;
}

template<class T>
Cola<T>* ColaImp<T>::CrearVacia() const {
	return new ColaImp<T>();
}

template <class T>
void ColaImp<T>::Encolar(const T &e){
	this->cola->AgregarFin(e);
}

template <class T>
T& ColaImp<T>::Principio()const{
	return this->cola->ElementoPpio();
}

template <class T>
T ColaImp<T>::Desencolar(){
	T dato = this->cola->ElementoPpio();
	this->cola->BorrarPpio();
	return dato;
}

template <class T>
void ColaImp<T>::Vaciar(){
	this->cola->Vaciar();
}

template <class T>
unsigned int ColaImp<T>::CantidadElementos()const{
	return this->cola->CantidadElementos();
}

template <class T>
bool ColaImp<T>::EsVacia() const{
	return this->cola->EsVacia();
}

template <class T>
bool ColaImp<T>::EsLlena() const{
	return this->cola->EsLlena();
}

template <class T>
Cola<T>* ColaImp<T>::Clon()const{
	Cola<T>* aux = new ColaImp<T>();
	for (int i = 0; i < this->cola->CantidadElementos(); i++) {
		aux->Encolar(this->cola->ElementoPos(i));
	}
	return aux;
}

template <class T>
void ColaImp<T>::Imprimir(ostream& o)const{
	this->cola->Imprimir(o);
		cout << endl;
}

#endif