#include <iostream>
#include <fstream>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

int welcome() {
    std::cout << "Please enter 1 if you would like to see a list of ingredients:\n\n";
    std::cout << "Please enter 2 if you would like to search for an ingredient:\n";
    int x;
    std::cin >> x;
    return x;
}

std::vector<std::string> search(std::unordered_map<std::string, std::string> dict, std::string query) {
    std::vector<std::string> results;
    int i = 1;
    for(auto it: dict) {
        std::string str = it.first;
        std::size_t keyword = str.rfind(query, 0);
        if(keyword == 0) {
            std::cout << i << " "<< str << "\n";
            i++;
            results.push_back(str);
        }
    }
    return results;
}

int main() {


   std::ifstream guide ("substitution_ingredients_list.txt");
   std::unordered_map <std::string, std::string> substitution_dict;
   std::string line;
   std::string key;
   std::string value;

   if (guide.is_open()) {
    while (guide.good()) {
        std::getline(guide, key);
        std::getline(guide, value);
        substitution_dict.insert({key, value});
    }
    }
//welcome starts here

    std::cout << "Welcome to 'Who used all the milk!?' your guide to ingredient substitution!\n";

    int x = 0;
    std::string search_query;
    char response = 'y';
    int list_choice = 1;

    while(response == 'y') {
        while(x != 1 || x != 2) {
            x = welcome();

            if(x == 1) {
                for(auto it: substitution_dict) {
                    std::cout << it.first << "\n";
                }
                std::cout << "Would you like more information on one of the ingredients?\n";
                std::cout << "Press 'y' for yes or 'n' to exit:\n";
                std::cin >> response;
                if(tolower(response) == 'n') {
                   std::cout << "Thanks for using 'Who used all milk!?'\n";
                   std::cout << "Goodbye!"; 
                }
                else {
                    x = 2;
                }
            }

            if(x == 2) {
                std::vector<std::string> results;
                std::cout << "Please enter a letter(s) or word to search:\n";
                std::cin >> search_query;
                /*for(int i = 0; i < search_query.length(); i++) {
                    search_query = tolower(search_query[i]);
                    std::cout << search_query << "\n";

                    NEED to debug making input all lower, when Lem is searched it brings up lemon, lime, lard
                }*/

                try {
                    //std::cout << substitution_dict.at(search_query) << "\n";
                    results = search(substitution_dict, search_query);
                }

                catch (const std::out_of_range& e) {
                    std::cout << "Sorry, no entry found. Please try another ingredient.\n";
                }

                std::cout << "If you would like to see more information on one of the results please enter 'y' for yes or 'n' for no:\n";
                std::cin >> response;

                if(tolower(response == 'y')) {
                    
                    std::cout << "Please enter the number of the ingredient you would like to view:\n";
                    std::cin >> list_choice;

                    try {
                        std::cout << "You selected:\n";
                        std::cout << results[list_choice - 1] << "\n";
                        std::cout << substitution_dict[results[list_choice - 1]] << "\n";
                    }
                    catch (const std::out_of_range& e) {
                            std::cout << "Sorry, no entry found. Please try another number.\n";
                    }
                }
                    
            }
                std::cout << "Would you like to search another ingredient?\n";
                std::cout << "Press 'y' to search, or 'n' to exit:\n";

                x = 0;
                std::cin >> response;

                if(tolower(response) == 'n') {
                    std::cout << "Thanks for using 'Who used all milk!?'\n";
                    std::cout << "Goodbye!\n";
                    break;
                }
        }
    
    }
    return 0;
}
