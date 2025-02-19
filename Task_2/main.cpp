#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "nlohmann/json.hpp"

struct Film {
    struct Actor
    {
        std::string name;
        std::string role;
        Actor(std::string inName,std::string inRole) : name(inName),role(inRole) {}
    };
    std::vector<Actor> actors;
    std::string filmName;
    int yearProduction;
    std::string country;
    std::string genre;
    std::string director;
    std::string scrinwriter;
    std::string producer;
    
};

std::string inputStr() {
    std::string temp;
    std::cout<<" input : ";
    std::getline(std::cin>>std::ws,temp);
    return temp;
}

Film addFilm() {
    Film tempFilm;
    std::cout<<"\nFilm name ";
    tempFilm.filmName = inputStr();
    std::cout<<"\nYear of production : ";
    std::cin>> tempFilm.yearProduction;
    std::cout<<"\nCountry ";
    tempFilm.country = inputStr();
    std::cout<<"\nGenre ";
    tempFilm.genre = inputStr();
    std::cout<<"\nDirector ";
    tempFilm.director = inputStr();
    std::cout<<"\nScrinwriter ";
    tempFilm.scrinwriter = inputStr();
    std::cout << "\nProducer ";
    tempFilm.producer = inputStr();
    do {
        char choice;
        std::cout<<"\nAdd actor (y/n) : ";
        std::cin>>choice;
        if(choice == 'y') {
            std::string tempName;
            std::string tempRole;
            std::cout<<"\nActor name ";
            tempName = inputStr();
            std::cout<<"\nRole ";
            tempRole = inputStr();
            tempFilm.actors.emplace_back(tempName,tempRole);
        }
        else if (choice == 'n') {
            break;
        }
    }while(true);
    return tempFilm;
}

bool findActor(std::string nameSearh,std::string name) {
    for(int i = 0; i <= name.length()-nameSearh.length();++i) {
        bool find = true;
        for(int j = 0; j < nameSearh.length();++j) {
            if(name[i+j] != nameSearh[j]) {
                find = false;
            }
        }
        if(find) {
            return true;
        }
    }
    return false;
}

int main () {
    std::ifstream in_file("cinema.json");
    nlohmann::json dict;
    if(in_file.is_open()){
        
    }
    in_file.close();    
    std::vector<Film> cinema;
    std::string choice;
    while(choice != "find") {        
        std::cout<<"\nEnter add or find : ";
        std::cin>>choice;
        if(choice == "add") {
            cinema.push_back(addFilm());
        }
    }
    if(!cinema.empty()) {
        for(auto & current : cinema) {
            dict[current.filmName]["yearProduction"] = current.yearProduction;
            dict[current.filmName]["country"] = current.country;
            dict[current.filmName]["director"] = current.director;
            dict[current.filmName]["genre"] = current.genre;
            dict[current.filmName]["scrinwriter"] = current.scrinwriter;
            dict[current.filmName]["producer"] = current.producer;
            for(auto currentActors : current.actors) {
                dict[current.filmName]["actors"][currentActors.role] = currentActors.name;                
            }
        }
        std::ofstream out_File("cinema.json");
        out_File << dict;
        out_File.close();
    }
    std::string nameSearh;
    std::cout << "\nName of actor : ";
    std::cin >> nameSearh;
    std::ifstream in_file2 ("cinema.json");
    in_file2 >> dict;
    in_file.close();
    for (auto iterFilm = dict.begin(); iterFilm != dict.end(); ++iterFilm) {
        auto iterFilmFild = iterFilm->find("actors");
        for (auto& iterActors = iterFilmFild->begin(); iterActors != iterFilmFild->end(); ++iterActors) {
            if (findActor(nameSearh, iterActors.value())) {
                std::cout << "Actor " << iterActors.value() << " Play role " << iterActors.key() << std::endl;
                std::cout << "In film : " << iterFilm.key() << std::endl;
            }
        }
    }
}