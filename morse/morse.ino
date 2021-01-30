#define UNIT 200

#define SHORT UNIT
#define LONG (UNIT*3)
#define WAIT UNIT
#define PAUSE (UNIT*7)

const String morse[] = { ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..",".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."};

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);
}

void loop() {
    String sentence = "SOS";
    sentence.toUpperCase();

    Serial.print("Morse: ");
    for (int i = 0; i < sentence.length(); i++)
    {
        charToMorse(sentence[i]);
    }
    Serial.print("\n");
    delay(PAUSE);

}

void blinkL(int time) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(time);
    digitalWrite(LED_BUILTIN, LOW);
    delay(WAIT);
}

void charToMorse(char ch)
{
    //assumes uppercase input
    int index = ch - 65;
    if (index >=0 && index <= 25)
    {
        String morseCode = morse[index];

        for(int i = 0; i < morseCode.length(); i++)
        {    
            if(morseCode[i] == '.')
            {
                blinkL(SHORT);
                Serial.print(".");
            }
            if(morseCode[i] == '-')
            {
                blinkL(LONG);
                Serial.print("-");
            }
        }
    }
    else //Something not in the alpabet AKA space
    {
        delay(PAUSE);
        Serial.print(" | ");
    }
    Serial.print(" ");
}