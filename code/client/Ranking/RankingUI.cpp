
#include <vector>
#include "RankingUI.hpp"

void RankingUI::display(std::vector<RankingInfos> &ranking) {
    int rank = 1;
    for(RankingInfos &elem : ranking) {
        std::cout << rank << ") " << elem.username << "\t\t\t\t\t" << std::to_string(elem.victories) << " victories\n";
        rank++;
    }
    std::cout << "\nAppuyez sur une touche pour revenir dans le Menu..." << std::endl;
    int q;
    std::cin >>q;
    std::cin.clear();
    std::cin.ignore();
}