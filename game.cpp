#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<conio.h>
#include<time.h>
#include<iostream>
#include<math.h>
#define TAM 50
#define EQUIPOS 32
#define JUGADORES 23
using namespace std;
struct datos{
	char nombre[30];
	int codigo;
	char password[50];
	double cantidad;
	double monedas;
	int album[EQUIPOS][JUGADORES];
};
string equipos[]={
	"RUSIA","BRASIL","IRAN","JAPON","MEXICO","BELGICA",
		"COREA DEL SUR","ARABIA SAUDITA","INGLATERRA","ALEMANIA",
		"ESPANA","NIGERIA","COSTA RICA","EGIPTO","POLONIA","SERBIA",
		"ISLANDIA","FRANCIA","PORTUGAL","URUGUAY","COLOMBIA","ARGENTINA",
		"PANAMA","SENEGAL","MARRUECOS","TUNEZ","SUIZA","CROACIA","SUECIA",
		"DINAMARCA","AUSTRALIA","PERU"
};
int Recuperar(datos jugador[]);
void Grabar(datos jugador[],int registro);
void Inicializar(datos *jugador,int registro,int pos);
void Opcion1(datos *jugador,int pos);
void Opcion2(datos *jugador,int pos);
void Opcion3(datos *jugador,int pos);
void Opcion4(datos *jugador,int pos);
void Piedra(datos *jugador,int pos);
void Adivinar(datos *jugador,int pos);
void Operaciones(datos *jugador,int pos);
void Apostar(datos *jugador,int pos);
bool Confirmar(datos *jugador,int registro,int *pos);
void Ingresar(datos *jugador,int registro,int pos);
int Crear_Cuenta(datos *jugador,int registro);
void Mostrar(datos *jugador,int registro);
int Eliminar_Cuenta(datos *jugador,int registro,int pos);
void Cambiar_Password(datos *jugador,int registro,int pos);
void Menu(datos *jugador,int pos);
int Fibonacci(int n);
void Ranking(datos *jugador,int registro);
int main(){
	int opcion,pos=0;
	datos jugador[TAM];
	int registro=0;
	registro = Recuperar(jugador);
	while(true){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
		cout<<"======================="<<endl;
		cout<<" ALBUM 3 REYES VIRTUAL "<<endl;
		cout<<"======================="<<endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
		cout<<"[1].INICIAR SESION"<<endl;
		cout<<"[2].CREAR CUENTA"<<endl;
		cout<<"[3].MOSTRAR"<<endl;
		cout<<"[4].ELIMINAR CUENTA"<<endl;
		cout<<"[5].CAMBIAR PASSWORD"<<endl;
		cout<<"[6].SALIR"<<endl<<endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		cout<<"INGRESE OPCION = ";
		cin>>opcion;
		switch(opcion){
		case 1: Ingresar(jugador,registro,pos);
		break;
		case 2: registro = Crear_Cuenta(jugador,registro);
		break;
		case 3: Mostrar(jugador,registro);
		break;
		case 4: registro = Eliminar_Cuenta(jugador,registro,pos);
		break;
		case 5: Cambiar_Password(jugador,registro,pos);
		break;
		case 6: Grabar(jugador,registro);
		return true;
		break;
		default: cout<<"OPCION NO VALIDA ......"<<endl;
		}
		getch();
		system("cls");
	}
	return 0;
}
int Recuperar(datos jugador[]){
	datos aux;
	FILE *fichero;
	fichero=fopen("ficheros\\album.txt","rb");
	if(fichero==NULL){
		cout<<"Archivo no encontrado...";
		exit(1);
	}
	int i=0;
	fread(&aux,sizeof(datos),1,fichero);
	while(!feof(fichero)){
		strcpy(jugador[i].nombre,aux.nombre);
		jugador[i].codigo=aux.codigo;
		strcpy(jugador[i].password,aux.password);
		jugador[i].cantidad=aux.cantidad;
		jugador[i].monedas=aux.monedas;
		for(int j=0;j<32;j++){
			for(int k=0;k<23;k++){
				jugador[i].album[j][k]=aux.album[j][k];
			}
		}
		fread(&aux,sizeof(datos),1,fichero);
		i++;
	}
	fclose(fichero);
	return i;
}
void Grabar(datos jugador[],int registro){
	FILE *fichero;
	fichero=fopen("ficheros\\album.txt","wb");
	if(fichero==NULL){
		cout<<"Archivo no encontrado...";
		return;
	}
	for(int i=0;i<registro;i++)
	   fwrite(&jugador[i],sizeof(datos),1,fichero);
	fclose(fichero);
}
void Inicializar(datos *jugador,int registro){
	for(int i=0;i<32;i++){
		for(int j=0;j<23;j++){
			(jugador+registro)->album[i][j]=0;
		}
	}
	(jugador+registro)->cantidad=0;
	(jugador+registro)->monedas=1.50;
}
int Crear_Cuenta(datos *jugador,int registro){
	system("cls");
	getch();
	if(registro>=TAM){
		cout<<"No hay espacio en array"<<endl;
		return 1;
	}
	cout<<"================================="<<endl;
	cout<<"\tCREAR CUENTA "<<registro+1<<endl;
	cout<<"================================="<<endl;
	bool valor;
	do{
		valor=true;
		cout<<"INGRESAR CODIGO = ";
		cin>>(jugador+registro)->codigo;
		if(registro!=0){
			for(int i=0;i<registro;i++){
				if((jugador+registro)->codigo==(jugador+i)->codigo){
					valor=false;
				}
			}
		}
		if(valor==false){
			cout<<"CODIGO YA REGISTRADO"<<endl;
		}
	}while(!valor);
	cout<<"INGRESE PASSWORD = ";
	cin>>(jugador+registro)->password; fflush(stdin);
	cout<<"INGRESE SUS NOMBRES = ";
	cin.getline((jugador+registro)->nombre,30); fflush(stdin);
	Inicializar(jugador,registro);
	registro++;
	return registro;
}
bool Confirmar(datos *jugador,int registro,int *pos){
	bool cuenta=false;
	int entrada;
	if(registro==0){
		cout<<"============================================"<<endl;
		cout<<"         CREARSE ALMENOS UNA CUENTA        "<<endl;
		cout<<"============================================"<<endl;
		return false;
	}else{
		cout<<"INGRESE USUARIO = ";
		cin>>entrada;
		for(int i=0;i<registro;i++){
			if((jugador+i)->codigo==entrada){
				cuenta=true;
				*pos=i;
			}
		}
		if(cuenta){
			cout<<"INGRESE PASSWORD = ";
			char palabra[50]={'\0'};
			char tecla=getch();
			int k=0;
			while(tecla!=13){
				palabra[k]=tecla;
				cout<<"*";
				k++;
				tecla=getch();
			}
			if(strcmp(palabra,(jugador+*pos)->password)==0) return true;
			else {
				cout<<endl;
				cout<<"============================================"<<endl;
				cout<<"            PASSWORD INCORRECTO             "<<endl;
				cout<<"============================================"<<endl;
				return false;
			}
		}else{
			cout<<"============================================"<<endl;
			cout<<"              NO EXISTE CUENTA              "<<endl;
			cout<<"============================================"<<endl;
			return false;
		}
	}
}
void Ingresar(datos *jugador,int registro,int pos){
	system("cls");
	getch();
	if(Confirmar(jugador,registro,&pos)){
		Menu(jugador,pos);
	}
}
void Mostrar(datos *jugador,int registro){
	system("cls");
	getch();
	if(registro!=0){
		Ranking(jugador,registro);
		for(int i=0;i<registro;i++){
			cout<<"============================================"<<endl;
			cout<<"\t     CUENTA  = "<<(jugador+i)->codigo<<endl;
			cout<<"============================================"<<endl;
			cout<<"NOMBRES = "<<(jugador+i)->nombre<<endl;
			cout<<"FIGURAS PEGADAS = "<<(jugador+i)->cantidad<<endl;
			cout<<"FIGURAS RESTANTES = "<<736-(jugador+i)->cantidad<<endl;
			cout<<"RANKING = "<<i+1;
			cout<<endl;
		}
	}
	else{
		cout<<"============================================"<<endl;
		cout<<"        NO HAY CUENTAS PARA MOSTRAR         "<<endl;
		cout<<"============================================"<<endl;
	}
}
int Eliminar_Cuenta(datos *jugador,int registro,int pos){
	system("cls");
	getch();
	if(Confirmar(jugador,registro,&pos)){
		for(int i=pos;i<registro;i++){
			*(jugador+i)=*(jugador+i+1);
		}
		registro--;
	}
	return registro;
}
void Cambiar_Password(datos *jugador,int registro,int pos){
	system("cls");
	getch();
	if(Confirmar(jugador,registro,&pos)){
		char nueva[50]={'\0'};
		cout<<"\nINGRESE NUEVO PASSWORD = ";
		cin>>nueva;
		strcpy((jugador+pos)->password,nueva);
	}
}
void Menu(datos *jugador,int pos){
	char opcion;
	getch();
	system("cls");
	do{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
		cout<<"========================"<<endl;
		cout<<"      ALBUM 3 REYES     "<<endl;
		cout<<"========================"<<endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
		cout<<"[1].COMPRAR 1 SOBRE"<<endl;
		cout<<"[2].CONSEGUIR MONEDAS"<<endl;
		cout<<"[3].VER DATOS"<<endl;
		cout<<"[4].VER EL ALBUM"<<endl;
		cout<<"[5].CERRAR SESION"<<endl<<endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		cout<<"INGRESAR OPCION = ";
		cin>>opcion;
		system("cls");
		switch(opcion){
		case '1': Opcion1(jugador,pos);
		break;
		case '2': Opcion2(jugador,pos);
		break;
		case '3': Opcion3(jugador,pos);
		break;
		case '4': Opcion4(jugador,pos);
		break;
		}
	}while(opcion!='5');
}
void Piedra(datos *jugador,int pos){
	getch();
	system("cls");
	int x,y;
	int cant1=0,cant2=0;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	cout<<"==============================================="<<endl;
	cout<<"   JANKENPON - 6.75*(GANADOS-PERDIDOS) SOLES   "<<endl;
	cout<<"==============================================="<<endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	cout<<"[1].PIEDRA"<<endl;
	cout<<"[2].PAPEL"<<endl;
	cout<<"[3].TIJERA"<<endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	for(int i=0;i<3;i++){
		y=rand()%3+1;
		do{
			cout<<"INGRESE NUMERO = ";
			cin>>x;
		}while(x<0 or x>3);
		cout<<x<<" - "<<y<<endl;
		if(x==1 and y==2){
			cout<<"GANA C++"<<endl;
			cant2++;
		}
		else if(x==2 and y==1){
			cout<<"GANA  "<<(jugador+pos)->nombre<<endl;
			cant1++;
		}
		else if(x==1 and y==3){
			cout<<"GANA  "<<(jugador+pos)->nombre<<endl;
			cant1++;
		}
		else if(x==3 and y==1){
			cout<<"GANA  C++"<<endl;
			cant2++;
		}
		else if(x==2 and y==3){
			cout<<"GANA  C++"<<endl;
			cant2++;
		}
		else if(x==3 and y==2){
			cout<<"GANA  "<<(jugador+pos)->nombre<<endl;
			cant1++;
		}
		else cout<<"EMPATES"<<endl;
	}
	if(cant1>cant2){
		cout<<"Has ganado "<<6.75*(cant1-cant2)<<" soles"<<endl;
		(jugador+pos)->monedas=(jugador+pos)->monedas+6.75*(cant1-cant2);
	}
	else cout<<"Sigue intentando"<<endl;
}
void Adivinar(datos *jugador,int pos){
	getch();
	system("cls");
	srand(time(NULL));
	int entrada,veces=0;
	int aleatorio=rand()%20+1;
	do{
		getch();
		system("cls");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
		cout<<"========================================================="<<endl;
		cout<<" INGRESAR NUMERO ENTRE (1-20) - 0.75*(10-INTENTOS) SOLES "<<endl;
		cout<<"========================================================="<<endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		do{
			cout<<"INGRESAR NUMERO = ";
			cin>>entrada;
		}while(entrada<1 or entrada>20);
		if(entrada!=aleatorio){
			if(entrada>aleatorio) cout<<"Estas arriba del numero"<<endl;
			else cout<<"Estas abajo del numero"<<endl;
		}
		veces++;
	}while(entrada!=aleatorio and veces!=10);
	if(veces!=10){
		(jugador+pos)->monedas=(jugador+pos)->monedas+0.75*(10-veces);
		cout<<"Felicitaciones has ganado "<<0.75*(10-veces)<<" soles"<<endl;
	}else cout<<"Perdiste"<<endl;
}
void Operaciones(datos *jugador,int pos){
	srand(time(NULL));
	char digitar;
	int a,b,c,d,e,f;
	do{
		getch();
		system("cls");
		int intentos=0;
		double entrada;
		int resultado;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
		cout<<"==============================================="<<endl;
		cout<<" RESOLVER EL EJERCICIOS EN MENOS DE 3 INTENTOS "<<endl;
		cout<<"==============================================="<<endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
		cout<<"[1].FACIL - 1.50*(3-INTENTOS) SOLES"<<endl;
		cout<<"[2].INTERMEDIO - 3.50*(3-INTENTOS) SOLES"<<endl;
		cout<<"[3].DIFICIL - 7.50*(3-INTENTOS) SOLES"<<endl;
		cout<<"[4].MUY DIFICIL - 17.5*(3-INTENTOS) SOLES"<<endl;
		cout<<"[5].SALIR"<<endl<<endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		cout<<"INGRESAR OPCION = ";
		cin>>digitar;
		if(digitar=='1'){
			a=rand()%6;	b=rand()%6; c=rand()%6;
			resultado=a*b+c;
			do{
				cout<<a<<" x "<<b<<" + "<<c<<" = ";
				cin>>entrada;
				if(entrada!=resultado) intentos++;
			}while(intentos!=3 and entrada!=resultado);
			if(intentos!=3){
				(jugador+pos)->monedas=(jugador+pos)->monedas+1.50*(3-intentos);
				cout<<"Felicitaciones has ganado "<<1.50*(3-intentos)<<" soles"<<endl;
			}else cout<<"Perdiste"<<endl;
		}
		if(digitar=='2'){
			a=rand()%10;	b=rand()%15; c=rand()%10; d=rand()%15;
			resultado=a*(b+c*d);
			do{
				cout<<a<<" x ("<<b<<" + "<<c<<" x "<<d<<") = ";
				cin>>entrada;
				if(entrada!=resultado) intentos++;
			}while(intentos!=3 and entrada!=resultado);
			if(intentos!=3){
				jugador->monedas=jugador->monedas+3.50*(3-intentos);
				cout<<"Felicitaciones has ganado "<<3.50*(3-intentos)<<" soles"<<endl;
			}else cout<<"Perdiste"<<endl;
		}
		if(digitar=='3'){
			a=rand()%10;	b=rand()%15+20; c=rand()%10+20; d=rand()%15; e=rand()%3+5;
			resultado=a*(b+c*d)*e*e;
			do{
				cout<<a<<" x ("<<b<<" + "<<c<<" x "<<d<<") x "<<e<<" ^ 2 = ";
				cin>>entrada;
				if(entrada!=resultado) intentos++;
			}while(intentos!=3 and entrada!=resultado);
			if(intentos!=3){
				(jugador+pos)->monedas=(jugador+pos)->monedas+7.50*(3-intentos);
				cout<<"Felicitaciones has ganado "<<7.50*(3-intentos)<<" soles"<<endl;
			}else cout<<"Perdiste"<<endl;
		}
		if(digitar=='4'){
			a=rand()%30+21;	b=rand()%12+3; c=rand()%10+20; d=rand()%15; e=rand()%3+12; f=rand()%2+3;
			resultado=a*(b+c*d)*e*e+pow(b,f);
			do{
				cout<<a<<" x ("<<b<<" + "<<c<<" x "<<d<<") x "<<e<<" ^ 2 + "<<b<<" ^ "<<f<<" = ";
				cin>>entrada;
				if(entrada!=resultado) intentos++;
			}while(intentos!=3 and entrada!=resultado);
			if(intentos!=3){
				(jugador+pos)->monedas=(jugador+pos)->monedas+17.50*(3-intentos);
				cout<<"Felicitaciones has ganado "<<17.50*(3-intentos)<<" soles"<<endl;
			}else cout<<"Perdiste"<<endl;
		}
	}while(digitar!='5');
}
void Apostar(datos *jugador,int pos){
	getch();
	system("cls");
	srand(time(NULL));
	int entrada,n,respuesta;
	double apostar;
	if((jugador+pos)->monedas>0){
		n=rand()%10+5;
		do{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
			cout<<"=============================================="<<endl;
			cout<<" APOSTAR Y RESOLVER UN EJERCICIO DE FIBONACCI "<<endl;
			cout<<"=============================================="<<endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
			cout<<"SUS MONEDAS = "<<(jugador+pos)->monedas<<endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
			cout<<"[1].SI ACIERTA -> 3*APUESTA SOLES"<<endl;
			cout<<"[2].SI NO ACIERTA -> PIERDE EL DINERO APOSTADO"<<endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			cout<<"DIGITE SU APUESTA = ";
			cin>>apostar;
			if((jugador+pos)->monedas<apostar){
				cout<<"Dinero Insuficiente"<<endl;
				break;
			}
		}while((jugador+pos)->monedas<apostar and (jugador+pos)->monedas<0);
		if((jugador+pos)->monedas>=apostar){
			entrada=Fibonacci(n);
			cout<<"Ingrese la sucesion Fibonacci hasta el termino "<<n<<" = ";
			cin>>respuesta;
			if(entrada==respuesta){
				cout<<"Correcto, has ganado "<<3*apostar<<" soles"<<endl;
				(jugador+pos)->monedas=(jugador+pos)->monedas+3*apostar;
			}else{
				cout<<"Perdiste "<<apostar<<" soles"<<endl;
				(jugador+pos)->monedas=(jugador+pos)->monedas-apostar;
			}
		}
	}else cout<<"No tienes monedas"<<endl;
	
}
int Fibonacci(int n){
	if(n==1) return 0;
	if(n==2) return 1;
	return (Fibonacci(n-1)+Fibonacci(n-2));
}
void Opcion1(datos *jugador,int pos){
	int aux=0;
	int x,y;
	srand(time(NULL));
	if((jugador+pos)->monedas>=1.50){
		for(int i=0;i<7;i++){
			x=rand()%32;
			y=rand()%23;
			if(y==9 && aux==1){
				do{
					y=rand()%23;
				}while(y==9);
			}
			if(y==9 && aux==0) aux=1;
			if(y!=9){
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
				cout<<"============================="<<endl;
				cout<<"SOBRE "<<i+1<<" = "<<x*23+y+1<<endl;
				cout<<"============================="<<endl;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				cout<<"EQUIPO = "<<equipos[x]<<endl;
				cout<<"PAGINA = "<<x+1<<endl;
				cout<<"JUGADOR = "<<y+1<<endl;
			}
			else {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
				cout<<"============================="<<endl;
				cout<<"SOBRE "<<i+1<<" - ESPECIAL = "<<x*23+y+1<<endl;
				cout<<"============================="<<endl;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				cout<<"EQUIPO = "<<equipos[x]<<endl;
				cout<<"PAGINA = "<<x+1<<endl;
				cout<<"JUGADOR = "<<y+1<<endl;
			}
			if((jugador+pos)->album[x][y]==0) (jugador+pos)->cantidad=(jugador+pos)->cantidad+1;
			(jugador+pos)->album[x][y]=1;
		}
		if(y!=9) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
		else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		cout<<"============================="<<endl;
		(jugador+pos)->monedas=(jugador+pos)->monedas-1.50;
	}
	else {
		cout<<"============================="<<endl;
		cout<<"    Insuficiente monedas     "<<endl;
		cout<<"============================="<<endl;
	}
	getch();
	system("cls");
}
void Opcion2(datos *jugador,int pos){
	char opc;
	do{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
		cout<<"========================"<<endl;
		cout<<"  CONSEGUIR DINERO :V  "<<endl;
		cout<<"========================"<<endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
		cout<<"[1].PIEDRA,PAPEL Y TIJERAS"<<endl;
		cout<<"[2].ADIVINAR NUMERO"<<endl;
		cout<<"[3].RESOLVER OPERACIONES MATEMATICAS"<<endl;
		cout<<"[4].APOSTAR"<<endl;
		cout<<"[5].REGRESAR"<<endl<<endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		cout<<"INGRESAR OPCION = ";
		cin>>opc;
		switch(opc){
			
		case '1': Piedra(jugador,pos);
		break;
		case '2': Adivinar(jugador,pos);
		break;
		case '3': Operaciones(jugador,pos);
		break;
		case '4': Apostar(jugador,pos);
		break;
		}
		getch();
		system("cls");
	}while(opc!='5');
}
void Opcion3(datos *jugador,int pos){
	cout<<"========================"<<endl;
	cout<<"       INFORMACION      "<<endl;
	cout<<"========================"<<endl;
	cout<<"CODIGO = "<<(jugador+pos)->codigo<<endl;
	cout<<"PASSWORD = "<<(jugador+pos)->password<<endl;
	cout<<"NOMBRES = "<<(jugador+pos)->nombre<<endl;
	cout<<"DINERO = "<<(jugador+pos)->monedas<<" SOLES"<<endl;
	cout<<"FIGURAS PEGADAS = "<<(jugador+pos)->cantidad<<endl;
	cout<<"FIGURAS RESTANTES = "<<736-(jugador+pos)->cantidad<<endl;
	cout<<"PORCENTAJE = "<<((jugador+pos)->cantidad*100)/736<<" %"<<endl;
	getch();
	system("cls");
}
void Opcion4(datos *jugador,int pos){
	for(int j=0;j<32;j++){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
		cout<<"================================================="<<endl;
		cout<<"\t\t"<<j+1<<"-"<<equipos[j]<<endl;
		cout<<"================================================="<<endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
		for(int i=0;i<5;i++){
			cout<<" J"<<i+1<<" = "<<(jugador+pos)->album[j][i]<<"   ";
		}cout<<endl;
		for(int i=5;i<9;i++){
			cout<<" J"<<i+1<<" = "<<(jugador+pos)->album[j][i]<<"   ";
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		cout<<"J10 = "<<(jugador+pos)->album[j][9]<<endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
		for(int i=10;i<15;i++){
			cout<<"J"<<i+1<<" = "<<(jugador+pos)->album[j][i]<<"   ";
		}cout<<endl;
		for(int i=15;i<20;i++){
			cout<<"J"<<i+1<<" = "<<(jugador+pos)->album[j][i]<<"   ";
		}cout<<endl;
		for(int i=20;i<23;i++){
			cout<<"J"<<i+1<<" = "<<(jugador+pos)->album[j][i]<<"   ";
		}cout<<endl;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	cout<<"================================================="<<endl;
	getch();
	system("cls");
}
void Ranking(datos *jugador,int registro){
	datos aux;
	for(int i=0;i<registro;i++){
		for(int j=0;j<registro;j++){
			if((jugador+i)->cantidad>(jugador+j)->cantidad){
				aux=*(jugador+j);
				*(jugador+j)=*(jugador+i);
				*(jugador+i)=aux;
			}
		}
	}
}
