#include <dirent.h>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <unistd.h>
#include <vector>



using namespace std;

///////////////////////Function prototypes//////////////////////////
void pwdCommand();

void echoCommand(string token);

void lsCommand();

void helpCommand();

string getUserInput();

vector <string> splitStringToToken(string inputStr, char delimiter);
/////////////////////////////////////////////////////////////////////


int main()
{
    bool programIsOn = true;

    char delimiter = ';';

    string userInput;

    string commandToken;


    cout << "----------BIT GASH-----------" << endl;
    cout << "\nWelcome to Bit Gash" << endl;
    cout << "Type 'help' to see list of commands. \nMultiple commands must be separated by ';' " << endl;


    do
    {
        cout << "\ngaveng@CMPSCI-322 MINGWls64 ~" << endl;
        cout << "$ ";

        userInput = getUserInput();

        vector <string> tokens = splitStringToToken(userInput, delimiter);

        while (!tokens.empty())
        {
            commandToken = tokens.front();

            tokens.erase(tokens.begin());

            if (commandToken == "pwd") {

                pwdCommand();

            } else if (commandToken.find("echo") == 0) {

                echoCommand(commandToken);

            } else if (commandToken == "ls") {

                lsCommand();

            } else if (commandToken == "help") {

                helpCommand();

            } else if (commandToken == "exit") {

                programIsOn = false;

            } else {

                cout << "The command '" + commandToken + "' does not exist. Type 'help' for list of commands." << endl;

            }
        }

    } while (programIsOn);

    return 0;

}


void pwdCommand()   //function for pwd command. prints current working directory
{
    char *buf = NULL;

    char *ptr = NULL;

    size_t size = 1024;    //size of the character array pointed to by the buf argument

    ptr = getcwd(buf, size);    //getcwd() returns the buf argument

    cout << ptr << endl;

    free(buf);

}

void echoCommand(string token)  //function for echo command. prints any arguments to screen
{
    token.erase(0, 5);

    cout << "Arguments: " + token << endl;  //prints any extra arguments to screen
}

void lsCommand()    //function for ls command; this function uses dirent.h
{
    struct dirent *temp = NULL;     //pointer used to return information about directory entries

    DIR *dirPointer = NULL;     //directory stream

    dirPointer = opendir(".");      //opens current program directory

    while (temp = readdir(dirPointer))
    {
        printf("%s\n", temp->d_name);   //prints items in directory
    }

    closedir(dirPointer);   //closes directory stream
}

void helpCommand()    //function for help command. prints all commands and their descriptions
{
    string pwdMessage = "pwd - Display the current working directory. NO ARGUMENTS\n";

    string echoMessage = "echo - Prints any extra arguments to screen. ACCEPTS ARGUMENTS\n";

    string lsMessage = "ls - Displays all files and folders in the current working directory. NO ARGUMENTS\n";

    string helpMessage = "help - Displays a list of all the commands available. NO ARGUMENTS\n";

    string exitMessage = "exit - Quits the program. NO ARGUMENTS";


    cout << pwdMessage + echoMessage + lsMessage + helpMessage + exitMessage << endl;
}


string getUserInput()   //function that returns user inputted string
{
    string input;

    getline(cin, input);

    return input;
}


vector <string> splitStringToToken(string inputStr, char delimiter)     //splits string into tokens to be stored into a vector
{
    stringstream ss(inputStr);  //create string stream object

    string token;   //variable to store token from stringstream

    vector <string> tokenVector;    //vector that will be returned


    while (getline(ss, token, delimiter))   //iterates through stringstream and separates by delimiter
    {
        if (ss.get() == ' '){   //checks if there is a space character in front of command

            ss.ignore(0);    //ignores space character

            //cout << "erase successful" << endl;     //debugging purpose

            tokenVector.push_back(token);   //pushes token to the end of the vector

        } else {

            //cout << "no erase" << endl;       //debugging purpose

            tokenVector.push_back(token);   //pushes token to the end of the vector

        }
    }

    return tokenVector;
}

