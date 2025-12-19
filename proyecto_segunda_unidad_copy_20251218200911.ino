#include <LiquidCrystal.h>
#include <DHT.h>

// --- PINES LCD ---
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

// --- PINES DHT ---
#define DHTPIN 8       
#define DHTTYPE DHT11    
DHT dht(DHTPIN, DHTTYPE); 

// --- PINES LED RGB (CC) ---
#define PIN_LED_R 9
#define PIN_LED_G 10
#define PIN_LED_B 11

// --- PINES BOTÓN ---
#define PIN_BOTON 12

// --- VARIABLES GLOBALES ---
float temp = 0;
float hum = 0;
float temp_max = -100; // Un valor muy bajo para empezar
float temp_min = 100;  // Un valor muy alto para empezar

bool modoActual = 0; // 0 = Actual, 1 = Max/Min

// --- Temporizadores (millis) ---
unsigned long tiempoAnteriorSensor = 0;
const long intervaloSensor = 2000; // 2 segundos

// --- CONFIGURACIÓN ---
void setup() {
  lcd.begin(16, 2);
  dht.begin();       
  
  pinMode(PIN_LED_R, OUTPUT);
  pinMode(PIN_LED_G, OUTPUT);
  pinMode(PIN_LED_B, OUTPUT);
  
  // Configura el botón con resistencia PULL-UP interna
  pinMode(PIN_BOTON, INPUT_PULLUP);
  
  lcd.print("Estacion v3.0");
  lcd.setCursor(0, 1);
  lcd.print("Iniciando...");
  delay(1500); 
}

// --- BUCLE PRINCIPAL ---
void loop() {
  unsigned long tiempoActual = millis();

  // ----- TAREA 1: LEER SENSORES (Cada 2 segundos) -----
  if (tiempoActual - tiempoAnteriorSensor >= intervaloSensor) {
    tiempoAnteriorSensor = tiempoActual;
    leerSensores();
    // Actualizamos el LCD solo si estamos en el modo 0
    if (modoActual == 0) {
      actualizarLCD_Actual();
    }
  }

  // ----- TAREA 2: LEER BOTÓN (Constante) -----
  leerBoton();

  // ----- TAREA 3: ACTUALIZAR LED (Constante) -----
  actualizarLED(temp); 
}

// --- FUNCIONES ---

void leerSensores() {
  float h = dht.readHumidity();
  float t = dht.readTemperature(); 

  if (!isnan(h) && !isnan(t)) {
    hum = h;
    temp = t;

    // Actualizamos los máximos y mínimos
    if (temp > temp_max) {
      temp_max = temp;
    }
    if (temp < temp_min) {
      temp_min = temp;
    }
  }
}

// Muestra la pantalla de Temperatura Actual
void actualizarLCD_Actual() {
  lcd.clear(); 
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temp); 
  lcd.print(" C");
  lcd.setCursor(0, 1);
  lcd.print("Hum:  ");
  lcd.print(hum); 
  lcd.print(" %");
}

// Muestra la pantalla de Max / Min
void actualizarLCD_MaxMin() {
  lcd.clear(); 
  lcd.setCursor(0, 0);
  lcd.print("Max: ");
  lcd.print(temp_max); 
  lcd.print(" C");
  lcd.setCursor(0, 1);
  lcd.print("Min: ");
  lcd.print(temp_min); 
  lcd.print(" C");
}

void leerBoton() {
  // Si el botón se presiona (LOW porque es PULLUP)
  if (digitalRead(PIN_BOTON) == LOW) {
    // Cambiamos el modo
    modoActual = !modoActual; // Invierte el modo (0 a 1, 1 a 0)
    
    // Mostramos la pantalla correcta
    if (modoActual == 0) {
      actualizarLCD_Actual();
    } else {
      actualizarLCD_MaxMin();
    }
    
    // Un delay anti-rebote para que no cambie 100 veces
    delay(400); 
  }
}

void actualizarLED(float temperatura) {
  // Cátodo Común: HIGH = ENCENDIDO
  if (temperatura < 20) {
    digitalWrite(PIN_LED_R, LOW); digitalWrite(PIN_LED_G, LOW); digitalWrite(PIN_LED_B, HIGH); // Azul
  } else if (temperatura >= 20 && temperatura < 27) {
    digitalWrite(PIN_LED_R, LOW); digitalWrite(PIN_LED_G, HIGH); digitalWrite(PIN_LED_B, LOW); // Verde
  } else { 
    digitalWrite(PIN_LED_R, HIGH); digitalWrite(PIN_LED_G, LOW); digitalWrite(PIN_LED_B, LOW); // Rojo
  }
}