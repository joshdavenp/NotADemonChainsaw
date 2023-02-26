/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// GPS21                gps           21              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/


void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

void setMotors(int prct){
  frontLeftDrive.setVelocity(prct, pct);
  backLeftDrive.setVelocity(prct, pct);
  frontRightDrive.setVelocity(prct, pct);
  backRightDrive.setVelocity(prct, pct);
}

void turnRoller(int amount){
  rollerMotor.spinFor(reverse, amount, degrees, false);
}

void allForward(int dist){
  frontLeftDrive.spinFor(forward, dist, degrees, false);
  frontRightDrive.spinFor(reverse, dist, degrees, false);
  backRightDrive.spinFor(reverse, dist, degrees, false);
  backLeftDrive.spinFor(forward, dist, degrees);
}

void allForwardc(int dist){
  frontLeftDrive.spinFor(forward, dist, degrees, false);
  frontRightDrive.spinFor(reverse, dist, degrees, false);
  backRightDrive.spinFor(reverse, dist, degrees, false);
  backLeftDrive.spinFor(forward, dist, degrees, false);
}


void allStart(){
  frontLeftDrive.spin(forward);
  frontRightDrive.spin(reverse);
  backRightDrive.spin(reverse);
  backLeftDrive.spin(forward);
}

void allBrake(){
  frontLeftDrive.stop(brake);
  frontRightDrive.stop(brake);
  backRightDrive.stop(brake);
  backLeftDrive.stop(brake);
}

void backLeftPivot(float dist){
  frontLeftDrive.spinFor(reverse, dist, degrees, false);
  frontRightDrive.spinFor(forward, dist, degrees, false);
  backRightDrive.spinFor(forward, dist, degrees, false);
  backLeftDrive.spinFor(forward, dist, degrees);
}

void tankTurn(int dist){
  frontLeftDrive.spinFor(forward, dist, degrees, false);
  frontRightDrive.spinFor(forward, dist, degrees, false);
  backRightDrive.spinFor(forward, dist, degrees, false);
  backLeftDrive.spinFor(forward, dist, degrees);
}

void autoMechan(int z){
  frontLeftDrive.setVelocity(100, pct);
  backLeftDrive.setVelocity(200, pct);
  frontRightDrive.setVelocity(100, pct);
  backRightDrive.setVelocity(200, pct);
  frontLeftDrive.spinFor(reverse,z,deg, false);
  frontRightDrive.spinFor(reverse,z,deg, false);
  backLeftDrive.spinFor(forward,z,deg, false);
  backRightDrive.spinFor(forward,z,deg, false);
}

void expandSkill (){
  expandMotor.spin(reverse);
}


void allStop(){
  frontLeftDrive.stop(hold);
  frontRightDrive.stop(hold);
  backLeftDrive.stop(hold);
  backRightDrive.stop(hold);
}

void startLauncher(){
  launcherR.spin(forward);
  launcherL.spin(reverse);
}

void turnAndIntake(long z){
  conveyorMotor.spinFor(forward,z,deg, false);
}

void mechaniumRight(int howFar){
  frontLeftDrive.spinFor(forward,howFar,deg, false);
  frontRightDrive.spinFor(forward,howFar,deg, false);
  backLeftDrive.spinFor(reverse,howFar,deg, false);
  backRightDrive.spinFor(reverse,howFar,deg);
}

void mechaniumLeft(int howFar){
  frontLeftDrive.spinFor(reverse,howFar,deg, false);
  frontRightDrive.spinFor(reverse,howFar,deg, false);
  backLeftDrive.spinFor(forward,howFar,deg, false);
  backRightDrive.spinFor(forward,howFar,deg, false);
}
// the turn and intake are not spining enough
void shortSide (){
  launcherL.setVelocity(100, pct);
  launcherL.setVelocity(100, pct);
  startLauncher();
  wait(2, sec);
  turnAndIntake(1000000);
  allForward(50);
  allStop();
  turnAndIntake(90);
}

void longSide (){
  launcherL.setVelocity(100, pct);
  launcherL.setVelocity(100, pct);
  mechaniumRight(90);
  allForward(90);
  allStop();
  turnAndIntake(90);
  startLauncher();
  turnAndIntake(1000);
}

void skills (){
  allForwardc(100);
  setMotors(100);
  turnRoller(100);
  allForward(-100);
  mechaniumRight(600);
  backLeftPivot(520);
  tankTurn(625);
  mechaniumRight(600);
  allForward(500);
  setMotors(25);
  allForward(50);
  turnRoller(-120);
  setMotors(100);
  allForward(-600);
  tankTurn(-450);
  expandSkill();
}

void driveForward(int duration){
  
  frontLeftDrive.spin(forward);
  frontRightDrive.spin(reverse);
  backLeftDrive.spin(forward);
  backRightDrive.spin(reverse);

}


void autonomous(void) {
  // autoMechan(10000);
  //shortSide();
  skills();
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                        */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                 5                          */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/


int conveyor = 0;

void conveyorStart (){
  if (controller1.ButtonL1.pressing()){
    conveyor =  1;
  }
  if(controller1.ButtonL2.pressing()){
    conveyor = 0;
  }
  if(controller1.ButtonRight.pressing()){
    conveyor = -1;
  }
}

void conveyorControl(){
  //conveyorStart();
  if (conveyor ==  1) {
    conveyorMotor.spin(vex::forward, 100, velocityUnits::pct);
  }
  else if (conveyor ==  -1){
    conveyorMotor.spin(vex::reverse, 100, velocityUnits::pct);
  }
  else if (conveyor ==  0){
    if (controller1.ButtonA.pressing()){
      conveyorMotor.spin(vex::forward, 50, pct);
    }                 
    else if (controller1.ButtonB.pressing()){
      conveyorMotor.spin(vex::reverse, 50, pct);
    }
    else{
      conveyorMotor.stop();
    }
  }
}

void rollerControl (float i){
 rollerMotor.spin(vex::reverse, 50 * i, velocityUnits::pct);
}

bool fastRoller = true;

void rollerSpeed(){
  if(controller1.ButtonL1.pressing()){
    fastRoller = false;
  }
  else if (controller1.ButtonL2.pressing()) {
    fastRoller = true;
  }
}

//allows for forward and reverse control of the roller
void rollerThing(){ 
  rollerSpeed();
  if(controller1.ButtonA.pressing()){
    if (fastRoller == true){
      rollerControl(1);
    }
    else if (fastRoller == false){
      rollerControl(.5);
    }
  }
  else if(controller1.ButtonB.pressing()){
    if (fastRoller == true){
      rollerControl(-1);
    }
    else if (fastRoller == false){
      rollerControl(-.5);
    }
  }
  else{
    rollerMotor.stop();
  }
}

//prints to the brain
void printDrive (int input, int another){
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1,1);
  Brain.Screen.print(input);
  Brain.Screen.setCursor(1,32);
  Brain.Screen.print(another);
}

// void drivecontrol (){
//   int axis3 = controller1.Axis3.position();
//   int axis4 = controller1.Axis4.position();
//   int leftOutput = axis4 + axis3;
//   int rightOutput = axis4 - axis3;

//   leftDrive.spin(vex::forward, leftOutput , vex::percent);
//   rightDrive.spin(vex::forward, rightOutput , vex::percent);
//   rightOutput = rightOutput * -1;
//   printDrive(leftOutput, rightOutput);
// }

void getLocation()
{
  float x = GPSSensor.xPosition(mm) / 1000;
  float y = GPSSensor.yPosition(mm) / 1000;
  float z = GPSSensor.heading();

  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1,1);
  Brain.Screen.print("X value = ");
  Brain.Screen.print(x);
  Brain.Screen.setCursor(2, 1);
  Brain.Screen.print("Y value = ");
  Brain.Screen.print(y);
  Brain.Screen.setCursor(3, 1);
  Brain.Screen.print("Rotation = ");
  Brain.Screen.print(z);
}

void crazyIdea (int xvalue, int yvalue){
 double T = atan(yvalue/xvalue);
 int z = GPSSensor.heading();

 double axis3 = 100 * sin(T - z);
 double axis4 = 100 * cos(T - z);
 double axis1 = 0;
  int frontRightWheel = axis3 - axis4 - axis1;
  int frontLeftWheel = axis3 + axis4 + axis1;
  int backRightWheel = axis3 + axis4 - axis1;
  int backLeftWheel = axis3 - axis4 + axis1;

  frontLeftDrive.spin(vex::forward, frontLeftWheel, vex::percent);
  backLeftDrive.spin(vex::forward, backLeftWheel, vex::percent);
  frontRightDrive.spin(vex::reverse, frontRightWheel, vex::percent);
  backRightDrive.spin(vex::reverse, backRightWheel, vex::percent);
}

void expand (){
  if(controller1.ButtonLeft.pressing()){
    expandMotor.spin(reverse, 100, pct); 
  }
  else{
    expandMotor.stop();
  }
}

bool whichWay = 0;

void mechaniumWheels(){
  int axis1 = controller1.Axis1.position();
  int axis3 = controller1.Axis3.position();
  int axis4 = controller1.Axis4.position();
  
  int frontRightWheel = axis3 - axis4 - axis1;
  int frontLeftWheel = axis3 + axis4 + axis1;
  int backRightWheel = axis3 + axis4 - axis1;
  int backLeftWheel = axis3 - axis4 + axis1;
  
  if (controller1.ButtonUp.pressing()){
    whichWay = 1;
  }
  if (controller1.ButtonDown.pressing()){
    whichWay = 0;
  }
  if (whichWay == 0){
    frontLeftDrive.spin(vex::forward, frontLeftWheel, vex::percent);
    backLeftDrive.spin(vex::forward, backLeftWheel, vex::percent);
    frontRightDrive.spin(vex::reverse, frontRightWheel, vex::percent);
    backRightDrive.spin(vex::reverse, backRightWheel, vex::percent);
  }
  if (whichWay == 1){
  frontLeftDrive.spin(vex::reverse, frontLeftWheel, vex::percent);
  backLeftDrive.spin(vex::reverse, backLeftWheel, vex::percent);
  frontRightDrive.spin(vex::forward, frontRightWheel, vex::percent);
  backRightDrive.spin(vex::forward, backRightWheel, vex::percent);
  }
}

void acklenNator (){
  float x = -1 * (GPSSensor.xPosition(mm) -  1550);
  float wheelSpeed = (100 * (x/3100));
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1,1);
  Brain.Screen.print(" Distance from wall= ");
  Brain.Screen.print(x);
  Brain.Screen.print(" speed= ");
  Brain.Screen.print(wheelSpeed);
  if (controller1.ButtonA.pressing()){
    frontLeftDrive.spin(vex::forward, wheelSpeed, vex::percent);
    backLeftDrive.spin(vex::forward, wheelSpeed, vex::percent);
    frontRightDrive.spin(vex::reverse, wheelSpeed, vex::percent);
    backRightDrive.spin(vex::reverse, wheelSpeed, vex::percent);
  }
  if (controller1.ButtonR1.pressing()){
    crazyIdea(0,0);
  }
  else{
   mechaniumWheels();
  }
}


void displayWheels (){
  int axis1 = controller1.Axis1.position();
  int axis3 = controller1.Axis3.position();
  int axis4 = controller1.Axis4.position();

  int frontRightWheel = axis3 - axis4 - axis1;
  int frontLeftWheel = axis3 + axis4 + axis1;
  int backRightWheel = axis3 + axis4 - axis1;
  int backLeftWheel = axis3 - axis4 + axis1;

  Brain.Screen.clearScreen();
  
  Brain.Screen.print("Front right Wheel: ");
  Brain.Screen.print(frontRightWheel);
  Brain.Screen.print(" Front left Wheel: ");
  Brain.Screen.print(frontLeftWheel);
  Brain.Screen.print(" Back right Wheel: ");
  Brain.Screen.print(backRightWheel);
  Brain.Screen.print(" Back left Wheel: ");
  Brain.Screen.print(backLeftWheel);
}



void robotTurn (int v){
  frontLeftDrive.spin(vex::forward, v, vex::percent);
  backLeftDrive.spin(vex::forward, v, vex::percent);
  frontRightDrive.spin(vex::reverse, -v, vex::percent);
  backRightDrive.spin(vex::reverse, -v, vex::percent);
}   


void robotAdvance (int v){
  frontLeftDrive.spin(vex::forward, v, vex::percent);
  backLeftDrive.spin(vex::forward, v, vex::percent);
  frontRightDrive.spin(vex::reverse, v, vex::percent);
  backRightDrive.spin(vex::reverse, v, vex::percent);
}

float numberAdjust (float deg){
  if (deg > 360){
    deg =  deg -  360;
  }
  else if (deg < 0){
    deg = deg + 360;
  }
  return deg;
}


//x= -1.12 y= -1.27 for one of the rollers
//right is 1 left is 0
bool isTurningRight = 1;
float turnSpeed = 50;
float margin = 45;

void posisioning (float target){
  float x = GPSSensor.xPosition(mm);
  float y = GPSSensor.yPosition(mm);
  float z = GPSSensor.heading();
  
  controller1.Screen.clearScreen();
  controller1.Screen.setCursor(1,1);
  controller1.Screen.print("Heading: ");
  controller1.Screen.print(z);
  controller1.Screen.setCursor(2,1);
  controller1.Screen.print("Logic: ");
  if (z > numberAdjust(target + margin) && z < numberAdjust(target + 180)){
    controller1.Screen.print(numberAdjust(target + margin));
    controller1.Screen.print(" < ");
    controller1.Screen.print(z);
    controller1.Screen.print(" < ");
    controller1.Screen.print(numberAdjust(target + 180));
    controller1.Screen.setCursor(3,1);
    controller1.Screen.print("Turning Left");
  }
  else if (z <= numberAdjust(target + margin) && z > numberAdjust(target + 180)){
    controller1.Screen.print(numberAdjust(target + margin));
    controller1.Screen.print(" < ");
    controller1.Screen.print(z);
    controller1.Screen.print(" < ");
    controller1.Screen.print(numberAdjust(target + 180));
    controller1.Screen.setCursor(3,1);
    controller1.Screen.print("Turning Right");
  }

  Brain.Screen.setCursor(1,1);
  Brain.Screen.clearScreen();
  Brain.Screen.print("x = ");
  Brain.Screen.print(x);
  Brain.Screen.print("y = ");
  Brain.Screen.print(y);
  Brain.Screen.print("turn = ");
  Brain.Screen.print(z);


  if(isTurningRight == 1){  
    Brain.Screen.print("Turn Right");
    robotTurn(turnSpeed);
    if(z > numberAdjust(target + margin) && z < numberAdjust(target + 180)){
      Brain.Screen.print("Reversing");
      isTurningRight = 0;
      turnSpeed = turnSpeed * .5;
      margin = margin * .5;
    }
  }
  else{
    Brain.Screen.print("Turn Left");
    robotTurn(-1 * turnSpeed);
    if(z <= numberAdjust(target - margin) && z > numberAdjust(target + 180)){
      Brain.Screen.print("Reversing");
      isTurningRight = 1;
      turnSpeed = turnSpeed * .5;
      margin = margin * .5;
    }
  }
  controller1.Screen.setCursor(4,1);
  controller1.Screen.print(turnSpeed);

}

void screenDisplay(){
  int x = GPSSensor.xPosition(mm);
  int y = GPSSensor.yPosition(mm);
  int Rotation = GPSSensor.heading();

  controller1.Screen.clearScreen();
  controller1.Screen.setCursor(1,1);
  controller1.Screen.print("x= ");
  controller1.Screen.print(x);
  controller1.Screen.setCursor(2,1);
  controller1.Screen.print("y= ");
  controller1.Screen.print(y);
  controller1.Screen.setCursor(3,1);
  controller1.Screen.print("Rotation= ");
  controller1.Screen.print(Rotation);
}

bool launchControl = false;
bool launchFast = true;
int x = 100;

void launcher (){
  if (controller1.ButtonR1.pressing()){
    launchControl = true;
  }
  if (controller1.ButtonR2.pressing()){
    launchControl = false;
  }
  if (controller1.ButtonX.pressing()){
    launchFast = false;
  }
  if (controller1.ButtonY.pressing()){
    launchFast = true;
  }
  if (launchControl){
    if(launchFast){ 
      launcherR.spin(forward, x,velocityUnits::pct);
      launcherL.spin(reverse, x,velocityUnits::pct);
    }
    if(!launchFast){ 
      launcherR.spin(forward, x/2 ,velocityUnits::pct);
      launcherL.spin(reverse, x/2 ,velocityUnits::pct);
    }
  }
  if(!launchControl){
    launcherR.stop();
    launcherL.stop();
  }
  
}

void troubleShooting(){
 testMotor.spin(forward);
 controller1.Screen.clearScreen();
 controller1.Screen.setCursor(1,1);
 controller1.Screen.print(testMotor.current(pct));
}

void whatColor(){
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1,1);
  colorSensor.takeSnapshot(colorSensor__REDSIDE);
  if (colorSensor.objectCount >= 1){
    Brain.Screen.print("YAYAYAYAYAYAYAYAYAYAYAYAYAYAYAY");
  }
  else{
    Brain.Screen.print(";-;");
  }
}

void startMatch (){
  allForwardc(100);
  setMotors(100);
  turnRoller(100);
  allForward(-100);
  mechaniumRight(600);
  backLeftPivot(520);
  tankTurn(625);
  mechaniumRight(600);
  allForward(500);
  setMotors(25);
  allForward(50);
  turnRoller(-120);
  setMotors(100);
  allForward(-600);
  tankTurn(-450);
}

void usercontrol(void) {
  // User control code here, inside the loop
  Brain.Timer.reset();
  startMatch();
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.
    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................
    // conveyorStart();
    // conveyorControl(); //intake
    launcher(); //output launcher
    mechaniumWheels(); //drivecontrol
    expand(); //Expander
    troubleShooting();

    rollerThing();
    //roller
    // getLocation();
    // //posisioning(180);
    // //acklenNator(); //drivercontrol
    // //screenDisplay();



    // whatColor();

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}


int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
