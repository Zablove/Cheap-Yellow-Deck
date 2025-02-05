/*  Rui Santos & Sara Santos - Random Nerd Tutorials
    THIS EXAMPLE WAS TESTED WITH THE FOLLOWING HARDWARE:
    1) ESP32-2432S028R 2.8 inch 240×320 also known as the Cheap Yellow Display (CYD): https://makeradvisor.com/tools/cyd-cheap-yellow-display-esp32-2432s028r/
      SET UP INSTRUCTIONS: https://RandomNerdTutorials.com/cyd-lvgl/
    2) REGULAR ESP32 Dev Board + 2.8 inch 240x320 TFT Display: https://makeradvisor.com/tools/2-8-inch-ili9341-tft-240x320/ and https://makeradvisor.com/tools/esp32-dev-board-wi-fi-bluetooth/
      SET UP INSTRUCTIONS: https://RandomNerdTutorials.com/esp32-tft-lvgl/
    Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files.
    The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
*/

/*  Install the "lvgl" library version 9.2 by kisvegabor to interface with the TFT Display - https://lvgl.io/
    *** IMPORTANT: lv_conf.h available on the internet will probably NOT work with the examples available at Random Nerd Tutorials ***
    *** YOU MUST USE THE lv_conf.h FILE PROVIDED IN THE LINK BELOW IN ORDER TO USE THE EXAMPLES FROM RANDOM NERD TUTORIALS ***
    FULL INSTRUCTIONS AVAILABLE ON HOW CONFIGURE THE LIBRARY: https://RandomNerdTutorials.com/cyd-lvgl/ or https://RandomNerdTutorials.com/esp32-tft-lvgl/   */
#include <lvgl.h>

/*  Install the "TFT_eSPI" library by Bodmer to interface with the TFT Display - https://github.com/Bodmer/TFT_eSPI
    *** IMPORTANT: User_Setup.h available on the internet will probably NOT work with the examples available at Random Nerd Tutorials ***
    *** YOU MUST USE THE User_Setup.h FILE PROVIDED IN THE LINK BELOW IN ORDER TO USE THE EXAMPLES FROM RANDOM NERD TUTORIALS ***
    FULL INSTRUCTIONS AVAILABLE ON HOW CONFIGURE THE LIBRARY: https://RandomNerdTutorials.com/cyd-lvgl/ or https://RandomNerdTutorials.com/esp32-tft-lvgl/   */
#include <TFT_eSPI.h>

// Install the "XPT2046_Touchscreen" library by Paul Stoffregen to use the Touchscreen - https://github.com/PaulStoffregen/XPT2046_Touchscreen - Note: this library doesn't require further configuration
#include <XPT2046_Touchscreen.h>

// Include Bluetooth keyboard setup
#include <BleKeyboard.h>
BleKeyboard bleKeyboard;

// Touchscreen pins
#define XPT2046_IRQ 36   // T_IRQ
#define XPT2046_MOSI 32  // T_DIN
#define XPT2046_MISO 39  // T_OUT
#define XPT2046_CLK 25   // T_CLK
#define XPT2046_CS 33    // T_CS

SPIClass touchscreenSPI = SPIClass(VSPI);
XPT2046_Touchscreen touchscreen(XPT2046_CS, XPT2046_IRQ);

#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 320

// Touchscreen coordinates: (x, y) and pressure (z)
int x, y, z;

#define DRAW_BUF_SIZE (SCREEN_WIDTH * SCREEN_HEIGHT / 10 * (LV_COLOR_DEPTH / 8))
uint32_t draw_buf[DRAW_BUF_SIZE / 4];

// If logging is enabled, it will inform the user about what is happening in the library
//void log_print(lv_log_level_t level, const char * buf) {
//  LV_UNUSED(level);
  //Serial.println(buf);
  //Serial.flush();
//}

// Get the Touchscreen data
void touchscreen_read(lv_indev_t * indev, lv_indev_data_t * data) {
  // Checks if Touchscreen was touched, and prints X, Y and Pressure (Z)
  if(touchscreen.tirqTouched() && touchscreen.touched()) {
    // Get Touchscreen points
    TS_Point p = touchscreen.getPoint();
    // Calibrate Touchscreen points with map function to the correct width and height
    x = map(p.x, 200, 3700, 1, SCREEN_WIDTH);
    y = map(p.y, 240, 3800, 1, SCREEN_HEIGHT);
    z = p.z;

    data->state = LV_INDEV_STATE_PRESSED;

    // Set the coordinates
    data->point.x = x;
    data->point.y = y;

    // Print Touchscreen info about X, Y and Pressure (Z) on the Serial Monitor
    Serial.print("X = ");
    Serial.print(x);
    Serial.print(" | Y = ");
    Serial.print(y);
    Serial.print(" | Pressure = ");
    Serial.print(z);
    Serial.println();
  }
  else {
    data->state = LV_INDEV_STATE_RELEASED;
  }
}

// Callback that is triggered when btn1 is clicked
static void event_handler_btn1(lv_event_t * e) {
  lv_event_code_t code = lv_event_get_code(e);
  if(code == LV_EVENT_CLICKED) {
    bleKeyboard.press(KEY_LEFT_GUI);
    delay(100);
    bleKeyboard.press(51); //Win+3 = Keepass
    delay(100);
    bleKeyboard.releaseAll();
    delay(100);
    bleKeyboard.press(KEY_LEFT_CTRL);
    delay(100);
    bleKeyboard.press(102); //Ctrl+F to search in Keepass
    delay(100);
    bleKeyboard.releaseAll();
    bleKeyboard.print("1streamdeck"); //Search 1streamdeck password
    delay(100);
    bleKeyboard.press(KEY_LEFT_CTRL);
    delay(100);
    bleKeyboard.press(99); //Ctrl+C for copy password
    delay(100);
    bleKeyboard.releaseAll();
    bleKeyboard.press(KEY_LEFT_ALT);
    delay(100);
    bleKeyboard.press(KEY_TAB); //Alt+TAB to switch back to application
    delay(100);
    bleKeyboard.releaseAll();
    bleKeyboard.press(KEY_LEFT_CTRL);
    delay(100);
    bleKeyboard.press(118); //Ctrl+v to paste password
    delay(100);
    bleKeyboard.releaseAll();
    bleKeyboard.press(KEY_RETURN);
    delay(100);
    bleKeyboard.releaseAll();
    bleKeyboard.press(KEY_RIGHT_GUI);
    delay(100);
    bleKeyboard.press(51); //Win+3 = Keepass
    delay(100);
    bleKeyboard.releaseAll();
    bleKeyboard.press(KEY_LEFT_CTRL);
    delay(100);
    bleKeyboard.press(116); //Ctrl+t to copy OTP
    delay(100);
    bleKeyboard.releaseAll();
    bleKeyboard.press(KEY_LEFT_ALT);
    delay(100);
    bleKeyboard.press(KEY_TAB); //Alt+TAB to switch back to application
    delay(100);
    bleKeyboard.releaseAll();
    bleKeyboard.press(KEY_LEFT_CTRL);
    delay(100);
    bleKeyboard.press(118); //Ctrl+v to paste password
    delay(100);
    bleKeyboard.releaseAll();
    bleKeyboard.press(KEY_RETURN);
    delay(100);
    bleKeyboard.releaseAll();
    delay(3000);
    bleKeyboard.print("aj");
    bleKeyboard.press(KEY_RETURN);
    delay(100);
    bleKeyboard.releaseAll();
    
  }
}

// Callback that is triggered when btn2 is clicked
static void event_handler_btn2(lv_event_t * e) {
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t * obj = (lv_obj_t*) lv_event_get_target(e);
  if(code == LV_EVENT_CLICKED) {
    bleKeyboard.press(KEY_LEFT_GUI);
    delay(100);
    bleKeyboard.press(51); //Win+3 = Keepass
    delay(100);
    bleKeyboard.releaseAll();
    delay(100);
    bleKeyboard.press(KEY_LEFT_CTRL);
    delay(100);
    bleKeyboard.press(102); //Ctrl+F to search in Keepass
    delay(100);
    bleKeyboard.releaseAll();
    bleKeyboard.print("1streamdeck"); //Search 1streamdeck password
    delay(100);
    bleKeyboard.press(KEY_LEFT_CTRL);
    delay(100);
    bleKeyboard.press(99); //Ctrl+C for copy password
    delay(100);
    bleKeyboard.releaseAll();
    bleKeyboard.press(KEY_LEFT_ALT);
    delay(100);
    bleKeyboard.press(KEY_TAB); //Alt+TAB to switch back to application
    delay(100);
    bleKeyboard.releaseAll();
    bleKeyboard.press(KEY_LEFT_CTRL);
    delay(100);
    bleKeyboard.press(118); //Ctrl+v to paste password
    delay(100);
    bleKeyboard.releaseAll();
    bleKeyboard.press(KEY_RETURN);
    delay(100);
    bleKeyboard.releaseAll();
  }
}

static void event_handler_btn3(lv_event_t * e) {
  lv_event_code_t code = lv_event_get_code(e);
  if(code == LV_EVENT_CLICKED) {
    bleKeyboard.press(KEY_LEFT_GUI);
    delay(100);
    bleKeyboard.press(51); //Win+3 = Keepass
    delay(100);
    bleKeyboard.releaseAll();
    delay(100);
    bleKeyboard.press(KEY_LEFT_CTRL);
    delay(100);
    bleKeyboard.press(102); //Ctrl+F to search in Keepass
    delay(100);
    bleKeyboard.releaseAll();
    bleKeyboard.print("2streamdeck"); //Search 1streamdeck password
    delay(100);
    bleKeyboard.press(KEY_LEFT_CTRL);
    delay(100);
    bleKeyboard.press(99); //Ctrl+C for copy password
    delay(100);
    bleKeyboard.releaseAll();
    bleKeyboard.press(KEY_LEFT_ALT);
    delay(100);
    bleKeyboard.press(KEY_TAB); //Alt+TAB to switch back to application
    delay(100);
    bleKeyboard.releaseAll();
    bleKeyboard.press(KEY_LEFT_CTRL);
    delay(100);
    bleKeyboard.press(118); //Ctrl+v to paste password
    delay(100);
    bleKeyboard.releaseAll();
    bleKeyboard.press(KEY_RETURN);
    delay(100);
    bleKeyboard.releaseAll();
  }
}

static void event_handler_btn4(lv_event_t * e) {
  lv_event_code_t code = lv_event_get_code(e);
  if(code == LV_EVENT_CLICKED) {
    bleKeyboard.print("Knop4");
    bleKeyboard.press(KEY_RETURN);
    bleKeyboard.releaseAll();
  }
}

static void event_handler_btn5(lv_event_t * e) {
  lv_event_code_t code = lv_event_get_code(e);
  if(code == LV_EVENT_CLICKED) {
    bleKeyboard.print("Knop5");
    bleKeyboard.press(KEY_RETURN);
    bleKeyboard.releaseAll();
  }
}

static void event_handler_btn6(lv_event_t * e) {
  lv_event_code_t code = lv_event_get_code(e);
  if(code == LV_EVENT_CLICKED) {
    bleKeyboard.print("Knop6");
    bleKeyboard.press(KEY_RETURN);
    bleKeyboard.releaseAll();
  }
}

static void event_handler_btn7(lv_event_t * e) {
  lv_event_code_t code = lv_event_get_code(e);
  if(code == LV_EVENT_CLICKED) {
    bleKeyboard.print("Knop7");
    bleKeyboard.press(KEY_RETURN);
    bleKeyboard.releaseAll();
  }
}

static void event_handler_btn8(lv_event_t * e) {
  lv_event_code_t code = lv_event_get_code(e);
  if(code == LV_EVENT_CLICKED) {
    bleKeyboard.print("Knop8");
    bleKeyboard.press(KEY_RETURN);
    bleKeyboard.releaseAll();
  }
}

static void event_handler_btn9(lv_event_t * e) {
  lv_event_code_t code = lv_event_get_code(e);
  if(code == LV_EVENT_CLICKED) {
    bleKeyboard.print("Knop9");
    bleKeyboard.press(KEY_RETURN);
    bleKeyboard.releaseAll();
  }
}

static void event_handler_btn10(lv_event_t * e) {
  lv_event_code_t code = lv_event_get_code(e);
  if(code == LV_EVENT_CLICKED) {
    bleKeyboard.print("Knop10");
    bleKeyboard.press(KEY_RETURN);
    bleKeyboard.releaseAll();
  }
}

static void event_handler_btn11(lv_event_t * e) {
  lv_event_code_t code = lv_event_get_code(e);
  if(code == LV_EVENT_CLICKED) {
    bleKeyboard.print("Knop11");
    bleKeyboard.press(KEY_RETURN);
    bleKeyboard.releaseAll();
  }
}

static void event_handler_btn12(lv_event_t * e) {
  lv_event_code_t code = lv_event_get_code(e);
  if(code == LV_EVENT_CLICKED) {
    bleKeyboard.print("Knop12");
    bleKeyboard.press(KEY_RETURN);
    bleKeyboard.releaseAll();
  }
}

// static lv_obj_t * slider_label;
// // Callback that prints the current slider value on the TFT display and Serial Monitor for debugging purposes
// static void slider_event_callback(lv_event_t * e) {
//   lv_obj_t * slider = (lv_obj_t*) lv_event_get_target(e);
//   char buf[8];
//   lv_snprintf(buf, sizeof(buf), "%d%%", (int)lv_slider_get_value(slider));
//   lv_label_set_text(slider_label, buf);
//   lv_obj_align_to(slider_label, slider, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
//   LV_LOG_USER("Slider changed to %d%%", (int)lv_slider_get_value(slider));
// }

void lv_create_main_gui(void) {
  // Create a text label aligned center on top ("Hello, world!")
  // lv_obj_t * text_label = lv_label_create(lv_screen_active());
  // lv_label_set_long_mode(text_label, LV_LABEL_LONG_WRAP);    // Breaks the long lines
  // lv_label_set_text(text_label, "Hello, world!");
  // lv_obj_set_width(text_label, 150);    // Set smaller width to make the lines wrap
  // lv_obj_set_style_text_align(text_label, LV_TEXT_ALIGN_CENTER, 0);
  // lv_obj_align(text_label, LV_ALIGN_CENTER, 0, -90);

  lv_obj_t * screen = lv_scr_act();  // Haal het actieve scherm op
  lv_obj_set_style_bg_color(screen, lv_color_black(), 0);  // Stel de achtergrondkleur in op zwart


  lv_obj_t * btn_label;
  // Create a Button (btn1)
  lv_obj_t * btn1 = lv_button_create(lv_screen_active());
  lv_obj_add_event_cb(btn1, event_handler_btn1, LV_EVENT_ALL, NULL);
  lv_obj_align(btn1, LV_ALIGN_CENTER, -110, -90);
  lv_obj_remove_flag(btn1, LV_OBJ_FLAG_PRESS_LOCK);
  btn_label = lv_label_create(btn1);
  lv_label_set_text(btn_label, "AKS");
  lv_obj_center(btn_label);
  lv_obj_set_size(btn1, 100, 50);

  // Create a Toggle button (btn2)
  lv_obj_t * btn2 = lv_button_create(lv_screen_active());
  lv_obj_add_event_cb(btn2, event_handler_btn2, LV_EVENT_ALL, NULL);
  lv_obj_align(btn2, LV_ALIGN_CENTER, -110, -30);
  lv_obj_remove_flag(btn2, LV_OBJ_FLAG_PRESS_LOCK);
  btn_label = lv_label_create(btn2);
  lv_label_set_text(btn_label, "OCC Pwd");
  lv_obj_center(btn_label);
  lv_obj_set_size(btn2, 100, 50);
  
  // Create a Button (btn3)
  lv_obj_t * btn3 = lv_button_create(lv_screen_active());
  lv_obj_add_event_cb(btn3, event_handler_btn3, LV_EVENT_ALL, NULL);
  lv_obj_align(btn3, LV_ALIGN_CENTER, -110, 30);
  lv_obj_remove_flag(btn3, LV_OBJ_FLAG_PRESS_LOCK);
  btn_label = lv_label_create(btn3);
  lv_label_set_text(btn_label, "CE Pwd");
  lv_obj_center(btn_label);
  lv_obj_set_size(btn3, 100, 50);

  // Create a Button (btn4)
  lv_obj_t * btn4 = lv_button_create(lv_screen_active());
  lv_obj_add_event_cb(btn4, event_handler_btn4, LV_EVENT_ALL, NULL);
  lv_obj_align(btn4, LV_ALIGN_CENTER, -110, 90);
  lv_obj_remove_flag(btn4, LV_OBJ_FLAG_PRESS_LOCK);
  btn_label = lv_label_create(btn4);
  lv_label_set_text(btn_label, "Knop4");
  lv_obj_center(btn_label);
  lv_obj_set_size(btn4, 100, 50);

  // Create a Button (btn5)
  lv_obj_t * btn5 = lv_button_create(lv_screen_active());
  lv_obj_add_event_cb(btn5, event_handler_btn5, LV_EVENT_ALL, NULL);
  lv_obj_align(btn5, LV_ALIGN_CENTER, 0, -90);
  lv_obj_remove_flag(btn5, LV_OBJ_FLAG_PRESS_LOCK);
  btn_label = lv_label_create(btn5);
  lv_label_set_text(btn_label, "Knop5");
  lv_obj_center(btn_label);
  lv_obj_set_size(btn5, 100, 50);

  // Create a Toggle button (btn6)
  lv_obj_t * btn6 = lv_button_create(lv_screen_active());
  lv_obj_add_event_cb(btn6, event_handler_btn6, LV_EVENT_ALL, NULL);
  lv_obj_align(btn6, LV_ALIGN_CENTER, 0, -30);
  lv_obj_remove_flag(btn6, LV_OBJ_FLAG_PRESS_LOCK);
  btn_label = lv_label_create(btn6);
  lv_label_set_text(btn_label, "Knop6");
  lv_obj_center(btn_label);
  lv_obj_set_size(btn6, 100, 50);
  
  // Create a Button (btn7)
  lv_obj_t * btn7 = lv_button_create(lv_screen_active());
  lv_obj_add_event_cb(btn7, event_handler_btn7, LV_EVENT_ALL, NULL);
  lv_obj_align(btn7, LV_ALIGN_CENTER, 0, 30);
  lv_obj_remove_flag(btn7, LV_OBJ_FLAG_PRESS_LOCK);
  btn_label = lv_label_create(btn7);
  lv_label_set_text(btn_label, "Knop7");
  lv_obj_center(btn_label);
  lv_obj_set_size(btn7, 100, 50);

  // Create a Button (btn8)
  lv_obj_t * btn8 = lv_button_create(lv_screen_active());
  lv_obj_add_event_cb(btn8, event_handler_btn8, LV_EVENT_ALL, NULL);
  lv_obj_align(btn8, LV_ALIGN_CENTER, 0, 90);
  lv_obj_remove_flag(btn8, LV_OBJ_FLAG_PRESS_LOCK);
  btn_label = lv_label_create(btn8);
  lv_label_set_text(btn_label, "Knop8");
  lv_obj_center(btn_label);
  lv_obj_set_size(btn8, 100, 50);

  // Create a Button (btn9)
  lv_obj_t * btn9 = lv_button_create(lv_screen_active());
  lv_obj_add_event_cb(btn9, event_handler_btn9, LV_EVENT_ALL, NULL);
  lv_obj_align(btn9, LV_ALIGN_CENTER, 110, -90);
  lv_obj_remove_flag(btn9, LV_OBJ_FLAG_PRESS_LOCK);
  btn_label = lv_label_create(btn9);
  lv_label_set_text(btn_label, "Knop9");
  lv_obj_center(btn_label);
  lv_obj_set_size(btn9, 100, 50);

  // Create a Button (btn10)
  lv_obj_t * btn10 = lv_button_create(lv_screen_active());
  lv_obj_add_event_cb(btn10, event_handler_btn10, LV_EVENT_ALL, NULL);
  lv_obj_align(btn10, LV_ALIGN_CENTER, 110, -30);
  lv_obj_remove_flag(btn10, LV_OBJ_FLAG_PRESS_LOCK);
  btn_label = lv_label_create(btn10);
  lv_label_set_text(btn_label, "Knop10");
  lv_obj_center(btn_label);
  lv_obj_set_size(btn10, 100, 50);

    // Create a Button (btn11)
  lv_obj_t * btn11 = lv_button_create(lv_screen_active());
  lv_obj_add_event_cb(btn11, event_handler_btn11, LV_EVENT_ALL, NULL);
  lv_obj_align(btn11, LV_ALIGN_CENTER, 110, 30);
  lv_obj_remove_flag(btn11, LV_OBJ_FLAG_PRESS_LOCK);
  btn_label = lv_label_create(btn11);
  lv_label_set_text(btn_label, "Knop11");
  lv_obj_center(btn_label);
  lv_obj_set_size(btn11, 100, 50);

    // Create a Button (btn12)
  lv_obj_t * btn12 = lv_button_create(lv_screen_active());
  lv_obj_add_event_cb(btn12, event_handler_btn12, LV_EVENT_ALL, NULL);
  lv_obj_align(btn12, LV_ALIGN_CENTER, 110, 90);
  lv_obj_remove_flag(btn12, LV_OBJ_FLAG_PRESS_LOCK);
  btn_label = lv_label_create(btn12);
  lv_label_set_text(btn_label, "Knop12");
  lv_obj_center(btn_label);
  lv_obj_set_size(btn12, 100, 50);
}

void setup() {
  String LVGL_Arduino = String("LVGL Library Version: ") + lv_version_major() + "." + lv_version_minor() + "." + lv_version_patch();
  Serial.begin(115200);
  //Serial.println(LVGL_Arduino);
  
  // Start LVGL
  lv_init();
  // Register print function for debugging
  //lv_log_register_print_cb(log_print);

  // Start the SPI for the touchscreen and init the touchscreen
  touchscreenSPI.begin(XPT2046_CLK, XPT2046_MISO, XPT2046_MOSI, XPT2046_CS);
  touchscreen.begin(touchscreenSPI);
  // Set the Touchscreen rotation in landscape mode
  // Note: in some displays, the touchscreen might be upside down, so you might need to set the rotation to 0: touchscreen.setRotation(0);
  touchscreen.setRotation(2);

  // Create a display object
  lv_display_t * disp;
  // Initialize the TFT display using the TFT_eSPI library
  disp = lv_tft_espi_create(SCREEN_WIDTH, SCREEN_HEIGHT, draw_buf, sizeof(draw_buf));
  lv_display_set_rotation(disp, LV_DISPLAY_ROTATION_270);
    
  // Initialize an LVGL input device object (Touchscreen)
  lv_indev_t * indev = lv_indev_create();
  lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
  // Set the callback function to read Touchscreen input
  lv_indev_set_read_cb(indev, touchscreen_read);

  // Function to draw the GUI (text, buttons and sliders)
  lv_create_main_gui();

  // Start Bluetooth Keyboard
  bleKeyboard.begin();
}

void loop() {
  lv_task_handler();  // let the GUI do its work
  lv_tick_inc(5);     // tell LVGL how much time has passed
  delay(5);           // let this time pass
}