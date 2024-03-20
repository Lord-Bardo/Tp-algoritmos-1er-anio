#include <iostream>
#include <string.h>


using namespace std;

struct Docente
{
	char nombre[20]; 
	int dni;

};
struct Alumno{
	
	char nombre[20];
	int dni;
	int codigoCA;
	
};

struct NodoInsc{ //lista principal    
	Alumno alumno;
	NodoInsc *sig;
};

struct NodoCola{ //sos  cola de cursos
	Alumno alumno;
	NodoCola *sig;
};
struct Curso
{
	int codigo; 
	char idioma[10];
	int nivel;
	int cupo;
	Docente docente;
	NodoCola *pri;
	NodoCola *ultimo;
};
struct NodoArbol{
    int doc;
	int cantEst;
	char nombre[20];
    NodoArbol* izq;
    NodoArbol* der;
};



int vacOcupadas[48]; //vector de vacantes ocupadas global

Curso cursos[49]; //Vector cursos global;

//Prototipo Funciones
void inicializar(); // Guarda la informacion de los archivos en el vector de cursos;
int leerIdioma(char idioma[], int i);
void menu();
void inscripcionEstudiante(NodoInsc *&lista);
bool existeCurso(int codigo); //Verifica si existe el curso
bool hayCupo(int codigo);//Verifica si hay cupo para ese curso;
void mostrarCursos(NodoInsc *&lista);
void leer();
void agregar(NodoInsc *&lista,Alumno alumno);
void restarCupo(int codigo);
void mostrarIngresantes(NodoInsc *&lista,int );
void encolar(Alumno aux);
void mostrarEncolados();
void bajaEstudiante(NodoInsc *&lista);
NodoCola *&ultimo(int codigo);
void mostrarCola(Curso curso);
int mostrameCupo(int codigo);
int cantidadCursos();
bool existeInscripto(int dni,NodoInsc *&lista);
void eliminarInscripto(int dni, NodoInsc *&lista);
void agregarDeCola(int codigoCurso, NodoInsc *&lista);
Alumno eliminarTraer(NodoCola *&pri,NodoCola *&ult);
void ordenar();
void punto4(NodoArbol *&arbol,NodoInsc *lista);
void insertar(NodoArbol*&raiz,int i);
void arbol(NodoArbol *&raiz);
void listarIn(NodoArbol*raiz);
void generarArchivo(int codigo,NodoInsc *&lista);
void gener(NodoInsc *lista);
void intAchar(int n,char cad[]);

int main(int argc, char** argv) {

   // leer();
	inicializar(); // abre cada idioma y lo guarda en cursos[48]//
	ordenar();

	menu();

	return 0;
}

void menu(){
	
	int aux=0;
	NodoInsc *lista = NULL;	
	NodoArbol *raiz = NULL;
	while(aux!=4){
		
	cout<<"[1] Inscripcion Estudiante \n";
	cout<<"[2] Baja del Estudiante \n";
	cout<<"[3] Mostrar Cursos\n";
	cout<<"[4] Salir \n";
	cout<<"\n";
	cin>>aux;
	
	
	switch(aux){
	case 1: 
			inscripcionEstudiante(lista);
			break;
	case 2: 
			bajaEstudiante(lista);
			break;
	case 3: 
			mostrarCursos(lista);
			break;
	case 4: 
			punto4(raiz,lista);

			break;
	default: break;
	
	
	}
	}
	
}

void listarIn(NodoArbol*raiz){
    if(raiz!=NULL)
    {
        listarIn(raiz->izq);
        cout<<"\nNumero de DNI: "<<raiz->doc<<endl;
		cout<<"Nombre: "<<raiz->nombre<<endl;
		cout<<"Cantidad de estudiantes: "<<raiz->cantEst;
        listarIn(raiz->der);
}
}
void gener(NodoInsc *lista){
	for(int i = 0;i<48;i++){
		if(cursos[i].codigo != 0)
		generarArchivo(cursos[i].codigo,lista);
	}
}
void generarArchivo(int codigo,NodoInsc *&lista){  //genera los archivos con el nombre del codigo y los estudiantes dentro
	char nom[20];
	NodoInsc *p = lista;
	intAchar(codigo,nom);
	strcat(nom,".dat");
	FILE*f=fopen(nom,"wb");
	while(p!=NULL){
		if(p->alumno.codigoCA == codigo){ 
			fwrite(p,sizeof(Alumno),1,f);
		}
		p = p->sig;
	}
	cout<<"\nArchivo de codigo "<<codigo<<" creado.";
}

void intAchar(int n,char cad[]){  //funcion que pasa de int codigo a char para crear el archivo 
    int nroDig = 0;
	int aux = n;
	while(aux>0){
		aux=aux/10;
		nroDig++;
	}
	cad[nroDig] = '\0';
	aux = n;
	int pos = nroDig-1 ,dig;
	while(pos>=0){
		dig = aux%10;
		aux = aux/10;
		cad[pos] = dig + '0';
		pos--;
	}
}

void punto4(NodoArbol *&raiz,NodoInsc *lista){
	mostrarEncolados();
	arbol(raiz);
	listarIn(raiz);
	gener(lista);
}
void arbol(NodoArbol *&raiz){
	for(int i = 0;i<48;i++){
		if(cursos[i].codigo != 0){
			insertar(raiz,i);
		}
	}
}
void insertar(NodoArbol*&raiz,int i)
{
    NodoArbol *n;
    n=new NodoArbol;
    n->cantEst = (vacOcupadas[i] - cursos[i].cupo);
	n->doc = cursos[i].docente.dni;
	strcpy(n->nombre,cursos[i].docente.nombre);
    n->der=n->izq=NULL;

    if(raiz==NULL)
        raiz=n;
    else
    {
        NodoArbol *r=raiz,*ant;
        while(r!=NULL)
        {
            ant=r;
            if(n->doc < r->doc)
                r=r->izq;
            else if(n->doc > r->doc)
                r=r->der;
			else{
				break;
			}
		
        }
        if(n->doc < ant->doc)
            ant->izq=n;
        else if(n->doc > ant->doc)
            ant->der=n;
		else{
			ant->cantEst += n->cantEst;
		}
    }
}


void ordenar(){
	Curso aux;
	int aux2;
	for(int i = 0;i<48;i++){
		for(int j = 0;j<48;j++){
			if(cursos[j].codigo > cursos[j+1].codigo && cursos[j].codigo != 0 && cursos[j+1].codigo != 0){
			aux = cursos[j];
			cursos[j] = cursos[j+1];
			cursos[j+1] = aux;

			aux2 = vacOcupadas[j];  //orden de vacantes ocupadas
			vacOcupadas[j] = vacOcupadas[j+1];
			vacOcupadas[j+1] = aux2;
			}
		}
	}
}
void mostrarCursos(NodoInsc *&lista){ //muestra las posisiones no vacias del vector cursos, lo usamos para testing
	for(int j=0;j<48;j++){
		//cout<<cursos[j].idioma<<endl;
		if(cursos[j].codigo!=0){
			cout<<"---------Curso--------"<<endl;
			cout<<"codigo: "<<cursos[j].codigo<<endl;
			cout<<"Vacantes disponibles: "<<cursos[j].cupo<<endl;
			cout<<"Vacantes ocupadas: "<<(vacOcupadas[j] - cursos[j].cupo)<<endl; //resta cupos iniciales con actual
			cout<<"Inscriptos: "<<endl;
			mostrarIngresantes(lista,j);
        	cout<<"----------------"<<endl;
		}
	}
}


void bajaEstudiante(NodoInsc *&lista){
	/*Dado el n�mero de documento del estudiante que pide la baja y c�digo del curso del cual se baja,
eliminarlo y darle la vacante a quien corresponda si es que hay estudiantes en cola de espera*/
	int dni=0;
	int codigoCurso=0;
	do{
		cout<<"Ingrese el dni del estudiante a dar de baja \n";
		cin>>dni;
		cout<<"Ingrese el codigo de curso del cual se va a dar de baja \n";
		cin>>codigoCurso;	
	}while(!existeCurso(codigoCurso) || !existeInscripto(dni,lista));


	eliminarInscripto(dni,lista);
	agregarDeCola(codigoCurso,lista);

}


void agregarDeCola(int codigoCurso, NodoInsc *&lista){
	//Elimina al 1er estudiante con codCurso==alumno.codCurso de la listaCola, y lo agrega a la lista Inscriptos,
	int tamanio= cantidadCursos();
	for(int i=0; i<tamanio;i++){
		if(cursos[i].codigo==codigoCurso){
		
			agregar(lista,eliminarTraer(cursos[i].pri,cursos[i].ultimo));
		}
	}
}

Alumno eliminarTraer(NodoCola *&pri,NodoCola *&ult)
{
    Alumno dato;
    NodoCola*p=pri;
    dato=p->alumno;
    
    if(pri==ult){
    	pri=NULL;
    	ult=NULL;
	}
	else{
		pri=pri->sig;
	}
    delete p;
    return dato;
}


bool existeInscripto(int dni, NodoInsc *&lista){
	//recorrerlista donde dni==inscripto.dni;
	NodoInsc*p=lista;
    while(p!=NULL){
    	if(dni==p->alumno.dni){
    		return true;
		}
        p=p->sig;
	}
	return false;
}

void eliminarInscripto(int dni, NodoInsc *&lista){
	//recorrer lista hasta Alumno.codCurso==codCurso && alumno.dni== dni
	NodoInsc*ant,*p=lista;
    while(p!=NULL && p->alumno.dni<dni)
    {
        ant=p;
        p=p->sig;
    }
	if(p!=lista)
        ant->sig=p->sig;
    else
        lista=p->sig;
    delete p;
    
}


void inscripcionEstudiante(NodoInsc *&lista){
	Alumno ingresante;

	cout<<"Ingrese nombre del alumno"<<endl;
	fflush(stdin);
	cin.getline(ingresante.nombre,20);
	fflush(stdin);
	
	cout<<"Ingrese dni del alumno"<<endl;
	cin>>ingresante.dni;
	fflush(stdin);
	
	cout<<"Ingrese el codigo de curso del alumno"<<endl;
	cin>>ingresante.codigoCA;
	fflush(stdin);
	
	if(existeCurso(ingresante.codigoCA)){	
	
		if(hayCupo(ingresante.codigoCA)==true){
			
			agregar(lista,ingresante);
						
		}
		else{
			/*poner en la cola*/
			cout<<"No hay cupos disponibles."<<endl;
			
			encolar(ingresante);
			
		}
	}
	else{
		cout<<"No existe ese curso, inscripcion rechazada";
	}
}
int cantidadCursos(){
	int cont=0;
	for(int i=0;i<48;i++)
	{
		if(cursos[i].codigo>0){
			cont++;
		}
	}
	return cont;
}
int mostrameCupo(int codigo){
	for(int i=0;i<cantidadCursos();i++){
		if(codigo==cursos[i].codigo){
			return cursos[i].cupo;
		}
	}
	return 400;
}




bool existeCurso(int codigo){

	int tamanio= cantidadCursos();

    for(int i=0;i<tamanio;i++){
        if(codigo==cursos[i].codigo){
            return true;
        }
    }
    return false;
}

bool hayCupo(int codigo){
	int tamanio= cantidadCursos();
    for(int i=0;i<tamanio;i++){
        if((codigo==cursos[i].codigo) && (cursos[i].cupo > 0)){//distingo?
            return true;
        }
    }
    return false;

}


void inicializar(){ // Tenemos que hacer lo mismo con los demas idiomas, usar un strcpy x que ppisa el idioma anterior.
	int i=0;
	char palabra[10];
	strcpy(palabra,"Ingles");
	i=leerIdioma(palabra,i);

	strcpy(palabra,"Frances");
	i=leerIdioma(palabra,i);

	strcpy(palabra,"Italiano");
	i=leerIdioma(palabra,i);

	strcpy(palabra,"Portugues");
	i=leerIdioma(palabra,i);

	strcpy(palabra,"Aleman");
	i=leerIdioma(palabra,i);

	strcpy(palabra,"Chino");
	i=leerIdioma(palabra,i);

	
}

int leerIdioma(char idioma[], int i){ //este leerIdioma recive un idioma y guarda todo lo que haya en el archivo correspondiente en el vector cursos

	Curso aux;
	strcat(idioma,".dat");
	
	FILE *f = fopen(idioma ,"r");  
     if(f == NULL){
        cout<<idioma<<" no existe"<<endl;
     }else{

     fread(&aux,sizeof(Curso)-16,1,f);
     while(!feof(f)){
        cursos[i].codigo = aux.codigo;
		cursos[i].cupo = aux.cupo;
		strcpy(cursos[i].idioma,aux.idioma);
		cursos[i].nivel=aux.nivel;
		strcpy(cursos[i].docente.nombre,aux.docente.nombre);
		cursos[i].docente.dni = aux.docente.dni;    	
		fread(&aux,sizeof(Curso)-16,1,f);

		vacOcupadas[i] = aux.cupo;

     	i++;
     }
     
    }
    fclose(f);
    return i;

}


void agregar(NodoInsc *&lista,Alumno aux){
    NodoInsc *n,*p,*ant;
    n=new NodoInsc;
	n->alumno.codigoCA = aux.codigoCA;
	n->alumno.dni = aux.dni;
	strcpy(n->alumno.nombre,aux.nombre);

    p=lista;
    while(p!=NULL && p->alumno.dni<aux.dni)
    {
        ant=p;
        p=p->sig;
    }
    n->sig=p;
    if(p!=lista)
        ant->sig=n;
    else
        lista=n;

	restarCupo(aux.codigoCA);
}

void restarCupo(int codigo){
	for(int i = 0;i<cantidadCursos();i++){
		if(cursos[i].codigo == codigo){
			cursos[i].cupo--;
		}
	}

}


void encolar(Alumno dato)
{
	int j;
	NodoCola*p;
    p=new NodoCola;

	for(int k=0;k< cantidadCursos();k++){
		if(cursos[k].codigo==dato.codigoCA){
			j=k;
		}
	}
	
    p->alumno=dato;
    p->sig=NULL;
    if(cursos[j].ultimo!=NULL){
    	cursos[j].ultimo->sig=p;
	}
	else{
		cursos[j].pri=p;
	}
    cursos[j].ultimo=p;
}


void mostrarEncolados(){
	for(int i=0;i<48;i++){
		if(cursos[i].codigo !=0){
		mostrarCola(cursos[i]);
		}
	}
}
void mostrarCola(Curso cursos){
	NodoCola*aux= cursos.pri;
	if(aux != NULL){
	cout<<"En lista  de espera: "<<endl;
	
    while(aux!=NULL){
		cout<<"----------"<<endl;
		cout<<"nombre: "<<aux->alumno.nombre<<endl;
		cout<<"dni: "<<aux->alumno.dni<<endl;
        aux=aux->sig;
	}
	cout<<"------------"<<endl;
	}else{
		cout<<"Sin estudiantes en lista de espera de curso codigo "<<cursos.codigo<<endl;
	}
}

void mostrarIngresantes(NodoInsc *&lista,int j){
	NodoInsc*p=lista;
    while(p!=NULL){
		if(p->alumno.codigoCA == cursos[j].codigo){
			cout<<endl;
			cout<<" dni: "<< p->alumno.dni<<"\n";
			cout<<" nombre: "<< p->alumno.nombre<<"\n";

		}
        p=p->sig;
	}
}
