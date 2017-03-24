
#include <vector>
#include "RankingConsoleUI.hpp"


RankingConsoleUI::RankingConsoleUI(RankingManager *rankingManager) : RankingUI(rankingManager) {}

void RankingConsoleUI::display(std::vector<RankingInfos> &ranking) {
    int rank = 1;
    for(RankingInfos &elem : ranking) {
        std::cout << rank << ") " << elem.username << "\t\t\t\t\t" << std::to_string(elem.victories) << " victories\n";
        rank++;
    }

    std::cout << "\nPress Enter to come back in the main menu..." << std::endl;
    std::cin.ignore().get();
}