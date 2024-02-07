/*
 * ProductManager.h
 *
 *  Created on: 2 de fev. de 2024
 *      Author: joao
 */

#ifndef PRODUCTMANAGER_H_
#define PRODUCTMANAGER_H_
#include <iostream>
#include <stdio.h>
#include <limits>
#include "DatabaseManager.h"
using namespace std;

class ProductManager {
	public:
		// Function to create product
		void create(DatabaseManager db){
			try{
				string nome, tipo, marca;
				float preco;

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

				db.sql_insert(nome, marca, tipo, preco);
			} catch (const exception& e){
				cerr << "Error: " << e.what() << endl;
			}

			return;
		}

		void read(){

			return;
		}

		void update(){

			return;
		}

		void delete_(){

			return;
		}
};

#endif /* PRODUCTMANAGER_H_ */
