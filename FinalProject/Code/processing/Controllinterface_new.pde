import processing.serial.*;
import controlP5.*;

Serial myPort; // Create object from Serial class
int val; // Data received from the serial port
int l = 70;
ControlP5 cp5;
Button btn1, btn2, btn3, btn4, btn5, btn6, btn7, btn8;
long prevSendTime = 0;

void setup()
{
  size(400, 600);
  noStroke();

  String[] portsAvailable = Serial.list(); // Get a List of all the serial ports available
  for (int i=0; i < portsAvailable.length; i++) { // Iterate over the list and print them on console for selection
    print("[" + i + "]\t");
    println(portsAvailable[i]);
  }
  String portName = portsAvailable[4]; // "4" is our selection
  myPort = new Serial(this, portName, 9600); // Connect to the specified port


  cp5 = new ControlP5(this);
  btn1 = cp5.addButton("rotate cw")
    .setPosition(100, 100)
      .setSize(l, 19);
  btn2 = cp5.addButton("rotate ccw")
    .setPosition(100, 120)
      .setSize(l, 19);
  btn3 = cp5.addButton("tilt cw")
    .setPosition(250, 100)
      .setSize(l, 19);
  btn4 = cp5.addButton("tilt ccw")
    .setPosition(250, 120)
      .setSize(l, 19);
  btn5 = cp5.addButton("slide r")
    .setPosition(100, 200)
      .setSize(l, 19);
  btn6 = cp5.addButton("slide l")
    .setPosition(100, 220)
      .setSize(l, 19);
  btn7 = cp5.addButton("slide/rotate r")
    .setPosition(250, 200)
      .setSize(l, 19);
  btn8 = cp5.addButton("slide/rotate l")
    .setPosition(250, 220)
      .setSize(l, 19);
}
void draw() {
  if (btn1.isPressed()) {
    sendCMD('A', 1);
  } 
  if (btn2.isPressed()) {
    sendCMD('A', 2);
  } 
  if (btn3.isPressed()) {
    sendCMD('B', 3);
  } 
  if (btn4.isPressed()) {
    sendCMD('B', 4);
  } 
  if (btn5.isPressed()) {
    sendCMD('C', 5);
  }
  if (btn6.isPressed()) {
    sendCMD('C', 6);
  }
  if (btn7.isPressed()) {
    sendCMD('D', 7);
  }
  if (btn8.isPressed()) {
    sendCMD('D', 8);
  }
}

//public void sendCMD(char cmd, int value) {
//  print("SENDING CMD: ");
//  print(cmd);
//  print(" VALUE: ");
//  print(value);
//  print(" >> ");
//  print(cmd);
//  println(str(value));
//  myPort.write(cmd);
//  myPort.write(String.valueOf(value));
//  myPort.write('\n');
//}

public void sendCMD(char cmd, int value) {
  long currentSendTime = millis();
  
  int period = 1;

  if (currentSendTime - prevSendTime > period) {
    print("SENDING CMD: ");
    print(cmd);
    print(" VALUE: ");
    print(value);
    print(" >> ");
    print(cmd);
    println(str(value));
    myPort.write(cmd);
    myPort.write(String.valueOf(value));
    myPort.write('\n');
  } 
  else {
    //    println("Nothing");
  }
}

void serialEvent(Serial myPort) {
  String myString = myPort.readStringUntil('\n');
  if (myString != null) {
    print("RECEIVD CMD: ");
    println(myString);
  }
}

