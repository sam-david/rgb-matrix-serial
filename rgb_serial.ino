#include <QueueArray.h>
// Library Includes //
#include <Adafruit_GFX.h>   // Core graphics library
#include <RGBmatrixPanel.h> // Hardware-specific library
//#include <PaintMatrixLogo.h> // Logo string paintMatrixLogo

// Hardware Hookup //
#define OE  9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2
#define D   A3
#define CLK 11
RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false);

#define arr_len( x )  ( sizeof( x ) / sizeof( *x ) )

//int cellQueue[50];
QueueArray <String> cellQueue;
boolean currentlyWriting = false;

void setup() {
  matrix.begin();
  Serial.begin(9600);
  drawSplashScreen(5000);
}

void loop() {
  while (Serial.available()) {
    String serialString = Serial.readString();
    char headChar = serialString.charAt(0);
    if (headChar == 'U') {
      cellQueue.enqueue(serialString);
    } else {
      matrix.setCursor(0,0);
      drawPictureRGB(serialString);  
    }
  }

  if (cellQueue.isEmpty() == false && currentlyWriting == false) {
    currentlyWriting = true;
    String currentString = cellQueue.dequeue();
    drawPixelFromString(currentString);
    currentlyWriting = false;
  }
}

void drawPixelFromString(String currentString) {
  String x = currentString.substring(1,3);
  String y = currentString.substring(3,5);
  int xInt = x.toInt();
  int yInt = y.toInt();
  char r = currentString.charAt(5); 
  char g = currentString.charAt(6);
  char b = currentString.charAt(7);
  int rInt = r;
  int gInt = g;
  int bInt = b;
  matrix.drawPixel(xInt, yInt, matrix.Color333(rInt, gInt, bInt));
}

void drawLogo(int delayLength) {
//  drawPictureRGB(paintMatrixLogo);
  delay(delayLength);
  blankMatrix();
}

void drawSplashScreen(int delayLength) {
  matrix.setCursor(0,0);
  matrix.print("Paint");
  matrix.setCursor(0,10);
  matrix.print("Matrix");
  delay(delayLength);
  blankMatrix();
}


void drawPictureRGB(String pictureString) { 
  int stringIndex = 0;
  for(int x = 0; x < 32; x++) {
    for(int y = 0; y < 32; y++) {
      char r = pictureString.charAt(stringIndex);
      char g = pictureString.charAt(stringIndex + 1);
      char b = pictureString.charAt(stringIndex + 2);
      matrix.drawPixel(x, y, matrix.Color333(r,g,b));
      stringIndex += 3;
    }
  }
}

void blankMatrix()
{
  matrix.fillScreen(0);
}

void endSerial() {
  Serial.end();
}

