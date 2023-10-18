#ifndef CONTROLLER_H_INCLUDED
#define CONTROLLER_H_INCLUDED

#include <iostream>
#include <windows.h>
#include "qndProdutos.h"
#include "../menus.h"

int quickMenu() {
    int resp;

    system("cls");
    cout << "=======================================================================================================================" << endl;
    cout << "                                                    Quick Menu" << endl;
    cout << "=======================================================================================================================" << endl;
    cout << "--> Digite 1 para organizar por quantidade de produtos" << endl;
    cout << "--> Digite 0 para sair" << endl;
    cout << "=======================================================================================================================" << endl;
    cout << "Digite sua opcao: ";
    cin >> resp;

    switch(resp) {
        case 0:
            return 0;
            break;
        case 1:
            quickPorQndDeProdutos();
            break;
    }
    quickMenu();
}

#endif // CONTROLLER_H_INCLUDED
