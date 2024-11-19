#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include "nlohmann/json.hpp"

struct Film {
    int yearProduction;
    std::string country;
    std::string genre;
    std::string director;
    std::string screenwriter;
    std::string filmCompany;
    std::string producer;
    std::map<std::string,std::string> actors;
};

bool checkNum(const std::string & numStr) {
    for(int i = 0;i < numStr.length();++i){
        if(numStr[i] < '0' || numStr[i] > '9') {
            std::cout<<"Not a number !"<<std::endl;
            return true;
        }
    }
    return false;
}

std::string enterStr() {
    std::string tempName;        
    std::getline(std::cin>>std::ws,tempName);
    return tempName;
}

Film makeFilm() {
    Film tempFilm;    
    std::string tempStr;
    do {
        std::cout<<"\nEnter year of production : ";
        std::cin>>tempStr;
    } while(checkNum(tempStr));
    tempFilm.yearProduction = std::stoi(tempStr);
    std::cout<<"\nEnter film country : ";
    tempFilm.country = enterStr();
    std::cout<<"\nEnter film genre : ";
    tempFilm.genre = enterStr();
    std::cout<<"\nEnter film director : ";
    tempFilm.director = enterStr();
    std::cout<<"\nEnter film screewriter : ";
    tempFilm.screenwriter = enterStr();
    std::cout<<"\nEnter film company : ";
    tempFilm.filmCompany = enterStr();
    std::cout<<"\nEnter producer : ";
    tempFilm.producer = enterStr();
    do {
        std::cout<<"\nRole name : ";
        tempStr = enterStr();
        std::cout<<"\nActor name : ";
        tempFilm.actors[tempStr] = enterStr();
        std::cout<<"\nadd actor or \"end\" ?";
        std::cin>>tempStr;
    } while(tempStr != "end");
    return tempFilm;
}

bool findStr(std::string strWhat,std::string strIn) {    
    for(int i = 0 ; i <= strIn.length() - strWhat.length();++i) {
        bool found = true;
        for(int j = 0; j < strWhat.length() && found;++j) {
            if(strIn[i+j] != strWhat[j]){
                found = false;
            }
        }
        if(found){
            return true;
        }
    }
    return false;
}

int main () {
    std::string choice;
    std::cout<<"\"add\" or \"upload\" movies ? If you are a user, you can just upload, the movies are already added : ";
    std::cin>>choice;
    if(choice == "add") {
        nlohmann::json dict;
        std::ifstream in_file("cinema.json");
        if(in_file.is_open()) {
            in_file >> dict;
        }        
        in_file.close();
        std::map<std::string,Film> cinema;  
        std::ofstream out_file("cinema.json");
        while(choice != "end") {
            std::cout<<"\"add\" movie or \"end\" additing : ";
            std::cin>>choice;
            if(choice == "add") {
                std::cout<<"\nEnter film name : "<<std::endl;
                std::string filmName = enterStr();
                cinema.insert(std::pair<std::string,Film> (filmName,makeFilm()));
            }
        }        
        std::map<std::string,Film>::iterator iter = cinema.begin();
        if(iter != cinema.end()) {
            for(;iter != cinema.end();++iter) {
                dict[iter->first]["yearProduction"] = iter->second.yearProduction;
                dict[iter->first]["country"] = iter->second.country;
                dict[iter->first]["genre"] = iter->second.genre;
                dict[iter->first]["director"] = iter->second.director;
                dict[iter->first]["screenwriter"] = iter->second.screenwriter;
                dict[iter->first]["filmCompany"] = iter->second.filmCompany;
                dict[iter->first]["producer"] = iter->second.producer;
                for(std::map<std::string,std::string>::iterator iterActor = iter->second.actors.begin(); iterActor != iter->second.actors.end();++iterActor) {
                    dict[iter->first]["actors"][iterActor->first] = iterActor->second;
                }
            }
        }
        out_file << dict;
        out_file.close();
    }  
    std::ifstream in_file("cinema.json");
    nlohmann::json dict;
    in_file >> dict;
    std::string nameActor;
    while(true) {    
        std::cout<<"\nEnter actor name, last name or \"exit\" : ";
        std::cin>>nameActor;
        if(nameActor == "exit") {
            break;
        }
        for(nlohmann::json::iterator iterFilm = dict.begin(); iterFilm != dict.end();++iterFilm) {         
            for(nlohmann::json::iterator iterActor = iterFilm->begin();iterActor != iterFilm->end();++iterActor) {
                if(iterActor.key() == "actors") {
                    for(nlohmann::json::iterator iterName = iterActor->begin();iterName != iterActor->end();++iterName) {
                        if(findStr(nameActor,iterName.value())){
                            std::cout<<"Actor " << iterName.value() << " Play role : " << iterName.key() <<std::endl;
                            std::cout<<"In film : " << iterFilm.key()<<std::endl;
                        }
                    }
                }
            }            
        }
    }
    in_file.close();
}