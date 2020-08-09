#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <iomanip>
#include <sstream>

using namespace std;

struct Fecha{
	int dia;
	int mes;
	int anio;
};

struct Hora{
	int hora;
	int minutos;
};

struct Paciente{
	Paciente* siguiente;
	char Apellido_Paterno[15];
	char Apellido_Materno[15];
	char Nombres[25];
	char Estado_Civil[11];
	char Genero;
	Fecha Fecha_Nac;
	int DNI;
	int telefono;
	char Seguro[10];
	char Problemas_Medicos[200];
};

struct Historial{
	int codigoHist;
	int DNI;
	Fecha fechaHist;
};

struct Medico {
	int DNI;
	char nombre[25];
	char apellidoP[25];
	char apellidoM[25];
	int telefono;
	char correoElectronico[25];
	char centroDeEstudio[49];
	char especialidad[25];
};

struct Cita {
	Cita* siguiente;
	int codigoCit;
	int DNI;
	char Especialidad[25];
	Fecha fechaCita;
	Hora horaCita;
}* primero, * ultimo;

struct Consulta{	
	int codigoHist;
	char signos[200];
	char sintomas[200];
	char resultados[200];
	char diagnostico[200];
	
};

struct Receta{
	int codigoCit;
	char medicamentos[200];
	char instrucciones[200];
};

void menu_principal();
void menu_medico();
void menu_medico_opciones();

void opcion_crear_medico();
bool insertar_medico_archivo(Medico user);
void existe_medico(bool &existe, int codigo,Medico *user);

void opcion_mostrar_medico();
Medico *obtener_stu_archivo(int *n);
bool modificar_archivo_medico(Medico user);

void menu_paciente();
void menu_paciente_opciones(void);

void opcion_crear_paciente();
bool insertar_paciente_archivo(Paciente pac);
void existe_paciente(bool &existe, int DNI,Paciente *pac);

void opcion_mostrar_paciente();
Paciente *obtener_pac_archivo(int *n);


void menu_consulta();
void menu_consulta_opciones(void);

void opcion_realizar_consulta();
bool insertar_consulta_archivo(Consulta cons);

void opcion_mostrar_consulta();
Consulta *obtener_cons_archivo(int *n);


void menu_receta();
void menu_receta_opciones(void);

bool insertar_receta_archivo(Receta rec);

void opcion_mostrar_receta();
Receta *obtener_rec_archivo(int *n);


void menu_historial();
void menu_historial_opciones(void);

void opcion_mostrar_historial();
Historial *obtener_his_archivo(int *n);

int obtener_edad(Paciente pac);


void menu_cita();
void menu_cita_opciones();

void opcion_crear_archivo(FILE *archivoCita, char nombreArchivo[20]);

void opcion_agregar_cita();
bool insertar_cita_archivo(Cita cit);
void existe_cita(bool &existe, int codigoCit, Cita *cit);
bool doctor_libre(char Especialidad[25],Fecha fCita, Hora hCita);
void existe_historial(bool existe, int DNI,Historial *hist); // posible eliminacion
bool existe_especialidad(char Especialidad[25]);

void opcion_mostrar_cita();
Cita *obtener_array_cita(int *n);


void menu_reportes();
void menu_reportes_opciones();

void opcion_especialidad_masolicitada();
void opcion_promedio_edad();
void opcion_promedio_edad_x_especialidad();


int obtener_entero();
int obtener_entero(int inf, int sup);
bool es_entero_valido(string str);
double obtener_flotante();
bool es_flotante_valido(string str);

bool fecha_rango_valido(Fecha fCita);
bool hora_rango_valido(Hora hCita);
bool fecha_valida(Fecha fCita,Hora hCita);

void limpiar_pantalla();
void pausar_pantalla();
void titulo_principal(void);


int main()
{	
	menu_principal();
	return 0;
}

void menu_principal() {
	void menu_principal_opciones();
	bool se_repite = true;
	int opcion;

	do {
		menu_principal_opciones();
		opcion = obtener_entero(1,8);

		switch (opcion) {
			case 1:
				menu_medico();
				break;
			case 2:
				menu_paciente();
				break;
			case 3:
				menu_cita();
				break;
			case 4:
				menu_consulta();
				break;
			case 5:
				menu_historial();
				break;
			case 6:
				menu_receta();
				break;
			case 7:
				menu_reportes();
				break;
			case 8:
				se_repite = false;
				break;
		}
	} while (se_repite);
}

void menu_principal_opciones(void) {
  limpiar_pantalla();
	titulo_principal();
	cout << "\n\t\t\t\tMENU PRINCIPAL\n";
	cout << "\n\t\t[1]. Medicos\n";
	cout << "\t\t[2]. Pacientes\n";
	cout << "\t\t[3]. Cita\n";
	cout << "\t\t[4]. Consulta\n";
	cout << "\t\t[5]. Historial Medico\n";
	cout << "\t\t[6]. Recetas\n";
	cout << "\t\t[7]. Reportes\n";
	cout << "\t\t[8]. Salir\n";
	cout << "\n\t\tIngrese una opcion: ";
}

void menu_cita() {
	bool se_repite = true;
	int opcion;
	FILE *aCita;
	char nombreArchivo[] = "citas.dat";

	do {
		menu_cita_opciones();
		opcion = obtener_entero(1,4);

		switch (opcion) {
			case 1:
				opcion_crear_archivo(aCita, nombreArchivo);
				break;
			case 2:
				opcion_agregar_cita();
				break;
			case 3:
				opcion_mostrar_cita();
				break;
			case 4:
				se_repite = false;
				break;
		}
	} while (se_repite);
}

void menu_cita_opciones() {
  limpiar_pantalla();
	titulo_principal();
	cout << "\n\t\t\t\tMENU CITAS\n";
	cout << "\n\t\t[1]. Crear archivo citas\n";
	cout << "\t\t[2]. Agregar cita\n";
	cout << "\t\t[3]. Mostrar citas\n";
	cout << "\t\t[4]. Volver al menu principal\n";
	cout << "\n\t\tIngrese una opcion: ";
}

void opcion_crear_archivo(FILE *archivoCita,char nombreArchivo[20]) {
	archivoCita = fopen(nombreArchivo,"wb");
	
	if(archivoCita == NULL)
	{
		limpiar_pantalla();
		titulo_principal();
		cout<<"\n\tEl archivo no se pudo crear."<<endl;
		pausar_pantalla();
	}
	else
	{
		limpiar_pantalla();
		titulo_principal();
		cout<<"\n\tEl archivo se creo correctamente. "<<endl;
		pausar_pantalla();
	}
}

void opcion_agregar_cita() {
	Cita cit;
	Cita* nuevaCita = new Cita();
	Paciente pac;
	int DNI,tipoSer,codigoCit,opcionTipoEsp,edad;
	Fecha fCita;
	Hora hCita;
	string respuesta;
	bool ninio = true,mujer = true,se_repite = true, existe;
	char med[30] = "Medicina General", ped[30] = "Pediatria", gin[30] = "Ginecologia";
	
	
	limpiar_pantalla();
	titulo_principal();
	cout << "\n\t\tCREAR NUEVA CITA\n";

	cout << "\tIngresa el Codigo de la cita: ";
	codigoCit = obtener_entero();
	existe_cita(existe, codigoCit, &cit);

	if(existe)
	{
		cout<<"\n\tEsta cita ya existe"<<endl;
	} else {
		if(primero==NULL){
			primero=nuevaCita;
			primero->siguiente=NULL;
			ultimo= primero;		 //SE UTILIZA LA ESTRUCTURA DE DATOS COLA, PARA SIMULAR A LAS COLAS DE PACIENTES QUE BUSCAN UNA CITA EN LA CLINICA
		}else{
			ultimo->siguiente = nuevaCita;
			nuevaCita->siguiente = NULL;
			ultimo=nuevaCita;	
		}
		cout << "\tIngresa el DNI del usuario: ";
		DNI = obtener_entero();
		existe_paciente(existe, DNI, &pac);

		if (existe){
			cit.codigoCit = codigoCit;
			cit.DNI = DNI;
			nuevaCita->codigoCit=codigoCit;
			nuevaCita->DNI=DNI;
			do {
				ninio = true,mujer = true;
				limpiar_pantalla();
				titulo_principal();
				cout << "\n\t\tCREAR NUEVA CITA\n";
				cout << "\tIngresa el Codigo de la cita: "<<codigoCit<<endl;
				cout << "\tIngresa el DNI del usuario: "<<DNI<<endl;

				cout<<"\n\tSeleccione la Especialidad: "<<endl;

				cout<<"\n\t1.- Medicina General."<<endl;
				cout<<"\t2.- Pediatria."<<endl;
				cout<<"\t3.- Ginecologia."<<endl;
				cout<<"\tDigite la opcion: ";

				opcionTipoEsp = obtener_entero(1,3);

				switch(opcionTipoEsp) {
					case 1:
						strcpy(cit.Especialidad,med);
						strcpy(nuevaCita->Especialidad,med);
						break;
					case 2:
						strcpy(cit.Especialidad,ped);
						strcpy(nuevaCita->Especialidad,ped);
						break;
					case 3:
						strcpy(cit.Especialidad,gin);
						strcpy(nuevaCita->Especialidad,gin);
						break;
				}

				if(!existe_especialidad(cit.Especialidad)) {
					cout<<"\n\tEspecialidad no disponible"<<endl;
					cout<<"\n\t";
					pausar_pantalla();
				} else {
					if(opcionTipoEsp == 2) {
						if(obtener_edad(pac) > 12) {
							cout<<"\n\tSolo los niños pueden acceder a Pediatria. "<<endl;
							cout<<"\n\t";
							pausar_pantalla();
							ninio = false;	
						}
					}	 
				}
			}while(!ninio || !mujer);

			if(existe_especialidad(cit.Especialidad)) {
				cout << "\n\tDigite la fecha de la cita: ";
				cout<<"\n\tDia: ";
				fCita.dia = obtener_entero();
				cout<<"\tMes: ";
				fCita.mes = obtener_entero();
				cout<<"\tAño: ";
				fCita.anio = obtener_entero();
				do {
					limpiar_pantalla();
					titulo_principal();
					cout << "\n\t\tCREAR NUEVA CITA\n";
					cout << "\tIngresa el Codigo de la cita: "<<codigoCit<<endl;
					cout << "\tIngresa el DNI del usuario: "<<DNI<<endl;

					cout<<"\n\tSeleccione la Especialidad: "<<endl;

					cout<<"\n\t1.- Medicina General."<<endl;
					cout<<"\t2.- Pediatria."<<endl;
					cout<<"\t3.- Ginecologia."<<endl;
					cout<<"\tDigite la opcion: "<<opcionTipoEsp<<endl;

					cout << "\n\tDigite la fecha de la cita: ";
					cout<<"\n\tDia: "<<fCita.dia;
					cout<<"\n\tMes: "<<fCita.mes;
					cout<<"\n\tAño: "<<fCita.anio;

					cout<< "\n\tDigite la hora de la cita: ";

					cout<<"\n\tHora: ";
					hCita.hora = obtener_entero();
					cout<<"\tMinutos: ";
					hCita.minutos = obtener_entero();

					cit.horaCita.minutos = hCita.minutos;
					cit.horaCita.hora = hCita.hora;
					cit.fechaCita.dia = fCita.dia;
					cit.fechaCita.mes = fCita.mes;
					cit.fechaCita.anio = fCita.anio;
					
					nuevaCita->horaCita.minutos = hCita.minutos;
					nuevaCita->horaCita.hora = hCita.hora;
					nuevaCita->fechaCita.dia = fCita.dia;
					nuevaCita->fechaCita.mes = fCita.mes;
					nuevaCita->fechaCita.anio = fCita.anio;

					if(!doctor_libre(cit.Especialidad,fCita,hCita)) {
						cout<<"\n\tEl doctor no esta disponible a esa hora, digite otra ";
						cout<<"\n\t";
						pausar_pantalla();
					}
				}while(!doctor_libre(cit.Especialidad,fCita,hCita));

				if(!fecha_valida(fCita,hCita) || !fecha_rango_valido(fCita) || !hora_rango_valido(hCita)) {
					cout << "\n\tLa fecha de la cita es incorrecta." << endl;	
					pausar_pantalla();
				} else if(insertar_cita_archivo(cit)) {
					cout << "\n\tLa cita fue creada satisfactoriamente" << endl;
					pausar_pantalla();
				} else {
					cout<< "\n\tLa cita no se pudo crear correctamente, intentelo mas tarde " << endl;
					pausar_pantalla();
				}
			}
		} else {
			cout << "\n\tEl paciente no existe" << endl;
			cout << "\tIntentelo nuevamente" << endl;
			pausar_pantalla();
		}
	}
}

bool insertar_cita_archivo(Cita cit) {
	FILE *archivo;
	bool insercion;

	archivo = fopen("citas.dat", "ab");

	if (archivo == NULL) {
		insercion = false;
	} else {
		fwrite(&cit, sizeof(cit), 1, archivo);
		insercion = true;
		fclose(archivo);
	}

	return insercion;
}

bool fecha_valida(Fecha fCita,Hora hCita)
{
	Fecha fActual;
	Hora hActual;
	bool fValida = true;
	time_t fechaActual = time(0);
	tm *Fecha = localtime(&fechaActual);
	
	fActual.anio = 1900 + Fecha->tm_year;
	fActual.mes = 1 + Fecha->tm_mon;
	fActual.dia = Fecha->tm_mday;
	hActual.hora = Fecha->tm_hour;
	hActual.minutos = Fecha->tm_min;
	
	if(fCita.anio < fActual.anio)
		fValida = false;
	else if(fCita.anio == fActual.anio)
	{
		if(fCita.mes < fActual.mes)
			fValida = false;
		else if(fCita.mes == fActual.mes)
		{
			if(fCita.dia < fActual.dia)
				fValida = false;
			else if(fCita.dia == fActual.dia)
			{
				if(hCita.hora < hActual.hora)
					fValida = false;
				else if(hCita.hora == hActual.hora)
				{
					if(hCita.minutos < hActual.minutos)
						fValida = false;
				}
			}
		}
	}
	
	return fValida;
}

Cita *obtener_array_cita(int *n) {
	FILE *archivo;
	Cita cita;
	Cita *citas;
	int i;

	archivo = fopen("citas.dat", "rb");

	if (archivo == NULL) {
		*n = 0;
		citas = NULL;
	} else {
		fseek(archivo, 0, SEEK_END);
		*n = ftell(archivo) / sizeof(Cita);
		citas = (Cita *)malloc((*n) * sizeof(Cita));
		fseek(archivo, 0, SEEK_SET);
		fread(&cita, sizeof(cita), 1, archivo);
		i = 0;
		while (!feof(archivo)) {
			citas[i] = cita;
			fread(&cita, sizeof(cita), 1, archivo);
			i++;
		}
		fclose(archivo);
	}
	return citas;
}

bool fecha_rango_valido(Fecha fCita)
{
	bool rango_valido = true;
	bool bisiesto;
	
	if((fCita.anio%4==0 && fCita.anio%100!=0) || (fCita.anio%4==0 && fCita.anio%100==0 && fCita.anio%400==0))
        bisiesto=true;
    else
        bisiesto=false;
        
    if(fCita.mes>0 && fCita.mes<=12)
    {
        if(fCita.mes==1 || fCita.mes==3 || fCita.mes==5 || fCita.mes==7 || fCita.mes==10 || fCita.mes==12)
        {
            if(fCita.dia<=0 || fCita.dia>31)
                rango_valido = false;
        }
    	
		if(fCita.mes==2)
		{
        	if(bisiesto)
            {
            	if(fCita.dia<=0 || fCita.dia>29)
                	rango_valido = false;
            }	
            
            if(!bisiesto)
            {
        		if(fCita.dia<=0 || fCita.dia>28)
                	rango_valido = false;
            }
    	}
    	
		if(fCita.mes==4 || fCita.mes==6 || fCita.mes==8 || fCita.mes==9 || fCita.mes==11)
    	{
        	if(fCita.dia<=0 || fCita.dia>30)
                rango_valido = false;
		}
    }else
        rango_valido = false;
        
	return rango_valido;
}

bool hora_rango_valido(Hora hCita)
{
	bool rango_valido = true;
	
	if(hCita.hora > 24 || hCita.hora < 0 || hCita.minutos > 60 || hCita.minutos < 0)
		rango_valido = false;
		
	return rango_valido;
}

void existe_cita(bool &existe, int codigoCit, Cita *cit) {
	FILE *archivo;

	archivo = fopen("citas.dat", "rb");

	if (!(archivo == NULL)) {
		fread(&(*cit), sizeof(*cit), 1, archivo);
		while (!feof(archivo)) {
			if ((*cit).codigoCit == codigoCit) {
				existe = true;
				break;
			}
			fread(&(*cit), sizeof(*cit), 1, archivo);
		}
		fclose(archivo);
	}
	
}

void existe_historial(bool &existe, int codigo_historial, Historial *hist) {
	FILE *archivo;

	archivo = fopen("historial.dat", "rb");

	if (!(archivo == NULL)) {
		fread(&(*hist), sizeof(*hist), 1, archivo);
		while (!feof(archivo)) {
			if ((*hist).codigoHist == codigo_historial) {
				existe = true;
				break;
			}
			fread(&(*hist), sizeof(*hist), 1, archivo);
		}
		fclose(archivo);
	}
	
}

bool doctor_libre(char Especialidad[30],Fecha fCita,Hora hCita)
{
	bool doctorLibre = true;
	int minsCit,minsCitas,n;
	minsCit = hCita.hora*60 + hCita.minutos;
	Cita *citas;
	
	citas = obtener_array_cita(&n);
	
	for(int i=0;i<n;i++)
	{
		minsCitas = citas[i].horaCita.hora * 60 + citas[i].horaCita.minutos;
		if(strcmp(citas[i].Especialidad,Especialidad) == 0)
		{
			if(citas[i].fechaCita.anio == fCita.anio && citas[i].fechaCita.mes == fCita.mes && citas[i].fechaCita.dia == fCita.dia)
			{	
				if(minsCit >= minsCitas && minsCit <= minsCitas + 60)
					doctorLibre = false;
			}
		}
	}
	return doctorLibre;
}

bool existe_especialidad(char Especialidad[25])
{
	bool existe_esp = false;
	Medico *med;
	int n;
	
	med = obtener_stu_archivo(&n);
	
	for(int i=0;i<n;i++)
	{
		if(strcmp(med[i].especialidad,Especialidad)==0)
			existe_esp = true;
	}

	return existe_esp;
}
void opcion_mostrar_cita(){
	
	Cita *citas;
	int nro_citas;
	stringstream ss;
	string fecha_completa;
	limpiar_pantalla();
	titulo_principal();
	citas = obtener_array_cita(&nro_citas);

	if (nro_citas == 0) {
		cout << "\n\tEl archivo esta vacio" << endl;
		pausar_pantalla();
	} else {
		cout << "\n\t\t\t\tCITAS REGISTRADAS\n";
		cout << "  " << setw(5) << setiosflags(ios::left) << "Cod";
		cout << setw(10) << setiosflags(ios::left) << "DNI";
		cout << setw(18) << setiosflags(ios::left) << "Especialidad";
		cout << setw(18) << setiosflags(ios::left) << "Fecha" << endl;
		for (int i = 0; i < nro_citas; i++){
			ss.str("");
			ss << setw(2) << setfill('0') << citas[i].fechaCita.dia << "-"
				 << setw(2) << setfill('0') << citas[i].fechaCita.mes << "-"
				 << setw(4) << citas[i].fechaCita.anio << " "
				 << setw(2) << setfill('0') << citas[i].horaCita.hora << ":"
				 << setw(2) << setfill('0') << citas[i].horaCita.minutos;
			fecha_completa = ss.str();
			cout << "  " << setw(5) << setiosflags(ios::left) << citas[i].codigoCit;
			cout << setw(10) << setiosflags(ios::left) << citas[i].DNI;
			cout << setw(18) << setiosflags(ios::left) << citas[i].Especialidad;
			cout << setw(18) << setiosflags(ios::left) << fecha_completa << endl;
		}
		pausar_pantalla();
	}
}

void menu_medico() {
	bool se_repite = true;
	int opcion;
	char med[20]="datosDeMedico.dat";
	FILE* archivo; 
	titulo_principal();
	do{
		menu_medico_opciones();
		opcion=obtener_entero(1,4);
		switch(opcion){
			case 1:
				opcion_crear_archivo(archivo,med);
				break;
			case 2:
				opcion_crear_medico();
				break;
			case 3: 
				opcion_mostrar_medico();
				break;
			case 4:
				se_repite = false;
				break;
		}
	}while(se_repite);
	
	cout << "\n\t\t\t\tMENU MEDICO\n";
	menu_medico_opciones();
	
}

void menu_medico_opciones(){
	
	limpiar_pantalla();
	titulo_principal();
	cout << "\n\t\t\t\tMENU MEDICOS\n";
	cout << "\n\t\t[1]. Crear archivo medico";
	cout << "\n\t\t[2]. Agregar medico";
	cout << "\n\t\t[3]. Mostrar medicos";
	cout << "\n\t\t[4]. Volver al menu principal\n";
	cout << "\n\t\tIngrese una opcion: ";
	
}

void opcion_crear_medico(){
	bool se_repite=true, existe;
	Medico user;
	int tipo,DNI,Telefono,Sueldo;
	string nombre,aPaterno,aMaterno,correo,centro,tipoEspecialidad,contra,opc;

	limpiar_pantalla();
	titulo_principal();
	cout << "\n\t\tingresar NUEVO MEDICO\n";
	cout << "\n\tIngresa el DNI del medico: ";
	DNI=obtener_entero();
	existe_medico(existe, DNI, &user);
	if(!existe) {
		user.DNI=DNI;
		cout << "\tIngresa el Nombre del medico: ";
		getline(cin,nombre);
		strcpy(user.nombre,nombre.c_str());
		cout << "\tIngresa el Apellido Paterno del medico: ";
		getline(cin,aPaterno);
		strcpy(user.apellidoP,aPaterno.c_str());
		cout << "\tIngresa el Apellido Materno del medico: ";
		getline(cin,aMaterno);
		strcpy(user.apellidoM,aMaterno.c_str());
		cout << "\tIngresa el Numero telefonico del medico: ";
		Telefono=obtener_entero();
		user.telefono=Telefono;
		cout << "\tIngresa el Centro de estudios del medico: ";
		getline(cin,centro);
		strcpy(user.centroDeEstudio,centro.c_str());
		cout << "\t\t\t\tIngresa la especialidad del Medico: \n";
		cout << "\n\t\tMedicina General.....[1]\n";
		cout << "\t\tPediatria............[2]\n";
		cout << "\t\tGinecologia.........[3]\n";
		cout<<"\n\t\tDigite opcion: ";
		tipo=obtener_entero(1,3);
		switch(tipo){
			case 1:
				tipoEspecialidad="Medicina General";
				strcpy(user.especialidad,tipoEspecialidad.c_str());
				break;
			case 2:
				tipoEspecialidad="Pediatria";
				strcpy(user.especialidad,tipoEspecialidad.c_str());
				break;
			case 3:
				tipoEspecialidad="Ginecologia";
				strcpy(user.especialidad,tipoEspecialidad.c_str());
				break;
		}
	
		if(insertar_medico_archivo(user)) {
			cout << "\n\t\t\t\t\tEl Medico fue creado con exito";
			pausar_pantalla();
		} else {
			cout << "\n\tOcurrio un error al intentar crear el Medico" << endl;
			cout << "\tIntentelo nuevamente" << endl;
			pausar_pantalla();
		}
	} else {
		cout << "\n\tEl Medico con DNI " << DNI << " ya existe.\n";
		cout << "\t  No puede ingresar dos Medicos con el mismo DNI" << endl;
		pausar_pantalla();
	}
}

bool insertar_medico_archivo(Medico user){
	FILE *datosMedico;
	bool agregado;
	datosMedico = fopen("datosDeMedico.dat","ab");
	if(datosMedico==NULL){
		agregado=false;	
	}else{
		fwrite(&user,sizeof(user),1,datosMedico);
		agregado=true;
		fclose(datosMedico);
	}
	return agregado;
}
void existe_medico(bool &existe, int DNI,Medico *user){
	FILE* datosMedico;
	
	datosMedico=fopen("datosDeMedico.dat","rb");
	if(!(datosMedico==NULL)){
		fread(&(*user),sizeof(*user),1,datosMedico);
		while(!feof(datosMedico)){
			if((*user).DNI==DNI){
				existe=true;
				break;
			}
			fread(&(*user),sizeof(*user),1,datosMedico);
		}
		fclose(datosMedico);
	}
}
void opcion_mostrar_medico(){
	
	Medico *medicos;
	int nro_medicos;
  string nombre_completo;

	limpiar_pantalla();
	titulo_principal();
	medicos = obtener_stu_archivo(&nro_medicos);

	if (nro_medicos == 0) {
		cout << "\n\tEl archivo esta vacio" << endl;
		pausar_pantalla();
	} else {

		cout << "\n\t\t\t\tMEDICOS REGISTRADOS\n";
    cout << "  " << setw(35) << setiosflags(ios::left) << "Nombre"
         << setw(18) << setiosflags(ios::left) << "Especialidad ";
    cout << setw(10) << setiosflags(ios::left) << "DNI ";
    cout << setw(12) << setiosflags(ios::left) << "Telefono";
    cout << setw(20) << setiosflags(ios::left) << "Centro de estudios " << endl;
		for (int i = 0; i < nro_medicos; i++) {
			nombre_completo = string(medicos[i].nombre) + " " + string(medicos[i].apellidoP) + " " + string(medicos[i].apellidoM);
			cout << "  " << setw(35) << setiosflags(ios::left) << nombre_completo;
			cout << setw(18) << setiosflags(ios::left) << medicos[i].especialidad;
			cout << setw(10) << setiosflags(ios::left) << medicos[i].DNI;
			cout << setw(12) << setiosflags(ios::left) << medicos[i].telefono;
			cout << setw(20) << setiosflags(ios::left) << medicos[i].centroDeEstudio << endl;
		}
		pausar_pantalla();
	}
}
Medico *obtener_stu_archivo(int *n) {
	
	FILE *archivo;
	Medico medico;
	Medico *medicos;
	int i;

	archivo = fopen("datosDeMedico.dat", "rb");

	if (archivo == NULL) {
		*n = 0;
		medicos = NULL;
	} else {
		fseek(archivo, 0, SEEK_END);
		*n = ftell(archivo) / sizeof(Medico);
		medicos = (Medico *)malloc((*n) * sizeof(Medico));
		fseek(archivo, 0, SEEK_SET);
		fread(&medico, sizeof(medico), 1, archivo);
		i = 0;
		while (!feof(archivo)) {
			medicos[i] = medico;
			fread(&medico, sizeof(medico), 1, archivo);
			i++;
		}
		fclose(archivo);
	}
	return medicos;
}

bool modificar_archivo_medico(Medico user) {
	
	FILE *archivo;
	bool modificado;
	Medico medico;

	archivo = fopen("datosDeMedico.dat", "rb+");

	if (!(archivo == NULL)) {
		modificado = false;
		fread(&medico, sizeof(medico), 1, archivo);
		while (!feof(archivo)) {
			if (medico.DNI == user.DNI) {
				fseek(archivo, ftell(archivo) - sizeof(user), SEEK_SET);
				fwrite(&user, sizeof(user), 1, archivo);
				modificado = true;
				break;
			}
			fread(&medico, sizeof(medico), 1, archivo);
		}
		fclose(archivo);
	}
	return modificado;
}

void opcion_mostrar_historial() {
	bool existe;
	Paciente pac;
	Cita *cit;
	Consulta *cons;
	
	int dni,num_cit,num_cons;
	
	cit = obtener_array_cita(&num_cit);
	cons = obtener_cons_archivo(&num_cons);
	
	limpiar_pantalla();
	titulo_principal();
	
	cout<<"\n\tDigite el numero de DNI del paciente: ";
	dni = obtener_entero();
	existe_paciente(existe, dni, &pac);
	
	if(existe)
	{
		cout<<"\n\tNombres: "<<pac.Nombres<<endl;
		cout<<"\tApellido Paterno: "<<pac.Apellido_Paterno<<endl;
		cout<<"\tApellido Materno: "<<pac.Apellido_Materno<<endl;
		cout<<"\tEdad: "<<obtener_edad(pac)<<endl;
		cout<<"\tProblemas medicos: "<<pac.Problemas_Medicos<<endl;
		
		
		for(int i=0;i<num_cit;i++)
		{
			if(cit[i].DNI==pac.DNI)
			{
				cout<<"\n\tCITA "<<endl;
				cout<<"\tEspecialidad: "<<cit[i].Especialidad<<endl;
				cout<<"\tFecha: "<<cit[i].fechaCita.anio<<"/"<<cit[i].fechaCita.mes<<"/"<<cit[i].fechaCita.dia<<endl;
				cout<<"\tHora: "<<cit[i].horaCita.hora<<":"<<cit[i].horaCita.minutos<<endl;
				
				
			}
		}
		
		for(int j=0;j<num_cons;j++)
		{
			if(cons[j].codigoHist==pac.DNI)
			{
				cout<<"\n\tCONSULTA"<<endl;
				cout<<"\tDiagnostico: "<<cons[j].diagnostico<<endl;
				cout<<"\tSignos: "<<cons[j].signos<<endl;
				cout<<"\tSintomas: "<<cons[j].sintomas<<endl;
				cout<<"\tResultados: "<<cons[j].resultados<<endl;
				
			}
		}
		
	}else
	{
		cout<<"\n\tEl paciente no esta registrado"<<endl;
		pausar_pantalla();
	}
	
	pausar_pantalla();
}

int obtener_edad(Paciente pac)
{
	Fecha fActual;
	Hora hActual;
	int edad;
	time_t fechaActual = time(0);
	tm *Fecha = localtime(&fechaActual);
	
	fActual.anio = 1900 + Fecha->tm_year;
	fActual.mes = 1 + Fecha->tm_mon;
	fActual.dia = Fecha->tm_mday;
	hActual.hora = Fecha->tm_hour;
	hActual.minutos = Fecha->tm_min;
	
	edad = fActual.anio - pac.Fecha_Nac.anio - 1;
	
	if(fActual.mes>=pac.Fecha_Nac.mes && fActual.dia >= pac.Fecha_Nac.dia)
		edad++;
		
	return edad;
}

bool insertar_historial_archivo(Historial hist) {
	
	FILE *archivo;
	bool insercion;

	archivo = fopen("historial.dat", "ab");

	if (archivo == NULL) {
		insercion = false;
	} else {
		fwrite(&hist, sizeof(hist), 1, archivo);
		insercion = true;
		fclose(archivo);
	}
	return insercion;
}

Historial *obtener_his_archivo(int *n) {
	
	FILE *archivo;
	Historial historial;
	Historial *historiales;
	int i;

	archivo = fopen("historial.dat", "rb");

	if (archivo == NULL) {
		*n = 0;
		historiales = NULL;
	} else {
		fseek(archivo, 0, SEEK_END);
		*n = ftell(archivo) / sizeof(Historial);
		historiales = (Historial *)malloc((*n) * sizeof(Historial));
		fseek(archivo, 0, SEEK_SET);
		fread(&historial, sizeof(historial), 1, archivo);
		i = 0;
		while (!feof(archivo)) {
			historiales[i] = historial;
			fread(&historial, sizeof(historial), 1, archivo);
			i++;
		}
		fclose(archivo);
	}
	return historiales;
}

void menu_historial_opciones(void) {

  limpiar_pantalla();
	titulo_principal();
	cout << "\n\t\t\t\tMENU HISTORIAL MEDICO\n";
	cout << "\n\t\t[1]. Mostrar historial medico\n";
	cout << "\t\t[2]. Volver al menu principal\n";
	cout << "\n\t\tIngrese una opcion: ";
}
void menu_historial() {
	
	bool repetir = true;
	int opcion;

	do {
		menu_historial_opciones();
		opcion = obtener_entero();
		switch (opcion) {
			case 1:
				opcion_mostrar_historial();
				break;
			case 2:
				repetir = false;
				break;
		}
	} while (repetir);
}

void menu_paciente() {
	
	bool repetir = true;
	FILE* archivo;
	char paciente[13]="paciente.dat";
	int opcion;

	do {
		menu_paciente_opciones();
		opcion = obtener_entero();
		switch (opcion) {
			case 1:
				opcion_crear_archivo(archivo, paciente);
				break;
			case 2:
				opcion_crear_paciente();
				break;
			case 3:
				opcion_mostrar_paciente();
				break;
			case 4:
				repetir = false;
				break;
		}
	} while (repetir);
}

void menu_paciente_opciones(void) {
	
  limpiar_pantalla();
	titulo_principal();
	cout << "\n\t\t\t\tMENU PACIENTES\n";
	cout << "\n\t\t[1]. Crear archivo paciente\n";
	cout << "\t\t[2]. Agregar paciente\n";
	cout << "\t\t[3]. Mostrar pacientes\n";
	cout << "\t\t[4]. Volver al menu principal\n";
	cout << "\n\t\tIngrese una opcion: ";
}

void opcion_crear_paciente(void){
	Paciente* paciente=new Paciente();
	Paciente pac;
	bool existe;
	string rspta,apelli1,apelli2,nombres,nacim,cita,problem;
	string hosp,aler,medi,estad1,segur1,gmail;
	bool repetir=true;
	int edad,genero,estado,seguro,dniPac,telef;
	string respuesta;
	Fecha fNac;
	limpiar_pantalla();
	titulo_principal();
	cout << "\n\t\tAGREGAR PACIENTE\n";
	cout<< "\tIngrese el DNI del paciente: ";
	dniPac=obtener_entero();
	existe_paciente(existe, dniPac, &pac);
	if (existe) {
		cout <<"\n\tEste paciente ya existe."<<endl;
		pausar_pantalla();
	} else {
		pac.DNI = dniPac;	
		cout << "\tApellido Paterno: ";
		getline(cin,apelli1);
		strcpy(pac.Apellido_Paterno,apelli1.c_str());
		cout << "\tApellido Materno: ";
		getline(cin,apelli2);
		strcpy(pac.Apellido_Materno,apelli2.c_str());
		cout<< "\tNombres: ";
		getline(cin,nombres);
		strcpy(pac.Nombres,nombres.c_str());
		cout<< "\tEstado Civil: ";
		cout<< "\n\t\tSoltero.....[1]";
		cout<< "\n\t\tCasado......[2]";
		cout<< "\n\t\tViudo.......[3]";
		cout<< "\n\t\tDivorciado..[4]";
		cout<< "\n\t\tDigite opcion: ";
		estado=obtener_entero(1,4);
		switch(estado){
			case 1:
				estad1="Soltero";
				strcpy(pac.Estado_Civil,estad1.c_str());
				break;
			case 2:
				estad1="Casado";
				strcpy(pac.Estado_Civil,estad1.c_str());
				break;
			case 3:
				estad1="Viudo";
				strcpy(pac.Estado_Civil,estad1.c_str());
				break;
			case 4:
				estad1="Divorciado";
				strcpy(pac.Estado_Civil,estad1.c_str());
				break;
		}
		cout<< "\tGenero: ";
		cout<< "\n\t\tFemenino.....[1]";
		cout<< "\n\t\tMasculino....[2]";
		cout<< "\n\t\tDigite opcion: ";
		genero=obtener_entero(1,2);

		switch(genero) {
			case 1: 
				pac.Genero = 'F';
				break;
			case 2:
				pac.Genero = 'M';
				break;
		}

		cout<< "\tFecha de Nacimiento: ";
		cout<<"\n\tDia: ";
		fNac.dia=obtener_entero(1,31);
		pac.Fecha_Nac.dia = fNac.dia;
		cout<<"\tMes: ";
		fNac.mes = obtener_entero(1,12);
		pac.Fecha_Nac.mes = fNac.mes;
		cout<<"\tAnio: ";
		fNac.anio = obtener_entero(1900,2100);
		pac.Fecha_Nac.anio = fNac.anio;
		fflush(stdin);

		cout<< "\tTelefono: ";
		telef=obtener_entero();
		pac.telefono=telef;
		cout<< "\tSeguro: ";
		cout<< "\n\t\tCuenta con Seguro......[1]";
		cout<< "\n\t\tNo cuenta con Seguro...[2]";
		cout<< "\n\t\tDigite opcion: ";

		seguro=obtener_entero(1,2);

		switch(seguro){
			case 1:
				segur1="Si";
				strcpy(pac.Seguro,segur1.c_str());
				break;
			case 2:
				segur1="No";
				strcpy(pac.Seguro,segur1.c_str());
				break;
		}

		cout<< "\tProblemas Medicos: ";
		getline(cin,problem);
		strcpy(pac.Problemas_Medicos,problem.c_str());

		if (insertar_paciente_archivo(pac)) {
			cout << "\n\tLos datos fueron agregados satisfactoriamente" << endl;
			pausar_pantalla();
		} else {
			cout << "\n\tExiste un error al intentar agregar los datos." << endl;
			cout << "\n\tIntentelo nuevamente." << endl;
			pausar_pantalla();
		}	
	}
}

void existe_paciente(bool &existe, int DNI, Paciente *pac) {
	FILE *archivo;
	

	archivo = fopen("paciente.dat", "rb");

	if (!(archivo == NULL)) {
		fread(&(*pac), sizeof(*pac), 1, archivo);
		while (!feof(archivo)) {
			if ((*pac).DNI == DNI) {
				existe = true;
				break;
			}
			fread(&(*pac), sizeof(*pac), 1, archivo);
		}
		fclose(archivo);
	}
}

bool insertar_paciente_archivo(Paciente pac) {
	
	FILE *archivo;
	bool insercion;

	archivo = fopen("paciente.dat", "ab");

	if (archivo == NULL) {
		insercion = false;
	} else {
		fwrite(&pac, sizeof(pac), 1, archivo);
		insercion = true;
		fclose(archivo);
	}
	return insercion;
}

void opcion_mostrar_paciente() {
	
	Paciente *pacientes;
	int num_pac;
	string nombre_completo, fecha_nacimiento;
  stringstream ss;

	limpiar_pantalla();
	titulo_principal();
	pacientes = obtener_pac_archivo(&num_pac);

	if (num_pac == 0) {
		cout << "\n\tEl archivo esta vacio" << endl;
		pausar_pantalla();
	} else {

		cout << "\n\t\t\t\tPACIENTES REGISTRADOS\n";
		cout << "  " << setw(10) << setiosflags(ios::left) << "DNI";
		cout << setw(35) << setiosflags(ios::left) << "Nombres";
		cout << setw(11) << setiosflags(ios::left) << "Est Civil";
		cout << setw(7) << setiosflags(ios::left) << "Genero";
    cout << setw(11) << setiosflags(ios::left) << "FNac";
		cout << setw(5) << setiosflags(ios::left) << "Edad";
		cout << setw(10) << setiosflags(ios::left) << "Telefono" << endl;
		for (int i = 0; i < num_pac; i++) {
			ss.str("");
			ss << setw(2) << setfill('0') << pacientes[i].Fecha_Nac.dia << "-"
				 << setw(2) << setfill('0') << pacientes[i].Fecha_Nac.mes << "-"
				 << setw(4) << pacientes[i].Fecha_Nac.anio;
			fecha_nacimiento = ss.str();
			nombre_completo = string(pacientes[i].Nombres) + " " + string(pacientes[i].Apellido_Paterno) + " ";
			nombre_completo = nombre_completo + string(pacientes[i].Apellido_Materno);
			cout << "  " << setw(10) << setiosflags(ios::left) << pacientes[i].DNI;
			cout << setw(35) << setiosflags(ios::left) << nombre_completo;
			cout << setw(11) << setiosflags(ios::left) << pacientes[i].Estado_Civil;
			cout << setw(7) << setiosflags(ios::left) << pacientes[i].Genero;
      cout << setw(11) << setiosflags(ios::left) << fecha_nacimiento;
			cout << setw(5) << setiosflags(ios::left) << obtener_edad(pacientes[i]);
			cout << setw(10) << setiosflags(ios::left) << pacientes[i].telefono << endl;
		}
		pausar_pantalla();
	}
}

Paciente *obtener_pac_archivo(int *n) {
	
	FILE *archivo;
	Paciente paciente;
	Paciente *pacientes;
	int i;

	archivo = fopen("paciente.dat", "rb");

	if (archivo == NULL) {
		*n = 0;
		pacientes = NULL;
	} else {
		fseek(archivo, 0, SEEK_END);
		*n = ftell(archivo) / sizeof(Paciente);
		pacientes = (Paciente *)malloc((*n) * sizeof(Paciente));
		fseek(archivo, 0, SEEK_SET);
		fread(&paciente, sizeof(paciente), 1, archivo);
		i = 0;
		while (!feof(archivo)) {
			pacientes[i] = paciente;
			fread(&paciente, sizeof(paciente), 1, archivo);
			i++;
		}
		fclose(archivo);
	}
	return pacientes;
}

void menu_consulta() {
	
	bool repetir = true;
	FILE* archivo;
	char consulta[20]="consulta.dat";
	int opcion;

	do {
		menu_consulta_opciones();
		opcion = obtener_entero(1,3);
		switch (opcion) {
			case 1:
				opcion_crear_archivo(archivo,consulta);
				break;
			case 2:
				opcion_realizar_consulta();
				break;
			case 3:
				repetir = false;
				break;
		}
	} while (repetir);
}

void menu_consulta_opciones(void) {

	limpiar_pantalla();
	titulo_principal();
	cout << "\n\t\t\t\tMENU CONSULTA\n";
	cout << "\n\t\t[1]. Crear archivo consulta\n";
	cout << "\t\t[2]. Realizar consulta\n";
	cout << "\t\t[3]. Volver al menu principal\n";
	cout << "\n\t\tIngrese una opcion: ";
}

void opcion_realizar_consulta(void){
	
	int codigoCit;
	bool repetir, existe;
	string signos,sintomas,resultados,diagnostico,medicamentos,instrucciones,respuesta;
	Cita cit;
	Consulta cons;
	Receta rec;
	
	limpiar_pantalla();
	titulo_principal();
	cout << "\n\t\tREALIZAR CONSULTA\n";
	cout<< "\tIngrese el codigo de la cita: ";
	codigoCit=obtener_entero();
	existe_cita(existe, codigoCit, &cit);

	if (!existe) {
		cout <<"\n\tNo ha sacado cita aun."<<endl;
	} else {

		cons.codigoHist = cit.DNI;

		cout << "\tIngrese los signos: ";
		getline(cin,signos);
		strcpy(cons.signos,signos.c_str());

		cout << "\tIngrese los sintomas: ";
		getline(cin,sintomas);
		strcpy(cons.sintomas,sintomas.c_str());

		cout<< "\tIngrese los resultados: ";
		getline(cin,resultados);
		strcpy(cons.resultados,resultados.c_str());

		cout<< "\tIngrese el diagnostico: ";
		getline(cin,diagnostico);
		strcpy(cons.diagnostico,diagnostico.c_str());

		if (insertar_consulta_archivo(cons)) {
			cout << "\n\tLa consulta fue registrada satisfactoriamente." << endl;
			pausar_pantalla();
		} else {
			cout << "\n\tExiste un error al intentar registrar la consulta." << endl;
			cout << "\n\tIntentelo nuevamente." << endl;
			pausar_pantalla();
		}	

		cout<<"\n\tRECETA: ";

		rec.codigoCit = codigoCit;

		cout << "\n\tIngrese los medicamentos: ";
		getline(cin,medicamentos);
		strcpy(rec.medicamentos,medicamentos.c_str());

		cout << "\tIngrese las instrucciones: ";
		getline(cin,instrucciones);
		strcpy(rec.instrucciones,instrucciones.c_str());

		if (insertar_receta_archivo(rec)) {
			cout << "\n\tLa receta fue registrada satisfactoriamente." << endl;
			pausar_pantalla();
		} else {
			cout << "\n\tExiste un error al intentar registrar la receta." << endl;
			cout << "\n\tIntentelo nuevamente." << endl;
			pausar_pantalla();
		}
	}
}

bool insertar_consulta_archivo(Consulta cons) {
	
	FILE *archivo;
	bool insercion;

	archivo = fopen("consulta.dat", "ab");

	if (archivo == NULL) {
		insercion = false;
	} else {
		fwrite(&cons, sizeof(cons), 1, archivo);
		insercion = true;
		fclose(archivo);
	}
	return insercion;
}

Consulta *obtener_cons_archivo(int *n) {
	
	FILE *archivo;
	Consulta consulta;
	Consulta *consultas;
	int i;

	archivo = fopen("consulta.dat", "rb");

	if (archivo == NULL) {
		*n = 0;
		consultas = NULL;
	} else {
		fseek(archivo, 0, SEEK_END);
		*n = ftell(archivo) / sizeof(Consulta);
		consultas = (Consulta *)malloc((*n) * sizeof(Consulta));
		fseek(archivo, 0, SEEK_SET);
		fread(&consulta, sizeof(consulta), 1, archivo);
		i = 0;
		while (!feof(archivo)) {
			consultas[i] = consulta;
			fread(&consulta, sizeof(consulta), 1, archivo);
			i++;
		}
		fclose(archivo);
	}
	return consultas;
}


void menu_receta() {
	bool repetir = true;
	FILE* archivo;
	char receta[20]="receta.dat";
	int opcion;

	do {
		menu_receta_opciones();
		opcion = obtener_entero(1,3);
		switch (opcion) {					
			case 1:
				opcion_crear_archivo(archivo, receta);
				break;
			case 2:
				opcion_mostrar_receta();
				break;
			case 3:
				repetir = false;
				break;
		}
	} while (repetir);
}

void menu_receta_opciones(void) {
  limpiar_pantalla();
	titulo_principal();
	cout << "\n\t\t\t\tMENU RECETA\n";
	cout << "\n\t\t[1]. Crear archivo receta\n";
	cout << "\t\t[2]. Mostrar recetas\n";
	cout << "\t\t[3]. Volver al menu principal\n";
	cout << "\n\t\tIngrese una opcion: ";
}


bool insertar_receta_archivo(Receta rec) {
	FILE *archivo;
	bool insercion;

	archivo = fopen("receta.dat", "ab");

	if (archivo == NULL) {
		insercion = false;
	} else {
		fwrite(&rec, sizeof(rec), 1, archivo);
		insercion = true;
		fclose(archivo);
	}
	return insercion;
}

Receta *obtener_rec_archivo(int *n) {
	
	FILE *archivo;
	Receta receta;
	Receta *recetas;
	int i;

	archivo = fopen("receta.dat", "rb");

	if (archivo == NULL) {
		*n = 0;
		recetas = NULL;
	} else {
		fseek(archivo, 0, SEEK_END);
		*n = ftell(archivo) / sizeof(Receta);
		recetas = (Receta *)malloc((*n) * sizeof(Receta));
		fseek(archivo, 0, SEEK_SET);
		fread(&receta, sizeof(receta), 1, archivo);
		i = 0;
		while (!feof(archivo)) {
			recetas[i] = receta;
			fread(&receta, sizeof(receta), 1, archivo);
			i++;
		}
		fclose(archivo);
	}
	return recetas;
}

void opcion_mostrar_receta() {
	Receta *recetas;
	int num_rec;

  limpiar_pantalla();
	titulo_principal();
	recetas = obtener_rec_archivo(&num_rec);

	if (num_rec == 0) {
		cout << "\n\tEl archivo esta vacio" << endl;
		pausar_pantalla();
	} else {

		cout << "\n\t\t\t\tRECETAS REGISTRADAS\n";
		cout << "\n\t   ------------------------------------------------------------\n";
		for (int i = 0; i < num_rec; i++) {
				
				cout << "\t\tCodigo de cita: "<< recetas[i].codigoCit<< endl;
				cout << "\n\t\tMedicamentos: ";
				cout  << "\n\t\t" << recetas[i].medicamentos<< endl;
				cout << "\n\t\tInstrucciones: ";
				cout  << "\n\t\t" << recetas[i].instrucciones<< endl;

			cout << "\n\t   ------------------------------------------------------------\n";
		}
		pausar_pantalla();
	}
}

void menu_reportes() { 
	
	void menu_principal_opciones();
	bool se_repite = true;
	int opcion;

	do {
		menu_reportes_opciones();
		opcion = obtener_entero();

		switch (opcion) {
			case 1:
				opcion_especialidad_masolicitada();
				break;
			case 2:
				opcion_promedio_edad();
				break;
			case 3:
				opcion_promedio_edad_x_especialidad();
				break;
			case 4:
				se_repite = false;
				break;
		}
	} while (se_repite);
}

void menu_reportes_opciones(void) {
  limpiar_pantalla();
	titulo_principal();
	cout << "\n\t\t\t\tMENU SERVICIOS\n";
	cout << "\n\t\t[1]. Especialidad mas solicitada\n";
	cout << "\t\t[2]. Edad promedio\n";
	cout << "\t\t[3]. Edad promedio por especialidad\n";
	cout << "\t\t[4]. Salir\n";
	cout << "\n\t\tIngrese una opcion: ";
}

void opcion_especialidad_masolicitada(){
Cita *citas;
int nro_citas;

int c1=0, c2=0, c3=0;

char n1[30]="Medicina General", n2[30]="Pediatria", n3[30]="Ginecologia";


  limpiar_pantalla();
	titulo_principal();		
	cout << "\n\t\tESPECIALIDAD MAS SOLICITADA\n";
	
	citas = obtener_array_cita(&nro_citas);
	
	if (nro_citas == 0) {
		cout << "\n\t\tNo hay reporte de este modulo" << endl;
		pausar_pantalla();
	}
	else{
		
		for(int i=0; i<nro_citas; i++){
			if(strcmp(citas[i].Especialidad,n1)==0){
				c1=c1+1;
			}
		}
		for(int i=0; i<nro_citas; i++){
			if(strcmp(citas[i].Especialidad,n2)==0){
				c2=c2+1;
			}
		}
		for(int i=0; i<nro_citas; i++){
			if(strcmp(citas[i].Especialidad,n3)==0){
				c3=c3+1;
			}
		}
		
		if((c1==c2)&&(c1==c3)&&(c2==c3)){
		
			cout<<"\n\t"<<n1<<" :"<<c1<<endl;
			cout<<"\t"<<n2<<" :"<<c2<<endl;
			cout<<"\t"<<n3<<" :"<<c3<<endl;		
  			cout<<"\n\tTodas las especialidades son solicitadas por igual.";
  			cout<<endl;
 		}
 		else if((c1==c2)&&(c1>c3)&&(c2>c3)){
 			cout<<"\n\t"<<n1<<" :"<<c1<<endl;
			cout<<"\t"<<n2<<" :"<<c2<<endl;
			cout<<"\t"<<n3<<" :"<<c3<<endl;
 			cout<<"\n\tLas especialidades mas solicitadas son: "<<n1<<" y "<<n2;
 			cout<<endl;
		}
		else if((c1==c3)&&(c1>c2)&&(c3>c2)){
			cout<<"\n\t"<<n1<<" :"<<c1<<endl;
			cout<<"\t"<<n2<<" :"<<c2<<endl;
			cout<<"\t"<<n3<<" :"<<c3<<endl;
 			cout<<"\n\tLas especialidades mas solicitadas son: "<<n1<<" y "<<n3;
 			cout<<endl;
		}
		else if((c2==c3)&&(c2>c1)&&(c3>c1)){
			cout<<"\n\t"<<n1<<" :"<<c1<<endl;
			cout<<"\t"<<n2<<" :"<<c2<<endl;
			cout<<"\t"<<n3<<" :"<<c3<<endl;
 			cout<<"\n\tLas especialidades mas solicitadas son: "<<n2<<" y "<<n3;
 			cout<<endl;
		}
 		else if((c1>c2)&&(c1>c3)){
 			cout<<"\n\t"<<n1<<" :"<<c1<<endl;
			cout<<"\t"<<n2<<" :"<<c2<<endl;
			cout<<"\t"<<n3<<" :"<<c3<<endl;
  			cout<<"\n\tLa especialidad mas solicitada es: "<<n1;
  			cout<<endl;
 		}
 		else if((c2>c1)&&(c2>c3)){
 			cout<<"\n\t"<<n1<<" :"<<c1<<endl;
			cout<<"\t"<<n2<<" :"<<c2<<endl;
			cout<<"\t"<<n3<<" :"<<c3<<endl;
  			cout<<"\n\tLa especialidad mas solicitada es: "<<n2;
  			cout<<endl;
 		}
 		else{
 			cout<<"\n\t"<<n1<<" :"<<c1<<endl;
			cout<<"\t"<<n2<<" :"<<c2<<endl;
			cout<<"\t"<<n3<<" :"<<c3<<endl;
  			cout<<"\n\tLa especialidad mas solicitada es: "<<n3;
  			cout<<endl;
 		}	 					
	pausar_pantalla();	
	}
}

void opcion_promedio_edad(){
Paciente *paciente;
int num_pac;
int sumaEdad=0;
float promedio;

  limpiar_pantalla();
	titulo_principal();
	cout << "\n\t\tEDAD PROMEDIO\n";
	paciente = obtener_pac_archivo(&num_pac);
	
	if (num_pac == 0) {
		cout << "\n\t\tNo hay reporte de este modulo" << endl;
		pausar_pantalla();
	} 
	else{
		for (int i = 0; i < num_pac; i++) {
				sumaEdad=sumaEdad+obtener_edad(paciente[i]);
			}
			promedio=(sumaEdad)/num_pac;
			cout<<"\n\tLa edad promedio registrado de todos los pacientes es: "<<promedio;
			cout<<endl; 
		}	
	pausar_pantalla();
}

void opcion_promedio_edad_x_especialidad(){
Paciente *paciente;
Cita *cita;
int num_cit, num_pac;
float sumaEdad_med=0, sumaEdad_ped=0, sumaEdad_gin=0, m=0, p=0, g=0;
float promedioMed,promedioPed,promedioGin;
char med[30]="Medicina General",ped[30]="Pediatria",gin[30]="Ginecologia";

  limpiar_pantalla();
	titulo_principal();
	cout << "\n\t\tEDAD PROMEDIO\n";
	cita = obtener_array_cita(&num_cit);
	paciente = obtener_pac_archivo(&num_pac);
	
	if (num_pac == 0) {
		cout << "\n\t\tNo hay reporte de este modulo" << endl;
		pausar_pantalla();
	} 
	else{
		for (int i = 0; i < num_cit; i++){
			
			if(strcmp(cita[i].Especialidad,med)==0){
				for(int j=0; j<num_pac; j++){
					if(cita[i].DNI==paciente[j].DNI){					
						sumaEdad_med=sumaEdad_med+obtener_edad(paciente[j]);
						m++;
					}
				}	
			}
			if(strcmp(cita[i].Especialidad,ped)==0){
				for(int j=0;j< num_pac;j++){
					if(cita[i].DNI==paciente[j].DNI){					
						sumaEdad_ped=sumaEdad_ped+obtener_edad(paciente[j]);
						p++;
					}
				}	
			}
			if(strcmp(cita[i].Especialidad,gin)==0){
				for(int j=0;j< num_pac;j++){
					if(cita[i].DNI==paciente[j].DNI){					
						sumaEdad_gin=sumaEdad_gin+obtener_edad(paciente[j]);
						g++;
					}
				}	
			}		
		}
		
		if(m>0){
			promedioMed = sumaEdad_med/m;
		}
		if(p>0){
			promedioPed = sumaEdad_ped/p;
		}
		if(g>0){
			promedioGin = sumaEdad_gin/g;
		}
	
		if(m!=0){
			cout<<"\n\tLa edad promedio registrada de Medicina General es: "<<promedioMed<<endl;
		}
		else{
			cout<<"\n\tLa especialidad no fue solicitada.";
			cout<<endl;
		}
		
		if(p!=0){
			cout<<"\n\tLa edad promedio registrada de Pediatria es: "<<promedioPed<<endl;
		}
		else{
			cout<<"\n\tLa especialidad Pedatria no fue solicitada.";
			cout<<endl;
		}
		
		if(g!=0){
			cout<<"\n\tLa edad promedio registrada de Ginecologia es: "<<promedioGin<<endl;
		}
		else{
			cout<<"\n\tLa especialidad Ginecologia no fue solicitada.";
			cout<<endl;
		}
		cout<<endl; 
	}	
	pausar_pantalla();
}  

void titulo_principal(void) {
	cout << "\n             ======================================================================\n";
	cout << "\t\t\t\t         CLINICA FISI\n";
	cout << "             ======================================================================\n";
}

int obtener_entero() {
	bool no_es_entero = true;
	string valor;

	while (no_es_entero) {
		try {
			getline(cin, valor);
			if (!es_entero_valido(valor)) {
				throw valor;
			}
		} catch(...) {
			cout << " ";
		}
		no_es_entero = false;
	}
	return atoi(valor.c_str());
}

int obtener_entero(int inf, int sup) {
	bool no_aceptado = true;
	int numero;
	while (no_aceptado) {
		try {
			numero = obtener_entero();
			if (numero < inf || numero > sup) {
				throw numero;
			}
		}catch(int e) {
			cout << "\t\tPor favor, ingrese un numero entero entre " << inf << " y " << sup << ": ";
			continue;
		}
		no_aceptado = false;
	}
	return numero;
}

bool es_entero_valido(string str) {
	int i=0;
	bool valido = true;
	if (str.length() == 0) {
		valido = false;
	}
	
	while (valido && i < int(str.length())) {
		if (!isdigit(str.at(i))) {
			valido = false;
		}
		i++;
	}

	return valido;
}

double obtener_flotante(void) {
	bool no_es_flotante = true;
	string valor;

	while (no_es_flotante) {
		try {
			getline(cin, valor);
			if (!es_flotante_valido(valor)) {
				throw valor;
			}
		} catch(string e) {
			cout << "\t\tPor favor, ingrese un numero decimal valido: ";
			continue;
		}
		no_es_flotante = false;
	}
	return atof(valor.c_str());
}

bool es_flotante_valido(string str) {
	int inicio = 0;
	int i, n_puntos = 0;
	bool valido = true;
	bool signo = false;

	if (int(str.length()) == 0) {
		valido = false;
	}

	if (str.at(0) == '-' || str.at(0) == '+') {
		signo = true;
		inicio = 1;
	}

	if (str.at(1) == '.') {
		valido = false;
	}

	if (signo && int(str.length()) == 1) {
		valido = false;
	}

	i = inicio;
	while (valido && i < int(str.length())) {
		if (!isdigit(str.at(i))) {
			if (!(str.at(i) == '.')) {
				valido = false;
			}
		}

		if (str.at(i) == '.') {
			n_puntos++;
		}
		i++;
	}

	if (n_puntos > 1) {
		valido = false;
	}

	return valido;
}

void pausar_pantalla() {
	char caracter;
	cout << "\n\tPresiona 'Enter' para continuar...";
	while (caracter != '\n') {
		cin.get(caracter);
	}
}

void limpiar_pantalla(void) {
  system("cls");
}










