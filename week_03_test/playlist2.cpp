#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <thread>
#include <random>

using namespace std;

class Player
{
private:
    string currentSong;

public:
    void play(const string &song)
    {
        currentSong = song;
        cout << "Playing:" << currentSong << endl;
    }

    void stop()
    {
        cout << "Stoping:" << currentSong << endl;
        currentSong.clear();
    }

    string getCurrentSong()
    {
        if (!currentSong.empty())
        {
            return currentSong;
        }
        else
        {
            cout << "No song playing";
            return "";
        }
    }
};

class Playlist
{
    vector<string> songs;
    vector<string> originalOrder; // to store original order
    bool shuffle = false;         // to enable shuffle
    int currentIndex = 0;

public:
    // add songs
    void addSong(const string &song)
    {
        songs.push_back(song);
        originalOrder = songs;
    }

    // remove song
    void removeSong(const string &song)
    {
        auto it = find(songs.begin(), songs.end(), song);

        if (it != songs.end())
        {
            int index = distance(songs.begin(), it);
            songs.erase(it);
            // set the index after removal
            if (index <= currentIndex && currentIndex > 0)
            {
                --currentIndex;
            }
            cout << "Removed:" << song << endl;
        }
        else
        {
            cout << "Song not found" << endl;
        }
    }

    bool hasNext()
    {
        return currentIndex < songs.size();
    }

    // play next
    string playNext()
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

    // reset
    void reset()
    {
        currentIndex = 0;
        if (shuffle)
        {
            shuffleSongs();
        }
        else
        {
            songs = originalOrder;
        }
    }

    // shuffle
    void enableShuffle(bool enable)
    {
        shuffle = enable;
        if (shuffle)
        {
            shuffleSongs();
        }
        else
        {
            songs = originalOrder;
        }

        reset();
    }

    void shuffleSongs()
    {
        random_device rd;
        mt19937 g(rd());
        std::shuffle(songs.begin(), songs.end(), g);
    }

    void display()
    {
        cout << "Current playlist:" << endl;
        for (auto song : songs)
        {
            cout << song << " ";
        }
        cout << endl;
    }
};

int main()
{
    Playlist playlist;
    Player player;

    // add songs
    playlist.addSong("song A");
    playlist.addSong("song B");
    playlist.addSong("song C");
    playlist.addSong("song D");

    // display list
    playlist.display();
    cout << endl;

    // play next
    playlist.enableShuffle(true);
    cout << "After shuffle" << endl;
    playlist.display();

    while (playlist.hasNext())
    {

        string song = playlist.playNext();
        player.play(song);
        this_thread::sleep_for(chrono::seconds(2));
        //   cout << "currently:" << player.getCurrentSong() << endl;
        player.stop();
    }

    playlist.removeSong("song B");
    cout << "After remove" << endl;

    cout << endl;
    cout << endl;

    playlist.enableShuffle(false); // disable shuflling
    playlist.display();
    playlist.reset();

    while (playlist.hasNext())
    {

        string song = playlist.playNext();
        player.play(song);
        this_thread::sleep_for(chrono::seconds(3));
        // cout << "Current song:" << player.getCurrentSong() << endl;
        player.stop();
    }

    return 0;
}