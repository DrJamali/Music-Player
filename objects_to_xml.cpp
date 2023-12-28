#include <iostream>
#include <vector>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

class Song {
public:
    std::string title;
    std::string artist;

    void serialize(boost::property_tree::ptree& pt) const {
        pt.put("title", title);
        pt.put("artist", artist);
    }

    void deserialize(const boost::property_tree::ptree& pt) {
        title = pt.get<std::string>("title");
        artist = pt.get<std::string>("artist");
    }
};

class Playlist {
public:
    std::string name;
    std::vector<Song> songs;

    void serialize(boost::property_tree::ptree& pt) const {
        pt.put("name", name);

        boost::property_tree::ptree songsTree;
        for (const auto& song : songs) {
            boost::property_tree::ptree songTree;
            song.serialize(songTree);
            songsTree.push_back(std::make_pair("", songTree));
        }
        pt.add_child("songs", songsTree);
    }

    void deserialize(const boost::property_tree::ptree& pt) {
        name = pt.get<std::string>("name");

        songs.clear();
        const boost::property_tree::ptree& songsTree = pt.get_child("songs");
        for (const auto& songNode : songsTree) {
            Song song;
            song.deserialize(songNode.second);
            songs.push_back(song);
        }
    }
};

class User {
public:
    std::string username;
    std::vector<Playlist> playlists;

    void serialize(boost::property_tree::ptree& pt) const {
        pt.put("username", username);

        boost::property_tree::ptree playlistsTree;
        for (const auto& playlist : playlists) {
            boost::property_tree::ptree playlistTree;
            playlist.serialize(playlistTree);
            playlistsTree.push_back(std::make_pair("", playlistTree));
        }
        pt.add_child("playlists", playlistsTree);
    }

    void deserialize(const boost::property_tree::ptree& pt) {
        username = pt.get<std::string>("username");

        playlists.clear();
        const boost::property_tree::ptree& playlistsTree = pt.get_child("playlists");
        for (const auto& playlistNode : playlistsTree) {
            Playlist playlist;
            playlist.deserialize(playlistNode.second);
            playlists.push_back(playlist);
        }
    }
};

int main() {
    // Create a sample user with playlists and songs
    User user;
    user.username = "john_doe";

    Playlist playlist1;
    playlist1.name = "Favorites";

    Song song1;
    song1.title = "Song 1";
    song1.artist = "Artist 1";
    playlist1.songs.push_back(song1);

    Song song2;
    song2.title = "Song 2";
    song2.artist = "Artist 2";
    playlist1.songs.push_back(song2);

    user.playlists.push_back(playlist1);

    // Serialize the user object to a property tree
    boost::property_tree::ptree pt;
    user.serialize(pt);

    // Write the property tree to an XML file
    boost::property_tree::write_xml("user_data.xml", pt);

    std::cout << "User data saved to XML successfully." << std::endl;

    return 0;
}
