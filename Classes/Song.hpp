#include"Classes_header.hpp"
class Song
{
protected:
    std::string name;
    std::string address;

public:
    Song();
    Song(const std::string& name, const std::string& address);

    virtual void setName(const std::string& name);
    virtual void setAddress(const std::string& address);
    virtual std::string getName() const;
    virtual std::string getAddress() const;

    json to_json() const;
    static Song* from_json(const json& song_json);
};
