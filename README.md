# Proyecto: Emulador de GameBoy en C con SDL 
## Documentación de Planeación Técnica 

## 1. Descripción del Proyecto 
### Objetivo Desarrollar un emulador funcional de la Nintendo GameBoy original utilizando el lenguaje C y SDL para renderizado gráfico, audio y entrada de usuario. 

### Alcance - Emulación de CPU Z80-like (Sharp LR35902)
- Soporte para ROMs .gb básicas (juegos simples) 
- Renderizado gráfico LCD (160x144 píxeles) 
- Sistema de audio básico 
- Manejo de entrada (teclado mapeado a botones) 

### Tecnologías 
| Componente           | Tecnología       | Sistemas Soportados   |                       
| -------------------- | ---------------- | --------------------- |  
| Lenguaje Core        | C99/C11 (C puro) |                       |
| Gráficos/Audio/Input | SDL2             |                       |
| Compilador           | GCC o Clang      | Windows, Linux, macOS |

--- 
## 2. Especificaciones Técnicas 
### CPU (Sharp LR35902) 
- 8-bit architecture 
- Clock: 4.19 MHz aprox. 
- Registros principales: A, B, C, D, E, H, L, SP, PC 
- Flags: Z, N, H, C 
- Instrucciones: ~513 opcodes 
- Modos de direccionamiento: inmediato, registro, indirecto 
### Memoria 
| Rango Hexadecimal | Descripción                  | Tamaño     |     |
| ----------------- | ---------------------------- | ---------- | --- |
| 0x0000 - 0x7FFF   | Cartridge ROM                | 32KB-128MB |     |
| 0x8000 - 0x9FFF   | Video RAM (VRAM)             | 8KB        |     |
| 0xA000 - 0xBFFF   | Cartridge RAM                | Variable   |     |
| 0xC000 - 0xDFFF   | Work RAM (WRAM)              | 4KB        |     |
| 0xE000 - 0xFDFF   | Echo RAM                     | 4KB        |     |
| 0xFE00 - 0xFE9F   | Sprite Attribute Table (OAM) | 160 bytes  |     |
| 0xFF00 - 0xFF7F   | I/O Registers                | 128 bytes  |     |
| 0xFF80 - 0xFFFF   | High RAM                     | 127 bytes  |     |
### GPU 
- Resolución: 160×144 píxeles 
- Colores: 4 tonos de verde (paleta DMG) 
- Tiles: 8x8 píxeles, 192 tiles máx. 
- Sprites: 40 sprites, 8x8 o 8x16 píxeles 
- Dos modos de operación: H-Blank, V-Blank

### Audio (APU) 
- 4 canales: Canal 1, Canal 2, Canal 3 (wav), Canal 4 (ruido) 
- Sample rate: ~16 kHz 
- Volume control y pan stereo

---
## 3. Pasos de Desarrollo Recomendados 
### Iteración 1: Fundamentos 
1. Instalar SDL2 y verificar instalación 
2. Crear ventana SDL básica (160x144 escala 2x o 3x) 
3. Implementar game loop con control de framerate (approx 59.73 fps) 
### Iteración 2: CPU Básica 
1. Crear estructura de registros 
2. Implementar fetch-decode-execute cycle 
3. Implementar 20-30 opcodes más comunes 
4. Añadir sistema de flags
### Iteración 3: Memory Mapping 
1. Crear array de memoria principal (64KB) 
2. Implementar funciones de lectura/escritura 
3. Load ROM desde archivo .bin/.gb 4. Mapeo de regiones de memoria 
### Iteración 4: GPU 
1. Renderizar buffer directo a textura SDL 
2. Implementar sistema de tiles básico 3. Añadir sprites simples 
3. Control de paleta de colores 
### Iteración 5: Integración Completa 
1. Conectar todos los módulos 
2. Implementar APU (audio opcional en primera versión) 
3. Pruebas con ROMs reales (tetris, etc.)

---
## 4. Recursos Necesarios
### Herramientas de Debugging

- GDB con soporte C
- Valgrind para detección de memory leaks
- Visual Studio Code o Vim con extensiones C
- Emuladores de referencia (SameBoy, BGB) para pruebas

### Material de Referencia

- Documento oficial GB Tech Manual (Panini)
- SameCycle CPU test ROM
- GameBoy CPU Reference Guide ([http://www.pastraiser.com/](http://www.pastraiser.com/))
- Repositorios open-source: SameBoy, GBDK

---
## 5. Posibles Desafíos y Soluciones

| Desafío                   | Solución Propuesta                                     |
| ------------------------- | ------------------------------------------------------ |
| Cycle-accurate timing     | Usar ciclo base de ~70224 cycles por frame             |
| Memory mapping complejo   | Implementar memoria mapeada con punteros a arrays      |
| Gráficos con parallax     | Usar double-buffering de SDL2                          |
| Audio sincronizado        | Buffer circular + thread separado o mixeo en main loop |
| Bug en implementación CPU | Usar test suite (blargg CPU tests) para validación     |

---
## 6. Estructura del Makefile

```Makefile
CC = gcc CFLAGS = -Wall -Wextra -pedantic -std=c11 -O2 
SDL_FLAGS = $(shell pkg-config --cflags sdl2) 
SDL_LIBS = $(shell pkg-config --libs sdl2) 

SRC_DIR = src 
BUILD_DIR = build 
BIN = gameboy_emulator 

SRCS = $(wildcard $(SRC_DIR)/*.c) 
OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS)) 

.PHONY: all clean 

all: $(BUILD_DIR) $(BIN) 

$(BUILD_DIR):
  mkdir -p $(BUILD_DIR) 

$(BIN): $(OBJS) 
  $(CC) $(OBJS) -o $@ $(SDL_LIBS)
  
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
  $(CC) $(CFLAGS) $(SDL_FLAGS) -c $< -o $@
  
clean:
  rm -rf $(BUILD_DIR) $(BIN) 

debug: CFLAGS += -g -DDEBUG 
debug: clean all
```

---
## 7. Definición de Éxito

### Criterios Mínimos

- [ ]  Emula juegos comerciales simples (ej: Tetris, Snake)
- [ ]  Frame rate estable ~59.73 FPS
- [ ]  Gráficos visibles y sincronizados
- [ ]  No hay crashes durante 30 minutos de ejecución

### Criterios Avanzados

- [ ]  Audio funcional
- [ ]  Soporte para save states
- [ ]  Compatible con múltiples ROMs
- [ ]  Test suite pasa completamente

---
## Recursos Adicionales Recomendados

### recursos utiles
- [cinoop](https://cturt.github.io/cinoop.html)
- [pandocs](https://gbdev.io/pandocs/)
- [DMG-01](https://rylev.github.io/DMG-01/public/book/print.html)
- [adventure in gameboy emulation](https://wornwinter.wordpress.com/2015/02/14/adventures-in-gameboy-emulation-part-2-the-cpu/)

1. **Documentación Oficial**: "Game Boy Documentation Project" en gbdev.io
2. **Test Suites**: blargg CPU tests y MBC tests
3. **Tutoriales**: Emulator.dev tiene guías paso a paso en varios lenguajes
4. **Comunidad**: Discord de GBDev y r/emulation en Reddit

---
_Documento para planeación de proyecto de emulador -Fecha: 14 Sep 2026_
