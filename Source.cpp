#include "Circle.h"
#include "Line.h"
#include "Point.h"
#include "Window.h"
#include "StaticText.h"
#include "Edge.h"
#include "Graph.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define VERDE RGB(0,255,0) 
#define AZUL RGB(0,0,255) 
#define AZUL_CLARO RGB(0,200,255)
#define VERMELHO RGB(255,0,0) 
#define CINZA RGB(211,211,211) 
#define PRETO RGB(0,0,0) 
#define BRANCO RGB(255,255,255) 


const char MapFilePath[] = "Map.txt";
const char ConectionsFilePath[] = "Connections.txt";
const char ImageFilePath[] = "Map.bmp";

const int c_CIRCLE_SIZES = 12;

//O return desta função é o numero de objectos lidos, 0 pode ser em caso de ter havido algum problema
int readMapFile (const char* Path, Point* &resultArray) {
	FILE* file;
	int num_Locations = 0;
	int locations_read = 0;

	fopen_s (&file, Path, "r");

	if (file == NULL)
		return 0;

	while (!feof(file)) {
		const int c_sizeReadLine = 100;		//Tamanho máximo a ser lido numa linha (tamanho da variável de leitura line)

		//Ler a linha
		char line[c_sizeReadLine];
		char* aux;
		fgets (line, c_sizeReadLine, file);

		//Ignorar os comments
		aux = strchr (line, '#');
		if (aux != NULL) {
			*aux = '\0';
		}

		//Parse dos números lidos de cada linha
		if (num_Locations == 0) {
			if (sscanf_s (line, "%d", &num_Locations) > 0) {

				//Criar o array a ser entregue como resultado da função
				delete[] resultArray;
				resultArray = new Point[num_Locations];
			}

		} else {
			//Criar o objecto da localização e fazer scan das coordenadas
			Point point;
			int x = 0;
			int y = 0;

			sscanf_s (line, "%d, %d", &x, &y);

			point.SetX (x);
			point.SetY (y);

			resultArray[locations_read] = point;

			locations_read++; 
		}

		if (locations_read == num_Locations)
			break;
	}
	fclose (file);
	return num_Locations;
}

//Esta função lê o ficheiro de conexões entre os pontos.
//O parâmetro Graph será alterado por esta função, portanto é aconselhável a passar-lhe um Graph acabado de criar (sem dados inseridos ainda)
//O parâmetro pointsArray é o array de pontos, usado para saber a distância dos Edge do Graph
//O return desta função é 0 (false) em caso de sucesso e 1 (true) em caso de haver um problema
bool readConectionFile (const char* Path, Graph &locationsToConnectArray, Point* pointsArray, int size) {
	FILE* file;
	fopen_s (&file, Path, "r");

	if (file == NULL)
		return 1;


	const int c_sizeReadLine = 100;					//Tamanho máximo a ser lido numa linha (tamanho da variável de leitura line)
	
	char line[c_sizeReadLine];						//String onde a linha lida será metida
	char* aux;

	int readChars = 0;								//Número de chars lidos numa certa iteração do sscanf
	int offset = 0;									//Utilizado para dar um offset no ponto do string que vai ser lido pelo sscanf, por forma a ser lido progressivamente

	bool skipLine = false;							//Bool que descreve se é para ignorar esta linha

	int bufferSize = 10;
	int* connectionBuffer = new int[bufferSize];	//Buffer para as conexões lidas (este tamanho poderá ter de ser aumentado caso tenhamos mais de 10 conexões)
	int readCount = 0;								//Número de ligações lidas
	

	for (int i = 0; i < size; i++) {
		if (feof (file)) break;

		//Inicializar as variáveis para este ciclo
		skipLine = false;
		readCount = 0;
		readChars = 0;
		offset = 0;
		//connectionBuffer = new int				//O Connection buffer não deve ser necessário ser limpo em cada ciclo 

		//Ler a linha
		fgets (line, c_sizeReadLine, file);

		//Verificar se o 1º caracter da linha (excluindo espaços) é um caracter de comment, e se sim excluir da contagem de linhas lidas do file
		for (int j = 0; j < c_sizeReadLine; j++) {
			if (line[j] == ' ') {
				continue;
			} else if (line[j] == '#') {
				i--;						//Diminuir o 'i' visto que o 'i' nos dirá qual a location em que nos encontramos
				skipLine = true;
				break;
			} else {
				break;
			}
		}

		if (skipLine) {
			continue;
		}

		//Ignorar tudo após o caracter de comment
		aux = strchr (line, '#');
		if (aux != NULL) {
			*aux = '\0';
		}

		//Ler os números das ligações
		while (sscanf_s(line + offset, "%d%n", &connectionBuffer[readCount], &readChars) > 0) {
			readCount++;
			offset += readChars;

			//Caso tenha de se aumentar o tamanho do buffer para evitar overflow
			if (readCount == bufferSize) {
				int* tempBuffer = connectionBuffer;
				connectionBuffer = new int[bufferSize * 2];

				for (int j = 0; j < bufferSize; j++) {
					connectionBuffer[j] = tempBuffer[j];
				}
				bufferSize *= 2;
				delete[] tempBuffer;
			}

			//Para evitar situações estranhas como números negativos ou números não existentes
			if (connectionBuffer[readCount - 1] <= 0 || connectionBuffer[readCount - 1] > size) {
				readCount--;
			}
		}

		//Passar as ligações do buffer para o objecto
		for (int j = 0; j < readCount; j++) {
			Edge e (i, connectionBuffer[j] - 1, pointsArray[i].GetDistance( pointsArray[connectionBuffer[j] - 1] ) );
			locationsToConnectArray.InsertEdge (e);
		}

	}
	fclose (file);
	return 0;
}

//Esta função desenha todos os pontos no mapa com a core default dos mesmos (desselecionados)
void drawAllLocations (HWND winID, Point* array, int size) {
	for (int i = 0; i < size; i++) {
		Circle c (array[i], c_CIRCLE_SIZES);
		char numToWrite[10];				//10 chars deve ser suficiente para qualquer quantidade de pontos que se queira alguma vez utilizar neste programa
		sprintf_s (numToWrite, "%d", i + 1);
		c.Draw (winID, AZUL, numToWrite, BRANCO);
	}
}

//Esta função desenha um ponto no mapa com a cor de estar selecionado, o parametro "numPoint" serve para desenhar o número do ponto no mapa
//A variável numPoint é o número do ponto NO MAPA, portanto a posição no array + 1
void selectLocation (HWND winID, Point point, int numPoint) {
	Circle c (point, c_CIRCLE_SIZES);
	char numToWrite[10];				//10 chars deve ser suficiente para qualquer quantidade de pontos que se queira alguma vez utilizar neste programa
	sprintf_s (numToWrite, "%d", numPoint);
	c.Draw (winID, AZUL_CLARO, numToWrite, BRANCO);
}

//Esta função é utilizada somente para ligar duas localidades adjacentes (portanto muda a cor e desenha a linha)
//Esta função retorna a distancia entre os dois pontos ligados
double connectLocations (HWND winID, Point P1, Point P2, int num1, int num2) {
	Line L (P1, P2);
	L.Draw (winID, AZUL_CLARO);
	selectLocation (winID, P1, num1);
	selectLocation (winID, P2, num2);
	
	return L.GetLength ();
}

//Esta função desenha o caminho entre dois pontos, usando o Graph que contem as distâncias e adjacências, e usando o array com os Pontos para os desenhar no mapa
//As variáveis P1 e P2 são as posições dos pontos DENTRO DO ARRAY, não são os números dos pontos no mapa
void connectPath (HWND winID, Graph &graph, Point* array, int P1, int P2) {
	graph.Dijkstra (P1);

	int currentPoint = P2;
	int nextPoint = graph.PrevVert (currentPoint);
	
	while (currentPoint != P1) {
		nextPoint = graph.PrevVert (currentPoint);
		connectLocations(winID, array[currentPoint], array[nextPoint], currentPoint + 1 , nextPoint + 1);
		currentPoint = nextPoint;
	}

	printf_s ("\n-----------------------------------------\n");
	printf_s ("Distance of selected path: %d\n", graph.PathWeight(P2));
	printf_s ("-----------------------------------------\n\n");
}

//Função que desenha as ligações todas dos pontos na janela
void drawAllConections (HWND winID, Graph &graph, Point* array, int size) {
	for (int i = 0; i < size; i++) {
		graph.Dijkstra (i);

		for (int j = 0; j < size; j++) {

			if (graph.PrevVert(j) == i) {
				Line l (array[i], array[j]);
				l.Draw (winID, AZUL_CLARO);
			}
		}
	}
	drawAllLocations (winID, array, size);
}


int main () {
	Window window;
	HWND windowId;

	Point* points = nullptr;
	int numLocations = 0;

	if (window.Create ((char*)"Map Nodes Pathfinding", (char*)ImageFilePath)) {
		if ((windowId = window.GetWindowId ()) != NULL) {
			MSG msg;

			numLocations = readMapFile (MapFilePath, points);				//Definir o array das localidades
			if (numLocations == 0) return 1;									//Se houver um erro a ler os pontos sair do programa
			if (points == nullptr) return 2;

			Graph graph (numLocations);
			if (readConectionFile (ConectionsFilePath, graph, points, numLocations)) return 3;	//Definir as ligacoes entre as localidades

			drawAllLocations (windowId, points, numLocations);

			int P1 = -1, P2 = -1;
			bool pathSelected = false;
			bool clickedOutsideNodes = false;											//Usado para verificar se o utilizador carregou fora dos circulos, para desselecionar
			
			while (GetMessage (&msg, 0, 0, 0)) {
				DispatchMessage (&msg);

				if (window.HasClicked ()) {
					clickedOutsideNodes = true;										//Assumir true para se trocar para false caso se verifique a condição

					for (int i = 0; i < numLocations; i++) {					//Verificar se se carregou numa localidade, criando um circulo nesse ponto somente para testar
						Circle c (points[i], c_CIRCLE_SIZES);

						if (c.Contains(window.GetPoint())) {
							clickedOutsideNodes = false;

							if (P1 == -1) {
								P1 = i;
								selectLocation (windowId, points[P1], P1 + 1);

							} else if (P2 == -1) {
								P2 = i;
								pathSelected = true;
								connectPath (windowId, graph, points, P1, P2);

							} else {
								P1 = i;
								pathSelected = false;
								P2 = -1;
								window.Clean ();
								drawAllLocations (windowId, points, numLocations);
								selectLocation (windowId, points[P1], P1 + 1);

							}
							break;
						}
					}

					if (clickedOutsideNodes) {
						P1 = -1;
						P2 = -1;
						pathSelected = false;
						window.Clean ();
						drawAllLocations (windowId, points, numLocations);
						//drawAllConections (windowId, graph, points, numLocations);
					}
				}

				if (window.HasPressEnter ()) {

				}
			}
		}
	}
	return 0;
}