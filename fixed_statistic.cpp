// recuerda usar la tabulación en la función gráfica conchetumare
#include <iostream>
#include <math.h>
#include <vector>
#include <string.h>
#include <algorithm>
#include <stdlib.h>
//#include <locale.h>

#define range(min,max) max-min                      //definicion del rango
#define interval_by_root(n) sqrt(n)                 //definición de intervalo por raíz cuadrada
#define sturge_formula(n) (1 + 3.322 * log10(n));   //definición de intervalo por regla de sturge
#define getrandom(min, max) \
    ((rand()%(int)(((max) + 1)-(min)))+ (min))      
//elección aleatoria por recomendación

using namespace std;

/* Declaración de funciones de ayuda y funcion de arranque */
void todo_help();
void run();

/* ####################################### */

/* Declaración de matriz, funciones para graficar e imprimir tablas*/
int get_matrix(); // Ordenamiento de posiciones para simular pixeles/unidades.
void graph(); // Función  para imprimir una gráfica de barras en la consola.
void print_table(double data[], int size);
void print_sorted_data(double data[], int size);

/* ####################################### */

/* Funciones de estadística */
double* data_sort(double data[], int limit)
{
    sort(data, data + limit);
    print_sorted_data(data, limit);
    return data;
    //
} // Trying to do this shit in english cuz im too lazy to change the keyboard layout in the console

double** matrix_pointer; 
int global_cont, global_intervals; //Contador con propositos multiples

double get_freq(double data[], int nElements)
{
    double detected[nElements][2], to_search;
    int cont, position=0;
    for (int i=0;i<nElements;i++){
        cont=0;
        to_search = data[position];
        int j_iterator=0;
        while ((position<nElements) && (to_search == data[position]))
        {
            cont++; j_iterator++; position++;
        }
        detected[i][0] = to_search;
        detected[i][1] = cont;
        //
    }
    int counter_s=0;
    bool end_sflag = false;
    cout << "-------------------------------------- \nFrequency without intervals" << endl;
    for (int i=0;i<nElements;i++){
        for (int j=0;j<2;j++){
            if (detected[i][1]!=0){
                cout << detected[i][j] << " - ";
                counter_s++;
            } else {
                end_sflag = true;
                break;
            }
            //
        }
        if (end_sflag == true){
            break;
        }
        cout << endl;
    }
    int s_size = counter_s/2;
    global_cont = s_size;

    //Reservar memoria para la matriz dinamica
    matrix_pointer = new double*[s_size]; //Reserva memoria para las filas que apuntaran a las columnas

    for (int i=0;i<s_size;i++){
        matrix_pointer[i] = new double[2]; 
    } 

    for (int i=0;i<s_size;i++){
        for (int j=0;j<2;j++){
            *(*(matrix_pointer+i)+j) = detected[i][j];
        }
    }

    /*
    for (int i=0;i<s_size;i++){
        for (int j=0;j<2;j++){
            cout << "|" << *(*(matrix_pointer+i)+j);
        }
        cout << endl;
    }
    */

    //
    cout << "--------------------------------------" << endl;
    return 0;
    //
}

double *interval_pointer = new double[global_intervals];

void get_interval_info(int nElements, double max, double min)
{
    char type; int intervals;
    cout << "Intervals by: Square [R]oot / [S]turge (Sturge formula) -> ";
    cin >> type;
    double d_range = range(min, max);
    cout << endl << "rango = " << d_range << endl;
    
    if (type=='R'||type=='r'){
        intervals = interval_by_root(nElements);
        //
    }else if (type=='S'||type=='s'){
        intervals = sturge_formula(nElements);
        //
    }

    cout << "Classes = " << intervals << endl;
    double w_interval = d_range / intervals;
    int round_i = w_interval * 100; double round_d = round_i;
    //cout << "round_d = " << round_d << endl; // eliminar linea
    w_interval = round_d / 100;
    cout << "Interval widht = " << w_interval << endl;

    //interval_pointer = new double[global_intervals];
    
    //transcription from first code version
    int position=0;
    double aux = min - w_interval;
    for (int i=0;i<intervals*2;i++){
        for (int j=0;j<2;j++){
            aux+=w_interval;
            *(interval_pointer+(position+j))= aux;
        }
        position += 2;
        aux+=0.01;
        aux-=w_interval;
    }
    global_intervals = intervals * 2;
    
}

void get_data()
{
    cout << "Enter the number of items -> ";
    int e;
    cin >> e;
    cout << "Enter all data to be tabulated -> \n{ " << endl;
    double todo_data[e];
    for (int i=0;i<e;i++){
        cin >> todo_data[i];
    }
    cout << "}" << endl;
    double *data_pointer = data_sort(todo_data, e), sorted_data[e]; // Gets the pointer to pass arrays between functions.
    for (int i=0; i<e;i++){
        sorted_data[i]=data_pointer[i];
    }
    get_freq(sorted_data, e); // Gets frequency.
    double freq_matrix[global_cont][2];
    for (int i=0;i<global_cont;i++){
        for (int j=0;j<2;j++){
            freq_matrix[i][j] = *(*(matrix_pointer+i)+j);
        }
    }
    //
    //Borrar el espacio reservado

    get_interval_info(e, sorted_data[e-1], sorted_data[0]);

    double got_intervals[global_intervals];

    //
    for (int i=0;i<global_intervals;i++){
        got_intervals[i] = *(interval_pointer+i);
        //
    }

    double mark_dt = (got_intervals[1] - got_intervals[0])/2;

    cout.precision(3);
    for (int i=1;i<global_intervals;i+=2){
        cout << got_intervals[i-1] << " - " << got_intervals[i] << " - Class mark = " << got_intervals[i-1] + mark_dt;
        cout << endl;
        //
    }
    
    //Below this comment lies an attempt to add the frequency into the intervals, by doing
    //some for(i;i;i) cycles, the number of times that one number repeats itself is added
    //to one value in the array only if it's within the range of that interval.

    //The thing here was that the final array had trash values, i don't had the time to think
    //about it, so I'll leave it there until I come back to this code. 
    /*
    int aux_freq=0;
    int iF_size = global_intervals/2;
    int freq_itr[iF_size], fI_pos=0;

    for (int i=0;i<iF_size;i++){
        aux_freq=0;
        for (int j=0;(freq_matrix[1][j]>=got_intervals[i] && freq_matrix[1][j]<=got_intervals[i+1]);j++){
            //
            aux_freq+=freq_matrix[1][j];
            freq_itr[fI_pos]=aux_freq;
        }
        fI_pos++;
    }

    for (int i=0;i<iF_size;i++){
        cout << "aaaa = " <<  freq_itr[i] << " ";
    }
    */

    //
    cout << endl;

}

/* ####################################### */

////////////////////////////////////////////////////////////////////////
int main ()
{
    //setlocale(LC_CTYPE, "Spanish");
    run();
    for (int i=0;i<global_cont;i++){
        delete[] matrix_pointer[i];
    }
    delete[] matrix_pointer;

    delete[] interval_pointer;
    return 0;
}
////////////////////////////////////////////////////////////////////////


void run()
{
    string instruction = "l";
    while (instruction != "q" || instruction != "quit")
    {
        cout << "~#command -> ";
        cin >> instruction;
        if (instruction == "input-d" || instruction == "input--data" || instruction == "input"){
            get_data();
        //
        } else
        if (instruction == "input-g" || instruction == "input-graph"){
            get_data();
            graph();
            //
        }else
        if (instruction == "h" || instruction == "help"){
            todo_help();
        } else
        if (instruction == "q" || instruction == "quit"){break;}
    }
    //
}

void graph()
{
    //
}

/* ########################################################## */
void todo_help()
{
    cout << "Commands:\n\n *input = uses the statistics function, get values for a frequency table\n   AKA: input-d/input--data";
    cout << "\n\n *input-g = uses the statistics function and prints a graph in console using a matrix, it isn't complete, so feel free to make it using a graphic library or something\n    AKA: input--graph";

    cout << "\n\n *h = to show this help message \n    AKA: help";
    cout << "\n\n *q = exits the program \n   AKA: quit";

    cout << endl << endl;


}

void print_sorted_data(double data[], int size)
{
    cout << endl << "------------------------------------------" << endl;
    cout << "Sorted data:" << endl;
    for (int i=0;i<size;i++){
        cout << data[i] << " ";
    }
    cout << endl << "------------------------------------------";
    cout << endl << "Max: " << data[size-1] << "\nMin: " << data[0];
    cout << endl << "------------------------------------------" << endl;
    //
}
