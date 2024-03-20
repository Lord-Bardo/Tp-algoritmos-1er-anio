#include <iostream>
#include <string.h>

using namespace std;

struct Docente
{
	int dni;
	char nombre[20]; 
};

struct Curso
{
	int codigo; 
	char idioma[10];//Portugues es el idioma mas largo y tiene 9 caracteres;
	int nivel;
	int cupo;
	Docente docente;
};


void punto1(Curso cursos[]);
void generarIdioma(Curso cursos, char idioma[]);
void ordenarVector(Curso cursos[]);
void vaciarCursos(Curso cursos[]);
void ingresoCursos(Curso cursos[]);
bool verificarCodigo(int i, Curso cursos[]);
bool verificarNivel(int nivel);
void punto2(Curso cursos[]);
int contarIdioma(Curso cursos[], char idioma[]);
void punto3 (Curso cursos[]);
void punto4 (Curso curso[]);
bool verificarError(Curso cursos[], int i);
void mostrar();

int main()
{
	
	Curso cursos[48];
	vaciarCursos(cursos);
	ingresoCursos(cursos);  
	cout<<" \nSe dictaran los siguientes cursos: \n";
	punto1(cursos);
	punto2(cursos);
	cout<<"Niveles sin curso: \n";
	punto3(cursos);
	punto4(cursos);
	mostrar();
	
    return 0;
}

void ingresoCursos(Curso cursos[])
{
	int i = 0;
	Docente auxiliar;
	int salir = 0;
	
	while (salir != 1)
	{
	
		do{
			
		cout << "Ingrese el codigo de curso (Un numero entero mayor a 0) \n";
		cin >> cursos[i].codigo;
		
		}while(verificarCodigo(i,cursos) || cursos[i].codigo == 0);
		
		cout << "Ingrese uno de los siguientes idiomas(EN MINUSCULA): ingles-italiano-frances-aleman-chino-portugues \n";
        cin >> cursos[i].idioma;
		
		cout << "Ingrese un nivel entre del 1 al 8, siendo 1 el nivel mas basico y 8 el mas avanzado \n";
		cin >> cursos[i].nivel;
		
		while (verificarNivel(cursos[i].nivel))
		{
			cout << "El nivel ingresado no se es un numero del 1 al 8, por favor vuelva a ingresarlo \n";
			cin >> cursos[i].nivel;
		}
		
		while (verificarError(cursos, i))
		{
			cout << "EL CURSO INGRESADO YA EXISTE, VUELVA A INTENTARLO \n";
			cout << "Ingrese el idioma \n";
			cin >> cursos[i].idioma;
			cout << "Ingrese el nivel \n";
			cin >> cursos[i].nivel;
			
			while (verificarNivel(cursos[i].nivel))
			{
				cout << "El nivel ingresado no se es un numero del 1 al 8, por favor vuelva a ingresarlo \n";
				cin >> cursos[i].nivel;
			}
			
		}
		
		cout << "Ingrese el cupo \n";
		cin >> cursos[i].cupo;
	
		cout << "Ingrese el DNI del docente a cargo \n";
		cin >> auxiliar.dni;
	
		cout << "Ingrese el nombre del docente a cargo \n";
		cin >> auxiliar.nombre;
		cursos[i].docente = auxiliar;
		
		cout << "Ingrese 1 para terminar con el ingreso de datos, 0 para continuar \n";
		cin >> salir;
		i++;
	}
	

}

bool verificarCodigo(int i, Curso cursos[]){

	bool salida=false;

	for(int j=0; j<48;j++){
		if((i!=j) && (cursos[i].codigo==cursos[j].codigo)){
			salida=true;
		}
	}
	return salida;
}

bool verificarNivel(int nivel)
{
	bool salida = true;
	for (int i = 0; i < 8; i++)
	{
		if (nivel == (i + 1))
		{
			salida = false;
		}
	}
	return salida;
}


void vaciarCursos(Curso cursos[])
{
	for (int i = 0; i < 48; i++)
	{
		cursos[i].codigo= 0;
		memset(cursos[i].idioma, 0, 10);
		cursos[i].nivel = 0;
		cursos[i].cupo = 0;
	}
}

void punto1(Curso cursos[]){
	ordenarVector(cursos);
	 char palabra[20];
	for (int i = 0; i < 48; i++)
	{
		
		if (strcmpi( cursos[i].idioma,"ingles")  == 0  )
		{
			strcpy(palabra,"Ingles");
			generarIdioma(cursos[i],palabra);
		}
		else if (strcmpi( cursos[i].idioma,"italiano")  == 0  )
		{
			strcpy(palabra,"Italiano");
			generarIdioma(cursos[i],palabra);
		}
		else if (strcmpi( cursos[i].idioma,"Frances")  == 0  )
		{
			strcpy(palabra,"Frances");
			generarIdioma(cursos[i],palabra);
		}
		else if (strcmpi( cursos[i].idioma,"Aleman")  == 0  )
		{
			strcpy(palabra,"Aleman");
			generarIdioma(cursos[i],palabra);
		}
		else if(strcmpi( cursos[i].idioma,"Chino")  == 0  )
		{
			strcpy(palabra,"Chino");
			generarIdioma(cursos[i],palabra);
		}
		else if (strcmpi( cursos[i].idioma,"Portugues")  == 0  )
		{
			strcpy(palabra,"Portugues");
			generarIdioma(cursos[i],palabra);
		}
	}
}

void generarIdioma(Curso cursos, char idioma[]){
	
	strcat(idioma,".dat");
	FILE *archParcial = fopen(idioma ,"ab");
	if (archParcial == NULL)
		cout << "ERROR" << endl;
	else
	{

		fwrite(&cursos, sizeof(Curso), 1, archParcial);

		
	}
	
	fclose(archParcial);
}


void ordenarVector(Curso cursos[])
{

	unsigned i = 1, j;
	Curso aux;
	bool cambio;
	do
	{
		cambio = false;
		for (j = 0; j < 47; j++)
		{
			if (cursos[j].codigo > cursos[j + 1].codigo)
			{
				aux = cursos[j];
				cursos[j] = cursos[j + 1];
				cursos[j + 1] = aux;
				cambio = true;
			}
		}
		i++;
	} while (i < 48 && cambio);
}

void punto2(Curso cursos[])
{
	char palabra[20];
	strcpy(palabra,"Ingles");
	cout << "Se dictaran  " << contarIdioma(cursos, palabra) << "  cursos de ingles \a\t\n";
	char palabra1[20];
	strcpy(palabra1,"Frances");	
	cout << "Se dictaran  " << contarIdioma(cursos, palabra1) << "  cursos de frances \n";
	char palabra2[20];
	strcpy(palabra2,"Portuges");
	cout << "Se dictaran  " << contarIdioma(cursos, palabra2) << "  cursos de portugues \n";
	char palabra3[20];
	strcpy(palabra3,"Italiano");
	cout << "Se dictaran  " << contarIdioma(cursos, palabra3) << "  cursos de italiano \n";
	char palabra4[20];
	strcpy(palabra4,"Aleman");
	cout << "Se dictaran  " << contarIdioma(cursos, palabra4) << "  cursos de aleman \n";
	char palabra5[20];
	strcpy(palabra5,"Chino");
	cout << "Se dictaran  " << contarIdioma(cursos, palabra5) << "  cursos de chino mandarin \n";
	cout<<"\n";
}

int contarIdioma(Curso cursos[], char idioma[]){
	// cuenta la cantidad de un idioma que hay
	
	int cont = 0;
	
	for(int i=0; i < 48 ; i++){
		if (strcmpi( cursos[i].idioma, idioma)  == 0  )
		{
			cont++;
		}
	}

	return cont;
}

void punto3(Curso cursos[])
{
	
	char palabra[20];
	strcpy(palabra,"Ingles");
	if (contarIdioma(cursos,palabra) == 8)
	{
		cout << "\nIngles tiene curso en los 8 niveles.";
	}
	
	char palabra1[20];
	strcpy(palabra1,"Frances");
	if (contarIdioma(cursos, palabra1) == 8)
	{
		cout << "\nFrances tiene curso en los 8 niveles.";
	}
	
	char palabra2[20];
	strcpy(palabra2,"Portugues");
	if (contarIdioma(cursos, palabra2) == 8)
	{
		cout << "\nPortugues tiene curso en los 8 niveles.";
	}
	
	char palabra3[20];
	strcpy(palabra3,"Italiano");
	if (contarIdioma(cursos, palabra3) == 8)
	{
		cout << "\nItaliano tiene curso en los 8 niveles.";
	}
	
	char palabra4[20];
	strcpy(palabra4,"Aleman");
	if (contarIdioma(cursos, palabra4) == 8)
	{
		cout << "\nAleman tiene curso en los 8 niveles.";
	}
	
	char palabra5[20];
	strcpy(palabra5,"Chino");
	if (contarIdioma(cursos, palabra5) == 8)
	{
		cout << "\nChino Mandarin tiene curso en los 8 niveles.";
	}
}

void punto4(Curso cursos[])
{
	int niveles[8] = {0, 0, 0, 0, 0, 0, 0, 0}; // este vector va a tener 1 donde haya al menos 1 curso de ese nivel siendo niveles[0]-->el nivel 1

	for (int i = 0; i < 48; i++) // recorremos el vector de cursos
	{
		for (int k = 0; k < 8; k++)
		{ // nos fijamos en cada curso si existe algun nivel entre el 1 y el 8
			if (cursos[i].nivel == (k + 1))
			{					// si existe un nivel
				niveles[k] = 1; // colocamos un 1 en la posicion equivalente a ese nivel. Ej nivel 3--> niveles[2]=1 (donde 2 va  a ser k)
			}
		}
	}

	for (int j = 0; j < 8; j++)
	{
		if (niveles[j] == 0)
		{ // mostramos del vector nivel las posiciones donde no haya un 1, es decir donde no haya nivel
			cout << "No hay cursos de nivel " << j + 1 << "\n";
		}
	}
}

bool verificarError(Curso cursos[], int i) // verifica que no exista ya el curso de ese idioma a ese nivel
{
	bool var = false;
	for (int k = 0; k < 48; k++)
	{
		if ((strcmpi( cursos[i].idioma, cursos[k].idioma)  == 0  ) && cursos[i].nivel == cursos[k].nivel && i != k)
		{ // el i!=k es para que no tome el que ya ingresamos
			var = true;
		}
	}
	return var;
}

void mostrar(){
	
     Curso cursos;

     FILE*f = fopen("Ingles.dat","rb");  //para abrir otro archivo pongan otro idioma y .dat//
     if(f == NULL){
        cout<<"Error";
     }else{

     
     fread(&cursos,sizeof(Curso),1,f);
     while(!feof(f)){
        cout<<"codigo: "<<cursos.codigo<<endl;
        cout<<"idioma: "<<cursos.idioma<<endl;
        cout<<"nivel: "<<cursos.nivel<<endl;
        cout<<"cupo: "<<cursos.cupo<<endl;
        cout<<"nombre: "<<cursos.docente.nombre<<endl;
        cout<<"dni: "<<cursos.docente.dni<<endl;
        cout<<"----------------"<<endl;
        fread(&cursos,sizeof(Curso),1,f);
     }
    }

}



