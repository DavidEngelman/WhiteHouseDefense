#include "ProfileUI.hpp"


void ProfileUI::display() {
        /*Show user's menu*/
        std::cout << "   ======================================   " << std::endl;
        std::cout << "   |       1. My Profile                |   " << std::endl;
        std::cout << "   |       2. Search profile            |   " << std::endl;
        std::cout << "   |       3. Return to Main Menu       |   " << std::endl;
        std::cout << "   ======================================   " << std::endl;
}

int ProfileUI::select(){
    /* Ask at the user his choice */
    int x = -1;
    std::cout << "   Enter your choice: ";
    std::cin >> x;
    while(std::cin.fail() or 0>x or x>3){
        display();
        std::cout << "   Error, enter a integer between 1 and 3" << std::endl;
        std::cout << "   Enter your choice: ";

        std::cin.clear();
        std::cin.ignore();
        std::cin >> x;
    }
    return x;
}

std::string ProfileUI::askUsername() {
    std::cout<<"Profile's username : ";
    std::string profile ;
    std::cin >> profile;
    std::cout<<std::endl;
    return profile;
}

void ProfileUI::displayProfile(std::string profile) {
    int counter = 0;
    std::string username = "";
    while (profile[counter] != ','){
        username += profile[counter];
        counter++;
    }
    std::cout<< "Username : "<<username<<std::endl;
    counter++;
    std::string victories = "";
    while (profile[counter] != ','){
        victories += profile[counter];
        counter++;
    }
    std::cout<< "Victories : "<<victories<<std::endl;
    counter++;
    std::string pnjKilled = "";
    while (profile[counter] != ';'){
        pnjKilled += profile[counter];
        counter++;
    }
    std::cout<< "Pnj Killed : "<<pnjKilled<<std::endl;

}