#include <iostream>
using namespace std;

class ProblemaTransporte {
private:
    int m, n;
    int** costos, **asignacion;
    int* oferta, *demanda;
    bool* filaActiva, *columnaActiva;

    double calcularPenalizacionFila(int i) {
        int min = 1000000, max = -1;
        for (int j = 1; j <= n; j++) {
            if (columnaActiva[j]) {
                if (costos[i][j] < min) min = costos[i][j];
                if (costos[i][j] > max) max = costos[i][j];
            }
        }
        return (min + max) / 2.0;
    }

    double calcularPenalizacionColumna(int j) {
        int min = 1000000, max = -1;
        for (int i = 1; i <= m; i++) {
            if (filaActiva[i]) {
                if (costos[i][j] < min) min = costos[i][j];
                if (costos[i][j] > max) max = costos[i][j];
            }
        }
        return (min + max) / 2.0;
    }

    void inicializarMatrices() {
        costos = new int*[m + 1];
        asignacion = new int*[m + 1];
        for (int i = 1; i <= m; i++) {
            costos[i] = new int[n + 1];
            asignacion[i] = new int[n + 1];
            for (int j = 1; j <= n; j++) asignacion[i][j] = 0;
        }

        oferta = new int[m + 1];
        demanda = new int[n + 1];
        filaActiva = new bool[m + 1];
        columnaActiva = new bool[n + 1];
    }

    void liberarMemoria() {
        for (int i = 1; i <= m; i++) {
            delete[] costos[i];
            delete[] asignacion[i];
        }
        delete[] costos;
        delete[] asignacion;
        delete[] oferta;
        delete[] demanda;
        delete[] filaActiva;
        delete[] columnaActiva;
    }

public:
    void leerDatos() {
        while (true) {
            cout << "Ingrese numero de origenes (filas): ";
            cin >> m;
            cout << "Ingrese numero de destinos (columnas): ";
            cin >> n;

            inicializarMatrices();

            cout << "Ingrese la matriz de costos (" << m << "x" << n << "):\n";
            for (int i = 1; i <= m; i++)
                for (int j = 1; j <= n; j++)
                    cin >> costos[i][j];

            cout << "Ingrese las ofertas:\n";
            for (int i = 1; i <= m; i++) {
                cin >> oferta[i];
                filaActiva[i] = true;
            }

            cout << "Ingrese las demandas:\n";
            for (int j = 1; j <= n; j++) {
                cin >> demanda[j];
                columnaActiva[j] = true;
            }

            cout << "\nMatriz de costos:\n";
            for (int i = 1; i <= m; i++){
                for (int j = 1; j <= n; j++){
                    cout << costos[i][j]<<"\t";
                }
                cout << "\n";
            }

            int totalOferta = 0, totalDemanda = 0;
            for (int i = 1; i <= m; i++) totalOferta += oferta[i];
            for (int j = 1; j <= n; j++) totalDemanda += demanda[j];

            if (totalOferta == totalDemanda) break;

            cout << "\nEl problema no esta balanceado:\n";
            cout << "   Total oferta: " << totalOferta << "\n";
            cout << "   Total demanda: " << totalDemanda << "\n";
            cout << "Por favor, ingrese datos balanceados.\n\n";

            liberarMemoria();
        }
    }

    void resolver() {
        while (true) {
            double* penalizacion = new double[m + n + 2];
            bool* esFila = new bool[m + n + 2];
            int* indice = new int[m + n + 2];
            int totalPen = 0;

            for (int i = 1; i <= m; i++) {
                if (filaActiva[i]) {
                    penalizacion[totalPen] = calcularPenalizacionFila(i);
                    cout << "Penalizacion fila " << i << ": " << (int)penalizacion[totalPen] << "\n";
                    esFila[totalPen] = true;
                    indice[totalPen] = i;
                    totalPen++;
                }
            }

            for (int j = 1; j <= n; j++) {
                if (columnaActiva[j]) {
                    penalizacion[totalPen] = calcularPenalizacionColumna(j);
                    cout << "Penalizacion columna " << j << ": " << (int)penalizacion[totalPen] << "\n";
                    esFila[totalPen] = false;
                    indice[totalPen] = j;
                    totalPen++;
                }
            }

            if (totalPen == 0) break;

            // Buscar penalización máxima
            double maxPen = -1;
            int idx = -1;
            for (int i = 0; i < totalPen; i++) {
                if (penalizacion[i] > maxPen) {
                    maxPen = penalizacion[i];
                    idx = i;
                }
            }

            if (esFila[idx])
                cout << "Penalizacion seleccionada: Fila " << indice[idx] << " con valor " << (int)maxPen << "\n";
            else
                cout << "Penalizacion seleccionada: Columna " << indice[idx] << " con valor " << (int)maxPen << "\n";


            // Elegir celda
            int filaSel = -1, colSel = -1;
            if (esFila[idx]) {
                filaSel = indice[idx];
                int menor = 1000000;
                for (int j = 1; j <= n; j++) {
                    if (columnaActiva[j] && costos[filaSel][j] < menor) {
                        menor = costos[filaSel][j];
                        colSel = j;
                    }
                }
            } else {
                colSel = indice[idx];
                int menor = 1000000;
                for (int i = 1; i <= m; i++) {
                    if (filaActiva[i] && costos[i][colSel] < menor) {
                        menor = costos[i][colSel];
                        filaSel = i;
                    }
                }
            }

            int cantidad = min(oferta[filaSel], demanda[colSel]);
            asignacion[filaSel][colSel] = cantidad;
            cout << "Asignar " << cantidad << " a celda (" << filaSel << "," << colSel << ") con costo " << costos[filaSel][colSel] << "\n\n";
            cout << "Estado actual de la matriz de asignaciones:\n";
            for (int i = 1; i <= m; i++) {
                for (int j = 1; j <= n; j++) {
                    cout << asignacion[i][j]<< "\t";
                }
                cout << "\n";
            }
            cout << "\n";

            oferta[filaSel] -= cantidad;
            demanda[colSel] -= cantidad;
            if (oferta[filaSel] == 0) filaActiva[filaSel] = false;
            if (demanda[colSel] == 0) columnaActiva[colSel] = false;

            delete[] penalizacion;
            delete[] esFila;
            delete[] indice;
        }
    }

    void imprimirResultado() {
        int total = 0;
        cout << "\nMatriz de asignaciones:\n";
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                cout << asignacion[i][j] << "\t";
                total += asignacion[i][j] * costos[i][j];
            }
            cout << "\n";
        }
        cout << "\nCosto total: " << total << "\n";
    }

    ~ProblemaTransporte() {
        liberarMemoria();
    }
};

int main() {
    ProblemaTransporte problema;
    problema.leerDatos();
    problema.resolver();
    problema.imprimirResultado();
    return 0;
}
