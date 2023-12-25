#include <SFML/Audio.hpp>
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <string>
#include <vector>
#include <dirent.h>
#include <sys/stat.h>
#include<unistd.h>
using namespace std;

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
    string playlist_name;
    vector<Song> playlist_songs;

public:
    Playlist() = default;
    Playlist(string playlist_name)
    {
        this->playlist_name = playlist_name;
    }
    string get_playlist_name()
    {
        return playlist_name;
    }
    void add_songs(Song *song)
    {
        playlist_songs.push_back(*song);
    }
    void display_songs()
    {
        for (Song x : playlist_songs)
        {
            cout << x.getName() << endl;
            cout << x.getAddress() << endl;
        }
    }
};
class User
{
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
    void create_playlist(Playlist *p1)
    {
        playlists.push_back(*p1);
    }
    void display_playlist()
    {
        cout << playlists.size() << endl;

        for (int i = 0; i < playlists.size(); i++)
        {
            cout << "Playlist";
            cout << playlists[i].get_playlist_name() << endl;
            cout << "Mein pug gaya";
            playlists[i].display_songs();
        }
    }
};
class Interface
{
public:
    int x_axis;
    int y_axis;
    string heading;
};
class File_Handaling
{
public:
    DIR *dir;
    struct dirent *entry;
    struct stat fileStat;
};
class player
{

    float voloume;
    bool loop;
    // Function to play the song
};
int main()
{
    User U1("Jamali", "123");
    Pop_Song p1("Chaal chal tu apni", "D:\\Chaal-Chal-Tu-Apni-Main-Tujhe-Pahchan-Lunga(PaglaSongs).wav");
    Playlist *playlist_ptr = new Playlist("Untitled");
    Song *ptr = &p1;
    playlist_ptr->add_songs(ptr);
    U1.create_playlist(playlist_ptr);
    U1.display_playlist();
    string soundFilePath = p1.getAddress();

    // Load the sound file
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(soundFilePath))
    {
        std::cerr << "Failed to load the sound file." << std::endl;
        return 1;
    }
    sf::Sound sound(buffer);
    sound.play();
    cout << "i am still running";
    cout<<sound.getStatus()<<endl;
    while(sound.getStatus()){

    };
    cout<<sound.getStatus()<<endl;
    sleep(100);
}