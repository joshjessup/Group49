#include <DSPI.h>
#include <OpenBCI_32bit_Library.h>
#include <OpenBCI_32Bit_Library_Definitions.h>

// Commands for starting:
// 2345678
// x1020001X
// b

void setup() {
  // Bring up the OpenBCI Board
  board.beginDebug();
  // Don't use the accel
  board.useAccel(false);
  board.useTimeStamp(false);
}

void loop() {
//  Serial.println(board.streaming + "   " + board.channelDataAvailable);
  if (board.streaming) {
    if (board.channelDataAvailable) {
      // Read from the ADS(s), store data, set channelDataAvailable flag to false
      board.updateChannelData();
      // Send that channel data
//      board.printlnSerial(board.boardChannelDataRaw[0]);
      board.printlnSerial(board.boardChannelDataInt[0]);
//      board.curPacketType = PACKET_TYPE_RAW_AUX;
//      board.sendChannelDataSerial();
      // board.sendChannelData();
    }
  }
  // Check the serial ports for new data
  if (board.hasDataSerial0()) board.processChar(board.getCharSerial0());
  if (board.hasDataSerial1()) board.processChar(board.getCharSerial1());
  board.loop();
}
