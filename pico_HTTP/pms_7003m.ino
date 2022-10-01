void get_air() {

  //Serial.println("air check! wait for second!");

  if (Serial1.available()) { //wait for data income >=32
    int i = 0;

    //initialize first two bytes with 0x00
    pmsbytes[0] = 0x00;
    pmsbytes[1] = 0x00;

    for (i = 0; i < 32 ; i++) {
      pmsbytes[i] = Serial1.read();

      //check first two bytes - HEAD_1 and HEAD_2, exit when it's not normal and read again from the start
      if ( (i == 0 && pmsbytes[0] != HEAD_1) || (i == 1 && pmsbytes[1] != HEAD_2) ) {
        //Serial.println("data error!");
        break;
      }
    }

    if (i > 2) { // only when first two stream bytes are normal
      if (pmsbytes[29] == 0x00) { // only when stream error code is 0
        PM1_0_val = (pmsbytes[10] << 8) | pmsbytes[11]; // pmsbytes[10]:HighByte + pmsbytes[11]:LowByte => two bytes
        PM2_5_val = (pmsbytes[12] << 8) | pmsbytes[13]; // pmsbytes[12]:HighByte + pmsbytes[13]:LowByte => two bytes
        PM10_val = (pmsbytes[14] << 8) | pmsbytes[15]; // pmsbytes[14]:HighByte + pmsbytes[15]:LowByte => two bytes

        Serial.print("PMS7003 sensor - PM1.0 : ");
        Serial.print(PM1_0_val);
        Serial.print(" ug/m^3,  PM2.5 : ");
        Serial.print(PM2_5_val);
        Serial.print(" ug/m^3,  PM10 : ");
        Serial.print(PM10_val);
        Serial.println(" ug/m^3");
        offset = 20;
        if (mode_status == "0") {
          if (PM2_5_val <= 15 * offset) { //blue
            ring_led(0, 0, 50);
          } else if ((PM2_5_val > 15 * offset) && (PM2_5_val <= 35 * offset)) { // green
            ring_led(0, 50, 0);
          } else if ((PM2_5_val > 35 * offset) && (PM2_5_val <= 75 * offset) ) { // yellow
            ring_led(50, 50, 0);
          } else if (PM2_5_val > 75 * offset) { //red
            ring_led(50, 0, 0);
          }
        }
        //get_data();
      } else {
        //Serial.println("Error skipped..");
      }
    } else {
      //Serial.println("Bad stream format error");
    }
  }
}
