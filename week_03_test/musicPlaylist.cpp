#include <iostream>
#include <list>
#include <algorithm>
#include <thread>
#include <vector>
#include <random>

using namespace std;

class Playlist
{
private:
    list<string> songs;
    list<string> originalOrder;
    bool shuffleMode;
    list<string>::iterator currentSong;

public:
    Playlist() : currentSong(songs.end()) {} // assign the item
    // add song
    /**
 * @brief Adds a song to the playlist.
 * 
 * This function appends a song title to the end of the playlist. 
 * If the playlist was previously empty, it also sets the current song to the first song 
 * in the list. Additionally, it updates the original order of the songs.
 * 
 * @param songTitle The title of the song to be added to the playlist.
 */
    void addSong(const string &songTitle)
    {
        songs.push_back(songTitle);
        originalOrder = songs;
        if (currentSong == songs.end())
        {
            currentSong = songs.begin(); // go to first element
        }
    }


    // remove song with title
    void removeSong(const string &songTitle)
    {
        cout << "remove()";
        if (songs.empty())
        {
            cout << "playlist is empty:" << endl;
            return;
        }
        auto it = find(songs.begin(), songs.end(), songTitle);
        if (it == songs.end()) // If song not found
        {
            cout << "Song not found in playlist." << endl;
            return;
        }
        // Move `currentSong` to the next song, or reset to begin if at the end
        if (it == currentSong)
        {
            currentSong = (next(currentSong) != songs.end()) ? next(currentSong) : songs.begin();
        }

        songs.erase(it);
        cout << "Removed:" << *it << endl;
        // Check if playlist is empty after deletion
        if (songs.empty())
        {
            currentSong = songs.end();
        }
    }

    void playCurrent()
    {
        if (currentSong == songs.end())
        {
            cout << "playlist is empty." << endl;
            return;
        }
        cout << "currently playing:" << *currentSong << endl;
    }

    void playNext()
    {

        if (songs.empty())
        {
            cout << "playlist is empty." << endl;
            return;
        }
        ++currentSong;
        //  looping
        if (currentSong == songs.end())
        {
            currentSong = songs.begin();
        }

        cout << "Playing Next:" << *currentSong << endl;
    }

    void playPrevious()
    {

        if (songs.empty())
        {
            cout << "playlist is empty." << endl;
            return;
        }

        // looping
        if (currentSong == songs.begin())
        {
            currentSong = songs.end();
        }
        --currentSong;
        cout << "Playing Previous:" << *currentSong << endl;
    }
    
    // reset to begin after shuffling
    void reset()
    {
        if (shuffleMode)
        {
            shufflePlaylist();
        }
        else
        {
            songs = originalOrder;
        }

        currentSong = songs.begin();
    }

    // enable or disable shuffle
    void enableShuffle(bool shuffle)
    {
        shuffleMode = shuffle;
        if (shuffleMode)
        {
            shufflePlaylist();
        }
        else
        {
            songs = originalOrder;
        }
        reset();
    }

    // shuffle using a temp vector so that we can use shuffle method of stl which works only on vectors then assign back to list
    void shufflePlaylist()
    {
        vector<string> temp(songs.begin(), songs.end()); // temp vector
        random_device rd;                                // Seed generator
        mt19937 g(rd());                                 // keep random value for larger raange so that it numbers do not repeat too early
        shuffle(temp.begin(), temp.end(), g);            // shuffle temp vector and then assign to original list that is songs
        songs.assign(temp.begin(), temp.end());
        currentSong = songs.begin(); // set the currentSong iterator to beginging of shuffled songes
    }

    void displayPlaylist() const
    {
        cout << "display() ";
        if (songs.empty())
        {
            cout << "playist is empty:" << endl;
            return;
        }
        cout << "Current playlist" << endl;
        for (const auto &song : songs)
        {
            cout << "-" << song;
        }
        cout << "\n";
    }
};

int main()
{

    Playlist playlist;
    playlist.addSong("Song A");
    playlist.addSong("Song B");
    playlist.addSong("Song C");
    playlist.addSong("Song D");

    playlist.displayPlaylist();
    cout << "\n";

    playlist.playNext();
    this_thread::sleep_for(chrono::seconds(3));
    playlist.playPrevious();
    cout << "\n";

    playlist.removeSong("Song B");
    playlist.displayPlaylist();
    cout << "\n";

    this_thread::sleep_for(chrono::seconds(3));
    playlist.playCurrent();
    this_thread::sleep_for(chrono::seconds(3));
    playlist.playNext();
    this_thread::sleep_for(chrono::seconds(3));
    // shuffling
    playlist.enableShuffle(true);
    cout << "After shuffle:" << endl;
    this_thread::sleep_for(chrono::seconds(3));
    playlist.displayPlaylist();
    // reset
    playlist.reset();

    // play current
    playlist.playCurrent();
    this_thread::sleep_for(chrono::seconds(3));
    playlist.playNext();

    this_thread::sleep_for(chrono::seconds(3));
    cout << "Original order:" << endl;
    playlist.enableShuffle(false);
    playlist.displayPlaylist();

    return 0;
}