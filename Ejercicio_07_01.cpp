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

const char* fileTeams = "EquiposLPFB.bin";
const char* fileResults = "ResultadosLPFB.bin";

struct sTeam{
    char name[50], shirtColor[50], department[30];
    int creationYear;
};

struct sResults{
    char homeTeam[50], visitorTeam[50], dateMatch[11];
    int homeTeamGoals, visitorTeamGoals;
};

struct sTotals{
    char name[50];
    int wins = 0, losses = 0, ties = 0, goalsFavor = 0, goalsAgainst = 0, pts = 0;
};

int menu();
sTeam addTeam();
sResults addResults();
bool verifyTeam(char[50]);
void addTeamToFile(sTeam);
bool verifyResults(char[50], char[50]);
void addResultsToFile(sResults);
int countTeams();
char* listTeams();
sTotals* fillStructs(sTotals);
sTotals* shellSort(sTotals*, int);
void showReport();


int main(){
    setlocale(LC_ALL, "");
    int option = 0;
    do{
        option = menu();
        switch(option){
            case 1:
                //system("cls");
                addTeamToFile(addTeam());
                break;
            case 2:
                //system("cls");
                addResultsToFile(addResults());
                break;
            case 3:
                //system("cls");
                showReport();
                break;
            default:
                //system("cls");
                cout << "Se ha salido del sistema." << endl;
                option = 0;
                break;
        }
    }
    while(option != 0);

    return 0;
}

int menu(){
    // system("cls");
    int op;
    cout << "\nMENU DE OPCIONES" << endl;
    cout << "==========================" << endl;
    cout << "\n\t1. Ingreso de datos de los equipo de la LPFB." << endl;
    cout << "\t2. Ingreso de los resultados de los partidos." << endl;
    cout << "\t3. Reporte de la tabla de posiciones." << endl;
    cout << "\t0. Salir." << endl;
    cout << "\nSu seleccion: ";
    cin >> op;
    return op;
}

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

bool verifyTeam(char name[50]){
    sTeam t;
    ifstream rf;
    rf.open(fileTeams, ios::binary);
    while(rf.read((char*)&t, sizeof(sTeam))){
        if(strcmp(name, t.name) == 0){
            cout << "\nEL EQUIPO YA HA SIDO INGRESADO." << endl;
            rf.close();
            return false;
        }
    }
    rf.close();
    return true;
}

void addTeamToFile(sTeam t){
    ofstream wf;
    wf.open(fileTeams, ios::binary | ios::app);
    if(verifyTeam(t.name)){
        wf.write((char*)&t, sizeof(sTeam));
        wf.close();
    }
}

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
    rf1.close();
    rf2.close();
    return false;
}

void addResultsToFile(sResults r){
    ofstream wf;
    wf.open(fileResults, ios::binary | ios::app);
    if(verifyResults(r.homeTeam, r.visitorTeam)){
        wf.write((char*)&r, sizeof(sResults));
        wf.close();
    }
}

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

sTotals* fillStructs(sTotals* totals){
    int pos = 0;
    //sTeam t;
    sResults r;
    char name[50] = "BM";
    ifstream rfT, rfR;
    //rfT.open(fileTeams, ios::binary);
    //while(rfT.read((char*)&t, sizeof(sTeam))){
        cout << "owo" << endl;
        rfR.open(fileResults, ios::binary);
        cout << "uwu" << endl;
        while(rfR.read((char*)&r, sizeof(sResults))){
            cout << "ewe" << endl;
            if(name == r.homeTeam){
                cout << ">-<" << endl;
                totals[pos].goalsFavor = r.homeTeamGoals;
                totals[pos].goalsAgainst = r.visitorTeamGoals;
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
                if(name == r.visitorTeam){
                    cout << ">-<" << endl;
                    totals[pos].goalsFavor = r.visitorTeamGoals;
                    totals[pos].goalsAgainst = r.homeTeamGoals;
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
        totals[pos].pts = 3 * totals[pos].wins + totals[pos].ties;
        rfR.close();
        pos++;
    //}
    
    //rfT.close();
    return totals;
}

sTotals* shellSort(sTotals* totals, int n){
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
    return totals;
}

void showReport(){
    int n = countTeams();
    sTotals* totals = {};
    cout << "holiwi" << endl;
    totals = fillStructs(totals);
    for(int i = 0; i < n; i++){
        cout << totals[i].name << " " << totals[i].wins << " " << totals[i].ties << " " << totals[i].losses << " " << totals[i].pts << endl;
    }
    cout << "aaa" << endl;
}