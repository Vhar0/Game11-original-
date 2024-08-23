#include <iostream>
#include <ctime>
#include <cstdio>
#include <conio.h>
#include <Windows.h>
#include <ctime>
#include <cstdlib>
#include <string>
#include <chrono>
#include <thread>


using namespace std;

//wasd : 119, 97, 115, 100;

/*void gotoxy() {
    COORD pos = {0, 0};
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(output, pos);
}*/

//funzione per il reset del cursore [non mia]
void gotoxy( int column, int line ){

    COORD coord;
    coord.X = column;
    coord.Y = line;
    SetConsoleCursorPosition(
            GetStdHandle( STD_OUTPUT_HANDLE ),
            coord
    );
}

// randomizzo le coordinate y degli oggetti nella mappa
int backgroundX(int mX, long long int modyf) {

    srand(modyf);
    int obj_coordinatesX = rand() % mX;

    return obj_coordinatesX;
}

// randomizzo le coordinate y degli oggetti nella mappa
int backgroundY(int mY, long long int modyf) {

    srand(modyf);
    int obj_coordinatesY = rand() % mY;

    return obj_coordinatesY;
}

//randomizzo le coordinate iniziali in modo che non siano long long
int randomizer(){
    srand(time(NULL));
    int input_rand = rand() % 150;

    return input_rand;
}

int main(){

    //--------------START DECLARATIONS-----------------//

	int x = 10, y = 1;

    int mX = 80, mY = 4;  // matrix width (MX), and matrix high (MY)//

	char game_space[mY][mX];

    int input_rand = 0;

    int random_objects = 10;

    string replace;

    int tree = 190;

    int score = 0;

    int column = 0, line = 0;

    int del = 0;

    int modyf = 0;

    int coordinatesX;
    int coordinatesY;

    //---------------END DECLARATIONS------------------//

    cout<<endl<<"random objects is as default set at 10, replace: y or n? ";
    cin>>replace;

    // inizio controllo input
    while(!(replace[0] == 'y' || replace[0] == 'n' || replace[0] == 'Y' || replace[0] == 'N')){
        cout<<endl<<"Please enter a valid character! ";
        cin>>replace;
    }

    if(replace[0] == 'y' || replace[0] == 'Y'){
        cout<<"insert the random obj const: ";
        cin>>random_objects;
    }
    cout<<endl<<endl;

    // fine controllo input

    system("cls");
    gotoxy(37, 5);
    cout<<"important!! press esc to exit the game!";
    gotoxy(50, 7);
    cout<<"   ENJOY!   ";
    cout<<endl<<endl;
    system("timeout 10");
    system("cls");

/*               // dato che le coordinate degli oggetti randomici vengono create in esecuzioni il "LOG RAND" non può più essere mostrato

    gotoxy(0, mY + 1);      // sposto il cursore giusto per scrivere il log.

    cout<<endl<<" ------------------ LOG RAND -------------------"<<endl;

    for(int i = 0; i < random_objects*2; i++){
        cout<<endl<<endl;
        cout<<endl<<" coordinates group "<<i/2 + 1<<" of "<<" 10?: Y = "<<coordinates[i+1]<<", X = "<<coordinates[i];
        i++;

    }
    cout<<endl<<"----------------- END RAND LOG -----------------"<<endl;
*/

    int i = 0, c = random_objects; // utilizzo il contatore c per controllare che la funzione sia chiamata al massimo 10 volte

    //long long int modyf = time(NULL);     // inizializzo il seed quì così posso aggiornarlo in esecuzione e far spownare gli oggetti randomicamente
    modyf = randomizer();

//    gameplay :    //

	while(true){

        if(modyf == 0){
            goto END;
        }

        gotoxy(0, mY + 3);
        cout<<" User position: Y = "<<y<<", X = "<<x<<endl;
        cout<<" score: "<<score<<endl;
        gotoxy(column, line);             //resetto il cursore




        // chiamo la funzione per spownare gli oggetti randomici

        if(i == 0){     // utilizzo il contatore i per far in modo che le funzioni vengano chiamate anche la prima volta (quando del = 0 );
            coordinatesX = backgroundX(mX, modyf);
            coordinatesY = backgroundY(mY, modyf);
        }
        if(del == 1 and c >= 0){
            coordinatesX = backgroundX(mX, modyf);
            coordinatesY = backgroundY(mY, modyf);
            --modyf;
        }

        i++;
        c--;

        // creo il campo di gioco

        for (int Y = 0; Y < mY; Y++) {

            for (int X = 0; X < mX; X++) {

                game_space[Y][X] = char(219);

                if (Y == y and X == x) {

                    game_space[Y][X] = char(48);
                }
                if (del == 1){
                    game_space[coordinatesX][coordinatesY] = char(219);
                    coordinatesX = 0;
                    coordinatesY = 0;

                }else if(coordinatesX == X and coordinatesY == Y) {

                    game_space[Y][X] = char(190);
                }

                cout<<game_space[Y][X];
            }
            cout<<endl;
        }


        // inizio controllo input

        this_thread::sleep_for(chrono::milliseconds(160));          // stoppo il processo per evitare che il personaggio: (0) essendo troppo veloce faccia crashare il programma//

        int U_input = getch();  // chiedo l' input

		switch (U_input){
			case 119:		    // W

				if(y!=0 and game_space[y-1][x] == char(219)) {       // controllo se il bordo è stato raggiunto [per tutti gli switch cases]
                    y--;
                }

				if(game_space[y-1][x] == char(190)){          // controllo se l'oggetto è stato "preso" o no [per tutti gli switch cases]
                    del = 1;
                    score++;

                }else{      // controllo se l' oggetto è ancora lì [per tutti gli switch cases]
                    del = 0;
                }
				break;

			case 97:		    // A

				if(x!= 0 and game_space[y][x-1] == char(219)) {
                    x--;
                }

                if(game_space[y][x-1] == char(190)){
                    del = 1;
                    score++;

                }else{
                    del = 0;
                }
				break;

			case 115:			// S

				if(y!=mY-1 and game_space[y+1][x] == char(219)) {
                    y++;
                }

                if(game_space[y+1][x] == char(190)){
                    del = 1;
                    score++;

                }else{
                    del = 0;
                }
				break;

			case 100:		    // D

				if(x!=mX-1 and game_space[y][x+1] == char(219)) {
                    x++;
                }

                if(game_space[y][x+1] == char(190)) {
                    del = 1;
                    score++;

                }else{
                    del = 0;
                }
				break;
/*
            default:        // continuo ad andare avanti se non è stato premuto alcun tasto
                switch (U_input) {
                    case 119:
                        y--;
                        break;

                    case 97:
                        x--;
                        break;

                    case 115:
                        y++;
                        break;

                    case 100:
                        x++;
                        break;
                }
                break;
*/
            case 27:

                goto END; // nel caso si prema ESC termino il programma
		}

		//system("cls");                                 //con il sistema del 'clear' si presentano bug visivi tipo: frame-loss ad alti input.

	}



    END:

        system("cls");

        cout<<endl<<"congratulations!! your score is: "<<score<<" thanks for playing!!"<<endl<<endl;

        system("timeout 10");

        return 0;
}
/*
-----------------------------N.B.------------------------
 del tiene conto se generare un altro oggetto ne campo di gioco


 freeze perchè non viene specificato quando del = 0

*/