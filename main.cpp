#include <iostream>
#include <fstream>
#include <string>
#include <thread>

using namespace std;

string logfile;
string trueLine;

void tunnelNgrok()
{
    // Run ngrok in the background and detach
    system("ngrok tcp 25565 --log=stdout > log.txt &");

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
