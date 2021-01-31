#include <Keypad.h>

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
    char key = keypad.getKey();

    //input
    user = readUser();
    readPass(user, &passAttempt);

    //test
    pass[(int)user - 65] == passAttempt ? correct() : incorrect();
}

void incorrect()
{
    Serial.print("\nIncorrect password!\n");
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
    Serial.print("\nCorrect password, access granted!\n");
    for (int i = 0; i < 3; i++)
    {
        digitalWrite(LED_BUILTIN, HIGH);
        delay(1000);
        digitalWrite(LED_BUILTIN, LOW);
        delay(500);
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
        }
    } while (!(key >= 'A' && key <= 'D'));

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
        *attempt += key;
        Serial.print(key);
    }
}