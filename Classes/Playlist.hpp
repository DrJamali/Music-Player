#ifndef PLAYLIST_HPP
#define PLAYLIST_HPP
#include"..\Libraries\Libraries.hpp"
#include "Song.hpp"

using namespace std;
using json = nlohmann::json;
class Playlist
{
    string name;
    vector<Song> songs;

public:
    Playlist() = default;
    Playlist(string playlist_name)
    {
    }
    string get_playlist_name()
    {
    }
    void add_songs_to_playlist(Song *song)
    {
    }
    void display_songs()
    {
    }
    Song *return_song_obj(int index)
    {
    }

    json to_json() const
    {
    }
    static Playlist from_json(const json &playlist_json)
    {
    }
};
#endif
