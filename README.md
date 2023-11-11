# Voice_Assistant_TONI_Cpp

Problem Statement:

The objective of this code is to create a simple text-based virtual assistant that can interact
with the user through a command-line interface in order to provide them with a simple way
to interact with it. This virtual assistant can perform various tasks based on user input,
including opening web pages, searching the internet, greeting the user, and responding to
specific commands.

Explanation:

It is the aim of the project to develop a basic virtual assistant that can assist the user with a
limited set of tasks through text-based interaction with the assistant. There are various tasks
that the virtual assistant can perform, including answering specific textual commands,
providing greetings, opening websites, and performing basic web searches for the user.

Key Components:

● Voice and Text-to-Speech:
    
○ This project includes a voice component for converting text into speech. To enable the assistant to speak aloud, it uses a simple 		Text-to-Speech (TTS) approach.

○ The Voice class serves as the base class, and TextToSpeech is an implementation of voice functionality. It generates a VBScript             file (speak.vbs) and uses SAPI (Speech Application Programming Interface) to produce speech.
        
● Assistant Classes:There are two main assistant classes:

○ GreetingAssistant: This assistant is specialized for providing greetings based
on the time of day.

○ CommandAssistant: This assistant is responsible for processing user
commands entered via text input.

● User Interaction:

○ User input is collected using the gets function, which reads text input from
the command line.

○ The assistant interacts with the user by both speaking the responses using
TTS and displaying text on the console.

● Functionality:TONI can perform various tasks like

○ opening browsers

○ opening application

○ conducting web searches on Google and Youtube

○ Informing date and time

○ Basic chat like “who are you” and “how are you”
