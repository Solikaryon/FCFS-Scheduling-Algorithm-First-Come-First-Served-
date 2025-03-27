#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <conio.h>
#include <iomanip>
#include <string.h>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <cmath>
#include <cctype>
#include <fstream>
#include <chrono>
#include <algorithm>
#include <unordered_set>
#include <queue>
#include <chrono>

using namespace std;
using namespace chrono;

// Código creado por Monjaraz Briseño Luis Fernando

int totalProcesses;
int totallotes;
int totallotesr;
int totallotesrr;
int timer = 0;
int timecontador = 0;
int programNumber = 0;
int verficatiempollegada = 0;
int verficatiemporespuesta = 0;
int iwannadie = 0;
struct Process {
    string operation;
    int number1;
    int number2;
    string result;
    string result2;
    int estimatedTime;
    int programNumber;
    int currentQueue;
    int tiempotranscurrido; // no se aplica en todos los casos
    int tiemporestante; // no se aplica en todos los casos

    int tiempobloqueado;
    int tiempollegada;
    int tiempofinalizacion;
    int tiemporetorno;
    int tiemporespuesta;
    int tiempoespera;
    int tiemposervicio; // este sera igual al tiempotransucurrido o al estimatedTime
};

// Función que valida que los datos ingresados por el usuario sean números enteros
bool ValidaNumerosEnteros(char *dato){
    bool ban = true;
    int i = 0;
    if (*dato == '-' || *dato == '+') {
        i++;
    }
    while (*(dato + i) != '\0') {
        if (*(dato + i) < '0' || *(dato + i) > '9') {
            ban = false;
            break;
        }
        i++;
    }
    return ban;
}

void gotoxy(int x,int y){  
      HANDLE hcon;  
      hcon = GetStdHandle(STD_OUTPUT_HANDLE);  
      COORD dwPos;  
      dwPos.X = x;  
      dwPos.Y= y;  
      SetConsoleCursorPosition(hcon,dwPos);  
 }  


    const int maxProcessesPerQueue = 5;
    const int maxQueues = maxProcessesPerQueue;
    queue<Process> queues[maxQueues];
    queue<Process> totalProcessesQueue[1];
    queue<Process> mequedesinideasparanombres[1];
    unordered_set<int> usedProgramNumbers;

void IWillHaveOrder(){
    int x = 1, y = 1;
    gotoxy(0,0);
    printf("%c", 201); //╔
    gotoxy(132,0);
    printf("%c", 187); //╗
    gotoxy(0,31);
    printf("%c", 200); //╚
    gotoxy(132,31);
    printf("%c", 188); //╝
    while (y<=30)
    {
        gotoxy(0,y);
        printf("%c", 186); //║
        gotoxy(132,y);
        printf("%c", 186); //║
        y++;
    }
    while (x<=131)
    {
        gotoxy(x,0);
        printf("%c", 205); //═
        gotoxy(x,31);
        printf("%c", 205); //═
        x++;
    }
    y = 1;
    int y2 = 3;
    gotoxy(16,2);
    printf("%c", 203); //╦
    gotoxy(16,31);
    printf("%c", 202); //╩
    gotoxy(33,0);
    printf("%c", 203); //╦
    gotoxy(33,31);
    printf("%c", 202); //╩
    gotoxy(79,0);
    printf("%c", 203); //╦
    gotoxy(79,31);
    printf("%c", 202); //╩
    while (y<=30)
    {
        gotoxy(33,y);
        printf("%c", 186); //║
        gotoxy(79,y);
        printf("%c", 186); //║
        y++;
    }
    while (y2<=30){
        gotoxy(16,y2);
        printf("%c", 186); //║
        y2++;
    }
    x = 1;
    gotoxy(0,2);
    printf("%c", 204); //╠
    gotoxy(23,2);
    printf("%c", 185); //╣
    while (x<=32)
    {
        gotoxy(x,2);
        printf("%c", 205); //═
        x++;
    }
    gotoxy(16,2);
    printf("%c", 203); //╦
}

void ThisIsOrder(){
    int x = 1, y = 1;
    gotoxy(0,0);
    printf("%c", 201); //╔
    gotoxy(132,0);
    printf("%c", 187); //╗
    gotoxy(0,31);
    printf("%c", 200); //╚
    gotoxy(132,31);
    printf("%c", 188); //╝
    while (y<=30)
    {
        gotoxy(0,y);
        printf("%c", 186); //║
        gotoxy(132,y);
        printf("%c", 186); //║
        y++;
    }
    while (x<=131)
    {
        gotoxy(x,0);
        printf("%c", 205); //═
        gotoxy(x,31);
        printf("%c", 205); //═
        x++;
    }
}

void datosLotes(){
    char totalProcessesc[100];
    gotoxy(1,1);
    cout << "Ingrese el numero de procesos: ";
    cin >> totalProcessesc;
    while(!ValidaNumerosEnteros(totalProcessesc)){
        gotoxy(1,1);
        cout << "                                                 ";
        gotoxy(1,1);
        cout << "Ingrese el numero de procesos de nuevo: ";
        cin >> totalProcessesc;
    }
    totalProcesses = atoi(totalProcessesc);

    int currentQueue = 0;
    for (int i = 1; i <= totalProcesses; ++i) {
        Process newProcess;
        newProcess.currentQueue = currentQueue+1;
        int operationIndex = rand() % 6;
        switch (operationIndex)
        {
        case 0:
            newProcess.operation = "+";
            break;
        case 1:
            newProcess.operation = "-";
            break;
        case 2:
            newProcess.operation = "*";
            break;
        case 3:
            newProcess.operation = "/";
            break;
        case 4:
            newProcess.operation = "residuo";
            break;
        case 5:
            newProcess.operation = "porcentaje";
            break;
        default:
            break;
        }
        int operationN1 = rand() % 101;
        int operationN2 = rand() % 101;
        newProcess.number1 = operationN1;
        newProcess.number2 = operationN2;

        if(newProcess.operation == "/"){
            while(newProcess.number2 == 0){
                int operationN2 = rand() % 101;
                newProcess.number2 = operationN2;
            }
        }
        if(newProcess.operation == "+"){
            newProcess.result = newProcess.number1 + newProcess.number2;       
        }
        else if(newProcess.operation == "-"){
            newProcess.result = to_string(newProcess.number1 - newProcess.number2);       
        }
        else if(newProcess.operation == "*"){
            newProcess.result = to_string(newProcess.number1 * newProcess.number2);       
        }
        else if(newProcess.operation == "/"){
            newProcess.result = to_string(newProcess.number1 / newProcess.number2);       
        }
        else if(newProcess.operation == "residuo"){
            newProcess.result = to_string(newProcess.number1 % newProcess.number2);       
        }
        else if(newProcess.operation == "porcentaje"){
            newProcess.result = to_string((newProcess.number1 * newProcess.number2) / 100);        
        }
        else {
            gotoxy(1,11);
            cout << "Operacion no valida" << endl;
        }
        int operationET = 6 + (rand() % 13); // Tiempo estimado de 6 a 18 segundos
        newProcess.estimatedTime = operationET;
        while(newProcess.estimatedTime == 0){
            int operationET = 6 + (rand() % 13); // Tiempo estimado de 6 a 18 segundos
            newProcess.estimatedTime = operationET;
        }

        newProcess.tiempotranscurrido = 0;
        newProcess.tiemporestante = newProcess.estimatedTime;
        
        programNumber++;
        newProcess.programNumber = programNumber;

        newProcess.tiempobloqueado = 8;
        newProcess.tiempollegada = 0;
        newProcess.tiempofinalizacion = 0;
        newProcess.tiemporetorno = 0;
        newProcess.tiemporespuesta = 0;
        newProcess.tiempoespera = 0;
        newProcess.tiemposervicio = 0;
        newProcess.result2 = "Normal";

        usedProgramNumbers.insert(newProcess.programNumber);
        queues[currentQueue].push(newProcess);
        if (queues[currentQueue].size() >= maxProcessesPerQueue) {
            currentQueue++;
        }
    }
}





void imprimirdata() {
    int procesosTotales = totalProcesses;
    int contadordeprocesosnuevos = totalProcesses;
    int contadordeprocesoslistos = 0;
    int ffy = 7;
    char pulsar = ' ';
    int a = 1;
    gotoxy(80, 13);
    cout << "I = Interrumpir";
    gotoxy(80, 15);
    cout << "E = Error";
    gotoxy(80, 17);
    cout << "P = Pausar";
    gotoxy(80, 19);
    cout << "C = Continuar";
    queue<Process> cpc = queues[0];
    while(!cpc.empty()){
        Process temporal = cpc.front();
        cpc.pop();
        contadordeprocesoslistos = contadordeprocesoslistos + 1;
        contadordeprocesosnuevos = contadordeprocesosnuevos - 1;
    }
    queue<Process> totalProcessesQueue[1]; // En esta cola se almacenaran todos los datos finalizados
    for (int i = 0; i < maxQueues; i++) {
        gotoxy(1,1);
        cout << "Procesos Nuevos: " << contadordeprocesosnuevos; // Modi
        int acomodainterumpir = 11;
        int ay = 7;
        int y = 7;
        if (!queues[i].empty()) {
            gotoxy(3,3);
            cout << "P Listos #" << contadordeprocesoslistos << endl; // Modi
            queue<Process> tempQueue = queues[i];  // Copia temporal de la cola
            queue<Process> bloqueados;
            gotoxy(80,50);
            while (!tempQueue.empty()) {
                // fila 1
                Process tprocess = tempQueue.front();
                tempQueue.pop();
                gotoxy(3,5);
                cout << "ID";
                gotoxy(3,y);
                cout << tprocess.programNumber;
                gotoxy(6,5);
                cout << "TME";
                gotoxy(6,y);
                cout << tprocess.estimatedTime;
                gotoxy(10,5);
                cout << "TT";
                gotoxy(10,y);
                cout << "  ";
                gotoxy(10,y);
                cout << tprocess.tiempotranscurrido;
                gotoxy(3,7);
                cout << "            ";
                y = y + 1;
                gotoxy(3,15);
                cout << "Bloqueados";
                gotoxy(3,17);
                cout << "ID";
                gotoxy(6,17);
                cout << "TB"; // tiempo bloqueado
            }
            while(!queues[i].empty()){
                int by = 19;
                
                // fila 2
                Process process = queues[i].front();
                gotoxy(17,3);
                cout << "Ejec";
                gotoxy(17,5);
                cout << "Nn "; // nombre
                gotoxy(17,7);
                cout << "ID";
                gotoxy(17,9);
                cout << "Ope";
                gotoxy(17,11);
                cout << "TME";
                gotoxy(17,13);
                cout << "TT";
                gotoxy(17,15);
                cout << "TR";
                gotoxy(22,7);
                cout << process.programNumber;
                gotoxy(22,9);
                cout << "          ";
                gotoxy(22,9);
                cout << process.operation;
                gotoxy(22,11);
                cout << "   ";
                gotoxy(22,11);
                cout << process.estimatedTime;
                gotoxy(80,5);
                cout << "Procesos restantes";
                gotoxy(80,7);
                cout << "            ";
                gotoxy(80,7);
                cout << procesosTotales;
                while(process.estimatedTime > process.tiempotranscurrido || !bloqueados.empty()){
                    queue<Process> imp = queues[i];
                    y = 7;
                    while(imp.empty()){
                        Process yanosequenombre = imp.front();
                        imp.pop();
                        gotoxy(3,5);
                        cout << "ID";
                        gotoxy(3,y);
                        cout << yanosequenombre.programNumber;
                        gotoxy(6,5);
                        cout << "TME";
                        gotoxy(6,y);
                        cout << yanosequenombre.estimatedTime;
                        gotoxy(10,5);
                        cout << "TT";
                        gotoxy(10,y);
                        cout << "  ";
                        gotoxy(10,y);
                        cout << yanosequenombre.tiempotranscurrido;
                        gotoxy(3,7);
                        cout << "            ";
                    }
                    by = 19;
                    gotoxy(22,13);
                    cout << "   ";
                    gotoxy(22,13);
                    cout << process.tiempotranscurrido;
                    gotoxy(22,15);
                    cout << "   ";
                    gotoxy(22,15);
                    cout << process.tiemporestante;
                    gotoxy(80,9);
                    cout << "Tiempo total";
                    gotoxy(80,11);
                    cout << "            ";
                    gotoxy(80,11);
                    cout << timecontador;
                    timer = timer + 1;
                    timecontador = timecontador + 1;
                    // tiempo de finalizacion
                    process.tiempofinalizacion = timecontador;
                    // tiempo de retorno
                    process.tiemporetorno = process.tiempofinalizacion - process.tiempollegada;
                    // tiempo de respuesta                    
                    if(process.tiemporespuesta == 0){
                        process.tiemporespuesta = timecontador;
                    }
                    else
                    {
                    }
                    // tiempo de espera
                    process.tiempoespera = process.tiemporetorno - process.tiemposervicio - 1; // El -1 es para ajustar el tiempo, pues por como funciona hace un incremento antes de terminar.
                    // tiempo de servicio
                    process.tiemposervicio = process.tiemposervicio + 1; 
                    process.tiemporestante = process.tiemporestante - 1;
                    process.tiempotranscurrido = process.tiempotranscurrido + 1;
                    Process interruptedProcess = queues[i].front(); // Obtener el proceso actual
                    if (_kbhit() && process.tiempotranscurrido != process.estimatedTime) {
                        char key = _getch();
                        if (key == 'I' || key == 'i') { // interrumpir
                            pulsar = 'i';
                            interruptedProcess.tiempotranscurrido = process.tiempotranscurrido; // Guardar el tiempo transcurrido
                            interruptedProcess.tiemporestante = process.tiemporestante; // Guardar el tiempo total
                            queues[i].pop(); // Sacar el proceso de la cola actual
                            bloqueados.push(interruptedProcess);
                            gotoxy(18,15);
                            cout << "    ";
                            timecontador = timecontador - 1;
                            // Limpiar la cola temporal
                            while (!tempQueue.empty()) {
                                tempQueue.pop();
                            }
                            // Volver a llenar la cola temporal con los procesos restantes de la cola original
                            queue<Process> originalQueue = queues[i];
                            Process tprocess = originalQueue.front();
                            y = 7;
                            while (!originalQueue.empty()) {
                                tempQueue.push(originalQueue.front());
                                gotoxy(3,5);
                                cout << "ID";
                                gotoxy(3,y);
                                cout << tprocess.programNumber;
                                gotoxy(6,5);
                                cout << "TME";
                                gotoxy(6,y);
                                cout << tprocess.estimatedTime;
                                gotoxy(10,5);
                                cout << "TT";
                                gotoxy(10,y);
                                cout << "  ";
                                gotoxy(10,y);
                                cout << tprocess.tiempotranscurrido;
                                gotoxy(3,7);
                                cout << "            ";
                                y = y + 1;
                                originalQueue.pop();
                            }
                            queue<Process> tempQueue = queues[i];  // Copia temporal de la cola
                            y = 7;
                            ay = 7;
                            int contadorded = 5;
                            while(contadorded >=0)
                            {
                                gotoxy(3,y);
                                cout << "             ";
                                y = y + 1;
                                contadorded--;
                            }
                            y = 7;
                            while (!tempQueue.empty()) {
                                // fila 1
                                Process tprocess = tempQueue.front();
                                tempQueue.pop();
                                gotoxy(3,5);
                                cout << "ID";
                                gotoxy(3,y);
                                cout << "  ";
                                gotoxy(3,y);
                                cout << tprocess.programNumber;
                                gotoxy(6,5);
                                cout << "TME";
                                gotoxy(6,y);
                                cout << "  ";
                                gotoxy(6,y);
                                cout << tprocess.estimatedTime;
                                gotoxy(10,5);
                                cout << "TT";
                                gotoxy(10,y);
                                cout << "  ";
                                gotoxy(10,y);
                                cout << tprocess.tiempotranscurrido;
                                gotoxy(3,7);
                                cout << "            ";
                                y = y + 1;
                            }
                            break;
                        } else if (key == 'P' || key == 'p') { // pausar
                            gotoxy(80,21);
                            cout << "Pausado";
                            while (true)
                            {
                                if (_kbhit()) {
                                    char key = _getch();
                                    if (key == 'C' || key == 'c') { // continuar
                                        gotoxy(80,21);
                                        cout << "        ";
                                        break;
                                    }
                                }
                            }
                        } else if (key == 'E' || key == 'e') { // error
                            pulsar = 'e';
                            timecontador = timecontador - 1;
                            break;
                        }
                    }
                    iwannadie = iwannadie + process.tiempofinalizacion;       
                    int contadorded = 5;
                    while(contadorded >=0)
                    {
                        gotoxy(3,by);
                        cout << "             ";
                        by = by + 1;
                        contadorded--;
                    }
                    by = 19;
                    if (!bloqueados.empty()) {        
                        queue<Process> tempbloq = bloqueados;
                        while (!tempbloq.empty()) {
                            Process temporal = tempbloq.front();
                            tempbloq.pop();
                            temporal.tiempobloqueado = temporal.tiempobloqueado - 1;
                            // Aquí se imprimirán los datos de cada proceso en la cola de bloqueados
                            gotoxy(3, by);
                            cout << temporal.programNumber;
                            gotoxy(6, by);
                            cout << temporal.tiempobloqueado; // tiempo bloqueado
                            by = by + 1;
                            bloqueados.pop();
                            bloqueados.push(temporal);
                            if (temporal.tiempobloqueado <= 0) {
                                temporal.tiempobloqueado = 8;
                                queues[i].push(temporal);
                                bloqueados.pop();
                                contadordeprocesoslistos = contadordeprocesoslistos + 1;
                            }
                            queue<Process> tempQueue = queues[i];  // Copia temporal de la cola
                            y = 7;
                            ay = 7;
                            int contadorded = 5;
                            while(contadorded >=0)
                            {
                                gotoxy(3,y);
                                cout << "             ";
                                y = y + 1;
                                contadorded--;
                            }
                            y = 7;
                            while (!tempQueue.empty()) {
                                // fila 1
                                Process tprocess = tempQueue.front();
                                tempQueue.pop();
                                gotoxy(3,5);
                                cout << "ID";
                                gotoxy(3,y);
                                cout << "  ";
                                gotoxy(3,y);
                                cout << tprocess.programNumber;
                                gotoxy(6,5);
                                cout << "TME";
                                gotoxy(6,y);
                                cout << "  ";
                                gotoxy(6,y);
                                cout << tprocess.estimatedTime;
                                gotoxy(10,5);
                                cout << "TT";
                                gotoxy(10,y);
                                cout << "  ";
                                gotoxy(10,y);
                                cout << tprocess.tiempotranscurrido;
                                gotoxy(3,7);
                                cout << "            ";
                                y = y + 1;
                            }
                        }
                    }
                    queue<Process> tempQueue = queues[i];  // Copia temporal de la cola
                    y = 7;
                    ay = 7;
                    contadorded = 5;
                    while(contadorded >=0)
                    {
                        gotoxy(3,y);
                        cout << "             ";
                        y = y + 1;
                        contadorded--;
                    }
                    y = 7;
                    while (!tempQueue.empty()) {
                        // fila 1
                        Process tprocess = tempQueue.front();
                        tempQueue.pop();
                        gotoxy(3,5);
                        cout << "ID";
                        gotoxy(3,y);
                        cout << "  ";
                        gotoxy(3,y);
                        cout << tprocess.programNumber;
                        gotoxy(6,5);
                        cout << "TME";
                        gotoxy(6,y);
                        cout << "  ";
                        gotoxy(6,y);
                        cout << tprocess.estimatedTime;
                        gotoxy(10,5);
                        cout << "TT";
                        gotoxy(10,y);
                        cout << "  ";
                        gotoxy(10,y);
                        cout << tprocess.tiempotranscurrido;
                        gotoxy(3,7);
                        cout << "            ";
                        y = y + 1;
                    }
                    Sleep(1000);
                }
                gotoxy(22,7);
                cout << "   ";
                gotoxy(22,9);
                cout << "          ";;
                gotoxy(22,11);
                cout << "   ";
                gotoxy(22,13);
                cout << "   ";
                gotoxy(22,15);
                cout << "   ";
                while(queues[i].empty()){ // mi salvación para el problema de bloqueos
                    Sleep(1000);
                    int contadorded = 5;
                    while(contadorded >=0)
                    {
                        gotoxy(3,by);
                        cout << "             ";
                        by = by + 1;
                        contadorded--;
                    }
                    by = 19;
                    if(!bloqueados.empty()){
                        pulsar = 'm';
                        queue<Process> tempbloq = bloqueados;
                        while (!tempbloq.empty()){
                            Process temporal = tempbloq.front();
                            tempbloq.pop();
                            temporal.tiempobloqueado = temporal.tiempobloqueado - 1;
                            // Aquí se imprimirán los datos de cada proceso en la cola de bloqueados
                            gotoxy(3, by);
                            cout << temporal.programNumber;
                            gotoxy(6, by);
                            cout << temporal.tiempobloqueado; // tiempo bloqueado
                            by = by + 1;
                            bloqueados.pop();
                            bloqueados.push(temporal);
                            if (temporal.tiempobloqueado <= 0) {
                                temporal.tiempobloqueado = 8;
                                queues[i].push(temporal);
                                bloqueados.pop();
                                contadordeprocesoslistos = contadordeprocesoslistos + 1;
                            }
                        }
                    }         
                }
                // fila 3           
                gotoxy(34,3);
                cout << "Terminados";
                gotoxy(34,5);
                cout << "ID";
                gotoxy(38,5);
                cout << "Ope";
                gotoxy(60,5);
                cout << "Res";
                gotoxy(74,5);
                cout << "Tanda";
                gotoxy(74,6);
                cout << "Guia";
                if(pulsar == 'e'){
                    contadordeprocesoslistos = contadordeprocesoslistos - 1;
                    gotoxy(3,3);
                    cout << "             ";
                    gotoxy(3,3);
                    cout << "P Listos #" << contadordeprocesoslistos << endl; // Modi
                    gotoxy(34,ffy);
                    cout << "      ";
                    gotoxy(34,ffy);
                    cout << process.programNumber;
                    gotoxy(38,ffy);
                    cout << "         ";
                    gotoxy(38,ffy);
                    cout << process.number1 << process.operation << process.number2;
                    gotoxy(60,ffy);
                    cout << "      ";
                    process.result = "Error";
                    process.result2 = "Error";
                    gotoxy(60,ffy);
                    cout << process.result;
                    gotoxy(66,ffy);
                    cout << "      ";
                    gotoxy(74,ffy);
                    cout << process.currentQueue;
                    ffy = ffy + 1;
                    pulsar = ' ';
                    // acomodar fila 1
                    gotoxy(3,ay);
                    cout << "       ";
                    ay = ay + 1;
                    queues[i].pop();
                    procesosTotales = procesosTotales - 1;
                    totalProcessesQueue->push(process);
                    queue<Process> tempQueue = queues[i];  // Copia temporal de la cola
                    y = 7;
                    ay = 7;
                    int contadorded = 5;
                    while(contadorded >=0)
                    {
                        gotoxy(3,y);
                        cout << "             ";
                        y = y + 1;
                        contadorded--;
                    }
                    y = 7;
                    while (!tempQueue.empty()) {
                        // fila 1
                        Process tprocess = tempQueue.front();
                        tempQueue.pop();
                        gotoxy(3,5);
                        cout << "ID";
                        gotoxy(3,y);
                        cout << "  ";
                        gotoxy(3,y);
                        cout << tprocess.programNumber;
                        gotoxy(6,5);
                        cout << "TME";
                        gotoxy(6,y);
                        cout << "  ";
                        gotoxy(6,y);
                        cout << tprocess.estimatedTime;
                        gotoxy(10,5);
                        cout << "TT";
                        gotoxy(10,y);
                        cout << "  ";
                        gotoxy(10,y);
                        cout << tprocess.tiempotranscurrido;
                        gotoxy(3,7);
                        cout << "            ";
                        y = y + 1;
                    }
                    bool flag = false;
                    int buscador = 0;
                    while (!flag){
                        buscador = buscador + 1;
                        if (i + a < maxQueues) {
                            if (!queues[i + a].empty()) {
                                Process otherqueue = queues[i + a].front(); // Obtenemos el elemento de la cola origen
                                queues[i + a].pop(); // Eliminamos el elemento de la cola origen
                                otherqueue.tiempollegada = timecontador;
                                queues[i].push(otherqueue); // Insertamos el elemento en la cola destino (queues[i])
                                contadordeprocesosnuevos = contadordeprocesosnuevos - 1;
                                gotoxy(1,1);
                                cout << "                      ";
                                gotoxy(1,1);
                                cout << "Procesos Nuevos: " << contadordeprocesosnuevos; // Modi
                                contadordeprocesoslistos = contadordeprocesoslistos + 1;
                                gotoxy(3,3);
                                cout << "             ";
                                gotoxy(3,3);
                                cout << "P Listos #" << contadordeprocesoslistos << endl; // Modi
                                flag = true;
                            } else {
                                a = a + 1; // Incrementamos 'a' si la cola origen está vacía
                            }
                        }
                        if(buscador == 5){
                            flag = true;
                        }
                    }
                }
                else if (pulsar == 'i')
                {
                    contadordeprocesoslistos = contadordeprocesoslistos - 1;
                    if(process.estimatedTime == process.tiempotranscurrido){
                        gotoxy(34,ffy);
                        cout << "      ";
                        gotoxy(34,ffy);
                        cout << process.programNumber;
                        gotoxy(38,ffy);
                        cout << "         ";
                        gotoxy(38,ffy);
                        cout << process.number1 << process.operation << process.number2;
                        gotoxy(60,ffy);
                        cout << "      ";
                        gotoxy(60,ffy);
                        cout << process.result;
                        gotoxy(66,ffy);
                        cout << "      ";
                        gotoxy(74,ffy);
                        cout << process.currentQueue;
                        ffy = ffy + 1;
                        // acomodar fila 1
                        gotoxy(3,ay);
                        cout << "       ";
                        ay = ay + 1;
                        queues[i].pop();
                        procesosTotales = procesosTotales - 1;
                        gotoxy(3,acomodainterumpir);
                        cout << "            ";
                        acomodainterumpir = acomodainterumpir - 1;
                        totalProcessesQueue->push(process);
                    }
                    queue<Process> tempQueue = queues[i];  // Copia temporal de la cola
                    y = 7;
                    ay = 7;
                    int contadorded = 5;
                    while(contadorded >=0)
                    {
                        gotoxy(3,y);
                        cout << "             ";
                        y = y + 1;
                        contadorded--;
                    }
                    y = 7;
                    while (!tempQueue.empty()) {
                        // fila 1
                        Process tprocess = tempQueue.front();
                        tempQueue.pop();
                        gotoxy(3,5);
                        cout << "ID";
                        gotoxy(3,y);
                        cout << "  ";
                        gotoxy(3,y);
                        cout << tprocess.programNumber;
                        gotoxy(6,5);
                        cout << "TME";
                        gotoxy(6,y);
                        cout << "  ";
                        gotoxy(6,y);
                        cout << tprocess.estimatedTime;
                        gotoxy(10,5);
                        cout << "TT";
                        gotoxy(10,y);
                        cout << "  ";
                        gotoxy(10,y);
                        cout << tprocess.tiempotranscurrido;
                        gotoxy(3,7);
                        cout << "            ";
                        y = y + 1;
                    }
                }
                else if (pulsar == 'm'){
                    contadordeprocesoslistos = contadordeprocesoslistos - 1;
                }
                else {
                    contadordeprocesoslistos = contadordeprocesoslistos - 1;
                    gotoxy(3,3);
                    cout << "             ";
                    gotoxy(3,3);
                    cout << "P Listos #" << contadordeprocesoslistos << endl; // Modi
                    gotoxy(34,ffy);
                    cout << "      ";
                    gotoxy(34,ffy);
                    cout << process.programNumber;
                    gotoxy(38,ffy);
                    cout << "         ";
                    gotoxy(38,ffy);
                    cout << process.number1 << process.operation << process.number2;
                    gotoxy(60,ffy);
                    cout << "      ";
                    gotoxy(60,ffy);
                    cout << process.result;
                    gotoxy(66,ffy);
                    cout << "      ";
                    gotoxy(74,ffy);
                    cout << process.currentQueue;
                    ffy = ffy + 1;
                    // acomodar fila 1
                    gotoxy(3,ay);
                    cout << "       ";
                    ay = ay + 1;
                    process.tiemposervicio = process.estimatedTime;
                    queues[i].pop();
                    procesosTotales = procesosTotales - 1;
                    totalProcessesQueue->push(process);
                    bool flag = false;
                    int buscador = 0;
                    while (!flag){
                        buscador = buscador + 1;
                        if (i + a < maxQueues) {
                            if (!queues[i + a].empty()) {
                                Process otherqueue = queues[i + a].front(); // Obtenemos el elemento de la cola origen
                                queues[i + a].pop(); // Eliminamos el elemento de la cola origen
                                otherqueue.tiempollegada = timecontador;
                                queues[i].push(otherqueue); // Insertamos el elemento en la cola destino (queues[i])
                                contadordeprocesosnuevos = contadordeprocesosnuevos - 1;
                                gotoxy(1,1);
                                cout << "                      ";
                                gotoxy(1,1);
                                cout << "Procesos Nuevos: " << contadordeprocesosnuevos; // Modi
                                contadordeprocesoslistos = contadordeprocesoslistos + 1;
                                gotoxy(3,3);
                                cout << "             ";
                                gotoxy(3,3);
                                cout << "P Listos #" << contadordeprocesoslistos << endl; // Modi
                                flag = true;
                            } else {
                                a = a + 1; // Incrementamos 'a' si la cola origen está vacía
                            }
                        }
                        if(buscador == 5){
                            flag = true;
                        }
                    }
                }
                pulsar = ' ';
                queue<Process> tempQueue = queues[i];  // Copia temporal de la cola
                y = 7;
                ay = 7;
                int contadorded = 5;
                while(contadorded >=0)
                {
                    gotoxy(3,y);
                    cout << "             ";
                    y = y + 1;
                    contadorded--;
                }
                y = 7;
                while (!tempQueue.empty()) {
                    // fila 1
                    Process tprocess = tempQueue.front();
                    tempQueue.pop();
                    gotoxy(3,5);
                    cout << "ID";
                    gotoxy(3,y);
                    cout << "  ";
                    gotoxy(3,y);
                    cout << tprocess.programNumber;
                    gotoxy(6,5);
                    cout << "TME";
                    gotoxy(6,y);
                    cout << "  ";
                    gotoxy(6,y);
                    cout << tprocess.estimatedTime;
                    gotoxy(10,5);
                    cout << "TT";
                    gotoxy(10,y);
                    cout << "  ";
                    gotoxy(10,y);
                    cout << tprocess.tiempotranscurrido;
                    gotoxy(3,7);
                    cout << "            ";
                    y = y + 1;
                }
            }
            int contador = 0;
            int by = 9;
            while (contador <= 5){
                gotoxy(3,by);
                cout << "       ";
                by = by + 1;
                contador++;
            }
        }
    }
    gotoxy(22,7);
    cout << "   ";
    gotoxy(22,9);
    cout << "          ";;
    gotoxy(22,11);
    cout << "   ";
    gotoxy(22,13);
    cout << "   ";
    gotoxy(22,15);
    cout << "   ";
    procesosTotales = 0;
    gotoxy(80,7);
    cout << "            ";
    gotoxy(80,30);
    system("pause");
    system("cls");
    ThisIsOrder();
    // imrpimir datos finales
    gotoxy(3,3);
    cout << "Procesos terminados";
    gotoxy(3,5);
    cout << "ID"; // ID
    gotoxy(7,5);
    cout << "TL"; // tiempo llegada
    gotoxy(11,5);
    cout << "TF"; // tiempo finalizacion
    gotoxy(15,5);
    cout << "TR"; // tiempo retorno
    gotoxy(19,5);
    cout << "TRa"; // tiempo respuesta
    gotoxy(25,5);
    cout << "TE"; // tiempo espera
    gotoxy(31,5);
    cout << "TS"; // tiempo servicio
    gotoxy(37,5);
    cout << "TME"; // tiempo estimado
    gotoxy(43,5);
    cout << "Estado"; // Tipo de finalización (Normal o Error)
    ffy = 7;
    while(!totalProcessesQueue->empty()){
        Process process = totalProcessesQueue->front();
        totalProcessesQueue->pop();
        gotoxy(3,ffy);
        cout << process.programNumber;
        gotoxy(7,ffy);
        cout << process.tiempollegada;
        gotoxy(11,ffy);
        cout << process.tiempofinalizacion;
        gotoxy(15,ffy);
        cout << process.tiemporetorno;
        gotoxy(19,ffy);
        cout << process.tiemporespuesta;
        gotoxy(25,ffy); 
        cout << process.tiempoespera;
        gotoxy(31,ffy);
        cout << process.tiemposervicio;
        gotoxy(37,ffy);
        cout << process.estimatedTime;
        gotoxy(43,ffy);
        cout << process.result2;
        ffy = ffy + 1;
    }
}


int main() {
    HWND consoleWindow = GetConsoleWindow();
    RECT desktop;
    GetWindowRect(GetDesktopWindow(), &desktop);
    MoveWindow(consoleWindow, desktop.left, desktop.top, desktop.right, desktop.bottom, TRUE);
    system("pause");
    ThisIsOrder();
    datosLotes();
    system("cls");
    IWillHaveOrder();
    imprimirdata();
    gotoxy(80,30);
    system("pause");
    system("cls");
    return 0;
}
