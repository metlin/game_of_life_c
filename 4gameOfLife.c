#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void printMatrix(int lines, int columns, int matrix[lines][columns]) {
	system("cls");
	printf("\n");

	for (int i = 0; i < lines; i++) {
		for (int j = 0; j < columns; j++) {
			if (matrix[i][j] == 1) {
				printf("%c ", 2);
			}
			else {
				printf("%c ", 1);
			}
		}
		printf("\n");
	}
	return;
}

int main(void) {
	int const lines = 7;
	int const columns = 7;
	int currentGeneration[lines][columns];

	FILE *data;
	data = fopen("data.txt", "r");
		
	for (int i = 0; i < lines; i++) {
		for (int j = 0; j < columns; j++) {
			fscanf(data, "%d", &currentGeneration[i][j]);
		}
	}
	fclose(data);

	printMatrix(lines, columns, currentGeneration);

	int nextGeneration[lines][columns];
	int countIdentifical = 0;
	
	while(countIdentifical != lines * columns) {
		countIdentifical = 0;
		
		for (int i = 0; i < lines; i++) {
			for (int j = 0; j < columns; j++) {
				int topIndex = i == 0 ? lines - 1 : i - 1;
				int bottomIndex = i == lines - 1 ? 0 : i + 1;
				int leftIndex = j == 0 ? columns - 1 : j - 1;
				int rightIndex = j == columns - 1 ? 0 : j + 1;

				int top = currentGeneration[topIndex][j]; 
				int bottom = currentGeneration[bottomIndex][j]; 
				int left = currentGeneration[i][leftIndex];
				int right = currentGeneration[i][rightIndex];
				int leftTop = currentGeneration[topIndex][leftIndex];
				int rightTop = currentGeneration[topIndex][rightIndex];
				int leftBottom = currentGeneration[bottomIndex][leftIndex];
				int rightBottom = currentGeneration[bottomIndex][rightIndex];

				int alive = top + leftTop + rightTop + left + right + leftBottom + bottom + rightBottom;

				nextGeneration[i][j] = currentGeneration[i][j];

				if (currentGeneration[i][j] == 1) {
					if (alive < 2 || alive > 3) {
						nextGeneration[i][j] = 0;
					}	
				}
				else {
					if (alive == 3) {
						nextGeneration[i][j] = 1;
					}
				}		
			}
		}
	
		for (int i = 0; i < lines; i++) {
			for (int j = 0; j < columns; j++) {
				if(currentGeneration[i][j] == nextGeneration[i][j]) {
					countIdentifical++;
				}

				currentGeneration[i][j] = nextGeneration[i][j];
			}
		} 

		sleep(1);

		printMatrix(lines, columns, nextGeneration);
	}

	printf("Game over"); 
	
	return 0;
}
