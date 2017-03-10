
#include "RankingUI.hpp"




void RankingUI::display(std::string ranking) {
    std::cout << ranking << std::endl;
    std::cout << "\nAppuyez sur une touche pour revenir dans le Menu..." << std::endl;
    int q;
    std::cin >>q;
    std::cin.clear();
    std::cin.ignore();
}