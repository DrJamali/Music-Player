#include"Classes_header.hpp"

Song::Song() : name(""), address("") {}

Song::Song(const std::string& name, const std::string& address) : name(name), address(address) {}

void Song::setName(const std::string& name) {
    this->name = name;
}

void Song::setAddress(const std::string& address) {
    this->address = address;
}

std::string Song::getName() const {
    return name;
}

std::string Song::getAddress() const {
    return address;
}

json Song::to_json() const {
    json user_json;
    user_json["name"] = name;
    user_json["address"] = address;
    return user_json;
}

Song* Song::from_json(const json& song_json) {
    std::string name = song_json.at("name").get<std::string>();
    std::string address = song_json.at("address").get<std::string>();
    return new Song(name, address);
}
