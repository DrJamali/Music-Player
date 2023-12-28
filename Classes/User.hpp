#include"..\Libraries\Libraries.hpp"
using namespace std;
using json = nlohmann::json;
class User
{
private:
    string username;
    string password;
    vector<Playlist> playlists;

public:
    User() = default;
    User(string username, string password)
    {
    }
    json to_json() const
    {
    }
    // Deserialize the User object from JSON
    static User from_json(const json &user_json)
    {
    }
    string get_username()
    {
    }
    string get_password()
    {
    }
    void create_playlist(Playlist *p1)
    {
    }
    void display_playlist()
    {
    }
};
