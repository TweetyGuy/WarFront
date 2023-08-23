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
        cout << "No IP found. Retrying. . ." << endl;
        sleep_for(seconds(2));
        search();
    }

    myStream.close();
}

void console()
{
    cout << "Would you like to open the server console? Y for yes, N for no.\n";
    char response;
    cin >> response;
    switch (response)
    {
    case 'Y':
        system("java @user_jvm_args.txt @libraries / net / minecraftforge / forge / 1.20 - 46.0.14 / unix_args.txt nogui \"$@\" &");
        break;
    case 'y':
        system("java @user_jvm_args.txt @libraries / net / minecraftforge / forge / 1.20 - 46.0.14 / unix_args.txt nogui \"$@\" &");
        break;
    case 'N':
        system("java @user_jvm_args.txt @libraries / net / minecraftforge / forge / 1.20 - 46.0.14 / unix_args.txt nogui \"$@\"");
        break;
    case 'n':
        system("java @user_jvm_args.txt @libraries / net / minecraftforge / forge / 1.20 - 46.0.14 / unix_args.txt nogui \"$@\"");
        break;
    default:
        std::cout << "Invalid response. Please enter either, \"y,\" or, \"n.\"";
        console();
        break;
    }
}

void mcserver()
{
    cout << "Starting the forge 1.20 minecraft server.\n";
    
    // console();
    
    cout << "Server";
}

int main()
{
    // Step 1, start the ngrok tunnel.
    tunnelNgrok();
    // Step 2, search for the ip of the ngrok tunnel.
    search();
    // Step 3, start the minecraft server.
    // mcserver();
    // Step 4, start the web-server.


    return 0;
}
