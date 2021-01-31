/*
# INSTRUCTIONS
Keypad 4x4:
- Connect rows with pins 9-6
- Connect cols with pins 5-2

Passive buzzer:
- Connect postive with pin 11
- Connect negative with the ground GND
*/

#include <Keypad.h>
#include <pitches.h>

//Define passive buzzer and tones
#define BUZPIN 11
#define KEYDUR 100
#define TONECOR NOTE_B4
#define TONEINCOR NOTE_B2

//Define keys on keypad and init
#define ROWS 4
#define COLS 4

char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};
byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

//Password per user
String pass[4] = {"1234", "AC12", "432A", "65CD"};
String passAttempt = "";

char user;

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
    Serial.begin(9600);

    int count = 0;
}

void loop()
{
    //input
    user = readUser();
    readPass(user, &passAttempt);

    //test
    pass[(int)user - 65] == passAttempt ? correct() : incorrect();
}

void incorrect()
{
    delay(KEYDUR*2);
    Serial.print("\nIncorrect password!\n");
    tone(BUZPIN, TONEINCOR, 700);
    for (int i = 0; i < 10; i++)
    {
        digitalWrite(LED_BUILTIN, HIGH);
        delay(100);
        digitalWrite(LED_BUILTIN, LOW);
        delay(100);
    }
}

void correct()
{
    delay(KEYDUR*2);
    Serial.print("\nCorrect password, access granted!\n");

    for (int i = 0; i < 3; i++)
    {
        digitalWrite(LED_BUILTIN, HIGH);
        tone(BUZPIN, TONECOR, 300);
        delay(300);
        digitalWrite(LED_BUILTIN, LOW);
        delay(100);
    }
}

char readUser()
{
    char key;

    do
    {
        Serial.print("Pick a user (A, B, C or D): ");
        key = keypad.waitForKey();
        Serial.print(key);

        if (!(key >= 'A' && key <= 'D'))
        {
            Serial.print("\nNot a user! Try again.\n");
            tone(BUZPIN, TONEINCOR, KEYDUR*2);
        }
    } while (!(key >= 'A' && key <= 'D'));

    tone(BUZPIN, TONECOR, KEYDUR);

    return key;
}

void readPass(char User, String *attempt)
{
    char key;
    *attempt = "";

    Serial.print("\nEnter password for user ");
    Serial.print(User);
    Serial.print(": ");

    while (attempt->length() != pass[(int)User - 65].length())
    {
        key = keypad.waitForKey();
        toneKeypad(key);
        *attempt += key;
        Serial.print(key);
    }
}

void toneKeypad(char ch)
{
    //Long switch, could be better with array and such bla bla
    switch (ch)
    {
        case '1':
        tone(BUZPIN, 953, KEYDUR);
        break;
        case '2':
        tone(BUZPIN, 1016, KEYDUR);
        break;
        case '3':
        tone(BUZPIN, 1087, KEYDUR);
        break;
        case '4':
        tone(BUZPIN, 990, KEYDUR);
        break;
        case '5':
        tone(BUZPIN, 1053, KEYDUR);
        break;
        case '6':
        tone(BUZPIN, 1124, KEYDUR);
        break;
        case '7':
        tone(BUZPIN, 1031, KEYDUR);
        break;
        case '8':
        tone(BUZPIN, 1094, KEYDUR);
        break;
        case '9':
        tone(BUZPIN, 1165, KEYDUR);
        break;
        case '0':
        tone(BUZPIN, 1139, KEYDUR);
        break;
        case 'A':
        tone(BUZPIN, 1165, KEYDUR);
        break;
        case 'B':
        tone(BUZPIN, 1202, KEYDUR);
        break;
        case 'C':
        tone(BUZPIN, 1243, KEYDUR);
        break;
        case 'D':
        tone(BUZPIN, 1633, KEYDUR);
        break;
        case '*':
        tone(BUZPIN, 1075, KEYDUR);
        break;
        case '#':
        tone(BUZPIN, 1209, KEYDUR);
        break;
    }
}