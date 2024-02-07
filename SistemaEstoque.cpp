//============================================================================
// Name        : SistemaEstoque.cpp
// Author      : João Pedro
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
/*
 * O objeto db de DatabaseManager deve ser passado pelas funções até ser usado para os comandos sql
 *
*/

#include <iostream>
#include <stdio.h>
#include "DatabaseManager.h"
#include "ProductManager.h"
using namespace std;

// Header Function - shows some instructions about the system
void header(){
	cout << "| Management System |\n" << endl;
	cout << "---------------------------------------------------------\n"
			"Here are the commands for using the system:\n"
			"New product - C\n"
			"List products - R\n"
			"Update product- U\n"
			"Delete product - D\n"
			"Exit - E\n"
			"---------------------------------------------------------\n" << endl;
	return;
}

// Admin Function - manages the user inputs
void admin(DatabaseManager db){
	ProductManager inst;
	char var = '\0';

	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	while(1){
		cout << "Command input: ";
		cin >> var;
		cout << endl;

		if(var == 'C' || var == 'c')
			inst.create(db);
		else if(var == 'R' || var == 'r')
			inst.read();
		else if(var == 'U' || var == 'u')
			inst.update();
		else if(var == 'D' || var == 'd')
			inst.delete_();
		else if(var == 'E' || var == 'e')
			break;
		else
			cout << "Invalid option!" << endl;
	}

	return;
}

int main(){
	DatabaseManager db;

	db.db_connect();
	header();
	admin(db);

	return 0;
}
