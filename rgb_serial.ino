// Library Includes //
//////////////////////
#include <Adafruit_GFX.h>   // Core graphics library
#include <RGBmatrixPanel.h> // Hardware-specific library
//#include <PaintMatrixLogo.h> // Logo string paintMatrixLogo

/////////////////////
// Hardware Hookup //
/////////////////////
// R0, G0, B0, R1, G1, B1 should be connected to pins 
// 2, 3, 4, 5, 6, and 7 respectively. Their pins aren't defined,
// because they're controlled directly in the library. These pins
// can be moved (somewhat):
#define OE  9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2
#define D   A3 // Comment this line out if you're using a 32x16
// CLK can be moved but must remain on PORTB(8, 9, 10, 11, 12, 13)
#define CLK 11  // MUST be on PORTB!

// Instantiate the RGBmatrixPanel class
RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false);

void setup() {
  matrix.begin();
  Serial.begin(9600);
//  drawLogo(7000);
  drawSplashScreen(5000);
//    Serial.end();
}

void loop() {
  while (Serial.available()) {
    String testerString = Serial.readString();
    char headChar = testerString.charAt(0);
    if (headChar == 'U') {
      String x = testerString.substring(1,3);
      String y = testerString.substring(3,5);
      char r = testerString.charAt(5); 
      char g = testerString.charAt(6);
      char b = testerString.charAt(7);
      int rInt = r;
      int gInt = g;
      int bInt = b;
      matrix.drawPixel(x.toInt(), y.toInt(), matrix.Color333(rInt, gInt, bInt));
      Serial.write("W");
    } else {
      matrix.setCursor(0,0);
      drawPictureRGB(testerString);  
    }
  }
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
