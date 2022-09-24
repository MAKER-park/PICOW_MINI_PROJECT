                             
void t3_Callback(void *ptr_t3)
{
       
  t3.setText(temp.c_str());  
}

void t4_Callback(void *ptr_t4)
{
  // static char htemp[]=;     
 // dtostrf(t4, 6, 2, htemp);    
  t4.setText(hmet.c_str());
  Serial.print("apple");  
}
void t5_Callback(void *ptr_t5)
{
  // static char dust[6]="70";     
 // dtostrf(t5, 6, 2, dust);    
  t5.setText(dust.c_str());  
}
