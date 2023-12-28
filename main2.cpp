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
        for (Song x : songs)
        {
            cout << x.getName() << endl;
            cout << x.getAddress() << endl;
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
    static Playlist from_json(const json &playlist_json)
    {
        Playlist P1;
        P1.name = playlist_json.at("name").get<std::string>();

        // Assuming you have a 'songs' array in your JSON representing the playlist's songs
        json songs_json = playlist_json.at("songs");
        for (const auto &song_json : songs_json)
        {
            Song *S1 = Song::from_json(song_json);
            P1.songs.push_back(*S1);
        }

        return P1;
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
    static User from_json(const json &user_json)
    {
        User user;
        user.username = user_json.at("username").get<std::string>();
        user.password = user_json.at("password").get<std::string>();

        // Deserialize playlists
        if (user_json.find("playlists") != user_json.end())
        {
            const json &playlists_json = user_json["playlists"];
            for (const auto &playlist_json : playlists_json)
            {
                user.playlists.push_back(Playlist::from_json(playlist_json));
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
    void display_playlist()
    {
        cout << playlists.size() << endl;

        for (int i = 0; i < playlists.size(); i++)
        {

            cout << playlists[i].get_playlist_name() << endl;
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
    static User createUser()
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
            User U1(name, password);
            return U1;
        }
        else
        {
            cout << "kuch nhi";
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
    static Playlist create_playlist(Playlist untitled)
    {
        string playlist_name;
        int index;
        cout << "Enter Your Playlist Name" << endl;
        cin >> playlist_name;
        Playlist p1(playlist_name);
        untitled.display_songs();
        cout << "Choose the Song and enter its Number" << endl;
        cin >> index;
        Song *ptr = untitled.return_song_obj(index);
        p1.add_songs_to_playlist(ptr);
        return p1;
    }
};
int main()
{
    Pop_Song p1("", "This is my address");
    Pop_Song p2("hello world", "This is my 2nd address");
    // json user_json=p1.to_json();
    // cout<<"I am still running"<<endl;
    //  std::ofstream file("song.json");
    // file << std::setw(4) << user_json; // Pretty print with indentation
    // file.close();
    // // sleep(200);
    Playlist pla("Mera naam playlist hai");
    pla.add_songs_to_playlist(&p1);
    pla.add_songs_to_playlist(&p2);
    cout << "Still runnnnnnnnnnnnnnnnnnn..." << endl;
    sleep(20);
    User U1 = User("Jamaal", "12345");
    U1.create_playlist(&pla);
    json user_json = U1.to_json();
    cout << "Still runnnnnnnnnnnnnnnnnnn..." << endl;
    std::ofstream file("U3.json");
    file << std::setw(4) << user_json; // Pretty print with indentation
    file.close();
    // std::ifstream infile("user.json");
    // json loaded_json;
    // infile >> loaded_json;

    // Deserialize from JSON
    // User loaded_user = User::from_json(loaded_json);
    // cout << loaded_user.get_password() << endl;
    // cout << loaded_user.get_username() << endl;
    // Controller C1;
    // User U1 = C1.createUser();
    // Song *S1 = C1.Song_addition();
    // Playlist p1("Untitled");
    // p1.add_songs_to_playlist(S1);
    // U1.create_playlist(&p1);
    // Playlist p2 = C1.create_playlist(p1);
    // U1.create_playlist(&p2);
    // U1.display_playlist();
    // U1.to_json();
    // string soundFilePath = S1->getAddress();
    // cout << "Still running: 1" << endl;
    // json user_json = U1.to_json();
    //   std::string jsonString = user_json.dump();

    // // Save the JSON string to a text file
    // std::ofstream file("output.txt");
    // if (file.is_open()) {
    //     file << jsonString;
    //     file.close();
    //     std::cout << "JSON data saved to output.txt" << std::endl;
    // } else {
    //     std::cerr << "Unable to open the file." << std::endl;
    // }
    // ofstream file1;
    // file1.open("text.txt", ios::app);
    // file1.write((char *)&U1, sizeof(U1));
    // file1.close();
    // User U2;
    // ifstream file2;
    // file2.open("Employee.txt", ios::in);
    // file2.seekg(0);
    // file2.read((char *)&U2, sizeof(U2));
    // cout << U2.get_username() << endl;
    // cout << U2.get_password() << endl;
    // U2.display_playlist();
    // sleep(1000);
    // Load the sound file
    // sf::SoundBuffer buffer;
    // if (!buffer.loadFromFile(soundFilePath))
    // {
    //     std::cerr << "Failed to load the sound file." << std::endl;
    //     return 1;
    // }
    // sf::Sound sound(buffer);
    // sound.play();
    // cout << "i am still running";
    // cout << sound.getStatus() << endl;
    // while (sound.getStatus())
    // {
    // };
    // cout << sound.getStatus() << endl;
    sleep(100);
}
