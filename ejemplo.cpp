 /**
@progName Picos en un Arreglo
Comentarios para prube de proyecto 1: Documentación en HTML
@desc El programa pide al usuario entrar numeros en la consola, y encuentra los pícos, tomando los datos como un arreglo círcular.
@author Kevin Chinchilla
A00825945@itesm.mx
@notATag welp
@date 16 de enero, 2019
*/
#include <iostream>
using namespace std;

	/** 
	@funcName getArray
 @desc Pide al usuario que introduzca el tamaño y el valor para guardar en un arreglo unidimesional
@param iSize, donde se esrciribirá el tamaño del arreglo, y iArrNumbers, donde se guardan los datos recuperados de la consola
@return Ninguno
*/
void getArray (int &iSize, int iArrNumbers[])
{
    cout << "Cuantos datos hay en el arreglo" << endl;
    cin >> iSize;
    for ( int iCounter = 0; iCounter < iSize; iCounter++)
    { 
	cout << "Cual es el valor " << iCounter << " del arreglo?" << endl;
	cin >> iArrNumbers[iCounter];
    }
}

/**
@funcName findPeaks
@desc Busca los "picos" en un arreglo, es decir, los elementos más altos en medio de dos elementos más bajos. El arreglo se considera circular.
@param iSize con el tamaño del arreglo, iArrNumbers con los datos a revisar, y iArrAnswer, donde se guardarán los picos encontrados.
@return El tamaño del arreglo con los picos.
Input: El arreglo a revisar, y el tamaño de este.
Output: Escribe a un arreglo cuáles son los picos, y regresa una entero con el tamaño del nuevo arreglo
 */
int findPeaks( int iSize, int iArrNumbers[], int iArrAnswer[] )
{ 
	if ( iSize == 1)
	{ 
		return 0;
	}
	
	else
	{ 
		int iFinalSize = 0;

		if ( (iArrNumbers[0] > iArrNumbers[ iSize - 1]) && (iArrNumbers[0] > iArrNumbers[1]) )
		{ 
			iArrAnswer[iFinalSize] = iArrNumbers[0];
			iFinalSize++;
		}

		for ( int iCounter = 1; (iCounter + 1) < iSize; iCounter++)
		{ 
			if ( (iArrNumbers[iCounter] > iArrNumbers [iCounter + 1] )&& (iArrNumbers[iCounter] > iArrNumbers[iCounter - 1]) )
			{ 
				iArrAnswer[iFinalSize] = iArrNumbers[iCounter];
				iFinalSize++;
			}
		}

		if ( (iArrNumbers[iSize - 1] > iArrNumbers[0]) && (iArrNumbers[iSize - 1] > iArrNumbers[iSize - 2]) )
		{ 
			iArrAnswer[iFinalSize] = iArrNumbers[iSize -1];
			iFinalSize++;
		}
		return iFinalSize;
	}
}

/**
@funcName printArray
@desc imprime un arreglo unidimesional a la consola
@param El arreglo y el tamaño del arreglo
@return NONE
*/
void printArray( int iArrNumbers[], int iSize)
{ 
	if ( iSize > 0 )
	{ 
		for ( int iCounter = 0; iCounter < iSize; iCounter++)
		{ 
			cout << iArrNumbers[iCounter] << " ";
		}
		cout << endl;
	
	}
	else 
	{ 
		cout << "NO PEAKS FOUND" << endl;
	}
}

/**
@funcName main
@desc  Llama las otras funciones
Input: NONE
Output: Regresa 0
@return 0
*/
int main ()
{ 
	//Variables
	int iArrNumbers[50];
	int iSize;

	//Input
	getArray( iSize, iArrNumbers);
	int iArrAnswer[iSize];

	//Processing
	iSize = findPeaks( iSize, iArrNumbers, iArrAnswer);

	//Output
	printArray (iArrAnswer, iSize);

	return 0;
}

/* Análisis
 * Inputs: Un arreglo de enteros, y el tamaño de este arreglo
 * Proceso: Escribir a un nuevo arreglo los "picos" del arreglo leído. Para esto utilizar una for-loop para todos los elementos excepto el primero y el último, que serán chequiados por ifs afuera de la loop.
 * Output: Imprime los picos a la consola
 *
 * Pruebas:
 * 	Prueba 1: 
 * 		Input:
 * 			Tamaño: 10
 * 			Arreglo: 1 3 2 4 7 5 2 8 1 6
 * 		Output: 
 * 			3 7 8 6
 *
 * 	Prueba 2:
 * 		Input:
 * 			Tamaño: 3
 * 			Arreglo: 3 3 3
 * 		Output:
 * 			NO PEAKS FOUND
 */
