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
#include "libpq-fe.h"
using namespace std;

PGresult *result;
PGconn *conn;
char x;
const char *conninfo;
string nome, tipo, marca;
float preco;

/*#### Database Management Functions ####*/

void exit_nicely(PGconn *conn){
	PQfinish(conn);
	exit(1);
}

void conn_stats(PGconn *conn){
	cout << "--------------" << endl;
	cout << "Database name: " << PQdb(conn) << endl;
	cout << "Database user: " << PQuser(conn) << endl;
	cout << "Server host: " << PQhost(conn) << endl;
	cout << "Port: " << PQport(conn) << endl;
	cout << "Protocol v.: " << PQprotocolVersion(conn) << endl;
	cout << "DB v.: " << PQserverVersion(conn) << endl;
	cout << "SSL: " << PQsslInUse(conn) << endl;
	cout << "--------------" << endl << endl;

	return;
}

void db_connect(){
	try {
		conninfo = "host=localhost port=5432 dbname=db_estoque connect_timeout=10 user=postgres";

		// Make conection
		conn = PQconnectdb(conninfo);

		// Check connection
		if (PQstatus(conn) != CONNECTION_OK){
			fprintf(stderr, "Connection to database failed: %s\n\n", PQerrorMessage(conn));
			exit_nicely(conn);
		} else {
			fprintf(stdout, "Connection okay!\n");

			cout << "Want db stats? Y/N" << endl;
			cin >> x;
			if(x == 'y' || x == 'Y')
				conn_stats(conn);
		}
	} catch (const exception& e){
		cerr << "Error: " << e.what() << endl << endl;
	}
}

void sql_insert(string nome, string marca, string tipo, float preco){
	/* SQL Command */
	// Prepared Statements
	const char *paramValues[4] = {nome.c_str(), marca.c_str(), tipo.c_str(), to_string(preco).c_str()};
	int a = nome.length(), b = marca.length(), c = tipo.length(), d = to_string(preco).length();
	const int paramLengths[4] = {a, b, c, d};
	const int paramFormats[4] = {0, 0, 0, 0};

	result = PQexecParams(conn, "INSERT INTO product (nome, marca, tipo, preco) VALUES ($1, $2, $3, $4)", 4, NULL, paramValues, paramLengths, paramFormats, 0);

	// Checking result
	if(PQresultStatus(result) == PGRES_COMMAND_OK)
		cout << "New product created successfully!" << endl << endl;
	else
		cerr << "Message: " << PQresultErrorMessage(result) << endl << endl;
	PQclear(result);

	return;
}
/*
void sql_delete(){

}

void sql_update(){

}

void sql_select(){

}
*/

/*#### Product Management Functions ####*/

// Function to create product
void create(){
	try{
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "~ Creating new product ~\n" << endl;

		while(true){
			cout << "Name: ";

			getline(cin, nome);

			if(!nome.empty()){
				bool isstring = true;

				for(char c : nome){
					if(!isalpha(c) && !isspace(c)){
						isstring = false;
					}
				}

				if(isstring){
					break;
				}else{
					cout << "Type again!" << endl << endl;
				}
			}else{
				cout << "The name cannot be empty!" << endl << endl;
			}
		}

		while(true){
			cout << "Type: ";
			getline(cin, tipo);

			if(!tipo.empty()){
				bool isstring = true;

				for(char c : tipo){
					if(!isalpha(c) && !isspace(c)){
						isstring = false;
					}
				}

				if(isstring){
					break;
				}else{
					cout << "Type again!" << endl << endl;
				}
			}else{
				cout << "The name cannot be empty!" << endl << endl;
			}
		}

		while(true){
			cout << "Brand: ";
			getline(cin, marca);

			if(!marca.empty()){
				bool isstring = true;

				for(char c : marca){
					if(!isalpha(c) && !isspace(c)){
						isstring = false;
					}
				}

				if(isstring){
					break;
				}else{
					cout << "Type again!" << endl << endl;
				}
			}else{
				cout << "The name cannot be empty!" << endl << endl;
			}
		}

		while(true){
			cout << "Price: ";

			if(cin >> preco){
				if(preco >= 0){
					break;
				}else{
					cout << "Type again!" << endl << endl;;
				}
			}else{
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

				cout << "Invalid input!" << endl << endl;
			}
		}

		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << endl;

		sql_insert(nome, marca, tipo, preco);
	} catch (const exception& e){
		cerr << "Error: " << e.what() << endl;
	}
	return;
}

void read(){
	cout << "reading" << endl << endl;
	return;
}

void update(){

	return;
}

void delete_(){

	return;
}

/*#### System Management Functions ####*/

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
void admin(){
	char var = '\0';

	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	while(true){
		cout << "Command input: ";
		cin >> var;
		cout << endl;

		if(var == 'C' || var == 'c')
			create();
		else if(var == 'R' || var == 'r')
			read();
		else if(var == 'U' || var == 'u')
			update();
		else if(var == 'D' || var == 'd')
			delete_();
		else if(var == 'E' || var == 'e')
			break;
		else
			cout << "Invalid option!" << endl;
	}

	return;
}

int main(){
	db_connect();
	header();
	admin();

	return 0;
}
