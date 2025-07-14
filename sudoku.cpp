#include <cstdlib>
#include <iostream>
#include <thread>
using namespace std;

const int SIZE = 9;

int board[SIZE][SIZE];
int initialBoard[SIZE][SIZE] = {
    {5, 3, 0, 0, 7, 0, 0, 0, 0},
    {6, 0, 0, 1, 9, 5, 0, 0, 0},
    {0, 9, 8, 0, 0, 0, 0, 6, 0},
    {8, 0, 0, 0, 6, 0, 0, 0, 3},
    {4, 0, 0, 8, 0, 3, 0, 0, 1},
    {7, 0, 0, 0, 2, 0, 0, 0, 6},
    {0, 6, 0, 0, 0, 0, 2, 8, 0},
    {0, 0, 0, 4, 1, 9, 0, 0, 5},
    {0, 0, 0, 0, 8, 0, 0, 7, 9}
};
 
void copiarTablero() {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            board[i][j] = initialBoard[i][j];
}

void clearTerminalAfterTime(int s) {
    std::this_thread::sleep_for(std::chrono::seconds(s));
    std::system("cls"); 
}

void printBoard() {
    cout << "    ";
    for (int col = 0; col < SIZE; col++) {
        if (col % 3 == 0 && col != 0)
            cout << "| ";
        cout << col << " ";
    }
    cout << "\n  -----------------------------\n";

    for (int row = 0; row < SIZE; row++) {
        cout << row << " | ";
        for (int col = 0; col < SIZE; col++) {
            if (col % 3 == 0 && col != 0)
                cout << "| ";
            if (board[row][col] == 0)
                cout << ". ";
            else
                cout << board[row][col] << " ";
        }
        cout << endl;

        if ((row + 1) % 3 == 0 && row != SIZE - 1)
            cout << "  -----------------------------\n";
    }
}

bool isValid(int row, int col, int num) {
    for (int i = 0; i < SIZE; i++)
        if (board[row][i] == num || board[i][col] == num)
            return false;

    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[startRow + i][startCol + j] == num)
                return false;

    return true;
}

bool quedanMovimientosValidos() {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (board[i][j] == 0)
                for (int num = 1; num <= 9; num++)
                    if (isValid(i, j, num))
                        return true;
    return false;
}

void insertNumber(int row, int col, int num) {
    if (initialBoard[row][col] != 0) {
        cout << "No puedes modificar una pista original.\n";
    } else if (board[row][col] != 0) {
        cout << "Esa casilla ya contiene un numero. Borralo primero si deseas cambiarlo.\n";
    } else if (!isValid(row, col, num)) {
        cout << "Movimiento invalido segun las reglas del Sudoku.\n";
    } else {
        board[row][col] = num;
        cout << "Numero insertado correctamente.\n";
    }
}

void borrarNumero(int fila, int columna) {
    if (initialBoard[fila][columna] != 0) {
        cout << "No puedes borrar una pista original.\n";
    } else if (board[fila][columna] == 0) {
        cout << "Esa casilla ya esta vacia.\n";
    } else {
        board[fila][columna] = 0;
        cout << "Numero borrado exitosamente.\n";
    }
}

bool isBoardComplete() {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (board[i][j] == 0)
                return false;
    return true;
}

int main() {
    char jugarDeNuevo;

    do {
        copiarTablero();
        cout << "Bienvenido al Sudoku!\n";
        bool abandono = false;

        while (!isBoardComplete()) {
            if (!quedanMovimientosValidos()) break;

            printBoard();

            int opcion;
            cout << "\nElige una opcion:\n";
            cout << "1. Insertar numero\n";
            cout << "2. Borrar numero\n";
            cout << "3. Salir del juego\n";
            cout << "Opcion: ";

                if (!(cin >> opcion)) {
                    cout << "Solo se permiten numeros.\n";
                    cin.clear();
                    cin.ignore(10000, '\n');
                    clearTerminalAfterTime(2);
                    continue;
                }

            if (opcion == 3) {
                abandono = true;
                break;
            } else if (opcion == 1) {
                int fila, columna, numero;

                cout << "Introduce la fila (0-8): ";
                if (!(cin >> fila)) {
                    cout << "Solo se permiten numeros.\n";
                    cin.clear(); cin.ignore(10000, '\n');
                    clearTerminalAfterTime(2);
                    continue;
                }
                if (fila < 0 || fila >= 9) {
                    cout << "Fuera del rango permitido.\n";
                    cin.clear(); cin.ignore(10000, '\n');
                    clearTerminalAfterTime(2);
                    continue;
                }

                cout << "Introduce la columna (0-8): ";
                if (!(cin >> columna)) {
                    cout << "Solo se permiten numeros.\n";
                    cin.clear(); cin.ignore(10000, '\n');
                    clearTerminalAfterTime(2);
                    continue;
                }
                if (columna < 0 || columna >= 9) {
                    cout << "Fuera del rango permitido.\n";
                    cin.clear(); cin.ignore(10000, '\n');
                    clearTerminalAfterTime(2);
                    continue;
                }

                cout << "Introduce el número (1-9): ";
                if (!(cin >> numero)) {
                    cout << "Solo se permiten numeros.\n";
                    cin.clear(); cin.ignore(10000, '\n');
                    clearTerminalAfterTime(2);
                    continue;
                }
                if (numero < 1 || numero > 9) {
                    cout << "Fuera del rango permitido.\n";
                    cin.clear(); cin.ignore(10000, '\n');
                    clearTerminalAfterTime(2);
                    continue;
                }

                insertNumber(fila, columna, numero);
                clearTerminalAfterTime(2);

            } else if (opcion == 2) {
                int fila, columna;

                cout << "Introduce la fila (0-8): ";
                if (!(cin >> fila)) {
                    cout << "Solo se permiten numeros.\n";
                    cin.clear(); cin.ignore(10000, '\n');
                    clearTerminalAfterTime(2);
                    continue;
                }
                if (fila < 0 || fila >= 9) {
                    cout << "Fuera del rango permitido.\n";
                    cin.clear(); cin.ignore(10000, '\n');
                    clearTerminalAfterTime(2);
                    continue;
                }

                cout << "Introduce la columna (0-8): ";
                if (!(cin >> columna)) {
                    cout << "Solo se permiten numeros.\n";
                    cin.clear(); cin.ignore(10000, '\n');
                    clearTerminalAfterTime(2);
                    continue;
                }
                if (columna < 0 || columna >= 9) {
                    cout << "Fuera del rango permitido.\n";
                    cin.clear(); cin.ignore(10000, '\n');
                    clearTerminalAfterTime(2);
                    continue;
                }

                borrarNumero(fila, columna);
                clearTerminalAfterTime(2);

            } else {
                cout << "No existe entre las opciones.\n";
                clearTerminalAfterTime(2);
                continue;
            }
        }

        if (isBoardComplete()) {
            cout << "\nFelicidades! Has completado el Sudoku.\n";
        } else if (abandono) {
            cout << "\nSaliste del juego. Hasta la proxima!\n";
        } else {
            cout << "\nNo quedan movimientos validos. Has perdido!\n";
        }

        printBoard();
        cout << "\nDeseas jugar otra vez? (s/n): ";
        cin >> jugarDeNuevo;
        clearTerminalAfterTime(2);

    } while (jugarDeNuevo == 's' || jugarDeNuevo == 'S');

    cout << "Gracias por jugar!\n";
    return 0;
}
