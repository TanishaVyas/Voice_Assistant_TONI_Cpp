#include <iostream>
#include <windows.h>
#include <mmsystem.h>
#include <ctime>
#include <fstream>
#include <cstdio>
#include <cstring>

using namespace std;

// Base class for voice functionality
class Voice
{
public:
    virtual void speak(string s) = 0;
};

// Text-to-speech implementation of Voice
class TextToSpeech : public Voice
{
public:
    void speak(string s) override
    {
        // Write the text to a VBScript file and use SAPI for speech synthesis
        ofstream file;
        file.open("speak.vbs", ios::out);
        file << "dim s";
        file << "\nset s = createObject(\"sapi.spvoice\")";
        file << "\ns.speak \"" << s << "\"";
        file.close();
        // Execute the VBScript to play the speech
        system("start speak.vbs");
        Sleep(300);
    }
};

// Base class for the assistant
class Assistant
{
public:
    Voice *voice;

    Assistant(Voice *v) : voice(v) {}

    // Overloaded typing function to display and speak messages
    void typing(string t)
    {
        voice->speak(t);
        cout << "\n\n";
        for (int i = 0; i < t.length(); i++)
        {
            cout << t[i];
            Sleep(65);
        }
    }

    void typing(const char *t)
    {
        typing(string(t));
    }
};

// Assistant specialized for greeting
class GreetingAssistant : public Assistant
{
public:
    GreetingAssistant(Voice *v) : Assistant(v) {}

    // Greet the user based on the time of day
    void greet()
    {
        time_t now = time(0);
        tm *time = localtime(&now);

        if (time->tm_hour < 12)
        {
            typing("Good Morning");
        }
        else if (time->tm_hour >= 12 && time->tm_hour <= 16)
        {
            typing("Good Afternoon");
        }
        else if (time->tm_hour > 16 && time->tm_hour < 24)
        {
            typing("Good Evening");
        }
    }
};

// Assistant for processing user commands
class CommandAssistant : public Assistant
{
public:
    CommandAssistant(Voice *v) : Assistant(v) {}

    void openGoogle()
    {
        string s = "https://www.google.co.in/";
        typing("Opening Google in the Chrome browser");
        cout << "\n\n";
        ShellExecute(NULL, "open", s.c_str(), NULL, NULL, SW_SHOWNORMAL);
    }

    void searchGoogle()
    {
        char text[100];
        string res;
        string g = "https://www.google.com/search?q=";
        typing("Enter what do you want to search: ");

        if (fgets(text, sizeof(text), stdin) != NULL)
        {
            text[strcspn(text, "\n")] = '\0';
            res = g + text;
            typing("Searching in Google");
            cout << "\n\n";
            ShellExecute(NULL, "open", res.c_str(), NULL, NULL, SW_SHOWNORMAL);
        }
    }

    void whoAreYou()
    {
        typing("Hi!, I'm Toni, which stands for 'Totally Overrated Noise Initiator.' My capabilities include executing straightforward tasks like conducting searches across various platforms and engaging in basic conversations.");
        cout << "\n\n";
    }

    void changeVoice()
    {
        typing("I'm sorry, but your request goes against my programming to maintain a respectful and helpful tone. If you have any other requests or need assistance with something, please feel free to ask, and I'll be happy to help");
        cout << "\n\n";
    }

    void openYoutube()
    {
        string n = "https://www.youtube.com/";

        typing("Opening YouTube in the Chrome browser");
        cout << "\n\n";

        ShellExecute(NULL, "open", n.c_str(), NULL, NULL, SW_SHOWNORMAL);
    }

    void searchYoutube()
    {
        char text1[100];

        typing("Enter what do you want to search: ");
        if (fgets(text1, sizeof(text1), stdin) != NULL)
        {
            text1[strcspn(text1, "\n")] = '\0';

            string s;
            string res1 = "https://www.youtube.com/results?search_query=";
            s = res1 + text1;

            typing("Searching on YouTube");
            cout << "\n\n";
            ShellExecute(NULL, "open", s.c_str(), NULL, NULL, SW_SHOWNORMAL);
        }
    }

    void bye()
    {
        system("cls");
        typing("Have a nice day");
        exit(0);
    }

    void howAreYou()
    {
        typing("I am good!, How are you!");
        cout << "\n\n";
    }

    void hello()
    {
        typing("What can I do for you?");
        cout << "\n\n";
    }

    void timeOrDate()
    {
        typing("The time and date is on top of the application");
        cout << "\n\n";
    }

    void processCommands()
    {
        char ch[100];
        while (1)
        {
            cout << "==>  ";
            if (fgets(ch, sizeof(ch), stdin) != NULL)
            {
                ch[strcspn(ch, "\n")] = '\0';

                if (strcmp(ch, "open google") == 0)
                {
                    openGoogle();
                }
                else if (strcmp(ch, "search google") == 0)
                {
                    searchGoogle();
                }
                else if (strcmp(ch, "who are you?") == 0)
                {
                    whoAreYou();
                }
                else if (strcmp(ch, "change voice") == 0)
                {
                    changeVoice();
                }
                else if (strcmp(ch, "open youtube") == 0)
                {
                    openYoutube();
                }
                else if (strcmp(ch, "search youtube") == 0)
                {
                    searchYoutube();
                }
                else if (strcmp(ch, "bye") == 0 || strcmp(ch, "stop") == 0 || strcmp(ch, "exit") == 0)
                {
                    bye();
                }
                else if (strcmp(ch, "how are you") == 0)
                {
                    howAreYou();
                }
                else if (strcmp(ch, "hi") == 0 || strcmp(ch, "hello") == 0)
                {
                    hello();
                }
                else if (strcmp(ch, "time") == 0 || strcmp(ch, "date") == 0)
                {
                    timeOrDate();
                }
                else
                {
                    typing("Pardon, Invalid command");
                    cout << "\n\n";
                }
            }
        }
    }
};

int main()
{
    TextToSpeech tts;
    GreetingAssistant greetingAssistant(&tts);
    CommandAssistant commandAssistant(&tts);

    greetingAssistant.greet();

    cout << "\n\n******************************** TONI *************************************** \n\n";
    time_t now = time(0);
    char *dt = ctime(&now);
    cout << "\n\nThe date and time is " << dt << endl;
    cout << "********************************************************************************************\n\n";

    commandAssistant.processCommands();

    return 0;
}
