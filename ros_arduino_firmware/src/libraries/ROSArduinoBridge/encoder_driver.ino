/* *************************************************************
   Encoder definitions
   
   Add an "#ifdef" block to this file to include support for
   a particular encoder board or library. Then add the appropriate
   #define near the top of the main ROSArduinoBridge.ino file.
   
   ************************************************************ */
   
#ifdef USE_BASE

#ifdef ROBOGAIA
  /* The Robogaia Mega Encoder shield */
  #include "MegaEncoderCounter.h"

  /* Create the encoder shield object */
  MegaEncoderCounter encoders = MegaEncoderCounter(4); // Initializes the Mega Encoder Counter in the 4X Count mode
  
  /* Wrap the encoder reading function */
  long readEncoder(int i) {
    if (i == LEFT) return encoders.YAxisGetCount();
    else return encoders.XAxisGetCount();
  }

  /* Wrap the encoder reset function */
  void resetEncoder(int i) {
    if (i == LEFT) return encoders.YAxisReset();
    else return encoders.XAxisReset();
  }
#elif defined(ARDUINO_ENC_COUNTER)
  volatile long left_enc_pos = 0L;
  volatile long right_enc_pos = 0L;
  static const int8_t ENC_STATES [] = {0,1,-1,0,-1,0,0,1,1,0,0,-1,0,-1,1,0};  //encoder lookup table
    
  /* Interrupt routine for LEFT encoder, taking care of actual counting */
  ISR (PCINT2_vect){
  	static uint8_t enc_last=0;
        
	enc_last <<=2; //shift previous state two places
	enc_last |= (PIND & (3 << 2)) >> 2; //read the current state into lowest 2 bits
  
  	left_enc_pos += ENC_STATES[(enc_last & 0x0f)];
  }
  
  /* Interrupt routine for RIGHT encoder, taking care of actual counting */
  ISR (PCINT1_vect){
        static uint8_t enc_last=0;
          	
	enc_last <<=2; //shift previous state two places
	enc_last |= (PINC & (3 << 4)) >> 4; //read the current state into lowest 2 bits
  
  	right_enc_pos += ENC_STATES[(enc_last & 0x0f)];
  }
  
  /* Wrap the encoder reading function */
  long readEncoder(int i) {
    if (i == LEFT) return left_enc_pos;
    else return right_enc_pos;
  }

  /* Wrap the encoder reset function */
  void resetEncoder(int i) {
    if (i == LEFT){
      left_enc_pos=0L;
      return;
    } else { 
      right_enc_pos=0L;
      return;
    }
  }
#ifdef TEENSY_OPTICAL_ENCODERS
  volatile long encoder_1_count = 0;
  volatile long encoder_2_count = 0;
  
  volatile byte encoder_1_previous_state = 0;
  volatile byte encoder_2_previous_state = 0;

  const int8_t encoder_lookup[17] = {0, 1, -1, INVALID,
                                     -1, 0, INVALID, 1,
                                     1, INVALID, 0, -1,
                                     INVALID, -1, 1, 0
                                    };
  
  void initializeEncoders() {
    //Set input pins for encoder 1
    pinMode(ENCODER_1_PIN_A, INPUT_PULLUP);
    pinMode(ENCODER_1_PIN_B, INPUT_PULLUP);
  
    //Attach interrupts to the ISR
    attachInterrupt(ENCODER_1_PIN_A, encoder_1_ISR, CHANGE);
    attachInterrupt(ENCODER_1_PIN_B, encoder_1_ISR, CHANGE);
  
    //Set input pins for encoder 2
    pinMode(ENCODER_2_PIN_A, INPUT_PULLUP);
    pinMode(ENCODER_2_PIN_B, INPUT_PULLUP);
  
    //Attach interrupts to the ISR
    attachInterrupt(ENCODER_2_PIN_A, encoder_2_ISR, CHANGE);
    attachInterrupt(ENCODER_2_PIN_B, encoder_2_IDR, CHANGE);
  }

  /**
     Called when either ENCODER_1_PIN_A or ENCODER_1_PIN_B changes. Updates the encoder_1_count.
  */
  void encoder_1_ISR(void) {
    //Get the 2 bits representing the current encoder state.
    byte current_state = (digitalReadFast(ENCODER_1_PIN_A) << 1) + digitalReadFast(ENCODER_1_PIN_B);
    //Use the previous state and current state to generate an index in the lookup,
    //then get that value and add it to the count.
    encoder_1_count += encoder_lookup[encoder_1_previous_state * 4 + current_state];
    //Save the current state for the next time.
    encoder_1_previous_state = current_state;
  }

  /**
     Called when either ENCODER_2_PIN_A or ENCODER_2_PIN_B changes. Updates the encoder_2_count.
  */
  void encoder_2_ISR(void) {
    //Get the 2 bits representing the current encoder state.
    byte current_state = (digitalReadFast(ENCODER_2_PIN_A) << 1) + digitalReadFast(ENCODER_2_PIN_B);
    //Use the previous state and current state to generate an index in the lookup,
    //then get that value and add it to the count.
    encoder_1_count += encoder_lookup[encoder_1_previous_state * 4 + current_state];
    //Save the current state for the next time.
    encoder_1_previous_state = current_state;
  }
                                    
  /* Wrap the encoder reading function */
  long readEncoder(int i) {
    if (i == LEFT) return encoder_1_count;
    else return encoder_2_count;
  }

  /* Wrap the encoder reset function */
  void resetEncoder(int i) {
    if (i == LEFT) encoder_1_count = 0;
    else encoder_2_count = 0;
  }
#else
  #error A encoder driver must be selected!
#endif

/* Wrap the encoder reset function */
void resetEncoders() {
  resetEncoder(LEFT);
  resetEncoder(RIGHT);
}

#endif
