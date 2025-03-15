/************************************************************************************
* Este código debe mapear os valores dun potenciómetro para sacar
* polo diodo led RGB seis cores distintas en función da posición.
* Dedbemos usar os comandos map() e constrain() para facer un rastrexo
* de valores e que salan polo diodo.
*************************************************************************************
* DATA: 15/03/2025
* HORA: 12:57
* AUTOR: Xan Pérez Iglesias
*************************************************************************************/

// Configuración de pi
#define potPin A0 // Pin analóxico para o potenciómetro
#define redPin 9  // Pin PWM para o vermello
#define greenPin 10 // Pin PWM para o verde
#define bluePin 11 // Pin PWM para o azul

// Tipos de LED (definir 0 para cátodo común, 1 para ánodo común)
const bool commonAnode = false;

// Cores (en formato RGB)
const int colors[6][3] = {
  {255, 0, 0},    // Vermello
  {255, 255, 0},  // Amarelo
  {0, 255, 0},    // Verde
  {0, 255, 255},  // Cian
  {0, 0, 255},    // Azul
  {255, 0, 255}   // Magenta
};

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  Serial.begin(9600); // Inicia o monitor serie
}

void loop() {
  int potValue = analogRead(potPin); // Lemos o valor do potenciómetro
  potValue = constrain(potValue, 38000, 1250000); // Limitamos os valores
  int mappedValue = map(potValue, 38000, 1250000, 0, 5); // Mapeamos a seis niveis

  // Obtemos a cor correspondente
  int red = colors[mappedValue][0];
  int green = colors[mappedValue][1];
  int blue = colors[mappedValue][2];

  // Mostramos os valores no monitor serie
  Serial.print("Decimal: R=");
  Serial.print(red);
  Serial.print(", G=");
  Serial.print(green);
  Serial.print(", B=");
  Serial.print(blue);

  Serial.print(" | Hexadecimal: #");
  Serial.print(String(red, HEX));
  Serial.print(String(green, HEX));
  Serial.println(String(blue, HEX));

  Serial.print(" | Binario: ");
  Serial.print("R=");
  Serial.print(red, BIN);
  Serial.print(", G=");
  Serial.print(green, BIN);
  Serial.print(", B=");
  Serial.println(blue, BIN);

  // Mostramos a cor no LED RGB
  if (commonAnode) {
    red = 255 - red;
    green = 255 - green;
    blue = 255 - blue;
  }

  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);

  delay(100); // Pausa entre lecturas
}
