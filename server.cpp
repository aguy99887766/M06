#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <vector>
#include <limits>
#include <string>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <algorithm>
#include <cctype>




std::vector<std::map<std::string, std::string>> ReadContent(std::string filename) {
    std::ifstream ReadFile(filename);
    std::string word;
    std::string line;

    std::vector<std::map<std::string, std::string>> states;

    std::string abrev, name, govern, flower;




    while (getline(ReadFile, abrev)) {

        std::map<std::string, std::string> state;
        state["abrevation"] = abrev;

        if (!getline(ReadFile, name)) {
            break;
        }

        state["name"] = name;
        if (!getline(ReadFile, govern)) {
            break;
        }

        state["govern"] = govern;
        if (!getline(ReadFile, flower)) {
            break;
        }

        state["flower"] = flower;
        states.push_back(state);
    }
    ReadFile.close();

    return states;


}


void stateInfo(std::string state_abrevation, std::vector<std::map<std::string, std::string>> states) {

    for (const auto& state : states) {
        if (state.at("abrevation") == state_abrevation) {
            std::cout << "Abrevation: " << state.at("abrevation") << std::endl;
            std::cout << "Name: " << state.at("name") << std::endl;
            std::cout << "Governor: " << state.at("govern") << std::endl;
            std::cout << "Flower: " << state.at("flower") << std::endl;
            return;
        }

    }
    std::cout << "Could not find " << state_abrevation << std::endl;

}
std::string stateName(std::string state_abrevation, std::vector<std::map<std::string, std::string>> states) {

    for (const auto& state : states) {
        if (state.at("abrevation") == state_abrevation) {
            return state.at("name");
        }

    }
    std::cout << "Could not find " << state_abrevation << std::endl;
    return "";

}

void listStates(std::vector<std::map<std::string, std::string>> states) {
    for (const auto& state : states) {
        std::cout << state.at("abrevation") << std::endl;
    }
}


template <typename T>
void input(const std::string& question, T& value) {
    /*
    
    user input, has validation check
    
    */
    while (true) {
        std::cout << question << ": ";
        std::cin >> value; 

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Validation failed. Try again." << std::endl;
            
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
        

    }
}

std::string trim(const std::string& str) {
    size_t start = str.find_first_not_of(" \t\r\n");
    if (start == std::string::npos) { 
        return "";
    }

    size_t end = str.find_last_not_of(" \t\r\n");
    return str.substr(start, end-start+1);
    
    

}

int main() {
    /*
    std::string user;

    std::cout << "Hello user, to find a state input the abrevation of the state eg input AZ" << std::endl;
    std::cout << "input exit to quit the program" << std::endl;

    do {


        input("Command", user);

        if (user != "help" && user != "exit") {
            stateInfo(user, states);
        }

        if (user == "help") {
            listStates(states);
        }

    } while(user != "exit");

    */

    std::vector<std::map<std::string, std::string>> states = ReadContent("states.txt");

    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    bind(serverSocket, (struct sockaddr*)&serverAddress,sizeof(serverAddress));
    listen(serverSocket, 5);


    std::cout << "[ SERVER ] Listening on port 8080... " << std::endl;
    std::cout << "[ SERVER ] nc (IP_ADDR) 8080" << std::endl;
    while (true) {
        int clientSocket = accept(serverSocket, nullptr, nullptr);
        char buffer[1024] = { 0 };
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer)-1,0);

        if (bytesReceived > 0) {
            buffer[bytesReceived] = '\0';
            std::string userInput = trim(buffer);
            std::cout << "[ SERVER ] User requested " << userInput << std::endl;
            std::string message = stateName(userInput, states);
            if (message == "") {
                message = "I do not understand this state";
            }
            message += "\n";
            send(clientSocket, message.c_str(), message.size(), 0);

        }

        close(clientSocket);

    }

    close(serverSocket);

    return 0;
}