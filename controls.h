//#define ROTATE_DPAD

#ifdef ROTATE_DPAD
  #define left_btn LEFT_BUTTON
  #define right_btn RIGHT_BUTTON
  #define up_btn UP_BUTTON
  #define down_btn DOWN_BUTTON
#else
#define left_btn UP_BUTTON
  #define right_btn DOWN_BUTTON
  #define up_btn RIGHT_BUTTON
  #define down_btn LEFT_BUTTON
#endif
