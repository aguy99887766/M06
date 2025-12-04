#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>
#include <sstream>
#include <limits>
#include <vector>


class POS {
protected:
    int movement_x;
    int movement_y;

public:
    POS(int x, int y) : movement_x(x), movement_y(y) {

        if (movement_x > 100 || movement_x < 0 || movement_y > 100 || movement_y < 0) {
            throw std::runtime_error("Position must be between 0 and 100");
        }


    }

    void moveX(int diff) {
        movement_x += diff;
    }

    void moveY(int diff) {
        movement_y += diff;
    }

    int getX() const {
        return movement_x;
    }

    int getY() const {
        return movement_y;
    }


};

class Player {
protected:

    std::string playerName;
    int playerID;
    int energy = 100;
    POS playerPos = POS(0, 0);

public:

    Player(std::string name, int player_id) : playerName(name), playerID(player_id) {}

    std::string getName() const {
        return playerName;
    }
    
    int getPlayerID() const {
        return playerID;
    }

    virtual std::string getRole() const {
        return "Generic";
    }

    void getPlayerPOS() {
        int x = playerPos.getX();
        int y = playerPos.getY();
        std::cout << "X: " << x << std::endl
                << "Y: " << y << std::endl;
    }
    
    int getEnergy() const {
        return energy;
    }

    void expendEnergy(int amount) {
        energy -= amount;
    }

    void move(int x_amount, int y_amount) {

        playerPos.moveX(x_amount);
        playerPos.moveY(y_amount);

        getPlayerPOS();
    }

    virtual void play() {

        if (energy <= 0) {
            std::cout << "I can't play anymore!" << std::endl;
        }
        energy -= 1;

        std::cout << "I have expanded energy" << std::endl << 
            "Energy: " << energy << std::endl;

    }

    std::string toString() const {
        int x = playerPos.getX();
        int y = playerPos.getY();
        std::string information = "Name: "+getName() + 
            "\nID: " + std::to_string(getPlayerID()) +
            "\n ROLE: " + getRole() + 
            "\nEnergy: " + std::to_string(getEnergy()) +
            "\n(" + std::to_string(x) + ", " + std::to_string(y) + ")";
        return information;
    }

};
// Offense
class QuarterBack : public Player {
public:
    QuarterBack(std::string n, int id) : Player(n, id) {}
    std::string getRole() const override { return "Quarterback"; }
    void play() override { std::cout << getName() << " throws passes!" << std::endl; Player::play(); }
};

class WideReceiver : public Player {
public:
    WideReceiver(std::string n, int id) : Player(n, id) {}
    std::string getRole() const override { return "Wide Receiver"; }
    void play() override { std::cout << getName() << " runs routes and catches passes!" << std::endl; Player::play(); }
};

class TightEnd : public Player {
public:
    TightEnd(std::string n, int id) : Player(n, id) {}
    std::string getRole() const override { return "Tight End"; }
    void play() override { std::cout << getName() << " blocks or catches passes!" << std::endl; Player::play(); }
};

class RunningBack : public Player {
public:
    RunningBack(std::string n, int id) : Player(n, id) {}
    std::string getRole() const override { return "Running Back"; }
    void play() override { std::cout << getName() << " runs the ball!" << std::endl; Player::play(); }
};

class OffensiveLineman : public Player {
public:
    OffensiveLineman(std::string n, int id) : Player(n, id) {}
    std::string getRole() const override { return "Offensive Lineman"; }
    void play() override { std::cout << getName() << " blocks and protects the QB!" << std::endl; Player::play(); }
};

// Defense
class DefensiveLineman : public Player {
public:
    DefensiveLineman(std::string n, int id) : Player(n, id) {}
    std::string getRole() const override { return "Defensive Lineman"; }
    void play() override { std::cout << getName() << " rushes the QB!" << std::endl; Player::play(); }
};

class Linebacker : public Player {
public:
    Linebacker(std::string n, int id) : Player(n, id) {}
    std::string getRole() const override { return "Linebacker"; }
    void play() override { std::cout << getName() << " stops the run or covers!" << std::endl; Player::play(); }
};

class DefensiveBack : public Player {
public:
    DefensiveBack(std::string n, int id) : Player(n, id) {}
    std::string getRole() const override { return "Defensive Back"; }
    void play() override { std::cout << getName() << " covers receivers!" << std::endl; Player::play(); }
};
// Special

class Kicker : public Player {
public:
    Kicker(std::string n, int id) : Player(n, id) {}
    std::string getRole() const override { return "Kicker"; }
    void play() override { std::cout << getName() << " kicks field goals!" << std::endl; Player::play(); }
};

class Holder : public Player {
public:
    Holder(std::string n, int id) : Player(n, id) {}
    std::string getRole() const override { return "Holder"; }
    void play() override { std::cout << getName() << " holds the ball for the kicker!" << std::endl; Player::play(); }
};

class Punter : public Player {
public:
    Punter(std::string n, int id) : Player(n, id) {}
    std::string getRole() const override { return "Punter"; }
    void play() override { std::cout << getName() << " punts the ball!" << std::endl; Player::play(); }
};

class Returner : public Player {
public:
    Returner(std::string n, int id) : Player(n, id) {}
    std::string getRole() const override { return "Returner"; }
    void play() override { std::cout << getName() << " returns kicks!" << std::endl; Player::play(); }

};

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


std::vector<Player*> menu() {
    std::vector<Player*> team;
    int choice;
    std::string name;
    int id;

    for (int i=0; i < 3; i++) {
        std::cout << "\nMenu:\n";
        std::cout << "1. Add Quarterback\n";
        std::cout << "2. Add Wide Receiver\n";
        std::cout << "3. Add Running Back\n";
        std::cout << "4. Add Defensive Lineman\n";
        std::cout << "5. Add Linebacker\n";
        std::cout << "6. Add Defensive Back\n";
        std::cout << "7. Add Kicker\n";
        std::cout << "8. Add Punter\n";
        std::cout << "9. Show all players\n";
        std::cout << "10. Exit\n";
        
        input("Choose an option", choice);

        switch (choice) {
            case 1:
                input("Enter player's name", name);
                input("Enter player's ID", id);
                team.push_back(new QuarterBack(name, id));
                break;

            case 2:
                input("Enter player's name", name);
                input("Enter player's ID", id);
                team.push_back(new WideReceiver(name, id));
                break;

            case 3:
                input("Enter player's name", name);
                input("Enter player's ID", id);
                team.push_back(new RunningBack(name, id));
                break;

            case 4:
                input("Enter player's name", name);
                input("Enter player's ID", id);
                team.push_back(new DefensiveLineman(name, id));
                break;

            case 5:
                input("Enter player's name", name);
                input("Enter player's ID", id);
                team.push_back(new Linebacker(name, id));
                break;

            case 6:
                input("Enter player's name", name);
                input("Enter player's ID", id);
                team.push_back(new DefensiveBack(name, id));
                break;

            case 7:
                input("Enter player's name", name);
                input("Enter player's ID", id);
                team.push_back(new Kicker(name, id));
                break;

            case 8:
                input("Enter player's name", name);
                input("Enter player's ID", id);
                team.push_back(new Punter(name, id));
                break;

            case 9:
                if (team.empty()) {
                    std::cout << "No players added yet.\n";
                } else {
                    std::cout << "\nList of Players on the Team:\n";
                    for (const auto& player : team) {
                        std::cout << "Name: " << player->getName() << "\n"
                                  << "ID: " << player->getPlayerID() << "\n"
                                  << "Description: " << player->toString() << "\n";
                        player->play();
                        std::cout << "------------------------\n";
                    }
                }
                break;

            case 10:
                std::cout << "Exiting program.\n";
                return team;

            default:
                std::cout << "Invalid option, please try again.\n";
                break;
        }
    }

    return team;

}

int main() {

    std::vector<Player*> team = menu();

    for (auto player : team) {
        std::cout << player->toString() << std::endl;
        delete player;
    }

    return 0;
}