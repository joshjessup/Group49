#include <DSPI.h>
#include <OBCI32_SD.h>
#include <EEPROM.h>
#include <OpenBCI_32bit_Library.h>
#include <OpenBCI_32bit_Library_Definitions.h>


// Booleans Required for SD_Card_Stuff.ino
boolean addAccelToSD = false; // On writeDataToSDcard() call adds Accel data to SD card write
boolean addAuxToSD = false; // On writeDataToSDCard() call adds Aux data to SD card write
boolean SDfileOpen = false; // Set true by SD_Card_Stuff.ino on successful file open

void setup() {
  // Bring up the OpenBCI Board
  //board.begin();
  board.beginDebug();
  board.useAccel(false);
  board.useTimeStamp(true);   // timestamping to data
  board.setSampleRate(1000);  // changing sampling rate
   // pre configured settings for plug and play
  Serial.write('x1020001X');
  Serial.write('x2020001X');
  Serial.write('x3020001X');
  Serial.write('x4020001X');
  Serial.write('x5020001X');
  Serial.write('x6020001X');
  Serial.write('x7020001X');
  Serial.write('x8020001X');
  delay(100);
  Serial.write('a');  // configuring SD card 
  Serial.write('b');  // start data streaming
  // Bring up wifi
  //wifi.begin(true, true);
}

void loop() {
  if (board.streaming) {
    if (board.channelDataAvailable) {
      // Read from the ADS(s), store data, set channelDataAvailable flag to false
      board.updateChannelData();
      // Verify the SD file is open
      if(SDfileOpen) {
        // Write to the SD card, writes aux data
        board.printlnSerial(board.boardChannelDataInt[0]);
        writeDataToSDcard(board.sampleCounter);
      }

    }
  }

  // Check serial 0 for new data
  if (board.hasDataSerial0()) {
    // Read one char from the serial 0 port
    char newChar = board.getCharSerial0();

    // Send to the sd library for processing
    sdProcessChar(newChar);

    // Send to the board library
    board.processChar(newChar);
  }

  if (board.hasDataSerial1()) {
    // Read one char from the serial 1 port
    char newChar = board.getCharSerial1();

    // Send to the sd library for processing
    sdProcessChar(newChar);

    // Read one char and process it
    board.processChar(newChar);
  }

  // Call the loop function on the board
  board.loop();

}
