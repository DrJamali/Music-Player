#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio/SoundStream.hpp>
#include<SFML/System.hpp>
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
#include <ctime>
using namespace std;
using json = nlohmann::json;
int Old_User_Flag = 0;
int width;

class Song
{
protected:
    string name;
    string address;

public:
    Song() = default;
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
        string name = song_json.at("name").get<string>();
        string address = song_json.at("address").get<string>();

        // Create and return a new Song object
        return new Song(name, address);
    }
};

class Qawali : public Song
{
    

public:
    Qawali() = default;
    Qawali(string name, string address) : Song(name, address)
    {
        cout << "Dtata stored" << endl;
    }
};
class Naat : public Song
{

public:
    Naat() = default;
    Naat(string name, string address) : Song(name, address)
    {
        cout << "Data stored" << endl;
    }
};
class Pop_Song : public Song
{
public:
    Pop_Song() = default;
    Pop_Song(string name, string address) : Song(name, address)
    {
        cout << "Data stored" << endl;
    }
};
class Other_Song : public Song
{
    
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

public:
    vector<Song> songs;

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
            cout << "Song Number: " << i << endl;
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
        vector<json> song_arr;

        for (int i = 0; i < songs.size(); i++)
        {
            song_arr.push_back(songs[i].to_json());
        }

        user_json["name"] = name;
        user_json["songs"] = song_arr;
        // You may also want to include playlists and songs here if needed
        return user_json;
    }
    static Playlist *from_json(const json &playlist_json)
    {
        Playlist *P1 = new Playlist();
        P1->name = playlist_json.at("name").get<string>();

        // Assuming you have a 'songs' array in your JSON representing the playlist's songs
        json songs_json = playlist_json.at("songs");
        for ( auto &song_json : songs_json)
        {
            
            P1->songs.push_back(*(Song::from_json(song_json)));
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

public:
    vector<Playlist> playlists;
    User() = default;
    User(string username, string password)
    {
        this->username = username;
        this->password = password;
    }
    json to_json() 
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
    static User *from_json( json &user_json)
    {
        User *user = new User();
        user->username = user_json.at("username").get<string>();
        user->password = user_json.at("password").get<string>();

        // Deserialize playlists
        if (user_json.find("playlists") != user_json.end())
        {
             json playlists_json = user_json["playlists"];
            for ( auto playlist_json : playlists_json)
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
    Playlist *get_playlist(int i)
    {
        return &playlists[i];
    }
    void display_playlist()
    {
        cout << playlists.size() << endl;

        for (int i = 0; i < playlists.size(); i++)
        {
            cout << "Playlist Number: " << i << endl
                 << " Playlist name: " << playlists[i].get_playlist_name() << endl;
            cout << "Playlist Songs: " << endl;
            playlists[i].display_songs();
        }
        
    }
};

class Interface_
{

public:
    static void gotox(int x)
    {
        COORD c;
        c.X = x;

        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
        return;
    }
    static void gotoxy(int x, int y)
    {
        COORD c;
        c.X = x;
        c.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
        return;
    }
    static void gotoy(int y)
    {
        COORD c;
        c.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
        return;
    }

    static int getConsoleSize()
    {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        return 0;
    }

    static void printStarLine(int length, int x, int y)
    {
        gotoxy(x, y);
        for (int i = 0; i < length; i++)
        {
            cout << "*";
        }
    }
    static void display_interace()
    {

        getConsoleSize();
        printStarLine(width, 0, 0);
        cout << endl;
        string heading = "Welcome to Our Music Player";
        int middle = (width - heading.size()) / 2;
        gotoxy(middle, 3);
        cout << heading << endl;
        printStarLine(width, 0, 4);
    }
};
class Suggestions
{
    int time;
    Song song;
    int count;

public:
    vector<Suggestions> suggestions;

    int get_time()
    {
        std::time_t currentTime = std::time(nullptr);

        // Convert the time to a local time structure
        tm *timeInfo = localtime(&currentTime);

        return timeInfo->tm_hour;
    }
    void add_suggestion_to_json(Song s1)
    {
        song = s1;
        time = get_time();
        json new_suggestion = song.to_json();
        new_suggestion["Time"] = time;
        // Read existing content from the file
        std::ifstream file_in(".\\log_files\\suggestions.json");
        json existing_content;
        file_in >> existing_content;
        file_in.close();
        // Add the new suggestion to the existing content
        existing_content.push_back(new_suggestion);
        // Write the modified content back to the file
        std::ofstream file_out(".\\log_files\\suggestions.json");
        file_out << std::setw(4) << existing_content;
        file_out.close();
    }
    void load_suggestion_from_json()
    {
        json loaded;
        ifstream file_in(".\\log_files\\suggestions.json");
        file_in >> loaded;
        static int quater;
        if (get_time() <= 6)
        {
            quater = 6;
        }
        else if (get_time() <= 12)
        {
            quater = 12;
        }
        else if (get_time() <= 18)
        {
            quater = 18;
        }
        else if (get_time() <= 24)
        {
            quater = 24;
        }

        for (auto &x : loaded)
        {
            if (x.at("Time").get<int>() >= quater)
            {
                continue;
            }
            Suggestions new_suggestions;
            new_suggestions.song.setName(x.at("name").get<string>());
            new_suggestions.song.setAddress(x.at("address").get<string>());
            new_suggestions.time = (x.at("Time").get<int>());
            this->suggestions.push_back(new_suggestions);
        }
    }
    void sort_suggestions()
    {
        for (int i = 0; i < suggestions.size(); i++)
        {
            Suggestions &s1 = suggestions[i]; // Use a reference here
            s1.count = 1;

            for (int j = i + 1; j < suggestions.size(); j++)
            {
                if (s1.song.getName() == suggestions[j].song.getName())
                {
                    s1.count++;
                    suggestions.erase(suggestions.begin() + j);
                    j--; // Adjust the index after erasing an element
                }
            }
        }
        for (int i = 0; i < suggestions.size() - 1; i++)
        {
            for (int j = i + 1; j < suggestions.size(); j++)
            {
                if (suggestions[i].count < suggestions[j].count)
                {
                    swap(suggestions[j], suggestions[i]);
                }
            }
        }
    }
    void display_suggestions()
    {
        this->load_suggestion_from_json();
        sort_suggestions();
        int i;
        for (auto x : suggestions)
        {
            cout<<"Song number: "<<i<<endl;
            cout << x.song.getAddress() << endl;
            cout << x.song.getName() << endl;
            cout << x.count << endl;
        }
        cout<<"Select the song you want to listen"<<endl;
        int index;
        cin >> index;
        call_controller(index);
    }
    void call_controller(int index);
};
class Controller
{

public:
    static void addSong(User user, Playlist playlist, Song song) {}
    static User *createUser()
    {
         string username;
            string password;
        cout << "Hey Welcome to our Music Player" << endl;
        cout << "Press 1 for Signing in" << endl;
        cout << "Press 2 for Signing up" << endl;
        char ch = getch();
        if (ch == '2')
        {
           
            cout << "Enter your Username" << endl;
            cin >> username;
            cout << "Enter your Password" << endl;
            cin >> password;
            Old_User_Flag = 0;
            return new User(username, password);
        }
        else if (ch == '1')
        {
            User *U1 = new User();
            
            cout << "Enter Your Username" << endl;
            cin >> username;
            U1 = Controller::json_from_file(username);
            cout << "Enter Your Password" << endl;
            cin >> password;
            
            if (U1->get_password() == password)
            {
                cout << "Jaane doo" << endl;
                Old_User_Flag = 1;
                return U1;
            }
            else
            {
                cout << "Your Password is incorrect" << endl;
                sleep(5);
                return createUser();
            }
        }
    }
    static Song *create_song()
    {
        

        string name;
        string address;
        char song_type;
        cout << "Enter Your Song name" << endl;
        getline(cin, name);
        cout << "Enter Your Song Adress" << endl;
        getline(cin, address);
        cout << "Enter Your Song type " << endl
             << "Press 1 for Pop Song" << endl
             << "2 for Naat" << endl
             << "3 for Qawali" << endl
             << "4 for any other " << endl;
        song_type = getch();
        
        if (song_type == '1')
        {
            return new Pop_Song(name, address);
        }
        else if (song_type == '2')
        {
            return new Naat(name, address);
        }
        else if (song_type == '3')
        {
            return new Qawali(name, address);
        }
        else
        {
            return new Other_Song(name, address);
        }
        
    }
    static void create_playlist(User &u1)
    {
        int index;
        cout << "If you want to add songs in existing plalists press 1" << endl;
        cout << "If you want to create new plalists press 2" << endl;
        char ch = getch();
        if (ch == '1')
        {
            u1.display_playlist();
            cout << "Enter the number of playlist in which you want to add song" << endl;
            cin >> index;
            Playlist *p2 = u1.get_playlist(index);
            cout << p2->get_playlist_name() << "selected" << endl;
            cout << "Songs already existed in playlist" << endl;
            p2->display_songs();
            cout << "Songs available to be added to playlist" << endl;
            u1.playlists[0].display_songs();
            cout << "Choose the Song and enter its Number from available to add them: ";
            cin >> index;
            Song *ptr = u1.playlists[0].return_song_obj(index);
            p2->add_songs_to_playlist(ptr);
            u1.playlists[0].delete_object(index);
            u1.create_playlist(p2);
            cout << "Playlist edited successfully..." << endl;
        }
        else if (ch == '2')
        {
            string playlist_name;
            cout << "Enter Your Playlist Name: " << endl;
            getline(cin, playlist_name);
            Playlist *p1 = new Playlist(playlist_name);
            u1.playlists[0].display_songs();
            cout << "Choose the Song and enter its Number: ";
            cin >> index;
            Song *ptr = u1.playlists[0].return_song_obj(index);
            p1->add_songs_to_playlist(ptr);
            u1.playlists[0].delete_object(index);
            u1.create_playlist(p1);
            cout << "Playlist created successfully..." << endl;
            u1.display_playlist();
        }
    }
    static void json_to_file(User &save)
    {
        string file_name = save.get_username();
        file_name = ".\\log_files\\" + file_name + ".json";
        cout << file_name << endl;
        json user_json = save.to_json();
        ofstream file(file_name);
        file << setw(4) << user_json; // Pretty print with indentation
        file.close();
    }
    static User *json_from_file(string file_name)
    {
        {
            file_name = ".\\log_files\\" + file_name + ".json";
            ifstream infile(file_name);
            json loaded_json;
            infile >> loaded_json;
            return (User::from_json(loaded_json));
        }
    }
    static void Main_Menu()
    {
        User *U1 = Controller::createUser();
        if (Old_User_Flag == 0)
        {
        Playlist *untitled;
            untitled = new Playlist("untitled");
            U1->create_playlist(untitled);
        }
        char ch;
        while (1)
        {
            ch = '0';
            cout << "Character value: " << ch << endl;
            cout << "To go to Player Menu press P" << endl;
            cout << "To add a new song press 1" << endl;
            cout << "To remove a song press 2" << endl;
            cout << "TO add a new Playlist press 3" << endl;
            cout << "To display Playlists and Songs Press 4" << endl;
            cout << "To save your data press 5" << endl;
            cout<<"To go to suggestions press 6" << endl;
            cout << "To Find the any song press f " << endl;
            ch = getch();
            if (ch == '1')
            {
                cout << "Press Enter to add songs" << endl;
                cin.ignore();
                Song *S1 = Controller::create_song();
                U1->playlists[0].songs.push_back(*S1);
                cout << "Song deleted successfully..." << endl;
                U1->display_playlist();
            }
            else if (ch == '2')
            {
                U1->display_playlist();
                cout << "Enter the Playlist number: ";
                int index = 0;
                cin >> index;
                Playlist *P1 = U1->get_playlist(index);
                cout << index << " Number playlist selected" << endl;
                P1->display_songs();
                cout << "Enter the Song number: ";
                cin >> index;
                P1->delete_object(index);
                cout << "Songs deleted successfully..." << endl;
            }
            else if (ch == '3')
            {

                Controller::create_playlist(*U1);
            }
            else if (ch == '4')
            {
                U1->display_playlist();
            }
            else if (ch == 'q')
            {
                return;
            }
            else if (ch == 'p')
            {
                Controller::player_menu(*U1);
            }
            else if (ch == '5')
            {
                Controller::json_to_file(*U1);
            }
            else if (ch == '6')
            {
                cout << "S accepted" << endl;
                Suggestions s1;
                s1.display_suggestions();
            }
            else if (ch == 'f')
            {
                string song_name;
                int flag;
                cout << "Enter your Song name: " << endl;
                cin.ignore();
                getline(cin, song_name);

                for (int i = 0; i < U1->playlists.size(); i++)
                {
                    flag = 0;
                    for (int j = 0; j < U1->playlists[i].songs.size(); j++)
                    {
                        if (U1->playlists[i].songs[j].getName() == song_name)
                        {
                            cout << "Your Song is in... "
                                 << "Playlist No: " << i << "Song Number: " << j << endl;
                            flag = 1;
                        }
                        cout<<U1->playlists[i].songs[j].getName()<<endl;
                        cout<<"Song name is "<<song_name<<endl;
                    }
                }
                if (flag == 0)
                {

                    cout << "Found Nothing" << endl
                         << "Try with different name" << endl;
                }
            }
            else
            {
                cout << "Invalid Input" << endl;
                sleep(5);
                Controller::Main_Menu();
            }
            cout << "Press enter to continue..." << endl;
            cin.ignore();
        }
    }
    static void player_menu(User U1)
    {

        while (1) // string soundFilePath;
        {
            U1.display_playlist();
            int index;
            cout << "Select a Playlist number" << endl;
            cin >> index;
            Playlist p1 = U1.playlists[index];
            p1.display_songs();
            cout << "To loop over whole Playlist press i" << endl;
            cout << "To play a single Song Press o" << endl;
            cout << "Press m to go to main menu" << endl;
            cout << "Press q to quit" << endl;
            char ch = getch();
            int loop_flag = 0;
            if (ch == 'i')
            {
                while (loop_flag != 2)
                {
                    for (auto x : p1.songs)
                    {
                        loop_flag = Controller::player(x, 1);
                        while (loop_flag == 1)
                        {
                            loop_flag = Controller::player(x, 1);
                        }
                        if (loop_flag == 2)
                        {
                            break;
                        }
                    }
                }
            }
            else if (ch == 'o')
            {
                cout << "Select a Song number" << endl;
                cin >> index;
                
                loop_flag = 1;
                while (loop_flag == 1)
                {
                    loop_flag = Controller::player(p1.songs[index], 0);
                }
            }
            else if (ch == 'm')
            {
                return;
            }
        }
    }

    static int player(Song s1, bool loop_playlist)
    {
        Suggestions su1;
        su1.add_suggestion_to_json(s1);
        system("cls");
        Interface_::display_interace();
        float volume;
        int loop = 0;
        // string soundFilePath = s1.getAddress();
        cout<<"lap 3"<<endl;
        // cout<<soundFilePath<<endl;
        sf::Music music;
        string temp = s1.getAddress();
        if (music.openFromFile(temp))
        {
            cerr << "File Loaded" << endl;
            
        }
        else
        {
            cerr << "Failed to load the sound file." << endl;
            sleep(20);
            exit(0);
        }
        
        cout << "To play a song press Spacebar" << endl;
        cout << "To stop a song press s" << endl;
        cout << "press l for loop on song" << endl;
        cout << "To pause the song press p" << endl;
        cout << "To go to Player Menu or break the playlist loop press c" << endl;
        cout << "press q to quit" << endl;
        cout << "Current Song: " << s1.getName() << endl;
        cout << "Music Started!" << endl;
        music.play();
        
        Interface_::gotox(102);
        Interface_::gotoy(18);
        cout << "Voloume: ";
        while (true)
        {
            sf::sleep(sf::milliseconds(150));
            sf::Time position = music.getPlayingOffset();
            sf::Time duration = music.getDuration();

            float progress = position.asSeconds() / duration.asSeconds();

            int barWidth = 50;
            int numAsterisks = static_cast<int>(progress * barWidth);

            // Print the music bar
            Interface_::gotox(28);
            Interface_::gotoy(20);

            cout << "Sound Bar "
                 << "[";
            for (int i = 0; i < barWidth; ++i)
            {
                if (i < numAsterisks)
                {

                    cout << "*";
                }
                else
                {
                    cout << " ";
                }
            }
            cout << "] " << progress * 100 << "%";
            cout.flush();

            if (music.getStatus() == sf::Music::Status::Stopped)
            {
                if (loop == false)
                {
                    return 0;
                }
                else if (loop == true)
                {
                    return 1;
                }
            }

            if (music.getStatus() == sf::Music::Status::Playing || music.getStatus() == sf::Music::Status::Paused || !loop_playlist)
            {
                // Check for keyboard input using SFML
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || ((music.getStatus() == sf::Music::Status::Stopped) && loop))
                {
                    music.play();
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
                {
                    music.pause();
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                {
                    music.stop();
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
                {
                    loop = !loop;
                    music.setLoop(loop);
                    (music.getLoop()) ? cout << "Currently Looped" << endl : cout << "Not Looped" << endl;
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
                {
                    return 2;
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
                {
                    exit(0);
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                {
                    volume = music.getVolume();
                    if (volume <= 100)
                    {
                        volume++;
                        music.setVolume(volume);
                    }
                    Interface_::gotox(110);
                    Interface_::gotoy(18);
                    cout << "     ";
                    Interface_::gotox(110);
                    Interface_::gotoy(18);
                    cout << volume;
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                {
                    volume = music.getVolume();
                    if (volume > 0)
                    {
                        volume--;
                        music.setVolume(volume);
                    }
                    Interface_::gotox(110);
                    Interface_::gotoy(18);
                    cout << "     ";
                    Interface_::gotox(110);
                    Interface_::gotoy(18);
                    cout << volume;
                }
            }
        }
    }
};
void Suggestions::call_controller(int index)
{
    Controller::player(suggestions[index].song,0);
}
int main()
{
    system("cls");
    Interface_::display_interace();
    Controller::Main_Menu();
    // Suggestions s1;
    // s1.add_suggestion_to_json(song1);
    return 0;
}
