// RenameIt.cpp : Programa para percorrer diretórios e renomear as extensões dos arquivos.

#include <iostream>
#include <fstream>
#include <filesystem>
#include <sstream>


namespace fs = std::filesystem;
using namespace std;
string fileTo, path;

void PrintMenu(int* option);
void PrintSelections();
void ChangeExtensions();
void ChangePath();
void PrintSelections();
bool RenameIt();


int main(int argc, char* argv[]){
    int option = 1;


    
    cout << "Welcome to rename the files extensions \n";
    PrintMenu(&option);
    while (option != 0) {
       
        PrintMenu(&option);
        system("CLS");
        cout << "Option chosen: " << option << endl;
        switch (option)
        {
        case 1: {
            ChangeExtensions();
            break;
        }
        case 2: {
            ChangePath();
            break;
        }
        case 3: {
            RenameIt();
            break;
        }
        case 4: {
            PrintSelections();
            break;
        }
        default:
            option = 0;
            cout << "Exiting the program." << endl;
            break;
        }
    }
    return 0;
};

void PrintMenu(int* option) {
    if (fileTo.empty() || path.empty()) {
        ChangeExtensions();
        ChangePath();
    }
    else {
        cout << "\n Select what you wanto to do" << endl;
        cout << "1 - Change the extensions." << endl;
        cout << "2 - Change the path." << endl;
        cout << "3 - Rename folder." << endl;
        cout << "4 - Print selections." << endl;
        cout << "# - Exit" << endl;
        cin >> *option;
    }
};

void PrintSelections() {
    cout << "Extension to be: " << fileTo << endl;
    cout << "Path: " << path << endl;
}

bool RenameIt() {
    fs::path curName, nName;
    stringstream theName;

    int dirCounter = 0, dirHelper = 0, counter = 0, nameCounter = 1;

    if (!fs::exists(path)) {
        cout << "The path is wrong or doesn't exists" << endl;
        return false;
    }

    for (fs::directory_entry direntry : fs::recursive_directory_iterator(path)) {
        if (direntry.is_directory()) {
            dirHelper++;
            dirCounter = dirHelper;
            nameCounter = 1;
            continue;
        }
        else {
            theName.str("");
            curName = direntry.path();
            if (!fs::exists(path)) {
                cout << "path doesn't exists" << endl;
            }
            nName = curName;
            if (nameCounter == 100) {
                nameCounter = 1; 
                dirCounter++;
            }
            theName << dirCounter << "(" << nameCounter << ").png";
            nName.replace_filename(theName.str());
            nameCounter++;
            counter++;

            fs::rename(curName, nName);
        }
    }
    cout << counter << " files renamed." << endl;
    return true;
}

void ChangeExtensions() {
    cout << "Enter the extension you want to be: ";
    cin >> fileTo;
    if (fileTo[0] != '.')
        fileTo = "." + fileTo;
}

void ChangePath() {
    cout << "Enter the path: ";
    cin >> path;
}
