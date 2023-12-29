#include <SFML/Audio.hpp>
#include <nlohmann/json.hpp>
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <string>
#include <vector>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fstream>
using namespace std;
using json = nlohmann::json;

class Song
{
protected:
    string name;
    string address;
    Song() = default;

public:
    Song(string name, string address)
    {
        this->name = name;
        this->address = address;
    }
    virtual void setName(string name)
    {
        this->name = name;
    }
    virtual void setAddress(string address)
    {
        this->address = address;
    };
    virtual string getName()
    {
        return name;
    }
    virtual string getAddress()
    {
        return address;
    }

    json to_json() const
    {
        json user_json;
        user_json["name"] = name;
        user_json["address"] = address;
        // You may also want to include playlists and songs here if needed
        return user_json;
    }
    static Song *from_json(const json &song_json)
    {
        std::string name = song_json.at("name").get<std::string>();
        std::string address = song_json.at("address").get<std::string>();

        // Create and return a new Song object
        return new Song(name, address);
    }
};

class Qawali : public Song
{
    static int qawali_played;

public:
    Qawali() = default;
    Qawali(string name, string address) : Song(name, address)
    {
        cout << "Dtata stored" << endl;
    }
};
class Naat : public Song
{
    static int Naat_played;

public:
    Naat() = default;
    Naat(string name, string address) : Song(name, address)
    {
        cout << "Data stored" << endl;
    }
};
class Pop_Song : public Song
{
    static int Pop_played;

public:
    Pop_Song() = default;
    Pop_Song(string name, string address) : Song(name, address)
    {
        cout << "Data stored" << endl;
    }
};
class Other_Song : public Song
{
    static int other_played;

public:
    Other_Song() = default;
    Other_Song(string name, string address) : Song(name, address)
    {
        cout << "Data stored" << endl;
    }
};

class Playlist
{
    string name;
    vector<Song> songs;

public:
    Playlist() = default;
    Playlist(string playlist_name)
    {
        this->name = playlist_name;
    }
    string get_playlist_name()
    {
        return name;
    }
    void add_songs_to_playlist(Song *song)
    {
        songs.push_back(*song);
    }
    void display_songs()
    {
        int i = 0;
        for (Song x : songs)
        {
            cout << i << endl;
            cout << "Song name: " << x.getName() << endl;
            cout << "Song address: " << x.getAddress() << endl;
            i++;
        }
    }
    Song *return_song_obj(int index)
    {
        return &(songs[index]);
    }

    json to_json() const
    {
        json user_json;

        // int arr [songs.size()];
        vector<json> arr;

        for (int i = 0; i < songs.size(); i++)
        {
            arr.push_back(songs[i].to_json());
        }

        user_json["name"] = name;
        user_json["songs"] = arr;
        // You may also want to include playlists and songs here if needed
        return user_json;
    }
    static Playlist *from_json(const json &playlist_json)
    {
        Playlist *P1 = new Playlist();
        P1->name = playlist_json.at("name").get<std::string>();

        // Assuming you have a 'songs' array in your JSON representing the playlist's songs
        json songs_json = playlist_json.at("songs");
        for (const auto &song_json : songs_json)
        {
            Song *S1 = Song::from_json(song_json);
            P1->songs.push_back(*S1);
        }

        return P1;
    }
    void delete_object(int i)
    {
        songs.erase(songs.begin() + i);
    }
};

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
        this->username = username;
        this->password = password;
    }
    json to_json() const
    {
        json user_json;

        vector<json> playlists_json;
        for (int i = 0; i < playlists.size(); i++)
        {
            playlists_json.push_back(playlists[i].to_json());
        }
        user_json["username"] = username;
        user_json["password"] = password;
        user_json["playlists"] = playlists_json;
        // You may also want to include playlists and songs here if needed
        return user_json;
    }
    // Deserialize the User object from JSON
    static User *from_json(const json &user_json)
    {
        User *user = new User();
        user->username = user_json.at("username").get<std::string>();
        user->password = user_json.at("password").get<std::string>();

        // Deserialize playlists
        if (user_json.find("playlists") != user_json.end())
        {
            const json &playlists_json = user_json["playlists"];
            for (const auto &playlist_json : playlists_json)
            {
                user->playlists.push_back(*(Playlist::from_json(playlist_json)));
            }
        }

        return user;
    }
    string get_username()
    {
        return username;
    }
    string get_password()
    {
        return password;
    }
    void create_playlist(Playlist *p1)
    {
        playlists.push_back(*p1);
    }
    Playlist get_playlist(int i)
    {
        return playlists[i];
    }
    void display_playlist()
    {
        cout << playlists.size() << endl;

        for (int i = 0; i < playlists.size(); i++)
        {
            cout << i + 1 << "Playlist name: " << playlists[i].get_playlist_name() << endl;
            cout << "Playlist Songs: " << endl;
            playlists[i].display_songs();
        }
    }
};

class File_Handaling
{
public:
    DIR *dir;
    struct dirent *entry;
    struct stat fileStat;
};
class Controller
{
public:
    static void addSong(User user, Playlist playlist, Song song) {}
    static User *createUser()
    {

        cout << "Hey Welcome to our Music Player" << endl;
        cout << "Press 1 for Signing in" << endl;
        cout << "Press 2 for Signing up" << endl;
        char ch = getch();
        if (ch == '1')
        {
            string name;
            string password;
            cout << "Enter your Username" << endl;
            cin >> name;
            cout << "Enter your Password" << endl;
            cin >> password;

            return new User(name, password);
        }
        else if (ch == '2')
        {
            User *U1 = new User();
            string username, password, saved_pass;
            cout << "Enter Your Username" << endl;
            cin >> username;
            U1 = Controller::json_from_file(username);
            cout << "Enter Your Password" << endl;
            cin >> password;
            saved_pass = U1->get_password();
            if (saved_pass == password)
            {
                cout << "Jaane doo" << endl;
                return U1;
            }
            else
            {
                cout << "Tu chutti kar mera puat" << endl;
            }
        }
    }
    static Song *Song_addition()
    {
        string name;
        string address;
        string song_type;
        cout << "Enter Your Song name" << endl;
        cin >> name;
        cout << "Enter Your Song Adress" << endl;
        cin >> address;
        Pop_Song *S1 = new Pop_Song(name, address);
        return S1;
    }
    static Playlist *create_playlist(Playlist &untitled)
    {
        string playlist_name;
        int index;
        cout << "Enter Your Playlist Name" << endl;
        cin >> playlist_name;
        Playlist *p1 = new Playlist(playlist_name);
        untitled.display_songs();
        cout << "Choose the Song and enter its Number" << endl;
        cin >> index;
        Song *ptr = untitled.return_song_obj(index);
        p1->add_songs_to_playlist(ptr);
        return p1;
    }
    static void json_to_file(User &save, string file_name)
    {

        file_name=".\\log_files\\" +file_name+".json";
        cout<<file_name<<endl;
        json user_json = save.to_json();
        std::ofstream file(file_name);
        file << std::setw(4) << user_json; // Pretty print with indentation
        file.close();
    }
    static User *json_from_file(string file_name)
    {
        {
            file_name = file_name + ".json";
            std::ifstream infile(file_name);
            json loaded_json;
            infile >> loaded_json;
            User *loaded_user = User::from_json(loaded_json);
            return loaded_user;
        }
    }
    static void Menu()
    {
        cout<<"To add a new song press 1"<<endl;
        cout<<"To remove a song press 2"<<endl;
        cout<<"TO add a new Playlist press 3"<<endl;
        cout<<"To edit an existing Playlist press 4"<<endl;
        cout<<"To display Playlists and Songs Press 5"<<endl;
    }
};
int main()
{
    // User *U1 = Controller::createUser();
    // U1->display_playlist();


    
    // User *U2 = Controller::createUser();
    // Song* S1=Controller::Song_addition();
    // Song* S2=Controller::Song_addition();
    // Playlist p1("Untitled");
    // p1.add_songs_to_playlist(S1);
    // p1.add_songs_to_playlist(S2);
    // U2->create_playlist(&p1);
    // Playlist* p2=Controller::create_playlist(p1);
    // U2->create_playlist(p2);
    User U2("jamali","1234");
    Controller::json_to_file(U2,"random_user");
    // Playlist P1 = U1->get_playlist(0);
    // Playlist *P2 = Controller::create_playlist(P1);
    // U1->create_playlist(P2);
    // cout << "pehla rola muka" << endl;
    // sleep(20);
    // U1->display_playlist();
    sleep(225);
    return 0;
}
