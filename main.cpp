#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>

using namespace std;
using namespace std::this_thread;
using namespace std::chrono;

string logfile;
string trueLine;

void tunnelNgrok()
{

    // Run ngrok in the background and detach
    std::cout << "Creating ngrok session. . .\n";
    system("ngrok tcp 25565 --log=stdout > log.txt &");
    std::cout << "Created ngrok session.\n";
}

void search()
{
    ifstream myStream("log.txt");

    while (getline(myStream, logfile))
    {
        // Process the line here
        if (logfile.find("url=") != string::npos)
        {
            cout << "Found URL line: " << logfile << endl;
            trueLine = logfile;
        }
    }

    size_t urlPosition = trueLine.find("url=");
    if (urlPosition != string::npos)
    {
        string ip = trueLine.substr(urlPosition + 10);
        cout << "Extracted IP: " << ip << endl;
    }
    else
    {
        cout << "No IP found." << endl;
        sleep_for(seconds(2));
        search();
    }

    myStream.close();
}

int main()
{
    // Launch tunnelNgrok in a separate thread
    tunnelNgrok();
    search();


    return 0;
}
