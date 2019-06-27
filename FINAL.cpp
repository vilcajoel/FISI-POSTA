#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <string.h>

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
	char centroDeEstudio[30];
	char especialidad[25];
};
struct Cita {
	int codigoCit;
	int DNI;
	char Especialidad[25];
	Fecha fechaCita;
	Hora horaCita;
};
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
void existe_medico(bool &existe,int codigo,Medico *user);
void opcion_mostrar_medico();
Medico *obtener_stu_archivo(int *n);
bool modificar_archivo_medico(Medico user);


void menu_paciente();
void menu_paciente_opciones(void);
void opcion_crear_paciente();
bool insertar_paciente_archivo(Paciente pac);
void existe_paciente(bool &existe,int DNI,Paciente *pac);
void opcion_mostrar_paciente();
Paciente *obtener_pac_archivo(int *n);


void menu_consulta();
void menu_consulta_opciones(void);
void opcion_realizar_consulta();
bool insertar_consulta_archivo(Consulta cons);
void existe_consulta(bool &existe,int DNI,Paciente *pac);
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
void opcion_crear_archivo(FILE *archivoCita,char nombreArchivo[20]);
void opcion_agregar_cita();
bool insertar_cita_archivo(Cita cit);
void existe_cita(bool &existe,int codigoCit, Cita *cit);
bool doctor_libre(char Especialidad[25],Fecha fCita, Hora hCita);
void existe_historial(bool &existe,int DNI,Historial *hist);
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


void pausar_pantalla();
void titulo_principal(void);


int main(){	
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
	system("cls");
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
				opcion_crear_archivo(aCita,nombreArchivo);
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
	system("cls");
	titulo_principal();
	cout << "\n\t\t\t\tMENU CITAS\n";
	cout << "\n\t\t[1]. Crear archivo citas\n";
	cout << "\t\t[2]. Agregar cita\n";
	cout << "\t\t[3]. Mostrar citas\n";
	cout << "\t\t[4]. Volver al menu principal\n";
	cout << "\n\t\tIngrese una opcion: ";
}
void opcion_crear_archivo(FILE *archivoCita,char nombreArchivo[20]){
	archivoCita = fopen(nombreArchivo,"wb");
	
	if(archivoCita == NULL)
	{
		system("cls");
		titulo_principal();
		cout<<"\n\tEl archivo no se pudo crear."<<endl;
		pausar_pantalla();
	}
	else
	{
		system("cls");
		titulo_principal();
		cout<<"\n\tEl archivo se creo correctamente. "<<endl;
		pausar_pantalla();
	}
}
void opcion_agregar_cita(){
	Cita cit;
	bool l,s,e;
	Paciente pac;
	int DNI,tipoSer,codigoCit,opcionTipoEsp,edad;
	Fecha fCita;
	Hora hCita;
	string respuesta;
	bool ninio = true,mujer = true,se_repite = true;
	char med[30] = "Medicina General", ped[30] = "Pediatria", gin[30] = "Ginecologia";
	existe_cita(l,codigoCit,&cit);
	
	do {
		system("cls");
		titulo_principal();
		cout << "\n\t\tCREAR NUEVA CITA\n";
		
		cout << "\tIngresa el Codigo de la cita: ";
		codigoCit = obtener_entero();
		
		if(l)
		{
			cout<<"\n\tEsta cita ya existe"<<endl;
		}else{
			
			cout << "\tIngresa el DNI del usuario: ";
			DNI = obtener_entero();
			existe_paciente(s,DNI,&pac);
			if (s) 
			{
		
			cit.codigoCit = codigoCit;
			cit.DNI = DNI;
			
			do {
				ninio = true,mujer = true;
				system("cls");
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
			
				switch(opcionTipoEsp)
				{
					case 1:
						strcpy(cit.Especialidad,med);
						break;
					case 2:
						strcpy(cit.Especialidad,ped);
						break;
					case 3:
						strcpy(cit.Especialidad,gin);
						break;
				}
			
				if(!(existe_especialidad(cit.Especialidad)))
				{
					cout<<"\n\tEspecialidad no disponible"<<endl;
					cout<<"\n\t";
					system("pause");
				}else
				{
											
				if(opcionTipoEsp == 2)
				{
					if(obtener_edad(pac) > 12)
					{
						cout<<"\n\tSolo los niños pueden acceder a Pediatria. "<<endl;
						cout<<"\n\t";
						system("pause");
						ninio = false;	
					}	
				}else if(opcionTipoEsp == 3)
				{
					if(pac.Genero != 'F')
					{
						cout<<"\n\tSolo las mujeres pueden acceder a Ginecologia. "<<endl;
						cout<<"\n\t";
						system("pause");
						mujer = false;
					}	
				} 
	
				}
			}while(!ninio || !mujer);
			
			if(existe_especialidad(cit.Especialidad));
			{			
				cout << "\n\tDigite la fecha de la cita: ";
			
				cout<<"\n\tDia: ";
				fCita.dia = obtener_entero();
				cout<<"\tMes: ";
				fCita.mes = obtener_entero();
				cout<<"\tAño: ";
				fCita.anio = obtener_entero();
			
				do{
					system("cls");
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
					fflush(stdin);
				
					if(!doctor_libre(cit.Especialidad,fCita,hCita))
					{	
						cout<<"\n\tEl doctor no esta disponible a esa hora, digite otra ";
						cout<<"\n\t";
						system("pause");
					}
			
				}while(!doctor_libre(cit.Especialidad,fCita,hCita));
			
				if(!fecha_valida(fCita,hCita) || !fecha_rango_valido(fCita) || !hora_rango_valido(hCita))
				{
					cout << "\n\tLa fecha de la cita es incorrecta." << endl;	
				}else if (insertar_cita_archivo(cit)) 
				{
					cout << "\n\tLa cita fue creada satisfactoriamente" << endl;
				}else
				{
					cout<< "\n\tLa cita no se pudo crear correctamente, intentelo mas tarde " << endl;
				}
			}	
		} else {
			cout << "\n\tEl paciente no existe" << endl;
			cout << "\tIntentelo nuevamente" << endl;
				}
		}
		
		cout << "\n\tDesea continuar? [S/n]: ";
		getline(cin, respuesta);
		
		if (!(respuesta.compare("s") == 0 || respuesta.compare("S") == 0))
			se_repite = false;
		else
			menu_principal();
		
	} while (se_repite);	
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
bool fecha_valida(Fecha fCita,Hora hCita){
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
bool fecha_rango_valido(Fecha fCita){
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
bool hora_rango_valido(Hora hCita){
	bool rango_valido = true;
	
	if(hCita.hora > 24 || hCita.hora < 0 || hCita.minutos > 60 || hCita.minutos < 0)
		rango_valido = false;
		
	return rango_valido;
}
void existe_cita(bool &existe,int codigoCit, Cita *cit) {
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
void existe_historial(bool &existe,int codigo_historial, Historial *hist) {
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
bool doctor_libre(char Especialidad[30],Fecha fCita,Hora hCita){
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
bool existe_especialidad(char Especialidad[25]){
	Medico *med;
	int n;
	bool existe_esp;
	med = obtener_stu_archivo(&n);
	
	for(int i=0;i<n;i++)
	{
		if(strcmp(med[i].especialidad,Especialidad)==0)
			existe_esp = true;
	}
	return existe_esp;


}
void opcion_mostrar_cita() {
	Cita *citas;
	int nro_citas;

	system("cls");
	titulo_principal();
	citas = obtener_array_cita(&nro_citas);

	if (nro_citas == 0) {
		cout << "\n\tEl archivo esta vacio" << endl;
		pausar_pantalla();
	} else {

		cout << "\n\t\t\t\tCITAS REGISTRADAS\n";
		cout << "\n\t   ------------------------------------------------------------\n";
		for (int i = 0; i < nro_citas; i++) {
				
				cout << "\t\tCodigo de la cita: " << citas[i].codigoCit << endl;
				cout << "\t\tDNI del paciente: " << citas[i].DNI << endl;
				cout << "\t\tEspecialidad: " << citas[i].Especialidad << endl;
				cout << "\t\tFecha de la cita: " << citas[i].fechaCita.dia << "/"<< citas[i].fechaCita.mes << "/" << citas[i].fechaCita.anio << endl;
				cout << "\t\tHora de la cita: "<<citas[i].horaCita.hora << ":" << citas[i].horaCita.minutos << endl;
			
			cout << "\n\t   ------------------------------------------------------------\n";
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
	
	system("cls");
	titulo_principal();
	cout << "\n\t\t\t\tMENU MEDICOS\n";
	cout << "\n\t\t[1]. Crear archivo medico";
	cout << "\n\t\t[2]. Agregar medico";
	cout << "\n\t\t[3]. Mostrar medicos";
	cout << "\n\t\t[4]. Volver al menu principal\n";
	cout << "\n\t\tIngrese una opcion: ";
	
}
void opcion_crear_medico(){
	bool se_repite=true,l;
	Medico user;
	int tipo,DNI,Telefono,Sueldo;
	string nombre,aPaterno,aMaterno,correo,centro,tipoEspecialidad,contra,opc;
	do{
		system("cls");
		titulo_principal();
		cout << "\n\t\tingresar NUEVO MEDICO\n";
		cout << "\n\tIngresa el DNI del medico: ";
		DNI=obtener_entero();
		existe_medico(l,DNI,&user);
		if(!l){
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
	
		if(insertar_medico_archivo(user)){
			cout << "\n\t\t\t\t\tEl Medico fue creado con exito";
		}else{
			cout << "\n\tOcurrio un error al intentar crear el Medico" << endl;
			cout << "\tIntentelo nuevamente" << endl;
		}
	}else{
		cout << "\n\tEl Medico con DNI " << DNI << " ya existe.\n";
		cout << "\t  No puede ingresar dos Medicos con el mismo DNI" << endl;
	}
		cout <<" ";
		cout << "\n\t\t\t\tDesea continuar? [S/n]: ";
		fflush(stdin);
		getline(cin,opc);
		if(!(opc.compare("S")==0 || opc.compare("s")==0)){
			se_repite=false;
		}

	menu_medico();
	
	}while(se_repite);
	
	menu_principal();
	
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
void existe_medico(bool &existe,int DNI,Medico *user){
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

	system("cls");
	titulo_principal();
	medicos = obtener_stu_archivo(&nro_medicos);

	if (nro_medicos == 0) {
		cout << "\n\tEl archivo esta vacio" << endl;
		pausar_pantalla();
	} else {

		cout << "\n\t\t\t\tMEDICOS REGISTRADOS\n";
		cout << "\n\t   ------------------------------------------------------------\n";
		for (int i = 0; i < nro_medicos; i++) {
				cout << "\t\t"<<medicos[i].nombre <<" "<< medicos[i].apellidoP <<" "<< medicos[i].apellidoM  << endl;
				cout << "\n\t\tEspecialidad: " << medicos[i].especialidad << endl;
				cout << "\t\tNro DNI: " << medicos[i].DNI << endl;
				cout << "\t\tNumero Telefonico: " << medicos[i].telefono << endl;
				cout << "\t\tCentro de estudio: " << medicos[i].centroDeEstudio << endl;
			
			cout << "\n\t   ------------------------------------------------------------\n";
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
	bool p;
	Paciente pac;
	Cita *cit;
	Consulta *cons;
	
	int dni,num_cit,num_cons;
	
	cit = obtener_array_cita(&num_cit);
	cons = obtener_cons_archivo(&num_cons);
	
	system("cls");
	titulo_principal();
	
	cout<<"\n\tDigite el numero de DNI del paciente: ";
	dni = obtener_entero();
	existe_paciente(p,dni,&pac);
	if(p)
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
int obtener_edad(Paciente pac){
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
	system("cls");
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
	char paciente[20]="paciente.dat";
	int opcion;

	do {
		menu_paciente_opciones();
		opcion = obtener_entero();
		switch (opcion) {
			case 1:
				opcion_crear_archivo(archivo,paciente);
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
	system("cls");
	titulo_principal();
	cout << "\n\t\t\t\tMENU PACIENTES\n";
	cout << "\n\t\t[1]. Crear archivo paciente\n";
	cout << "\t\t[2]. Agregar paciente\n";
	cout << "\t\t[3]. Mostrar pacientes\n";
	cout << "\t\t[4]. Volver al menu principal\n";
	cout << "\n\t\tIngrese una opcion: ";
}
void opcion_crear_paciente(void){
	Paciente pac;
	bool p;
	string rspta,apelli1,apelli2,nombres,nacim,cita,problem;
	string hosp,aler,medi,estad1,segur1,gmail;
	bool repetir=true;
	int edad,genero,estado,seguro,dniPac,telef;
	string respuesta;
	Fecha fNac;
	do {
		system("cls");
		titulo_principal();
		cout << "\n\t\tAGREGAR PACIENTE\n";
		cout<< "\tIngrese el DNI del paciente: ";
		dniPac=obtener_entero();
		existe_paciente(p,dniPac, &pac);
		if (p) {
			cout <<"\n\tEste paciente ya existe."<<endl;
		}else{
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
        switch(genero){
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
		fflush(stdin);
        cout<< "\tProblemas Medicos: ";
        getline(cin,problem);
        strcpy(pac.Problemas_Medicos,problem.c_str());
        fflush(stdin);

        if (insertar_paciente_archivo(pac)) {
				cout << "\n\tEl Historial fue creado satisfactoriamente" << endl;
			} else {
				cout << "\n\tExiste un error al intentar crear el historial." << endl;
				cout << "\n\tIntentelo nuevamente." << endl;
			}	
		}
		cout << "\n\tDesea continuar? [S/n]: ";
		getline(cin, respuesta);
		if (!(respuesta.compare("s") == 0 || respuesta.compare("S") == 0)) {
			repetir = false;
		}
		
		menu_paciente();
	} while (repetir); 
	
	menu_principal();   
}
void existe_paciente(bool &existe,int DNI, Paciente *pac) {
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

	system("cls");
	titulo_principal();
	pacientes = obtener_pac_archivo(&num_pac);

	if (num_pac == 0) {
		cout << "\n\tEl archivo esta vacio" << endl;
		pausar_pantalla();
	} else {

		cout << "\n\t\t\t\tPACIENTES REGISTRADOS\n";
		cout << "\n\t   ------------------------------------------------------------\n";
		for (int i = 0; i < num_pac; i++) {
				
				cout << "\t\tDNI: "<< pacientes[i].DNI<< endl;
				cout << "\t\tApellido Paterno: " << pacientes[i].Apellido_Paterno << endl;
				cout << "\t\tApellido Materno: " << pacientes[i].Apellido_Materno << endl;
				cout << "\t\tNombres: " << pacientes[i].Nombres << endl;
				cout << "\t\tEstado Civil: " << pacientes[i].Estado_Civil<< endl;
				cout << "\t\tGenero: " << pacientes[i].Genero << endl;
				cout << "\t\tFecha de Nacimiento: ";
				cout << "\n\t\tDia: "<<pacientes[i].Fecha_Nac.dia<<endl;
				cout << "\t\tMes: "<<pacientes[i].Fecha_Nac.mes<<endl;
				cout << "\t\tAnio: "<<pacientes[i].Fecha_Nac.anio<<endl;
				cout << "\t\tEdad: "<< obtener_edad(pacientes[i])<< endl;
				cout << "\t\tTelefono: "<< pacientes[i].telefono<<endl;
				cout << "\t\tSeguro: "<< pacientes[i].Seguro<<endl;
				cout << "\t\tProblemas Medicos: "<< pacientes[i].Problemas_Medicos<<endl;	

			cout << "\n\t   ------------------------------------------------------------\n";
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
	system("cls");
	titulo_principal();
	cout << "\n\t\t\t\tMENU CONSULTA\n";
	cout << "\n\t\t[1]. Crear archivo consulta\n";
	cout << "\t\t[2]. Realizar consulta\n";
	cout << "\t\t[3]. Volver al menu principal\n";
	cout << "\n\t\tIngrese una opcion: ";
}
void opcion_realizar_consulta(void){
	
	int codigoCit;
	bool repetir,l;
	string signos,sintomas,resultados,diagnostico,medicamentos,instrucciones,respuesta;
	Cita cit;
	Consulta cons;
	Receta rec;
	
	do {
		system("cls");
		titulo_principal();
		cout << "\n\t\tREALIZAR CONSULTA\n";
		cout<< "\tIngrese el codigo de la cita: ";
		codigoCit=obtener_entero();
		existe_cita(l,codigoCit, &cit);
		if (!l) {
			cout <<"\n\tNo ha sacado cita aun."<<endl;
		}else{
			
		cons.codigoHist = cit.DNI;
		
		cout << "\tIngrese los signos: ";
		getline(cin,signos);
		strcpy(cons.signos,signos.c_str());
		fflush(stdin);
		
		cout << "\tIngrese los sintomas: ";
		getline(cin,sintomas);
		strcpy(cons.sintomas,sintomas.c_str());
		fflush(stdin);
		
		cout<< "\tIngrese los resultados: ";
        getline(cin,resultados);
        strcpy(cons.resultados,resultados.c_str());
        fflush(stdin);
        
        cout<< "\tIngrese el diagnostico: ";
        getline(cin,diagnostico);
        strcpy(cons.diagnostico,diagnostico.c_str());
        fflush(stdin);

        if (insertar_consulta_archivo(cons)) {
				cout << "\n\tLa consulta fue registrada satisfactoriamente." << endl;
			} else {
				cout << "\n\tExiste un error al intentar registrar la consulta." << endl;
				cout << "\n\tIntentelo nuevamente." << endl;
			}	
		
		cout<<"\n\tRECETA: ";
		
		rec.codigoCit = codigoCit;
		
		cout << "\n\tIngrese los medicamentos: ";
		getline(cin,medicamentos);
		strcpy(rec.medicamentos,medicamentos.c_str());
		fflush(stdin);
		
		cout << "\tIngrese las instrucciones: ";
		getline(cin,instrucciones);
		strcpy(rec.instrucciones,instrucciones.c_str());
		fflush(stdin);

        if (insertar_receta_archivo(rec)) {
				cout << "\n\tLa receta fue registrada satisfactoriamente." << endl;
			} else {
				cout << "\n\tExiste un error al intentar registrar la receta." << endl;
				cout << "\n\tIntentelo nuevamente." << endl;
			}
		}
	
		cout << "\n\tDesea continuar? [S/n]: ";
		getline(cin, respuesta);
		if (!(respuesta.compare("s") == 0 || respuesta.compare("S") == 0)) {
			repetir = false;
		}
		
		menu_paciente();
	} while (repetir); 
	
	menu_principal();   
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
				opcion_crear_archivo(archivo,receta);
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
	system("cls");
	titulo_principal();
	cout << "\n\t\t\t\tMENU RECETA\n";
	cout << "\n\t\t[1]. Crear archivo receta\n";
	cout << "\t\t[2]. Mostrar recetas\n";
	cout << "\t\t[3]. Volver al menu principal\n";
	cout << "\n\t\tIngrese una opcion: ";
}
bool insertar_receta_archivo(Receta rec){
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

	system("cls");
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
	system("cls");
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


	system("cls");
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

	system("cls");
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

	system("cls");
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
	cout << "\n     ======================================================================\n";
	cout << "\t\t\t\t CLINICA FISI\n";
	cout << "     ======================================================================\n";
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






















