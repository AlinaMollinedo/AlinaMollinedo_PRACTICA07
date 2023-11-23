// Materia: Programación I, Paralelo 4

// Autor: Alina Mollinedo Dávila

// Fecha creación: 22/11/2023

// Fecha modificación: 22/11/2023

// Número de ejericio: 1

// Problema planteado: Escribe un programa que tenga un menú de tres opciones:
 
// ·	Ingreso de datos de los equipo de la LPFB.
// ·	Ingreso los resultados de los partidos.
// ·	Reporte de la tabla de posiciones
// ·	Salir

// La primera opción debe ingresar los datos de los nombres de los equipos de la liga de acuerdo con la siguiente estructura
// y estos sean almacenados en un archivo binario llamado “EquiposLPFB.bin”, se debe considerar en no duplicar los equipos de
// futbol por el Nombre del Equipo
// struct structEquiposLPFB
// {
//     char nombreEquipo[50];
//     char colorCamiseta[50];
//     char departamento[30];
//     int anioCreacion;
// }; 

// La segunda opción debe ingresar los resultados de los partidos, que debe almacenarse en el archivo “ResultadosLPFB.bin” de 
// acuerdo a la siguiente estructura, se debe considerer que solo se debe colocar resultados de los equipos ingresados en el 
// archive “EquiposLPFB.bin”:
// struct structResultadosLPFB
// {
//     char nombreEquipoLocal[50];
//     char nombreEquipoVisitante[50];
//     int golesEquipoLocal;
//     Int golesEquipoVisitante;
//     char fechaPartido[10]
// };

// La tercera opción debe dar un reporte de la tabla de posiciones

#include <iostream>
#include <fstream>
#include <wchar.h>
#include <cstring>
#include <stdlib.h>

using namespace std;

// Declaracion de los nombres de los archivos
const char* fileTeams = "EquiposLPFB.bin";
const char* fileResults = "ResultadosLPFB.bin";

//Estructura para los datos de un equipo
struct sTeam{
    char name[50], shirtColor[50], department[30];
    int creationYear;
};

//Estrucutura para los resultados de los partidos
struct sResults{
    char homeTeam[50], visitorTeam[50], dateMatch[11];
    int homeTeamGoals, visitorTeamGoals;
};

//Estrucutra de los resultados de cada equipo
struct sTotals{
    char name[50];
    int played = 0, wins = 0, losses = 0, ties = 0, goalsFavor = 0, goalsAgainst = 0, pts = 0;
};

//Funciones
int menu();
sTeam addTeam();
sResults addResults();
bool verifyTeam(char[50]);
void addTeamToFile(sTeam);
bool verifyResults(char[50], char[50]);
void addResultsToFile(sResults);
int countTeams();
void fillStructs(sTotals*);
void shellSort(sTotals*, int);
void showReport();


int main(){
    setlocale(LC_ALL, "");
    int option = 0;
    do{
        option = menu();
        //Realiza la opcion elegida en el menu
        switch(option){
            case 1:
                system("cls");
                addTeamToFile(addTeam());
                break;
            case 2:
                system("cls");
                addResultsToFile(addResults());
                break;
            case 3:
                system("cls");
                showReport();
                break;
            default:
                system("cls");
                cout << "\n---> Se ha salido del sistema." << endl;
                option = 0;
                break;
        }
    }
    while(option != 0);

    return 0;
}

//Despliega el menu de opciones
int menu(){
    system("cls");
    int op;
    cout << "\nMENU DE OPCIONES" << endl;
    cout << "================" << endl;
    cout << "\n\t1. Ingreso de datos de los equipo de la LPFB." << endl;
    cout << "\t2. Ingreso de los resultados de los partidos." << endl;
    cout << "\t3. Reporte de la tabla de posiciones." << endl;
    cout << "\t0. Salir." << endl;
    cout << "\nSu seleccion: ";
    cin >> op;
    return op;
}

//Pide los datos de un equipo
sTeam addTeam(){
    sTeam t;
    cout << "\nINGRESO DE DATOS DE LOS EQUIPOS DE LA LPFB" << endl;
    cout << "=============================================" << endl;
    cout << "\nNombre del equipo: ";
    cin.ignore(256, '\n');
    cin.getline(t.name, 50);
    cout << "Color de camiseta: ";
    cin.getline(t.shirtColor, 50);
    cout << "Departamento: ";
    cin.getline(t.department, 30);
    cout << "Año de creación: ";
    cin >> t.creationYear;
    return t;
}

//Pide los datos para los resultados de un partido
sResults addResults(){
    sResults r;
    cout << "\nINGRESO DE LOS RESULTADOS DE LOS PARTIDOS" << endl;
    cout << "=========================================" << endl;
    cout << "\nNombre del equipo local: ";
    cin.ignore(256, '\n');
    cin.getline(r.homeTeam, 50);
    cout << "Nombre del equipo visitante: ";
    cin.getline(r.visitorTeam, 50);
    cout << "Goles del equipo local: ";
    cin >> r.homeTeamGoals;
    cout << "Goles del equipo visitante: ";
    cin >> r.visitorTeamGoals;
    cout << "Fecha del partido (dd/mm/yyyy): ";
    cin.ignore(256, '\n');
    cin.getline(r.dateMatch, 11);
    return r;
}

//Verifica que el equipo no haya sido agregado anteriormente
bool verifyTeam(char name[50]){
    sTeam t;
    ifstream rf;
    rf.open(fileTeams, ios::binary);
    while(rf.read((char*)&t, sizeof(sTeam))){
        if(strcmp(name, t.name) == 0){
            cout << "\nEL EQUIPO YA HA SIDO INGRESADO." << endl;
            system("pause");
            return false;
        }
    }
    rf.close();
    return true;
}

//Agrega el equipo al archivo de equipos
void addTeamToFile(sTeam t){
    ofstream wf;
    if(verifyTeam(t.name)){
        wf.open(fileTeams, ios::binary | ios::app);
        wf.write((char*)&t, sizeof(sTeam));
        wf.close();
    }
}

//Verifica que los dos equipos de un partido ya hayan sido agregados anteriormente
bool verifyResults(char name1[50], char name2[50]){
    sTeam t;
    ifstream rf1, rf2;
    rf1.open(fileTeams, ios::binary);
    rf2.open(fileTeams, ios::binary);
    while(rf1.read((char*)&t, sizeof(sTeam))){
        if(strcmp(name1, t.name) == 0){
            while(rf2.read((char*)&t, sizeof(sTeam))){
                if(strcmp(name2, t.name) == 0){
                    rf1.close();
                    rf2.close();
                    return true;
                }
            }
        }
    }
    cout << "\nLOS EQUIPOS NO HAN SIDO INGRESADOS CON ANTERIORIDAD." << endl;
    system("pause");
    rf1.close();
    rf2.close();
    return false;
}

//Agrega los resultados al archivo de resultados
void addResultsToFile(sResults r){
    ofstream wf;
    if(verifyResults(r.homeTeam, r.visitorTeam)){
        wf.open(fileResults, ios::binary | ios::app);
        wf.write((char*)&r, sizeof(sResults));
        wf.close();
    }
}

//Cuenta la cantidad de equipos en el archivo de equipos
int countTeams(){
    ifstream rf;
    sTeam t;
    int counter = 0;
    rf.open(fileTeams, ios::binary);
    while(rf.read((char*)&t, sizeof(sTeam))){
        counter++;
    }
    return counter;
}

//Llena la estructura de los totales de cada equipo 
void fillStructs(sTotals* totals){
    int pos = 0;
    sTeam t;
    sResults r;

    ifstream rfT, rfR;
    rfT.open(fileTeams, ios::binary);

    while(rfT.read((char*)&t, sizeof(sTeam))){
        strcpy(totals[pos].name, t.name); //Agrega el nombre del equipo
        rfR.open(fileResults, ios::binary);

        while(rfR.read((char*)&r, sizeof(sResults))){
            //Verifica si el equipo jugó el partido
            if(strcmp(t.name, r.homeTeam) == 0){
                totals[pos].played++;
                //Agrega los goles
                totals[pos].goalsFavor += r.homeTeamGoals;
                totals[pos].goalsAgainst += r.visitorTeamGoals;
                //Agrega si ganó, empató o perdió el partido
                if(r.homeTeamGoals - r.visitorTeamGoals > 0){
                    totals[pos].wins++;
                }
                else{
                    if(r.visitorTeamGoals - r.homeTeamGoals > 0){
                        totals[pos].losses++;
                    }
                    else{
                        totals[pos].ties++;
                    }
                }
            }
            else{
                if(strcmp(t.name, r.visitorTeam) == 0){
                    totals[pos].played++;
                    //Agrega los goles
                    totals[pos].goalsFavor += r.visitorTeamGoals;
                    totals[pos].goalsAgainst += r.homeTeamGoals;
                    //Agrega si ganó, empató o perdió el partido
                    if(r.visitorTeamGoals - r.homeTeamGoals > 0){
                        totals[pos].wins++;
                    }
                    else{
                        if(r.homeTeamGoals - r.visitorTeamGoals > 0){
                            totals[pos].losses++;
                        }
                        else{
                            totals[pos].ties++;
                        }
                    }
                }
            }
        }
        //Cuenta los puntos del equipo
        totals[pos].pts = 3 * totals[pos].wins + totals[pos].ties;
        rfR.close();
        pos++;
    }
    rfT.close();
}

//Organiza los equipos de acuerdo a su numero de puntos, utilizando shell sort
void shellSort(sTotals* totals, int n){
    int piv = n / 2;
    while(piv != 1){
        for(int i = 0; i < n; i++){
            if(i + piv < n){
                if(totals[i].pts > totals[i + piv].pts){
                    swap(totals[i], totals[i + piv]);
                }
            }
        }
        piv /= 2;
    }
    bool flag = true;
    while(flag){
        flag = false;
        for(int i = 0; i < n - 1; i++){
            if(totals[i].pts > totals[i + piv].pts){
                swap(totals[i], totals[i + piv]);
                flag = true;
            }
        }
    }
}

//Muestra la tabla de posiciones
void showReport(){

    ifstream rf1, rf2;
    rf1.open(fileResults, ios::binary);
    rf2.open(fileResults, ios::binary);
    if(rf1.good() && rf2.good()){
        rf1.close();
        rf2.close();

        int n = countTeams();
        sTotals totals[n] = {};
        fillStructs(totals);
        shellSort(totals, n);

        cout << "\nTABLA DE POSICIONES" << endl;
        cout << "===================" << endl;
        cout << "\n\tClub\t\t\tPJ\tG\tE\tP\tGF\tGC\tDG\tPts" << endl;
        for(int i = n - 1; i > -1; i--){
            cout << "\t" << totals[i].name << "\t\t\t" << totals[i].played << "\t" << totals[i].wins << "\t" << totals[i].ties << "\t";
            cout << totals[i].losses << "\t" << totals[i].goalsFavor << "\t" << totals[i].goalsAgainst << "\t";
            cout << totals[i].goalsFavor - totals[i].goalsAgainst << "\t" << totals[i].pts << endl;
        }
        cout << endl;
        system("pause");
    }
    else{
        cout << "\n---> INFORMACION INSUFICIENTE PARA GENERAR REPORTE." << endl;
        system("pause");
    }
}