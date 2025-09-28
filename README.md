# 🥚 Incubadora de Huevos con Arduino

[![Arduino](https://img.shields.io/badge/Arduino-IDE-00979D.svg?logo=arduino)](https://www.arduino.cc/)
[![Software Libre](https://img.shields.io/badge/Software-Libre-green.svg)](https://www.gnu.org/philosophy/free-sw.html)

Sistema de incubadora automática para huevos controlada por **Arduino Uno** que monitorea y mantiene temperatura y humedad óptimas para la incubación.

> 🐣 **Proyecto probado exitosamente con huevos de pollo durante la pandemia de COVID-19**

*Nota: Pronto estaremos subiendo videos del funcionamiento y diagramas detallados de los componentes físicos como la hielera y la maya donde reposan los futuros pollitos.*

## 📋 Descripción

Este proyecto implementa un sistema de control automático para una incubadora de huevos que:

- 🌡️ **Control de temperatura**: Mantiene temperatura objetivo de 38°C (±1°C)
- 💧 **Monitoreo de humedad**: Supervisa niveles entre 50-70%
- 🚨 **Sistema de alarmas**: Alerta auditiva cuando los parámetros salen del rango
- 📺 **Display LCD**: Muestra información en tiempo real
- ⚡ **Control automático**: Enciende/apaga calentador según necesidad

## 🔧 Componentes Necesarios

### Hardware Principal
- **Arduino Uno** (1x) - Microcontrolador principal
- **Sensor DHT11** - Temperatura y Humedad (1x)
- **LCD 16x2** con interfaz I2C o paralelo (1x)
- **Buzzer** - Alarma auditiva (1x)
- **Módulo de Relevador de 5V** - Control del calentador (incluye resistencias integradas)
- **Foco incandescente de 60W** - Fuente de calor (tipo refrigerador)
- **Hielera de unicel** - Cámara de incubación con excelente aislamiento térmico
- **Fuente de alimentación 9V** - Para alimentar el Arduino

### Componentes Adicionales
- **Cables jumper** - Para conexiones
- **Protoboard o PCB** - Para organizar conexiones
- **Socket para foco** - Para conectar el foco de 60W
- **Cable de alimentación** - Para la fuente de 9V
- **Maya o rejilla** - Para sostener los huevos dentro de la hielera

## 🔌 Esquema de Conexiones

### Pines utilizados:
```
DHT11    → Pin Digital 2
Buzzer   → Pin Digital 3  
Relé     → Pin Digital 4
LCD RS   → Pin Digital 8
LCD E    → Pin Digital 9
LCD D4   → Pin Digital 10
LCD D5   → Pin Digital 11
LCD D6   → Pin Digital 12
LCD D7   → Pin Digital 13
```

### Diagrama de Conexión
```
Arduino Uno          DHT11
    5V    ────────── VCC
    GND   ────────── GND
    Pin 2 ────────── DATA

Arduino Uno          LCD 16x2
    5V    ────────── VCC
    GND   ────────── GND
    Pin 8 ────────── RS
    Pin 9 ────────── E
   Pin 10 ────────── D4
   Pin 11 ────────── D5
   Pin 12 ────────── D6
   Pin 13 ────────── D7

Arduino Uno          Módulo Relevador
   Pin 4  ────────── IN
    5V    ────────── VCC
   GND    ────────── GND
   
Módulo Relevador     Foco 60W
   COM    ────────── Fase de entrada
   NO     ────────── Fase hacia el foco

Arduino Uno          Buzzer
   Pin 3  ────────── +
   GND    ────────── -
   
Arduino Uno          Alimentación
   Jack 9V ────────── Fuente 9V
```

## 📚 Librerías Requeridas

Instala las siguientes librerías desde el Administrador de Librerías de Arduino IDE:

```cpp
#include <DHT.h>         // Sensor de temperatura y humedad
#include <DHT_U.h>       // Utilidades DHT
#include <LiquidCrystal.h> // Control LCD
```

### Instalación:
1. Abre Arduino IDE
2. Ve a **Herramientas → Administrar Librerías**
3. Busca e instala: **"DHT sensor library" by Adafruit**
4. La librería `LiquidCrystal` viene incluida con Arduino IDE

## 🚀 Instalación y Uso

### 1. Preparación del Hardware
1. **Preparar la hielera de unicel**: Hacer perforaciones para cables y ventilación
2. **Instalar el foco de 60W**: Conectar socket dentro de la hielera (tipo refrigerador)
3. **Conectar componentes**: Seguir el esquema de conexiones con módulo relevador
4. **Colocar sensor DHT11**: Instalar dentro de la hielera para lecturas precisas
5. **Verificar conexiones**: Antes de conectar la alimentación de 9V
6. **Instalar maya**: Para sostener los huevos a altura adecuada

### 2. Carga del Código
1. Clona este repositorio:
   ```bash
   git clone https://github.com/jonathanarana/incubadora.git
   ```
2. Abre `Incubadora.ino` en Arduino IDE
3. Verifica que las librerías estén instaladas
4. Selecciona tu placa Arduino y puerto COM
5. Carga el código al Arduino

### 3. Configuración Inicial
El sistema está pre-configurado con valores óptimos:

```cpp
float Objetivo = 38;    // Temperatura objetivo (°C)
float Margen = 1;       // Margen de tolerancia (°C)
float at = -0.5;        // Ajuste de calibración temperatura
float ah = 0;           // Ajuste de calibración humedad
```

## ⚙️ Configuración Avanzada

### Calibración de Temperatura
Si necesitas ajustar la lectura del sensor:
```cpp
float at = -0.5;  // Resta 0.5°C a la lectura (ajustar según necesidad)
```

### Calibración de Humedad  
```cpp
float ah = 0;     // Suma/resta valor a la humedad (ajustar según necesidad)
```

### Modificar Rangos Objetivo
```cpp
float Objetivo = 38;  // Temperatura ideal para pollos
// Para otros tipos de huevos:
// Patos: 37.5°C
// Codornices: 37.7°C
// Gansos: 37.4°C
```

## 📊 Funcionamiento

### Pantalla LCD
El display muestra:
1. **Pantalla de inicio**: "PrimerMaster Consultoria" (2 segundos)
2. **Lecturas actuales**: 
   - Línea 1: `Temp: XX.X C`
   - Línea 2: `Hum: XX.X %`

### Sistema de Control
- **Calentador ON**: Cuando temperatura < (Objetivo - Margen)
- **Calentador OFF**: Cuando temperatura > Objetivo
- **Alarma activada**: 
  - Temperatura fuera del rango ±2°C
  - Humedad fuera del rango 50-70%
  - Error de lectura del sensor

### Ciclo de Actualización
- Lecturas cada 5 segundos
- Control automático continuo
- Alarmas inmediatas ante anomalías

## 🔧 Mantenimiento

### Verificaciones Regulares
- [ ] Limpieza del sensor DHT11
- [ ] Verificación de conexiones
- [ ] Calibración de temperatura si es necesario
- [ ] Funcionamiento del sistema de calefacción

### Solución de Problemas

| Problema | Posible Causa | Solución |
|----------|---------------|----------|
| "Error de Lectura" | Sensor DHT11 desconectado | Verificar conexiones |
| Temperatura incorrecta | Necesita calibración | Ajustar variable `at` |
| Alarma constante | Parámetros fuera de rango | Revisar sistema de calefacción |
| LCD en blanco | Problema de conexión | Verificar pines del LCD |

## 📈 Parámetros de Incubación

### Temperaturas Recomendadas
- **Pollos**: 37.5-38.5°C ✅ **(Probado exitosamente)**
- **Patos**: 37.2-37.8°C  
- **Codornices**: 37.5-37.8°C
- **Pavos**: 37.5-37.8°C

### Humedad Recomendada
- **Primeros 18 días**: 55-60%
- **Últimos 3 días**: 65-75%

### Estructura Física
Este proyecto utiliza una **hielera de unicel** como cámara de incubación. Esta elección fue perfecta por:

✅ **Ventajas de la hielera de unicel:**
- Excelente aislamiento térmico del material
- Tamaño ideal para incubación casera
- Fácil de conseguir y económica (disponible en tiendas como OXXO)
- Tapa hermética que mantiene humedad
- Resistente y duradera

🔧 **Configuración del calentador:**
- **Foco de 60W tipo refrigerador**: Perfecto para generar calor controlado
- Disponible en ferreterías como "foco para refrigerador"
- Potencia ideal para mantener 38°C en el volumen de la hielera

**Próximamente**: Diagramas detallados de la estructura física incluyendo:
- 📦 Modificaciones específicas a la hielera de unicel
- 💡 Instalación del sistema de foco incandescente  
- 🥚 Sistema de maya para sostener los huevos
- 🎥 Videos del funcionamiento completo

## 🤝 Contribuciones

Las contribuciones son bienvenidas y se agradecen.

## 📄 Licencia

Este proyecto es **Software Libre** y garantiza las cuatro libertades fundamentales:
- Libertad de usar el programa para cualquier propósito
- Libertad de estudiar cómo funciona el programa y modificarlo
- Libertad de distribuir copias del programa
- Libertad de distribuir copias de las versiones modificadas

## 📖 Historia del Proyecto

Este proyecto nació durante los **primeros días del confinamiento por COVID-19**. En esos momentos difíciles de aislamiento, mi familia (esposa e hija) y yo buscábamos actividades que nos ayudaran a mantener la cordura y encontrar esperanza en medio de la incertidumbre.

La **primera incubación se debió realizar en marzo de 2020**, aprovechando que la primavera ofrece mejores condiciones de supervivencia para los pollitos. Después de múltiples ajustes y aprendizajes, se hizo una **segunda y última prueba, al parecer en noviembre de 2020** (cuando se guardó la versión final del código), nuevamente en una estación templada favorable para los recién nacidos.

Este proyecto no solo fue exitoso técnicamente, sino que se convirtió en una fuente de alegría y propósito durante uno de los períodos más desafiantes que hemos vivido como familia. Ver nacer vida nueva en casa fue exactamente lo que necesitábamos en esos días.

**Para quienes deseen intentar este proyecto**: Les deseamos el mayor de los éxitos. Que esta incubadora les traiga la misma satisfacción y esperanza que nos trajo a nosotros. ¡Que disfruten viendo nacer sus propios pollitos!

**Próximamente**: Videos explicativos del funcionamiento y diagramas de componentes físicos.

---

⭐ ¡Si este proyecto te ayuda, considera darle una estrella!
