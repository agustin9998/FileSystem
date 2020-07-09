#include "PruebasPropias.h"


PruebasPropias::PruebasPropias(ConductorPrueba* conductor)
	:Prueba(conductor)
{
}

PruebasPropias::~PruebasPropias()
{
}

const char* PruebasPropias::getNombre() const
{
	return "PruebasPropias";
}

void PruebasPropias::correrPruebaConcreta()
{
	// Este archivo lo puedo modificar para hacer mis propias pruebas

	// Ejemplo:

	//CADENA
	cout << "---------PRUEBA CADENA--------" << endl;
	Cadena texto = Cadena("hola");
	texto.insertarTexto(2, "LOL");
	cout << texto<< endl;
	texto = "";
	texto.insertarTexto(7, "agus");
	cout << texto << endl;

	texto = Cadena("El borita turbo");
	texto.eliminarDesdeHasta(1, 5);
	cout << texto<< endl;
	texto = "vamo a ver heavy metal";
	texto.eliminarDesdeHasta(3,8);
	cout << texto << endl;

	char* hola = new char[19];
	const char* tre = "/ruta/dir/dir1/dir2";
	for (int i = 0; i < 19; i++)
		hola[i] = tre[i];
	Cadena aux = Cadena("/ruta/dir/dir1/dir2");
	cout << "separo la ruta /ruta/dir/dir1/dir2" << endl;
	Cola<Cadena>* ruta = aux.split();
	while (!(ruta->EsVacia()))
		cout << ruta->Desencolar() << endl;

	//DIRECTORIO
	cout << "---------PRUEBA DIRECTORIO--------" << endl;
	Directorio prueba = Directorio("/");
	cout << "agrego hola.txt y ferna como archivos" << endl;
	prueba.AgregarArchivo("hola.txt");
	prueba.AgregarArchivo("ferna");
	cout << prueba.GetNombre() << endl;

	Archivo arch = Archivo("Archivo");
	cout << "agrego Archivo como archivo" << endl;
	prueba.AgregarArchivo(arch);
	prueba.ListarArchivos("/", "");

	prueba.EliminarArchivo("hola.txt");
	cout << "elimino hola.txt" << endl;
	prueba.ListarArchivos("/", "");
	prueba.AgregarArchivo("hola.txt");
	prueba.EliminarArchivo("ferna");
	cout << "agrego hola.txt y elimino ferna" << endl;
	prueba.ListarArchivos("/", "");

	prueba.AgregarArchivo("trato");
	cout << "agrego trato y elimino todos los archivos" << endl;
	prueba.EliminarArchivos();
	prueba.ListarArchivos("/", "");

	prueba.AgregarArchivo("ayuda");
	prueba.AgregarArchivo("laburo");
	cout << "agrego ayuda y laburo y me fijo si existe ayuda y teto" << endl;
	cout << prueba.ExisteArchivo("ayuda") << endl;
	cout << prueba.ExisteArchivo("teto") << endl;

	cout << "me fijo si contiene archivos" << endl;
	cout << prueba.ContieneArchivos() << endl;
	prueba.EliminarArchivos();
	cout << "elimino todos los archivos y me fijo devuelta" << endl;
	cout << prueba.ContieneArchivos() << endl;

	prueba.AgregarArchivo("ayuda");
	prueba.AgregarArchivo("laburo");
	cout << "agrego ayuda y laburo y devuelvo ambos" << endl;
	cout << prueba.BuscarArchivo("ayuda").GetNombre() << endl;
	cout << prueba.BuscarArchivo("laburo").GetNombre() << endl;

	cout << "pido el nombre /dir" << endl;
	cout << prueba.GetNombre() << endl;
	prueba.SetNombre("nombre");
	cout << "cambio el nobre a nombre y lo pido" << endl;
	cout << prueba.GetNombre() << endl;
	 
	//COLA
	cout << "---------PRUEBA COLA--------" << endl;
	Cola<int>* cola = new ColaImp<int>();
	cola->Encolar(6);
	cola->Encolar(0);
	cola->Encolar(9);
	cola->Encolar(5);
	cola->Encolar(7);
	cola->Encolar(8);
	cout << "imprimo la cola 609578" << endl;
	cola->Imprimir(cout);
	cout << "imprimo el 6 por principio"<< endl;
	cout << cola->Principio() << endl;
	cout << "me fijo si es vacia" << endl;
	cout << cola->EsVacia() << endl;
	cout << "me fijo si es llena" << endl;
	cout << cola->EsLlena() << endl;
	cout << "desencolo" <<endl;
	cout << cola->Desencolar() << endl;
	cout << "imprimo no deberia salir el primero"<< endl;
	cola->Imprimir(cout);
	Cola<int>* copia = new ColaImp<int>();
	copia = cola->Clon();
	cout << "copie cola y compruebo si es igual" << endl;
	copia->Imprimir(cout);
	cout << (copia == cola) << endl;
	cout << cola->CantidadElementos() << endl;
	cout << copia->CantidadElementos() << endl;
	cout << "cantidad elementos" << endl;
	cout << cola->CantidadElementos()<< endl;
	cola->Vaciar();
	cout << "vacio cola y imprimo" << endl;
	cola->Imprimir(cout);

	//DIRECTORIOS
	cout << "---------PRUEBA DIRECTORIOS--------" << endl;
	Directorios* direct = new Directorios();
	cout << "agrego el directorio dato" << endl;
	direct->AgregarDirectorio("./Dato");
	cout << "agrego directorio agus y birra en dato" << endl;
	direct->AgregarDirectorio("./Dato/agus");
	direct->AgregarDirectorio("./Dato/birra");
	cout << "Me fijo si existen ambos" << endl;
	cout << direct->ExisteDirectorio("./Dato/agus") << endl;
	cout << direct->ExisteDirectorio("./Dato/birra") << endl;
	cout << "me fijo si existe /Dato/algoritmos (no existe)" << endl;
	cout << direct->ExisteDirectorio("./Dato/algoritmos") << endl;
	cout << "busco el directorio birra y imprimo el nombre" << endl;
	cout << direct->BuscarDirectorio("./Dato/birra").GetNombre() << endl;
	cout << "Copio el directorio agus en birra y me fijo si existe" << endl;
	direct->CopiarDirectorio("./Dato/agus", "./Dato/birra");
	cout << direct->ExisteDirectorio("./Dato/birra/agus") << endl;
	cout << "Elimino /Dato/agus y me fijo si existe y si existe /Dato/birra y /Dato/birra/agus" << endl;
	direct->EliminarDirectorio("./Dato/agus");
	cout << direct->ExisteDirectorio("./Dato/agus") << endl;
	cout << direct->ExisteDirectorio("./Dato/birra") << endl;
	cout << direct->ExisteDirectorio("./Dato/birra/agus") << endl;
	cout << "elimino  /Dato/birra/agus y  me fijo si existe" << endl;
	direct->EliminarDirectorio("./Dato/birra/agus");
	cout << direct->ExisteDirectorio("./Dato/birra/agus") << endl;
	cout << "lo agrego devuelta y me fijo si existe" << endl;
	direct->AgregarDirectorio("./Dato/birra/agus");
	cout << direct->ExisteDirectorio("./Dato/birra/agus") << endl;
	cout << "Vacio el arbol y me fijo si existe la raiz, /Dato,  /Dato/agus,  /Dato/birra,  /Dato/birra/agus" << endl;
	direct->Vaciar();
	cout << direct->ExisteDirectorio("./") << endl;
	cout << direct->ExisteDirectorio("./Dato") << endl;
	cout << direct->ExisteDirectorio("./Dato/agus") << endl;
	cout << direct->ExisteDirectorio("./Dato/birra") << endl;
	cout << direct->ExisteDirectorio("./Dato/birra/agus") << endl;
	cout << "Imprimo con DIR" << endl;
	direct->Dir("/", "");

	//PILA
	cout << "---------PRUEBA PILA--------" << endl;
	Pila<int>* p = new PilaImp<int>();
	p->Vaciar();
	p->Push(6);
	p->Push(8);
	cout << p->Pop()<< endl;
	cout << p->Pop()<< endl;
	cout << p->EsVacia() << endl;
	cout << "hola"<< endl;
	p->Push(1);
	p->Push(2);
	p->Push(3);
	cout << "sreia un 3" << endl;
	cout << p->Pop() << endl;
	cout << p->EsLlena() << endl;
	cout << "imprimo elementos (2)";
	cout << p->CantidadElementos() << endl;
	cout << "seria un 2" << endl;
	cout << p->Top() << endl;
	cout << "Seria un 2" << endl;
	cout << p->Pop() << endl;
	cout << "imprimo elementos (1)" << endl;
	cout << p->CantidadElementos()<< endl;
	cout << "Seria un 1 " << endl;
	cout << p->Pop();

	//ARCHIVO
	cout << "------PRUEBAS ARCHIVO------\n";
	Archivo a1 = Archivo("Archivo1");
	Archivo a2 = Archivo("Archivo2");
	cout << "--- Prueba visibilidad ---\n";
	cout << a1.EstaOculto() << " visibilidad por defecto"<< endl;
	a1.ModificarVisibilidad("-H");
	cout << a1.EstaOculto() << " Cambiamos visibilidad a -H\n" << endl;
	cout << "--- Prueba insertarTexto ---\n" << endl;
	a1.InsertarTexto(1, 0, "el mate es el propio");
	a1.MostrarContenido();
	cout << "--- Prueba borrarTexto ---\n" << endl;
	a1.EliminarTexto(1, 1, 5);
	a1.MostrarContenido();
	cout << "--- Prueba mostrarContenido ---\n" << endl;
	a1.MostrarContenido();
	cout << "--- Prueba tieneLineas ---\n" << endl;
	cout << a1.TieneLineas() << " Deberia dar true" << endl;
	cout << a2.TieneLineas() << " Deberia dar false" << endl;
	
	InterfazDelSistema* interfaz = new InterfazDelSistemaImp(4);
	this->FormarRedBasica(interfaz);
}

void PruebasPropias::FormarRedBasica(InterfazDelSistema* interfaz) {

	//se crea directorios
	interfaz->Mkdir("/directorio1"), OK, "Se crea el directorio 'Directorio1'.";
	interfaz->Mkdir("/directorio2"), OK, "Se crea el directorio 'Directorio2'.";
	interfaz->Mkdir("/directorio1/directorio2"), OK, "Se crea el directorio 'Directorio2', dentro de 'Directorio1'.";
	interfaz->Mkdir("/directorio2/directorio1"), OK, "Se crea el directorio 'Directorio1', dentro de 'Directorio2'.";
	interfaz->Mkdir("/directorio1/directorio2/directorio1"), OK, "Se crea el directorio 'Directorio1', dentro de 'Directorio2'.";
	interfaz->Mkdir("/directorio3"), OK, "Se crea el directorio 'Directorio3'.";
	interfaz->Mkdir("/directorio3/directorio2"), OK, "Se crea el directorio 'Directorio2', dentro de 'Directorio3'.";
	interfaz->Mkdir("/directorio3/directorio1"), OK, "Se crea el directorio 'Directorio1', dentro de 'Directorio3'.";

	//se crean archivos
	interfaz->CreateFile("/archivo1.txt"), OK, "Se crea archivo1.txt en /.";
	interfaz->CreateFile("/Archivo1.txt"), OK, "Se crea Archivo1.txt en /.";
	interfaz->CreateFile("/directorio1/archivo11.txt"), OK, "Se crea archivo11.txt en /directorio1/directorio11.";
	interfaz->CreateFile("/directorio2/directorio1/archivo11.txt"), OK, "Se crea archivo11.txt en /directorio2/directorio1.";
	interfaz->CreateFile("/directorio3/directorio1/archivo11.txt"), OK, "Se crea archivo11.txt en /directorio3/directorio1.";
	interfaz->CreateFile("/directorio2/documento.txt"), OK, "Se crea documento.txt en /directorio2.";
	interfaz->CreateFile("/directorio3/directorio2/documento.txt"), OK, "Se crea documento.txt en /directorio3/directorio2.";

	//se introduce texto en archivos
	interfaz->InsertText("/archivo1.txt", 1, 1, "An error saepe."), OK, "Se inserta texto en archivo1.txt, linea 1, posicion 1.";
	interfaz->InsertText("/archivo1.txt", 1, 30, "An error saepe."), OK, "Se inserta texto en archivo1.txt, linea 1 posicion 30";
	interfaz->InsertText("/archivo1.txt", 40, 1, "Vis omnis legere"), OK, "Se inserta texto en archivo1.txt, linea 4, posicion 1";
	interfaz->InsertText("/archivo1.txt", 4, 1, "Omnesque philosophia eum an, ius tale."), OK, "Se inserta texto en archivo1.txt, en linea 4, posicion 1";
	interfaz->InsertText("/directorio3/directorio1/archivo11.txt", 1, 1, "Ius invidunt convenire at, has in atqui probatus deserunt."), OK, "Se inserta texto en /directorio1/directorio11/archivo11.txt, en linea 1, posicion 1";
	interfaz->InsertText("/directorio3/directorio1/archivo11.txt", 1, 1, "Eos nibh regione."), OK, "Se inserta texto en /directorio1/directorio11/archivo11.txt, en linea 1, posicion 1";
	interfaz->InsertText("/directorio3/directorio1/archivo11.txt", 10, 1, "Sed fabulas laoreet appellantur."), OK, "Se inserta texto en /directorio1/directorio11/archivo11.txt, en linea 10, posicion 1";
	interfaz->InsertText("/directorio3/directorio1/archivo11.txt", 4, 1, "Mel et illum sententiae, vix inani."), OK, "Se inserta texto en /directorio1/directorio11/archivo11.txt, en linea 4, posicion 1";
	interfaz->InsertText("/directorio2/directorio1/archivo11.txt", 1, 1, "Usu rebum virtute."), OK, "Se inserta texto en /directorio2/directorio21/directorio211/directorio2111/archivo2111.txt, en linea 1, posicion 1";
	interfaz->InsertText("/directorio2/directorio1/archivo11.txt", 2, 1, "Eam habeo."), OK, "Se inserta texto en /directorio2/directorio21/directorio211/directorio2111/archivo2111.txt, en linea 2, posicion 1";
	interfaz->InsertText("/directorio2/directorio1/archivo11.txt", 3, 1, "His no putant vivendo."), OK, "Se inserta texto en /directorio2/directorio21/directorio211/directorio2111/archivo2111.txt, en linea 3, posicion 1";
}