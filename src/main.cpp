#include <appdef.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <sdk/calc/calc.hpp>
#include <sdk/os/input.hpp>

extern "C" {
  #include "UGUI/ugui_config.h"
  #include "UGUI/ugui.h"
}

APP_NAME("Chart Test")
APP_DESCRIPTION("WIP Charts")
APP_AUTHOR("s3ansh33p")
APP_VERSION("1.0.0")

// wrapper for setPixel
void UGWrapper(UG_S16 x, UG_S16 y, UG_COLOR color) {
  setPixel(x, y, color);
}

void window_1_callback( UG_MESSAGE* msg ) {
  if ( msg->type == MSG_TYPE_OBJECT ) {
    switch( msg->id ) {
      case OBJ_TYPE_BUTTON: {
        if ( msg->event == OBJ_EVENT_PRESSED ) {
          switch( msg->sub_id ) {
            case BTN_ID_0:
              // fputs("Button 1 pressed\n", stdout);
              UG_PutString(10, 250, "Button 1 pressed");
              break;
            case BTN_ID_1:
              // fputs("Button 2 pressed\n", stdout);
              UG_PutString(10, 250, "Button 2 pressed");
              break;
            case BTN_ID_2:
              // fputs("Button 3 pressed\n", stdout);
              UG_PutString(10, 250, "Button 3 pressed");
              break;
          }
          LCD_Refresh();
        }
      }
      break;
    }
  }
}

#define MAX_OBJECTS 10

extern "C" int __attribute__((section(".bootstrap.text"))) main(void) {
  calcInit();


  struct InputEvent event;

  /* Initialize the GUI */
  UG_GUI gui;
  UG_Init( &gui, UGWrapper, width, height );

  UG_FontSelect( &FONT_8X8 );

  UG_WINDOW window_1;
  UG_BUTTON button_1;
  UG_BUTTON button_2;
  UG_BUTTON button_3;
  UG_TEXTBOX textbox_1;
  UG_OBJECT obj_buff_wnd_1[MAX_OBJECTS];

  // fill background
  UG_FillScreen( C_BLACK );

  UG_WindowCreate( &window_1, obj_buff_wnd_1, MAX_OBJECTS, window_1_callback );

  UG_WindowSetTitleText( &window_1, "Test Window Title" );
  UG_WindowSetTitleTextFont( &window_1, &FONT_8X12 );

  UG_ButtonCreate( &window_1, &button_1, BTN_ID_0, 10, 10, 110, 60 );
  UG_ButtonSetFont( &window_1, BTN_ID_0, &FONT_8X12 );
  UG_ButtonSetText( &window_1, BTN_ID_0, "Button 1" );

  UG_ButtonCreate( &window_1, &button_2, BTN_ID_1, 10, 80, 110, 130 );
  UG_ButtonSetFont( &window_1, BTN_ID_1, &FONT_8X12 );
  UG_ButtonSetText( &window_1, BTN_ID_1, "Button 2" );

  UG_ButtonCreate( &window_1, &button_3, BTN_ID_2, 10, 150, 110, 200 );
  UG_ButtonSetFont( &window_1, BTN_ID_2, &FONT_8X12 );
  UG_ButtonSetText( &window_1, BTN_ID_2, "Button 3" );

  UG_TextboxCreate( &window_1, &textbox_1, TXB_ID_0, 120, 10, 310, 200 );
  UG_TextboxSetFont( &window_1, TXB_ID_0, &FONT_8X12 );
  UG_TextboxSetText( &window_1, TXB_ID_0, "This is a test textbox\nSecond line" );
  UG_TextboxSetForeColor( &window_1, TXB_ID_0, C_BLACK );
  UG_TextboxSetAlignment( &window_1, TXB_ID_0, ALIGN_CENTER );

  UG_WindowShow( &window_1 );

  UG_Update();

  LCD_Refresh();  

  bool running = true;
  while(running) {
    GetInput(&event, 0xFFFFFFFF, 0x10); // polls
    
    switch (event.type) {
      case EVENT_TOUCH:
        if (event.data.touch_single.direction == TOUCH_DOWN) {
          UG_TouchUpdate(event.data.touch_single.p1_x, event.data.touch_single.p1_y, TOUCH_STATE_PRESSED);
        } else if (event.data.touch_single.direction == TOUCH_UP) {
          UG_TouchUpdate(event.data.touch_single.p1_x, event.data.touch_single.p1_y, TOUCH_STATE_RELEASED);
        }
        UG_Update();
        break;
      case EVENT_KEY:
        if (event.data.key.keyCode == KEYCODE_POWER_CLEAR) {
          running = false;
        }
        break;
    }
    LCD_Refresh();
  }



  // while(true){
	// 	uint32_t key1, key2;	//First create variables
	// 	getKey(&key1, &key2);	//then read the keys
	// 	if(testKey(key1, key2, KEY_CLEAR)){ //Use testKey() to test if a specific key is pressed
	// 		break;
	// 	}
	// }
  calcEnd();
  exit(EXIT_SUCCESS);
}
