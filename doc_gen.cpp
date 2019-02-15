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
/**
 @funcName parseLine
 @desc Revisa si la línea tiene una tag de documentación, y elimina los espacios en blanco antes de la tag si existen
 @param La string a revisar
 @return La línea, si contiene el tag, o nulo, si no
 */
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
				return "\0";
			}
		}
	}
	return "\0";
}

/**
 @funcName findComments
 @desc Busca comentarios en el formato correcto para documentar
 @param Un arreglo de strings donde se guardaran los comentarios para procesar, y el tamaño de este arreglo
 @return Verdadero, si todo sale bien, falso si no encuentra el archivo a revisar
 */
bool findComments(string comments[1000], int &size)
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
			do
			{ 
				getline(file, buffer);
				if ( buffer.find('@') != buffer.npos || buffer.find("*/") != buffer.npos)
				{ 
					if ( buffer[0] == '@' || buffer.find("*/") != buffer.npos)
					{ 
						comments[size++] = buffer;
					}
					else if (buffer[0] == 32 || buffer[0] == 9)
					{ 
						buffer = parseLine(buffer);
						if (buffer != "\0")
						{ 
							comments[size++] = buffer;
						}
						
					}
				}
			}
			while ( buffer.find("*/") > 1);
		}
	}

	file.close();
	return true;
}

/**
 @funcName findTitle
 @desc Busca la tag que contiene el nombre del programa
 @param El arreglo de strings con los comentarios a procesar, y el tamaño de este.
 @return La posición del arreglo donde está el nombre del programa, o -1 si no se euncuentra un nombre para el programa
 */
int findTitle(string comments [1000], int size)
{ 
	for ( short int i = 0; i < size; i++)
	{ 
		if (comments[i].find("@progName") != comments[i].npos)
		{ 
			return i;
		}
	}
	return -1;
}

/**
 @funcName writeSection
 @desc Escribe una sección de docmentación que incluyen autor, fecha de creación, parámetros y valor de retorno
 @param El stream para escribir el archivo, la posición del arreglo dónde inicia la sección, y el arreglo con los comentarios a procesar
 @return NONE
 */
void writeSection ( ofstream &oFile, int pos, string comments[1000])
{ 
	string buffer = comments[pos++];
	while (buffer.find("*/") == buffer.npos)
	{ 
		int tagEnd = buffer.find(" ");
		if (buffer.substr(0,tagEnd) == "@desc")
		{ 
			oFile << "<strong>Descripición:</strong> " << buffer.substr(tagEnd + 1) << "<br>\n";
		}
		if (buffer.substr(0,tagEnd) == "@author")
		{ 
			oFile << "<strong>Autor:</strong> " << buffer.substr(tagEnd + 1) << "<br>\n";
		}
		if (buffer.substr(0,tagEnd) == "@date")
		{ 
	
			oFile << "<strong>Fecha de elaboración:</strong> " << buffer.substr(tagEnd + 1) << "<br>\n";
		}
		if (buffer.substr(0,tagEnd) == "@param")
		{ 
			oFile << "<strong>Parametros:</strong> " << buffer.substr(tagEnd + 1) << "<br>\n";
		}
		if (buffer.substr(0,tagEnd) == "@return")
		{ 
			oFile << "<strong>Valor de retorno:</strong> " << buffer.substr(tagEnd + 1) << "<br>\n";
		}
		buffer = comments[pos++];
	}
	oFile << "<hr>";
}

/**
 @funcName writeHTML
 @desc Escribe el archivo HTML con la documentación
 @param El arreglo con los comentarios a procesar, y el tamaño de este
 @return NONE
 */
void writeHTML( string comments[1000], int size)
{ 
	ofstream oFile;
	string htmlName = filename.substr(0, filename.size()-3);
	htmlName.append("html");
	
	oFile.open(htmlName.c_str());
	oFile << "<!DOCTYPE html>\n<html>\n";

	//write header
	string buffer;
	oFile << "<head>\n";
	oFile << "<meta charset=\"UTF-8\">\n";
	oFile << "<title>Documentación del archivo " << filename << "</title>\n";
	oFile << "</head>\n";

	oFile << "<body>\n";


	//make title
	int counter = findTitle(comments, size);
	if (counter > -1)
	{ 
		int bufferStart = comments[counter].find(" ");
		buffer = comments[counter].substr(bufferStart+1);
	}
	else
	{ 
		buffer = filename.substr(0, filename.size()-4);
	}
	oFile << "<h2>\nPrograma: " << buffer << "<br>\n</h2>\n";
	writeSection (oFile, counter, comments);
		
	//rest of the program
	for (short int i = 0; i < size; i++)
	{ 
		buffer = comments[i];
		int tagEnd = buffer.find(" ");
		if (buffer.substr(0,tagEnd) == "@funcName")
		{ 
			oFile << "<h3>\nFunción: " << buffer.substr(buffer.find(" ")) << "<br>\n</h3>\n";
			writeSection(oFile, i, comments);
		}

	}
	

	oFile << "</body>\n";
	oFile << "</html>";
	oFile.close();
}

/**
 @funcName main
 @desc Llama todas las otras funciones
 @param Se puede pasar como parametro el nombre del programa a revisar
 @return 0
 */
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
	int size;
	bool check;

	//Input
	check = findComments(comments, size);
	if (!check)
	{ 
		return 0;
	}

	//Output
	writeHTML(comments, size);
	
	return 0;
}
