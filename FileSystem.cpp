#include "FileSystem.h"

#ifndef FILESYSTEM_CPP
#define FILESYTEM_CPP

FileSystem::FileSystem()
{
	this->dir = new Directorios();
	this->elim = new PilaImp<Asociacion<Archivo, Cadena>>();
	this->trashSize = 0;
}

FileSystem::FileSystem(unsigned int MAX_RECUPERAR)
{
	this->dir = new Directorios();
	this->elim = new PilaImp<Asociacion<Archivo, Cadena>>();
	this->trashSize = MAX_RECUPERAR;
}

FileSystem::~FileSystem()
{
	delete this->dir;
	delete this->elim;
}

FileSystem::FileSystem(const FileSystem& f)
{
	this->dir = f.dir;
	this->trashSize = f.trashSize;
	this->elim = f.elim;
}

FileSystem& FileSystem::operator=(const FileSystem& f)
{
	if (this != &f)
	{
		this->dir = f.dir;
		this->trashSize = f.trashSize;
		this->elim = f.elim;
	}
	return *this;
}

TipoRetorno FileSystem::Mkdir(Cadena rutaDirectorio)
{
	if (rutaDirectorio[0] == '/') {//VALIDA QUE LA RUTA COMIENZE CON '/'
		if (rutaDirectorio != "/") {
			rutaDirectorio.insertarTexto(0, ".");
			Cadena dirAux = this->dir->quitarArchivo(rutaDirectorio);//Directorio que hay que validar que exista.
			if (dir->ExisteDirectorio(dirAux)) {
				if (!dir->ExisteDirectorio(rutaDirectorio)) {//VALIDA QUE NO EXISTA EL MISMO DIR CON MISMO NOMBRE;
					dir->AgregarDirectorio(rutaDirectorio);
					return OK;
				}
				else {
					cout << "Ya existe un subdirectorio con el mismo nombre en esa ruta." << endl;
					return ERROR;
				}
			}
			else {
				cout << "No se encuentra la ruta." << endl;
				return ERROR;
			}
		}
		else {
			cout << "No se puede volver a crear el directorio raiz." << endl;
			return ERROR;
		}
	}
	else {
		cout << "La ruta no comienza con /. " << endl;
		return ERROR;
	}
}

TipoRetorno FileSystem::Rmdir(Cadena rutaDirectorio)
{
	if (rutaDirectorio[0] == '/') {
		rutaDirectorio.insertarTexto(0, ".");
		if (this->dir->ExisteDirectorio(rutaDirectorio)) {
			this->dir->EliminarDirectorio(rutaDirectorio);
		}
		else {
			cout << "No se encuentra la ruta." << endl;
			return ERROR;
		}
	}
	else {
		cout << "La ruta no comienza con /. " << endl;
		return ERROR;
	}
}

TipoRetorno FileSystem::CopyDir(Cadena rutaOrigen, Cadena rutaDestino)
{
	if (rutaOrigen[0] == '/' && rutaDestino[0] == '/') {
		rutaOrigen.insertarTexto(0, ".");
		rutaDestino.insertarTexto(0, ".");
		Cadena prueba = this->dir->quitarArchivo(rutaDestino);
		if (this->dir->ExisteDirectorio(rutaOrigen)) {//Valido que exista el dir original
			if (!this->dir->ExisteDirectorio(rutaDestino)) {//Valido que la ruta destino no este creada.
				if (this->dir->ExisteDirectorio(prueba)) {
					if (!this->dir->esSubdirectorio(rutaOrigen, rutaDestino)) {
						rutaDestino.eliminarDesdeHasta(0, 0);
						this->Mkdir(rutaDestino);
						rutaDestino.insertarTexto(0, ".");
						this->dir->CopiarDirectorio(rutaOrigen, rutaDestino);
					}
					else {
						cout << "La ruta destino no puede ser un subdirectorio de origen." << endl;
						return ERROR;
					}
				}
				else {
					cout << "No se encuentra el padre de la ruta destino." << endl;
					return ERROR;
				}
			}
			else {
				cout << "Ya existe la ruta destino." << endl;
				return ERROR;
			}
		}
		else {
			cout << "No se encuentra la ruta origen." << endl;
			return ERROR;
		}
	}
	else {
		cout << "La ruta no comienza con /. " << endl;
		return ERROR;
	}
}

TipoRetorno FileSystem::Dir(Cadena rutaDirectorio, Cadena parametro) const
{
	if (rutaDirectorio[0] == '/') {
		rutaDirectorio.insertarTexto(0, ".");
		if (parametro == "" || parametro == "-H") {
			if (this->dir->ExisteDirectorio(rutaDirectorio)) {//Valido que exista la ruta
				this->dir->Dir(rutaDirectorio, parametro);
				return OK;
			}
			else {
				cout << "No se encuentra la ruta" << endl;
				return ERROR;//El directorio no existe
			}
		}
		else {
			cout << "Parametro desconocido." << endl;
			return ERROR;
		}
	}
	else {
		cout << "La ruta no comienza con /. " << endl;
		return ERROR;
	}
}

TipoRetorno FileSystem::CreateFile(Cadena rutaArchivo)
{
	if (rutaArchivo[0] == '/') {
		rutaArchivo.insertarTexto(0, ".");
		Cadena dirAux = this->dir->quitarArchivo(rutaArchivo);//Directorio que hay que validar que exista.
		Cadena archivo = this->dir->agarrarUltimo(rutaArchivo);
		if (this->dir->ExisteDirectorio(dirAux)) {
			if (!this->dir->BuscarDirectorio(dirAux).ExisteArchivo(archivo)) {
				this->dir->BuscarDirectorio(dirAux).AgregarArchivo(archivo);
				return OK;
			}
			else {
				cout << "Ya existe un archivo con el mismo nombre en esa ruta. " << endl;
				return ERROR;
			}
		}
		else {
			cout << " No se encuentra la ruta" << endl;
			return ERROR;
		}
	}
	else {
		cout << "La ruta no comienza con /" << endl;
		return ERROR;//La ruta no empieza con '/'
	}
}

TipoRetorno FileSystem::Delete(Cadena rutaArchivo)
{
	if (rutaArchivo[0] == '/') {
	rutaArchivo.insertarTexto(0, ".");
	Cadena dirAux = this->dir->quitarArchivo(rutaArchivo);//Directorio que hay que validar que exista.
	Cadena archivo = this->dir->agarrarUltimo(rutaArchivo);
		if (this->dir->ExisteDirectorio(dirAux)) {
			if (this->dir->BuscarDirectorio(dirAux).ExisteArchivo(archivo)) {
				Archivo aux = this->dir->BuscarDirectorio(dirAux).BuscarArchivo(archivo);//Guardo el archivo a eliminar
				this->dir->BuscarDirectorio(dirAux).EliminarArchivo(archivo);//Lo elimino
				Asociacion<Archivo, Cadena> a = Asociacion<Archivo, Cadena>(aux, dirAux);
				if (this->elim->CantidadElementos() == this->trashSize) {
					this->elim->Pop();
					this->elim->Push(a);
				}
				else {
					this->elim->Push(a);
				}
				return OK;
			}
			else {
				cout << "No existe un archivo con ese nombre en esa ruta." << endl;
				return ERROR;//El directorio no existe
			}
		}
		else {
			cout << "No se encuentra la ruta. " << endl;
			return ERROR;//El directorio no existe
		}
	}
	else {
		cout << "La ruta no comienza con /" << endl;
		return ERROR;//La ruta no empieza con '/'
	}
}

TipoRetorno FileSystem::Attrib(Cadena rutaArchivo, Cadena parametro)
{
	if (rutaArchivo[0] == '/') {
		rutaArchivo.insertarTexto(0, ".");
		if (parametro == "+H" || parametro == "-H") {
			Cadena archivo = this->dir->agarrarUltimo(rutaArchivo);
			Cadena dirAux = this->dir->quitarArchivo(rutaArchivo);
			if (this->dir->ExisteDirectorio(dirAux)) {
				if (this->dir->BuscarDirectorio(dirAux).ExisteArchivo(archivo)) {
					this->dir->BuscarDirectorio(dirAux).BuscarArchivo(archivo).ModificarVisibilidad(parametro);
					return  OK;
				}
				else {
					cout << "No existe un archivo con ese nombre en esa ruta. " << endl;
					return ERROR;//No existe el archivo
				}
			}
			else {
				cout << "No se encuentra la ruta." << endl;
				return ERROR;//No existe la ruta
			}
		}
		else {
			cout << "Parametro desconocido" << endl;
			return ERROR;
		}
	}
	else {
		cout << "La ruta no comienza con /" << endl;
		return ERROR;//La ruta no empieza con '/' o 
	}
}

TipoRetorno FileSystem::InsertText(Cadena rutaArchivo, unsigned int nroLinea, unsigned int posLinea, Cadena texto)
{
	if (rutaArchivo[0] == '/') {
		rutaArchivo.insertarTexto(0, ".");
		if (nroLinea > 0) {
			if (posLinea > 0) {
				nroLinea--;
				posLinea--;
				Cadena archivo = this->dir->agarrarUltimo(rutaArchivo);
				Cadena dirAux = this->dir->quitarArchivo(rutaArchivo);
				if (this->dir->ExisteDirectorio(dirAux)) {
					if (this->dir->BuscarDirectorio(dirAux).ExisteArchivo(archivo)) {
						this->dir->BuscarDirectorio(dirAux).BuscarArchivo(archivo).InsertarTexto(nroLinea, posLinea, texto);
						return  OK;
					}
					else {
						cout << "No existe un archivo con ese nombre en esa ruta." << endl;
						return ERROR;//No existe el archivo
					}
				}
				else {
					cout << "No se encuentra la ruta." << endl;
					return ERROR;//No existe la ruta
				}
			}
			else {
				cout << "La posicion cero no es valida. " << endl;
				return ERROR;
			}
		}
		else {
			cout << "La linea cero no es valida." << endl;
			return ERROR;
		}
	}
	else {
		cout << "La ruta no comienza con /" << endl;
		return ERROR;//La ruta no empieza con '/' 
	}
}

TipoRetorno FileSystem::DeleteText(Cadena rutaArchivo, unsigned int nroLinea, unsigned int posLinea, unsigned int k)
{
	if (rutaArchivo[0] == '/') {
		rutaArchivo.insertarTexto(0, ".");
		if (nroLinea > 0){
			if (posLinea > 0) {
				nroLinea--;
				posLinea--;
				Cadena archivo = this->dir->agarrarUltimo(rutaArchivo);
				Cadena dirAux = this->dir->quitarArchivo(rutaArchivo);
				if (this->dir->ExisteDirectorio(dirAux)) {
					if (this->dir->BuscarDirectorio(dirAux).ExisteArchivo(archivo)) {
						if (this->dir->BuscarDirectorio(dirAux).BuscarArchivo(archivo).cantLineas() >= nroLinea) {
							
							this->dir->BuscarDirectorio(dirAux).BuscarArchivo(archivo).EliminarTexto(nroLinea, posLinea, k);
							return  OK;
						}
						else {
							cout << "La linea no existe." << endl;
							return ERROR;
						}
					}
					else {
						cout << "No existe un archivo con ese nombre en esa ruta." << endl;
						return ERROR;//No existe el archivo
					}
				}
				else {
					cout << "No se encuentra la ruta." << endl;
					return ERROR;//No existe la ruta
				}
			}
			else {
				cout << "La posicion cero no es valida. " << endl;
				return ERROR;
			}
		}
		else {
			cout << "La linea cero no es valida." << endl;
			return ERROR;
		}
	}
	else {
		cout << "La ruta no comienza con /" << endl;
		return ERROR;//La ruta no empieza con '/' 
	}
}

TipoRetorno FileSystem::Type(Cadena rutaArchivo) const
{
	if (rutaArchivo[0] == '/') {
		rutaArchivo.insertarTexto(0, ".");
		Cadena archivo = this->dir->agarrarUltimo(rutaArchivo);
		Cadena dirAux = this->dir->quitarArchivo(rutaArchivo);
		if (this->dir->ExisteDirectorio(dirAux)) {
			Directorio direct = this->dir->BuscarDirectorio(dirAux);
			if (direct.ExisteArchivo(archivo)) {
				cout << rutaArchivo << endl;//Imprimo ruta
				cout << "" << endl;//Salto en blanco por letra
				this->dir->BuscarDirectorio(dirAux).BuscarArchivo(archivo).MostrarContenido();
			}
			else {
				cout << "No existe un archivo con ese nombre en esa ruta." << endl;
				return ERROR;//No existe el archivo
			}
		}
		else {
			cout << "No se encuentra la ruta." << endl;
			return ERROR;//No existe la ruta
		}
	}
	else {
		cout << "La ruta no comienza con /" << endl;
		return ERROR;//La ruta no empieza con '/' 
	}
}

TipoRetorno FileSystem::Undelete()
{
	if (!this->elim->EsVacia()) {
		Asociacion<Archivo, Cadena> a = this->elim->Pop();
		Archivo arch = a.GetDominio();
		Cadena ruta = a.GetRango();
		if (!this->dir->BuscarDirectorio(ruta).ExisteArchivo(arch.GetNombre())) {
			this->dir->BuscarDirectorio(ruta).AgregarArchivo(arch);
		}
	}
	else {
		cout << "No hay archivos para recuperar." << endl;
		return ERROR;
	}
}



#endif