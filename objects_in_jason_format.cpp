#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <string.h>
using namespace std;
using json = nlohmann::json;

class User
{
private:
    std::string username;
    std::string password;

public:
    // ... (existing methods)
    User() = default;
    User(string username, string password)
    {
        this->username = username;
        this->password = password;
    }
    string get_username()
    {
        return username;
    }
    string get_password()
    {
        return password;
    }
    // Serialize the User object to JSON
    json to_json() const
    {
        json user_json;
        user_json["username"] = username;
        user_json["password"] = password;
        // You may also want to include playlists and songs here if needed
        return user_json;
    }

    // Deserialize the User object from JSON
    static User from_json(const json &user_json)
    {
        User user;
        user.username = user_json.at("username").get<std::string>();
        user.password = user_json.at("password").get<std::string>();
        // You may also want to handle playlists and songs here if needed
        
        return user;
    }
};

int main()
{
    // Example of serialization
    User user("john_doe", "password123");

    // Serialize to JSON
    json user_json = user.to_json();

    // Write to a file
    std::ofstream file("user.json");
    file << std::setw(4) << user_json; // Pretty print with indentation
    file.close();

    // Example of deserialization
    std::ifstream infile("user.json");
    json loaded_json;
    infile >> loaded_json;

    // Deserialize from JSON
    User loaded_user = User::from_json(loaded_json);
    cout<<loaded_user.get_password()<<endl;
    cout<<loaded_user.get_username()<<endl;
        // ... (continue with the rest of your code)
        return 0;
}
