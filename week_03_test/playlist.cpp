#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>

using namespace std;

class Player
{
private:
    string currentSong;

public:
    // play song
    void play(const string &song)
    {
        currentSong = song;
        cout << "Playing:" << currentSong << "\n";
    }

    // stop song
    void stop()
    {
        cout << "Stoping:" << currentSong << endl;
        currentSong.clear(); // clear() is in std::string , it will assign empty string to currentSong ""
    }
};

class Playlist
{
    vector<string> songs;
    int currentIndex = 0;

public:
    // add song
    void addSong(const string &song)
    {
        songs.push_back(song);
    }

    // remove song
    void removeSong(const string &song)
    {
        auto it = find(songs.begin(), songs.end(), song);
        if (it != songs.end())
        {
            int index = distance(songs.begin(), it);
            songs.erase(it);

            // set the current index
            if (index <= currentIndex && currentIndex > 0)
            {
                --currentIndex;
            }

            cout << "removed song:" << song << endl;
        }
        else
        {
            cout << "Song not found" << endl;
        }
    }

    // get curent song
    string getNextSong()
    {
        if (currentIndex < songs.size())
        {
            return songs[currentIndex++];
        }
        else
        {
            cout << "End of playlist" << endl;
            return "";
        }
    }

    bool hasNext()
    {
        return currentIndex < songs.size();
    }

    // reset playlist after removal
    void reset()
    {
        currentIndex = 0;
    }

    void displaySongs()
    {
        cout << "Current playlist" << endl;
        for (auto song : songs)
        {
            cout << song << endl;
        }
    }
};

int main()
{
    Playlist playlist; // create playlist
    Player player;     // create player

    playlist.addSong("song A");
    playlist.addSong("song B");
    playlist.addSong("song c");

    playlist.displaySongs();

    // play songs
    while (playlist.hasNext())
    {
        string currentSong = playlist.getNextSong();
        player.play(currentSong);
        player.stop();
    }

    // remove song B
    playlist.removeSong("song B");
    playlist.displaySongs();
    playlist.reset();

   
    while (playlist.hasNext())
    {
       
        string currentSong = playlist.getNextSong();
        player.play(currentSong);
        player.stop();
    }

    return 0;
}