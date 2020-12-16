/***************************************************************
   Motor driver function definitions - by James Nugen
   *************************************************************/

#ifdef L298_MOTOR_DRIVER
  #define RIGHT_MOTOR_BACKWARD 5
  #define LEFT_MOTOR_BACKWARD  6
  #define RIGHT_MOTOR_FORWARD  9
  #define LEFT_MOTOR_FORWARD   10
  #define RIGHT_MOTOR_ENABLE 12
  #define LEFT_MOTOR_ENABLE 13
#endif

#ifdef SABERTOOTH_MOTOR_DRIVER
  #define SABERTOOTH_BAUD 9600
  #define LEFT_LOW 1
  #define LEFT_HIGH 127
  #define RIGHT_LOW 128
  #define RIGHT_HIGH 255
  #define MOTOR_STOP 0x00

void initMotorController();
void setMotorSpeed(int i, int spd);
void setMotorSpeeds(int leftSpeed, int rightSpeed);
