/* *************************************************************
   Encoder driver function definitions - by James Nugen
   ************************************************************ */
   
   
#ifdef ARDUINO_ENC_COUNTER
  //below can be changed, but should be PORTD pins; 
  //otherwise additional changes in the code are required
  #define LEFT_ENC_PIN_A PD2  //pin 2
  #define LEFT_ENC_PIN_B PD3  //pin 3
  
  //below can be changed, but should be PORTC pins
  #define RIGHT_ENC_PIN_A PC4  //pin A4
  #define RIGHT_ENC_PIN_B PC5   //pin A5
#endif

#ifdef TEENSY_OPTICAL_ENCODERS
  #define ENCODER_1_PIN_A 9
  #define ENCODER_1_PIN_B 10

  #define ENCODER_2_PIN_A 11
  #define ENCODER_2_PIN_B 12
  
  #define INVALID 0
  
  void initEncoders();
  void encoder_1_ISR();
  void encoder_2_ISR();
#endif

long readEncoder(int i);
void resetEncoder(int i);
void resetEncoders();
