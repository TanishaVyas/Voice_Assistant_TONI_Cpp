#include <iostream>
#include <windows.h>
#include <mmsystem.h>
#include <stdio.h>
#include <ctime>
#include <fstream>
#include <cstdio>

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
        for (int i = 0; t[i] != '\0'; i++)
        {
            cout << t[i];
            Sleep(65);
        }
    }

    void typing(const char *t)
    {
        typing(string(t));
    }

    void typing(int t)
    {
        typing(to_string(t));
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

    // Process user commands from the command line
    void processCommands()
    {
        char ch[100];
        while (1)
        {
            gets(ch);

            if (strcmp(ch, "open google") == 0)
            {
                string s = "https://www.google.co.in/";
                typing("opening google in chrome browser");
                cout << "\n\n";
                ShellExecute(NULL, "open", s.c_str(), NULL, NULL, SW_SHOWNORMAL);
            }
            else if (strcmp(ch, "search google") == 0)
            {
                char text[100];
                string res;
                string g = "https://www.google.com/search?q=";
                typing("Enter what do you want to search : ");
                gets(text);
                res = g + text;
                typing("searching in google");
                cout << "\n\n";
                ShellExecute(NULL, "open", res.c_str(), NULL, NULL, SW_SHOWNORMAL);
            }
            else if (strcmp(ch, "who are you?") == 0)
            {
                typing("Hi!,I'm Toni, which stands for 'Totally Overrated Noise Initiator.' My capabilities include executing straightforward tasks like conducting searches across various platforms and engaging in basic conversations.");
                cout << "\n\n";
            }

            else if (strcmp(ch, "change voice") == 0)
            {
                typing("I'm sorry, but your request goes against my programming to maintain a respectful and helpful tone. If you have any other requests or need assistance with something, please feel free to ask, and I'll be happy to help");
                cout << "\n\n";
            }

            else if (strcmp(ch, "open youtube") == 0)

            {
                string n = "https://www.youtube.com/";

                typing("Opening youtube in chrome browser");
                cout << "\n\n";

                ShellExecute(NULL, "open", n.c_str(), NULL, NULL, SW_SHOWNORMAL);
            }

            else if (strcmp(ch, "search youtube") == 0)
            {
                char text1[100];

                typing("Enter what do you want to search : ");
                gets(text1);

                string s;
                string res1 = "https://www.youtube.com/results?search_query=";

                s = res1 + text1;

                typing("searching on youtube");
                cout << "\n\n";

                ShellExecute(NULL, "open", s.c_str(), NULL, NULL, SW_SHOWNORMAL);
            }

            else if (strcmp(ch, "bye") == 0 || strcmp(ch, "stop") == 0 || strcmp(ch, "exit") == 0)
            {
                system("cls");
                typing("Have a nice day");
                exit(0);
            }

            else if (strcmp(ch, "how are you") == 0)
            {

                typing("I am good!, How are you!");
                cout << "\n\n";
            }

            else if (strcmp(ch, "hi") == 0 || strcmp(ch, "hello") == 0)
            {

                typing("what I can do for you ");
                cout << "\n\n";
            }

            else if (strcmp(ch, "time") == 0 || strcmp(ch, "date") == 0)
            {
                typing("the time and date is on top of the application");
                cout << "\n\n";
            }

            else
            {

                typing("Pardon, Invalid command");
                cout << "\n\n";
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

    cout << "\n\n******************************** Your Assistant *************************************** \n\n";
    time_t now = time(0);
    char *dt = ctime(&now);
    cout << "\n\nThe date and time is " << dt << endl;
    cout << "********************************************************************************************\n\n==>  ";

    commandAssistant.processCommands();

    return 0;
}
