#ifndef MENUS_H_INCLUDED
#define MENUS_H_INCLUDED

#include <windows.h>
#include "quick/controller.h"

void mainMenu() {
    int resp;

    system("cls");
    cout << "=======================================================================================================================" << endl;
    cout << "                                                 THE STORE" << endl;
    cout << "=======================================================================================================================" << endl;
    cout << "--> Digite 1 para ver os clientes" << endl;
    cout << "--> Digite 2 para ordenar os clientes" << endl;
    cout << "=======================================================================================================================" << endl;
    cout << "Digite sua opcao: ";
    cin >> resp;

    switch(resp) {
    case 1:
        mostrarClients();
        system("pause");
        break;
    case 2:
        quickMenu();
        break;
    }
    mainMenu();
}


#endif // MENUS_H_INCLUDED
