# Cheap-Yellow-Deck
Arduino code to create a deck with buttons which create a bleutooth keyboard with keystrokes.

Some information about the Cheap Yellow Display: https://github.com/witnessmenow/ESP32-Cheap-Yellow-Display

Basic tutorial to create a buttons with lvgl: https://randomnerdtutorials.com/lvgl-cheap-yellow-display-esp32-2432s028r/

## Requirements
Before flashing this at your display, make sure that:
- You have installed the lvgl library (I have used 9.2.2)
- Select module ESP32 Dev Module
- Use partition scheme "Huge APP (3MB No OTA/1MB SPIFFS)" (bleutooth in combination with lvgl takes a lot of code, maybe it can be optimized)
