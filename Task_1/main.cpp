#include <iostream>
#include <fstream>
#include <map>
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

int main () {
    std::ofstream out_file("film.json");
    nlohmann::json dict;
    Film figterClub;
    figterClub.yearProduction = 1998;
    figterClub.country = "USA, Germany";
    figterClub.genre = "thriller, drama, crime";
    figterClub.director = "David Fincher";
    figterClub.screenwriter = "Jim Uhls, Chuck Palahniuk";
    figterClub.filmCompany = "Fox 2000 Pictures Regency Enterprises";
    figterClub.producer = "Ross Grayson Bell, Sian Chaffin, John C. Dorsey, ...";
    figterClub.actors["Tyler Durden"] = "Brad Pitt";
    figterClub.actors["Teller"] = "Edward Norton";
    figterClub.actors["Marla Singer"] = "Helena Bonham";
    figterClub.actors["Robert Paulsen"] = "Meat Loaf";
    figterClub.actors["Richard Chesler"] = "Zach Grenier";
    
    dict["yearProduction "] = figterClub.yearProduction;
    dict["county"] = figterClub.country;
    dict["genre"] = figterClub.genre;
    dict["director"] = figterClub.director;
    dict["screenwriter"] = figterClub.screenwriter;
    dict["filmCompany"] = figterClub.filmCompany;
    dict["producer"] = figterClub.producer;
    std::map<std::string,std::string>::iterator iter = figterClub.actors.begin();
    for(;iter != figterClub.actors.end();++iter) {
        dict["actors"][iter->first] = iter->second;
    }
    out_file << dict;
    out_file.close();    
    std::cout<<"Done"<<std::endl;
}