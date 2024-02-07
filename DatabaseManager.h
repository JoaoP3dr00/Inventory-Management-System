/*
 * DatabaseManager.h
 *
 *  Created on: 2 de fev. de 2024
 *      Author: joao
 */

#ifndef DATABASEMANAGER_H_
#define DATABASEMANAGER_H_
#include "libpq-fe.h"
#include <iostream>
#include <stdio.h>
using namespace std;

class DatabaseManager {
	private:
		PGresult *result;
		PGconn *conn;
		char x;
		const char *conninfo;

	public:
		static void exit_nicely(PGconn *conn){
			PQfinish(conn);
			exit(1);
		}

		virtual ~DatabaseManager(){
			exit_nicely(conn);
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
		}
	/*
		void sql_delete(){

		}

		void sql_update(){

		}

		void sql_select(){

		}
	*/
};

#endif /* DATABASEMANAGER_H_ */
