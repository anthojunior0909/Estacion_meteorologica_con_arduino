# 🌡️ Estación de Temperatura y Humedad con Arduino (v3.0)

Este proyecto implementa una **estación básica de monitoreo ambiental** utilizando Arduino, un sensor **DHT11**, una **pantalla LCD 16x2**, un **LED RGB** y un **botón** para cambiar el modo de visualización.

El sistema mide la **temperatura y humedad en tiempo real**, muestra la información en la pantalla LCD y utiliza un LED RGB para indicar el rango de temperatura mediante colores.

---

## 🔧 Características

- 📟 Pantalla LCD 16x2
  - Temperatura y humedad actuales
  - Temperatura máxima y mínima registradas
- 🌡️ Sensor DHT11
- 🔴🟢🔵 LED RGB (cátodo común) para indicar el estado de la temperatura
- 🔘 Botón para cambiar entre modos de visualización
- ⏱️ Lectura del sensor cada 2 segundos usando `millis()`
- 💾 Registro automático de temperaturas máximas y mínimas

---

## 🎨 Indicador LED RGB

| Temperatura | Color LED |
|------------|-----------|
| < 20 °C    | Azul 🔵   |
| 20 – 26 °C | Verde 🟢  |
| ≥ 27 °C    | Rojo 🔴   |

---

## 🧩 Componentes necesarios

- Arduino Uno / Nano / compatible
- Sensor DHT11
- Pantalla LCD 16x2
- LED RGB (cátodo común)
- Botón pulsador
- Resistencias
- Protoboard y cables

---

## 🔌 Conexiones

### LCD 16x2
- RS → Pin 7  
- E  → Pin 6  
- D4 → Pin 5  
- D5 → Pin 4  
- D6 → Pin 3  
- D7 → Pin 2  

### Sensor DHT11
- DATA → Pin 8  

### LED RGB (Cátodo común)
- Rojo → Pin 9  
- Verde → Pin 10  
- Azul → Pin 11  

### Botón
- Señal → Pin 12  
- Configurado con `INPUT_PULLUP`

---

## ⚙️ Funcionamiento

1. Al iniciar, se muestra un mensaje de bienvenida en la pantalla LCD.
2. Cada 2 segundos se leen los valores del sensor DHT11.
3. El LED RGB cambia de color según la temperatura medida.
4. Al presionar el botón:
   - Se alterna entre el modo **Actual** y **Máx/Mín**.
5. Las temperaturas máximas y mínimas se actualizan automáticamente.

---

## 📚 Librerías utilizadas

- `LiquidCrystal`
- `DHT`

Instalar desde el **Library Manager** del IDE de Arduino.

---

## 🚀 Versión

**v3.0**  
- Uso de `millis()` para temporización no bloqueante  
- Control de modos mediante botón  
- Visualización clara y optimizada  

---

## 📄 Licencia

Este proyecto es de uso educativo y libre para modificar y mejorar.
