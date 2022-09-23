void ring_led(int r, int g, int b){
  for(int index = 0 ; index < MAXIMUM_NUM_NEOPIXELS ; index++){
      p.neoPixelSetValue(index,r, g, b, true);//number , r, g, b ,true
      delay(100);
    }
}
