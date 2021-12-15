#pragma once
#include <mmsystem.h>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;


void GotoXY(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void SetColor(int backgound_color, int text_color) {
    /*
    0 = Black      8 = Gray
    1 = Blue       9 = Light Blue
    2 = Green      10 = Light Green
    3 = Aqua       11 = Light Aqua
    4 = Red        12 = Light Red
    5 = Purple     13 = Light Purple
    6 = Yellow     14 = Light Yellow
    7 = White      15 = Bright White
    */
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    int color_code = backgound_color * 16 + text_color;
    SetConsoleTextAttribute(hStdout, color_code);
}

void GameLoad(screen PlayGround, screen Light,
    vector<Vehicle*>& listCar, vector<TrafficLight>& listLight, vector<Animal*>& listAnimal, int level) {
    listCar.clear();
    listLight.clear();
    listAnimal.clear();

    bool Lane[9];
    for (int i = 0;i <= 8;i++) Lane[i] = false;

    int carNumber = 0;
    int truckNumber = 0;
    int TrueLevel = 0;
    int monkeyNumber = 0;
    int mooseNumber = 0;

    if (level <= 10 && level > 0) TrueLevel = 1;
    else if (level >= 11 && level <= 20) TrueLevel = 2;
    else if (level >= 21 && level <= 30) TrueLevel = 3;
    else if (level >= 31) TrueLevel = 4;

    int totalCarAndAnimal = 1;

    if (TrueLevel == 1) {
        totalCarAndAnimal = 1 + rand() % 3;
        monkeyNumber = rand() % totalCarAndAnimal;
        carNumber = rand() % (totalCarAndAnimal - monkeyNumber);
        mooseNumber = rand() % (totalCarAndAnimal - monkeyNumber - carNumber);
        truckNumber = totalCarAndAnimal - monkeyNumber - carNumber - mooseNumber;
        if (truckNumber < 0) truckNumber = 0;
    }
    else if (TrueLevel == 2) {
        totalCarAndAnimal = 3 + rand() % 5;
        monkeyNumber = rand() % totalCarAndAnimal;
        carNumber = rand() % (totalCarAndAnimal - monkeyNumber);
        mooseNumber = rand() % (totalCarAndAnimal - monkeyNumber - carNumber);
        truckNumber = totalCarAndAnimal - monkeyNumber - carNumber - mooseNumber;
        if (truckNumber < 0) truckNumber = 0;
    }
    else if (TrueLevel == 3) {
        totalCarAndAnimal = 5 + rand() % 4;
        monkeyNumber = rand() % totalCarAndAnimal;
        carNumber = rand() % (totalCarAndAnimal - monkeyNumber);
        mooseNumber = rand() % (totalCarAndAnimal - monkeyNumber - carNumber);
        truckNumber = totalCarAndAnimal - monkeyNumber - carNumber - mooseNumber;
        if (truckNumber < 0) truckNumber = 0;
    }
    else if (TrueLevel == 4) {
        totalCarAndAnimal = 8;
        monkeyNumber = rand() % totalCarAndAnimal;
        carNumber = rand() % (totalCarAndAnimal - monkeyNumber);
        mooseNumber = rand() % (totalCarAndAnimal - monkeyNumber - carNumber);
        truckNumber = totalCarAndAnimal - monkeyNumber - carNumber - mooseNumber;
        if (truckNumber < 0) truckNumber = 0;
    }

    sndPlaySound(NULL, SND_FILENAME | SND_ASYNC);

    if (monkeyNumber > 0 && mooseNumber > 0) sndPlaySound(TEXT("./SoundTrack/MonkeyInredeer.wav"), SND_FILENAME | SND_ASYNC | SND_LOOP);
    else if (monkeyNumber > 0) sndPlaySound(TEXT("./SoundTrack/MonkeySound.wav"), SND_FILENAME | SND_ASYNC | SND_LOOP);
    else if (mooseNumber > 0) sndPlaySound(TEXT("./SoundTrack/ReindeerSound.wav"), SND_FILENAME | SND_ASYNC | SND_LOOP);

    while (carNumber > 0) {
        int tempLane = rand() % 9;
        if (tempLane == 0) continue;
        if (!Lane[tempLane]) {
            Car* tempCar = new Car(PlayGround, tempLane, rand() % 2);
            listCar.push_back(tempCar);
            carNumber--;
            Lane[tempLane] = true;
        }
    }
    while (truckNumber > 0) {
        int tempLane = rand() % 9;
        if (tempLane == 0) continue;
        if (!Lane[tempLane]) {
            Truck* tempCar = new Truck(PlayGround, tempLane, rand() % 2);
            listCar.push_back(tempCar);
            truckNumber--;
            Lane[tempLane] = true;
        }
    }
    while (monkeyNumber > 0) {
        int tempLane = rand() % 9;
        if (tempLane == 0) continue;
        if (!Lane[tempLane]) {
            Monkey* tempAnimal = new Monkey(PlayGround, tempLane, rand() % 2);
            listAnimal.push_back(tempAnimal);
            monkeyNumber--;
            Lane[tempLane] = true;
        }
    }
    while (mooseNumber > 0) {
        int tempLane = rand() % 9;
        if (tempLane == 0) continue;
        if (!Lane[tempLane]) {
            Moose* tempAnimal = new Moose(PlayGround, tempLane, rand() % 2);
            listAnimal.push_back(tempAnimal);
            mooseNumber--;
            Lane[tempLane] = true;
        }
    }

    if (TrueLevel == 1) {
        for (unsigned int i = 0;i < listCar.size();i++) {
            listLight.push_back(TrafficLight(Light, listCar[i]->GetLane(), rand() % 3, rand() % 5 + 10));
        }
        for (unsigned int i = 0;i < listAnimal.size();i++) {
            listLight.push_back(TrafficLight(Light, listAnimal[i]->GetLane(), rand() % 3, rand() % 5 + 10));
        }
    }
    else if (TrueLevel == 2) {
        for (unsigned int i = 0;i < listCar.size();i++) {
            listLight.push_back(TrafficLight(Light, listCar[i]->GetLane(), rand() % 3, rand() % 5 + 5));
        }
        for (unsigned int i = 0;i < listAnimal.size();i++) {
            listLight.push_back(TrafficLight(Light, listAnimal[i]->GetLane(), rand() % 3, rand() % 5 + 5));
        }
    }
    else if (TrueLevel == 3) {
        for (unsigned int i = 0;i < listCar.size();i++) {
            listLight.push_back(TrafficLight(Light, listCar[i]->GetLane(), rand() % 3, rand() % 7 + 2));
        }
        for (unsigned int i = 0;i < listAnimal.size();i++) {
            listLight.push_back(TrafficLight(Light, listAnimal[i]->GetLane(), rand() % 3, rand() % 7 + 2));
        }
    }
    else if (TrueLevel == 4) {
        for (unsigned int i = 0;i < listCar.size();i++) {
            listLight.push_back(TrafficLight(Light, listCar[i]->GetLane(), rand() % 3, rand() % 5 + 3));
        }
        for (unsigned int i = 0;i < listAnimal.size();i++) {
            listLight.push_back(TrafficLight(Light, listAnimal[i]->GetLane(), rand() % 3, rand() % 5 + 3));
        }
    }

}
void GameReset(Player* a, vector<Vehicle*>& listCar, vector<TrafficLight>& listLight,
    vector<Animal*> listAnimal, int** carPos, int** animalPos) {
    delete a;

    listCar.clear();
    listLight.clear();
    listAnimal.clear();

    delete[] animalPos;
    delete[] carPos;

    sndPlaySound(NULL, SND_FILENAME | SND_ASYNC);
    mciSendString(TEXT("stop wav"), NULL, 0, NULL);
}
void GameSave(Player* a, string fileName, screen Menu) {
    ofstream fileOut(fileName, ios::app);
    time_t now = time(0);
    char* dt = ctime(&now);
    tm* gmtm = gmtime(&now);
    dt = asctime(gmtm);
    fileOut << a->getName() << endl;
    fileOut << a->getPoint() << " " << a->getLife() << " " << a->getLevel() << endl;
    fileOut << dt;
    fileOut.close();
}
Player* GameLoadFileFile(screen Display, string fileName, int color, screen PlayGround, char key) {
    SetColor(0, color);
    GotoXY(6, 11);
    cout << " ______  ______  ______  ______  ______  __  __   __  ______       ______  ______  ______  _____   ";
    GotoXY(6, 12);
    cout << "/\\  ___\\/\\  == \\/\\  __ \\/\\  ___\\/\\  ___\\/\\ \\/\\ \"-.\\ \\/\\  ___\\     /\\  == \\/\\  __ \\/\\  __ \\/\\  __-. ";
    GotoXY(6, 13);
    cout << "\\ \\ \\___\\ \\  __<\\ \\ \\/\\ \\ \\___  \\ \\___  \\ \\ \\ \\ \\-.  \\ \\ \\__ \\    \\ \\  __<\\ \\ \\/\\ \\ \\  __ \\ \\ \\/\\ \\ ";
    GotoXY(6, 14);
    cout << " \\ \\_____\\ \\_\\ \\_\\ \\_____\\/\\_____\\/\\_____\\ \\_\\ \\_\\\\\"\\_\\ \\_____\\    \\ \\_\\ \\_\\ \\_____\\ \\_\\ \\_\\ \\____- ";
    GotoXY(6, 15);
    cout << "  \\/_____/\\/_/ /_/\\/_____/\\/_____/\\/_____/\\/_/\\/_/ \\/_/\\/_____/     \\/_/ /_/\\/_____/\\/_/\\/_/\\/____/ ";
    GotoXY(49, 22);
    cout << "GAME SAVE";
    string name;
    int point;
    int life;
    int level;
    string date;

    Display._printFrame(6);

    vector<Player*> PlayerList;
    vector<string> dateList;
    ifstream fi(fileName);
    if (fi.fail()) {
        GotoXY(52, 25);
        cout << "Empty...";
        return NULL;
    }
    while (!fi.eof()) {
        getline(fi, name);
        if (name != "") {
            string temp;
            getline(fi, temp);
            stringstream ss(temp);
            ss >> point >> life >> level;
            Player* tempPlayer = new Player(PlayGround, name, point, life, level);
            PlayerList.push_back(tempPlayer);
            getline(fi, date);
            dateList.push_back(date);
        }
    }
    int line = 25;
    if (PlayerList.size() >= 3) {
        for (unsigned int i = PlayerList.size() - 3;i < PlayerList.size();i++) {
            GotoXY(41, line);
            cout << PlayerList.size() - i << ". ";
            cout << "Player name: " << PlayerList[i]->getName();
            GotoXY(44, line + 1);
            cout << "Scores: " << PlayerList[i]->getPoint() << " Life: " << PlayerList[i]->getLife() << " Level: " << PlayerList[i]->getLevel();
            GotoXY(44, line + 2);
            cout << dateList[PlayerList.size() - i - 1];
            line += 4;
        }
    }
    else {
        for (unsigned int i = 0;i < PlayerList.size();i++) {
            GotoXY(41, line);
            cout << PlayerList.size() - i << ". ";
            cout << "Player name: " << PlayerList[i]->getName();
            GotoXY(44, line + 1);
            cout << "Scores: " << PlayerList[i]->getPoint() << " Life: " << PlayerList[i]->getLife() << " Level: " << PlayerList[i]->getLevel();
            GotoXY(44, line + 2);
            cout << dateList[i];
            line += 4;
        }
    }
    fi.close();

    GotoXY(42, line);
    int pos = 1;
    cout << "Input player you want to choose (1-3): ";
    GotoXY(42, line + 1);
    cout << "Press esc to back.";
    if (key == 27) return NULL;
    if (key == 13) return PlayerList[0];
    else if (key == '1' && (key - '0') < PlayerList.size()) pos = 1;
    else if (key == '2' && (key - '0') < PlayerList.size()) pos = 2;
    else if (key == '3' && (key - '0') < PlayerList.size()) pos = 3;
    return PlayerList[PlayerList.size() - pos];
}
void GameHighScores(screen Display, string fileName, int color, screen PlayGround) {
    SetColor(0, color);
    GotoXY(6, 11);
    cout << " ______  ______  ______  ______  ______  __  __   __  ______       ______  ______  ______  _____   ";
    GotoXY(6, 12);
    cout << "/\\  ___\\/\\  == \\/\\  __ \\/\\  ___\\/\\  ___\\/\\ \\/\\ \"-.\\ \\/\\  ___\\     /\\  == \\/\\  __ \\/\\  __ \\/\\  __-. ";
    GotoXY(6, 13);
    cout << "\\ \\ \\___\\ \\  __<\\ \\ \\/\\ \\ \\___  \\ \\___  \\ \\ \\ \\ \\-.  \\ \\ \\__ \\    \\ \\  __<\\ \\ \\/\\ \\ \\  __ \\ \\ \\/\\ \\ ";
    GotoXY(6, 14);
    cout << " \\ \\_____\\ \\_\\ \\_\\ \\_____\\/\\_____\\/\\_____\\ \\_\\ \\_\\\\\"\\_\\ \\_____\\    \\ \\_\\ \\_\\ \\_____\\ \\_\\ \\_\\ \\____- ";
    GotoXY(6, 15);
    cout << "  \\/_____/\\/_/ /_/\\/_____/\\/_____/\\/_____/\\/_/\\/_/ \\/_/\\/_____/     \\/_/ /_/\\/_____/\\/_/\\/_/\\/____/ ";
    GotoXY(49, 22);
    cout << "HIGHSCORES";
    string name;
    int point;
    int life;
    int level;
    string date;

    Display._printFrame(6);

    vector<Player> PlayerList;
    vector<string> dateList;
    ifstream fi(fileName);

    if (fi.fail()) {
        GotoXY(52, 25);
        cout << "Empty...";
        return;
    }
    while (!fi.eof()) {
        getline(fi, name);
        if (name != "") {
            string temp;
            getline(fi, temp);
            stringstream ss(temp);
            ss >> point >> life >> level;
            Player tempPlayer(PlayGround, name, point, life, level);
            PlayerList.push_back(tempPlayer);
            getline(fi, date);
            dateList.push_back(date);
        }
    }
    int line = 25;

    sort(PlayerList.begin(), PlayerList.end(), Player::comp);

    if (PlayerList.size() >= 3) {
        for (unsigned int i = PlayerList.size() - 3;i < PlayerList.size();i++) {
            GotoXY(40, line);
            cout << PlayerList.size() - i << ". ";
            cout << "Player name: " << PlayerList[i].getName();
            GotoXY(43, line + 1);
            cout << "Scores: " << PlayerList[i].getPoint() << " Life: " << PlayerList[i].getLife() << " Level: " << PlayerList[i].getLevel();
            GotoXY(43, line + 2);
            cout << dateList[PlayerList.size() - i - 1];
            line += 4;
        }
    }
    else {
        for (unsigned int i = 0;i < PlayerList.size();i++) {
            GotoXY(40, line);
            cout << 3 - i << ". ";
            cout << "Player name: " << PlayerList[i].getName();
            GotoXY(43, line + 1);
            cout << "Scores: " << PlayerList[i].getPoint() << " Life: " << PlayerList[i].getLife() << " Level: " << PlayerList[i].getLevel();
            GotoXY(43, line + 2);
            cout << dateList[i];
            line += 4;
        }
    }

}

void Thread_running(bool* Running, char* key, bool& newKey) {
    srand(time(NULL));
    screen Menu(70, 0, 110, 40);
    screen PlayGround(0, 0, 65, 40);
    screen Display(0, 0, 110, 40);
    screen Light(65, 0, 70, 40);
    Display._format();
Again:
    Player* a = new Player(PlayGround);
    system("cls");
    Display._printFrame(6);
    Display._printDisplay(6);

    vector<Vehicle*> listCar;
    vector<TrafficLight> listLight;
    vector<Animal*> listAnimal;

    time_t now = time(0);
    tm* ltm = localtime(&now);
    int sec = 1 + ltm->tm_sec;
    int preSec = sec;

    int display_x = 47, display_y = 25;
    int display_x_playgame = 48;
    int choose = 25;
    int level = 11;
    bool RunningGame = false;
    int** carPos = new int* [listCar.size()];
    int** animalPos = new int* [listAnimal.size()];
    int timeDeleteNofication = 5;
    bool Exit = false;
    bool HighScoreOpen = false;
    bool InstructionOpen = false;
    bool LoadGame = false;
    bool GameLose = false;
    bool PlayGame = false;
    bool Init = false;
    bool Sound = true;

    while (*Running) {
        if (newKey && !RunningGame && !HighScoreOpen && !GameLose && !InstructionOpen && !LoadGame && !PlayGame && !Init) {
            choose = Display.displayMove(display_x, display_y, toupper(*key));
            if (*key == 13) {
                if (choose == 25) {
                    system("cls");
                    Display._printHowToPlay(6);
                    PlayGame = true;
                }
                if (choose == 26) {
                    system("cls");
                    GameLoadFileFile(Display, "SaveGame.txt", 6, PlayGround, *key);
                    LoadGame = true;
                }
                if (choose == 27) {
                    system("cls");
                    GameHighScores(Display, "SaveGame.txt", 6, PlayGround);
                    HighScoreOpen = true;
                }
                if (choose == 28) {
                    system("cls");
                    Display._printCredits(6);
                    InstructionOpen = true;
                }
                if (choose == 29) {
                    Display._ThanksForPlaying();
                    exit(1);
                    return;
                }
            }
            newKey = false;
        }
        else if (newKey && HighScoreOpen) {
            sndPlaySound(TEXT("./SoundTrack/SelectInMenu.wav"), SND_FILENAME | SND_ASYNC);
            HighScoreOpen = false;
            newKey = false;
            break;
        }
        else if (newKey && GameLose) {
            GameLose = false;
            newKey = false;
            break;
        }
        else if (newKey && InstructionOpen) {
            sndPlaySound(TEXT("./SoundTrack/SelectInMenu.wav"), SND_FILENAME | SND_ASYNC);
            InstructionOpen = false;
            newKey = false;
            break;
        }
        else if (newKey && LoadGame) {
            a = GameLoadFileFile(Display, "SaveGame.txt", 6, PlayGround, *key);
            if (a == NULL) {
                LoadGame = false;
                newKey = false;
                break;
            }
            system("cls");
            Menu._printFrame(6);
            PlayGround._printFrame(6);
            Menu._printScoreMenu(6, 0, a->getName(), a->getLife(), a->getLevel());
            GameLoad(PlayGround, Light, listCar, listLight, listAnimal, a->getLevel());
            a->_show();

            delete[] carPos;
            delete[] animalPos;

            carPos = new int* [listCar.size()];
            animalPos = new int* [listAnimal.size()];

            for (unsigned int i = 0; i < listCar.size(); i++)
                carPos[i] = new int[4];
            for (unsigned int i = 0;i < listAnimal.size();i++)
                animalPos[i] = new int[4];

            Light._printLightFrame(6);
            for (unsigned int i = 0;i < listLight.size();i++) listLight[i]._show();
            LoadGame = false;
            newKey = false;
            mciSendString(TEXT("open \"./SoundTrack/PlayGameSound.wav\" type mpegvideo alias wav"), NULL, 0, NULL);
            mciSendString(TEXT("play wav repeat"), NULL, 0, NULL);
            RunningGame = true;
        }
        else if (newKey && PlayGame) {
            system("cls");
            sndPlaySound(TEXT("./SoundTrack/SelectInMenu.wav"), SND_FILENAME | SND_ASYNC);
            Display._levelScreen(6);
            PlayGame = false;
            Init = true;
            newKey = false;
        }
        else if (newKey && Init) {
            level = Display._chooseLevel(display_x_playgame, display_y, toupper(*key));
            if (*key == 13) {
                system("cls");
                a->setName(Display._inputNameScreen(6));
                system("cls");
                a->setLevel(level);
                Menu._printFrame(6);
                Menu._printScoreMenu(6, 0, a->getName(), a->getLife(), a->getLevel());
                PlayGround._printFrame(6);
                a->_show();
                GameLoad(PlayGround, Light, listCar, listLight, listAnimal, a->getLevel());

                delete[] carPos;
                delete[] animalPos;

                carPos = new int* [listCar.size()];
                animalPos = new int* [listAnimal.size()];

                for (unsigned int i = 0; i < listCar.size(); i++)
                    carPos[i] = new int[4];
                for (unsigned int i = 0;i < listAnimal.size();i++)
                    animalPos[i] = new int[4];

                Light._printLightFrame(6);
                for (unsigned int i = 0;i < listLight.size();i++) listLight[i]._show();
                Init = false;
                mciSendString(TEXT("open \"./SoundTrack/PlayGameSound.wav\" type mpegvideo alias wav"), NULL, 0, NULL);
                mciSendString(TEXT("play wav repeat"), NULL, 0, NULL);
                RunningGame = true;

            }
            newKey = false;
        }
        //Test va cham xe
        else if (RunningGame) {
            now = time(0);
            ltm = localtime(&now);
            sec = 1 + ltm->tm_sec;
            if (sec != preSec) {
                preSec = sec;
                for (unsigned int i = 0;i < listLight.size();i++)
                    listLight[i]._changeAndShow();
                timeDeleteNofication--;
                if (timeDeleteNofication == 0) {
                    Menu._menuNofication("");
                    timeDeleteNofication = 5;
                }
            }
            for (unsigned int i = 0;i < listCar.size();i++)
                if (rand() % 10 == 1 && listLight[i].GetStatus() != 2)
                    carPos[i] = listCar[i]->_move(PlayGround, 50 + rand() % 100);

            for (unsigned int i = 0;i < listAnimal.size();i++)
                if (rand() % 10 == 1 && listLight[listCar.size() + i].GetStatus() != 2)
                    animalPos[i] = listAnimal[i]->_move(PlayGround, 50 + rand() % 100);

            if (newKey) {
                if (!Exit) {
                    if (toupper(*key) == 'B') {
                        GameSave(a, "SaveGame.txt", Menu);
                        Menu._menuNofication("Game Save...");
                        timeDeleteNofication = 5;
                    }
                    else if (*key == 27) {
                        Menu._menuNofication("Do you want to save game? (y/n)");
                        timeDeleteNofication = 60;
                        Exit = true;
                    }
                    else if (toupper(*key) == 'M') {
                        DWORD dwVolume;
                        if (Sound) {
                            waveOutSetVolume(NULL, 0);
                            Menu._menuNofication("Sound mute...");
                            timeDeleteNofication = 5;
                            Sound = false;
                        }
                        else {
                            waveOutSetVolume(NULL, 0xFFFF);
                            Menu._menuNofication("Sound unmute...");
                            timeDeleteNofication = 5;
                            Sound = true;
                        }
                    }
                    else a->_move(PlayGround, toupper(*key));

                }
                else {
                    if (*key == 'y') {
                        GameSave(a, "SaveGame.txt", Menu);
                        Menu._menuNofication("Game Save...");
                        timeDeleteNofication = 5;
                        Exit = false;
                        newKey = false;
                        break;
                    }
                    if (*key == 'n') {
                        Exit = false;
                        newKey = false;
                        break;
                    }
                    else {
                        Menu._menuNofication("Please only press y or n button.");
                        timeDeleteNofication = 5;
                        Exit = false;
                        newKey = false;
                    }
                }
                newKey = false;
            }
            if (a->_checkCollision(carPos, (int)listCar.size())) {
                sndPlaySound(TEXT("./SoundTrack/CarHit.wav"), SND_FILENAME | SND_ASYNC);
                a->setLife(a->getLife() - 1);
                a->_resetPosition(PlayGround);
                string nofication = "-1 Life. You only have " + to_string(a->getLife()) + " left...";
                timeDeleteNofication = 5;
                Menu._menuNofication(nofication);
            }

            if (a->_checkCollision(animalPos, (int)listAnimal.size())) {
                sndPlaySound(TEXT("./SoundTrack/CarHit.wav"), SND_FILENAME | SND_ASYNC);
                a->setLife(a->getLife() - 1);
                a->_resetPosition(PlayGround);
                string nofication = "-1 Life. You only have " + to_string(a->getLife()) + " left...";
                timeDeleteNofication = 5;
                Menu._menuNofication(nofication);
            }

            if (a->getLife() == 0) {
                system("cls");
                sndPlaySound(NULL, SND_FILENAME | SND_ASYNC);
                mciSendString(TEXT("stop wav"), NULL, 0, NULL);
                Display._loseScreen(a->getPoint());
                sndPlaySound(TEXT("./SoundTrack/LoseSound.wav"), SND_FILENAME | SND_ASYNC);
                Sleep(3000);
                GameLose = true;
                RunningGame = false;
            }
            else Menu._printScoreMenu(6, a->getPoint(), a->getName(), a->getLife(), a->getLevel());
            if (a->_winCheck()) {
                sndPlaySound(TEXT("./SoundTrack/WinLevel.wav"), SND_FILENAME | SND_ASYNC);
                Sleep(1000);
                system("cls");
                a->setLevel(a->getLevel() + 1);

                Menu._printFrame(6);
                Menu._printScoreMenu(6, 0, a->getName(), a->getLife(), a->getLevel());
                PlayGround._printFrame(6);
                a->_resetPosition(PlayGround);

                GameLoad(PlayGround, Light, listCar, listLight, listAnimal, a->getLevel());
                delete[] carPos;
                delete[] animalPos;

                carPos = new int* [listCar.size()];
                animalPos = new int* [listAnimal.size()];

                for (unsigned int i = 0; i < listCar.size(); i++)
                    carPos[i] = new int[4];
                for (unsigned int i = 0;i < listAnimal.size();i++)
                    animalPos[i] = new int[4];

                Light._printLightFrame(6);
                for (unsigned int i = 0;i < listLight.size();i++) listLight[i]._show();
            }
        }
    }
    GameReset(a, listCar, listLight, listAnimal, carPos, animalPos);
    goto Again;
}