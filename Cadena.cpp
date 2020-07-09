#include "Cadena.h"
#include "Cola.h"
#include "ColaImp.h"
#define _CRT_SECURE_NO_WARNINGS


#ifndef CADENA_CPP
#define CADENA_CPP

/****************************************************/
ostream &operator<<(ostream &os, const Cadena &cad) {
	if (cad.s)
		os << cad.s;
	return os;
}

istream &operator>>(istream &is, Cadena &cad) {
	char aux[200];
	is >> aux;
	cad = aux;
	return is;
}

/****************************************************/
Cadena::Cadena(const char *cad, bool ignoreCase) {
	size_t len = strlen(cad) + 1;
	s = new char[len];
	strcpy_s(s, len, cad);
	this->ignoreCase = ignoreCase;
}
/****************************************************/
Cadena::Cadena() {
	s = new char[1];
	s[0] = '\0';
	this->ignoreCase = true;
}
/****************************************************/
Cadena::Cadena(const Cadena &c) {
	s = NULL;
	*this = c;
}
/****************************************************/
Cadena::~Cadena() {
	if (s)
		delete[] s;
}
/****************************************************/
Cadena &Cadena::operator=(const Cadena &c) {
	if (this != &c) {
		delete[] s;

		size_t len = strlen(c.s) + 1;
		s = new char[len];
		strcpy_s(s, len, c.s);

		this->ignoreCase = c.ignoreCase;
	}
	return *this;
}
/****************************************************/
Cadena Cadena::operator+(const Cadena &c) const {
	size_t len = strlen(s) + strlen(c.s) + 1;
	char *sNew = new char[len];
	strcpy_s(sNew, len, s);
	strcat_s(sNew, len, c.s);
	Cadena cNew(sNew, ignoreCase);
	delete[] sNew;

	return cNew;
}
/****************************************************/
bool Cadena::operator==(const Cadena &c) const {
	if (ignoreCase)
		return _stricmp(s, c.s) == 0;
	else
		return strcmp(s, c.s) == 0;
}
/****************************************************/
bool Cadena::operator!=(const Cadena &c) const {
	if (ignoreCase)
		return _stricmp(s, c.s) != 0;
	else
		return strcmp(s, c.s) != 0;
}
/****************************************************/
bool Cadena::operator<(const Cadena &c) const {
	if (ignoreCase)
		return _stricmp(s, c.s) < 0;
	else
		return strcmp(s, c.s) < 0;
}
/****************************************************/
bool Cadena::operator>(const Cadena &c) const {
	if (ignoreCase)
		return _stricmp(s, c.s) > 0;
	else
		return strcmp(s, c.s) > 0;
}
/****************************************************/
bool Cadena::operator<=(const Cadena &c) const {
	if (ignoreCase)
		return _stricmp(s, c.s) <= 0;
	else
		return strcmp(s, c.s) <= 0;
}
/****************************************************/
bool Cadena::operator>=(const Cadena &c) const {
	if (ignoreCase)
		return _stricmp(s, c.s) >= 0;
	else
		return strcmp(s, c.s) >= 0;
}
/****************************************************/
char *Cadena::GetNewCharPtr() const {
	size_t len = strlen(s) + 1;
	char *ret = new char[len];
	strcpy_s(ret, len, s);
	return ret;
}
/****************************************************/

unsigned int Cadena::Length() const {
	return (unsigned int)strlen(s);
}

bool Cadena::Contains(const Cadena &substr) const {
	if (substr.Length() == 0)
		return true;
	char * s2 = substr.s;
	unsigned int j, j2;

	std::size_t largoS = strlen(s);
	std::size_t largoS2 = strlen(s2);
	if (!ignoreCase) {
		for (unsigned int i = 0; i < largoS; i++) {
			if (i + largoS2 > largoS + 1)
				return false;
			if (s[i] == s2[0]) {
				j = i;
				j2 = 0;
				while (j2 < largoS2 && s[j] == s2[j2]) {
					j++;
					j2++;
				}
				if (j2 == largoS2)
					return true;
			}
		}
	}
	else {
		for (unsigned int i = 0; i < largoS; i++) {
			if (i + largoS2 > largoS + 1)
				return false;
			if (toupper(s[i]) == toupper(s2[0])) {
				j = i;
				j2 = 0;
				while (j2 < largoS2 && toupper(s[j]) == toupper(s2[j2])) {
					j++;
					j2++;
				}
				if (j2 == largoS2)
					return true;
			}
		}
	}
	return false;
}

char Cadena::operator[] (const unsigned int index)
{
	assert(index < Length());
	return s[index];
}

void Cadena::insertarTexto(int pos, Cadena text) {
	while (this->Length() < pos)
		this->insertarTexto(this->Length(), " ");
	int largo = text.Length() + this->Length();
	char* nueva = new char[largo + 1];
	for (int i = 0; i < pos; i++) {
		nueva[i] = this->s[i];
	}
	for (int i = 0; i < text.Length(); i++) {
		nueva[i + pos] = text.s[i];
	}
	for (int i = pos; i < this->Length(); i++) {
		nueva[i + text.Length()] = this->s[i];
	}
	nueva[largo] = '\0';
	delete[] this->s;
	this->s = nueva;
}

void Cadena::eliminarDesdeHasta(int desde, int hasta) {
	while (hasta-desde > this->Length()-desde)
		this->insertarTexto(0, " ");
	if (hasta > Length()) {
		hasta = Length();
	}
	int largo = this->Length() - (hasta - desde);
	char* nueva = new char[largo + 1];
	int contador = 0;
	for (int i = 0; i < Length(); i++) {
		if (i < desde || i > hasta) {
			nueva[contador] = s[i];
			contador++;
		}
	}
	nueva[largo-1] = '\0';
	delete[] this->s;
	this->s = nueva;
}

Cola<Cadena>* Cadena::split()
{
	Cola<Cadena>* ret = new ColaImp<Cadena>();
	char* aux = this->GetNewCharPtr();
	char* tok = strtok(aux, "/");
	while (tok != NULL) {
		Cadena aux2 = Cadena(tok);
		ret->Encolar(aux2);
		tok = strtok(NULL, "/");
	}
	return ret;
}

#endif