#define UNIT 200

#define SHORT UNIT
#define LONG (UNIT*3)
#define WAIT UNIT
#define PAUSE (UNIT*7)
                        //A     B       C       D      E    F       G       H       I   J       K       L      M    N       O       P      Q        R   S       T   U       V       W       X       Y       Z
const String morse[] = { ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..",".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..",
//  0           1       2       3       4           5       6       7       8           9
    "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----."};

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
    Serial.begin(9600);
}

void loop() {
    String sentence;

    Serial.print("Enter a sentence to do in morse (chars and ints): ");
    while (Serial.available() == 0) {
        // Waiting for user input
    }

    sentence = Serial.readString();
    sentence.toUpperCase();
    Serial.print(sentence);
    sentence.trim();

    Serial.print("Morse: ");
    for (int i = 0; i < sentence.length(); i++)
    {
        charToMorse(sentence[i]);
    }
    Serial.print("\n");
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
    int index = -1;
    
    if(ch >= 'A' && ch <= 'Z')
    {
        index = ch - 65;
    }
    if(ch >= '0' && ch <= '9')
    {
        index = ch - 22;
    }

    if (index >=0 && index <= 35)
    {
        String morseCode = morse[index];

        for(int i = 0; i < morseCode.length(); i++)
        {    
            if(morseCode[i] == '.')
            {
                Serial.print(".");
                blinkL(SHORT);
            }
            if(morseCode[i] == '-')
            {
                Serial.print("-");
                blinkL(LONG);
            }
        }
    }
    else // Not letter or num -> space
    {
        Serial.print(" | ");
        delay(PAUSE);
    }
    Serial.print(" ");
}