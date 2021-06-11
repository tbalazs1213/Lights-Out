#include <iostream>
#include <ctime>

using namespace std;

enum FieldState {ures, sotet, vilagos};

struct PlayField {
	int rows;
	int cols;
	FieldState** field;
	int stepcount;
};

void InitGame(PlayField& f) {
	f.stepcount = 0;
	do {
		cout << "Adja meg a jatekmezo nagysagat!\n";
		cout << "Rows: "; cin >> f.rows;
		cout << "Cols: "; cin >> f.cols;
	} while(!(f.rows >= 3 && f.cols >=3));
	int light = (f.rows*f.cols) * 0.36;
	f.field = new FieldState*[f.rows];
	for(int row=0; row<f.rows; row++) {
		f.field[row] = new FieldState[f.cols];
		for(int col=0; col<f.cols; col++) {
			f.field[row][col] = ures;
		}
	}
	int initcounter = 0;
	while(initcounter<light) {
		int row = rand() % f.rows;
		int col = rand() % f.cols;
		if(f.field[row][col] == ures) {
			f.field[row][col] = vilagos; 
			initcounter++;
		}
	}
	for(int row=0; row<f.rows; row++) {
		for(int col=0; col<f.cols; col++) {
			if(f.field[row][col] == ures) f.field[row][col] = sotet;
		}
	}
}

char FieldToChar(FieldState& fs) {
	if(fs == sotet) return '.';
	else return '*';
}

void PrintGame(PlayField& f)
{
	cout << " ";
	for(int i=0; i<f.cols; i++) {
		if(i<9) {
			cout << " " << i+1;
		} else {
			cout << i+1;
		}
	}
	cout << endl;
  for (int i = 0; i < f.rows; i++)
  {
		if(i<9) {
			cout << " " << i+1;
		} else {
			cout << i+1;
		}
    for (int j = 0; j < f.cols; j++)
    {
      cout << FieldToChar(f.field[i][j]) << " ";
    }
    cout << endl;
  }
}

bool win(PlayField& f) 
{
	for(int i=0; i<f.rows; i++) {
		for(int j=0; j<f.cols; j++) {
			if(f.field[i][j] != sotet) return false;
		}
	}
	return true;
}

bool ValidInput(PlayField& f ,int row, int col) {
  if (row > 0 && row <= f.rows && col > 0 && col <= f.cols) return true;
  else return false;
}

void Colorchange(FieldState& f)
{
  if (f == sotet)
    {
      f = vilagos;
    }
    else
    {
      f = sotet;
    }
}

void makestep(PlayField& f, int row, int col) 
{
	if(row == 0) {
		if(col == 0) {
			Colorchange(f.field[row+1][col]);
			Colorchange(f.field[row][col+1]); 
			Colorchange(f.field[row][col]);
		}
		else if(col == f.cols-1) {
			Colorchange(f.field[row][col-1]);
    		Colorchange(f.field[row+1][col]);
			Colorchange(f.field[row][col]);
		} else {
			Colorchange(f.field[row][col-1]);
			Colorchange(f.field[row][col+1]);
			Colorchange(f.field[row+1][col]);
			Colorchange(f.field[row][col]);
		}
	} else if(row == f.rows-1) {
    	if(col == 0) {
			Colorchange(f.field[row-1][col]);
			Colorchange(f.field[row][col+1]);
			Colorchange(f.field[row][col]);
		} else if(col == f.cols-1) {
    		Colorchange(f.field[row][col-1]);
    		Colorchange(f.field[row-1][col]);
			Colorchange(f.field[row][col]);
		} else {
			Colorchange(f.field[row][col-1]);
			Colorchange(f.field[row][col+1]);
			Colorchange(f.field[row-1][col]);
			Colorchange(f.field[row][col]);
		}
  	} else if(col == 0) {
		Colorchange(f.field[row][col+1]);
		Colorchange(f.field[row+1][col]);
		Colorchange(f.field[row-1][col]);
		Colorchange(f.field[row][col]);
	} else if(col == f.cols-1) {
		Colorchange(f.field[row][col-1]);
		Colorchange(f.field[row+1][col]);
		Colorchange(f.field[row-1][col]);
		Colorchange(f.field[row][col]);
	} else {
		Colorchange(f.field[row][col+1]);
		Colorchange(f.field[row][col-1]);
		Colorchange(f.field[row+1][col]);
		Colorchange(f.field[row-1][col]);
		Colorchange(f.field[row][col]);
	}
	f.stepcount++;
}

int main()
{
	srand(time(NULL));
	PlayField game;
	InitGame(game);
	PrintGame(game);
	while(!win(game)) {
		cout << game.stepcount+1 << ". lepes!\n";
		int row;
		int col;
		do {
			cout << "Row: "; cin >> row;
			cout << "Col: "; cin >> col;
		} while(!ValidInput(game, row, col));
		makestep(game, row-1, col-1);
		PrintGame(game);
	}
	cout << "Nyertel!\n";
	return 0;
}
