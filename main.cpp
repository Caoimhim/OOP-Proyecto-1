/**
   @progName HTML Documentator
   @desc Crea Documentación de archivos en HTML
   @author Kevin Chinchilla
   A00825945
   @date 15 de febrero, 2019
 */

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//Global variables
string filename;
string parseLine(string buffer)
{ 
	
	for (unsigned short int i = 1; i < buffer.size(); i++ )
	{ 
		if (buffer[i] != 32 && buffer[i] != 9) 
		{ 
			if (buffer[i] == 64)
			{ 
				buffer = buffer.substr(i);
				return buffer;
			}
			else
			{ 
				i = buffer.size();
				return "-1";
			}
		}
	}
	return "-1";
}


bool findComments(string comments[1000], int size)
{ 
	size = 0;
	ifstream file;
	file.open (filename.c_str());
	if (!file.is_open())
	{ 
		cout << "No se encontro el archivo " << filename;
		return false;
	}

	string buffer;
	while (getline(file, buffer))
	{ 
		if (buffer.find("/**") != buffer.npos)
		{ 
			while ( buffer.find("*/") > 1)
			{ 
				getline(file, buffer);
				if ( buffer.find('@') != buffer.npos )
				{ 
					if ( buffer[0] == '@')
					{ 
						comments[size++] = buffer;
					}
					else if (buffer[0] == 32 || buffer[0] == 9)
					{ 
						buffer = parseLine(buffer);
						if (buffer != "-1")
						{ 
							comments[size++] = buffer;
						}
						
					}
				}
			}
		}
	}

	file.close();
	return true;
}

void writeHTML( string comments[1000], int size)
{ 
	ofstream file;
	string htmlName = filename.substr(0, filename.size()-3);
	htmlName.append("html");

	file.open(htmlName.c_str());
	file << "<!DOCTYPE html>\n<html>\n";



	file << "</html>";
	file.close();
}
int main (int argc, char *argv[])
{ 
	if (argc  < 2)
	{ 
		cout << "No se entraron parametros. \nNota: El programa también funciona si el archivo que se desea documentar se pasa como parametro.\n";
		//Talvez añadir flag de -h
		cin >> filename;
		filename.append(".cpp");
	}
	else
	{ 
		filename = argv[1];
	}

	//Variables
	string comments[1000];
	int size = 0;
	bool check;

	//Input
	check = findComments(comments, size);
	if (!check)
	{ 
		return 0;
	}
		

	//Processing
	//parseComments();

	//Output
	writeHTML(comments, size);
	
	return 0;
}
