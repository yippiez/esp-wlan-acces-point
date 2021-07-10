// Program to use esp8266 as a quick WLAN acces point with a CLI interface


#include <ESP8266WiFi.h>
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager WiFi Configuration Magic

extern "C" {
  #include<user_interface.h>
}

// wifi default parameters
const char* def_ssid = "WLAN-POINT";
const char* def_pass = "espwlanpoint";

// cli variables
String cli_input = "";
bool input_done = false;

WiFiManager wifiManager;

// https://www.esp8266.com/ modified
void showConnections(){
  
  unsigned char number_client;
  station_info *stat_info;
  
  ipv4_addr *IPaddress;
  IPAddress address;
  int i=1;
  
  number_client= wifi_softap_get_station_num();
  stat_info = wifi_softap_get_station_info();
  
  Serial.print(" Total Connected Clients are = ");
  Serial.println(number_client);
  
    while (stat_info != NULL) {
    
      IPaddress = &stat_info->ip;
      address = IPaddress->addr;
      
      Serial.print("client= ");
      
      Serial.print(i);
      Serial.print(" IP adress is = ");
      Serial.print((address));
      Serial.print(" with MAC adress is = ");
      
      Serial.print(stat_info->bssid[0],HEX);Serial.print(" ");
      Serial.print(stat_info->bssid[1],HEX);Serial.print(" ");
      Serial.print(stat_info->bssid[2],HEX);Serial.print(" ");
      Serial.print(stat_info->bssid[3],HEX);Serial.print(" ");
      Serial.print(stat_info->bssid[4],HEX);Serial.print(" ");
      Serial.print(stat_info->bssid[5],HEX);Serial.print(" ");
      
      stat_info = STAILQ_NEXT(stat_info, next);
      i++;
      Serial.println();
    }
    
  delay(500);
}

void setup() {

  Serial.begin(115200);
  Serial.println();
  Serial.println("Booting Device...");
  wifiManager.autoConnect(def_ssid, def_pass);
  cli_input.reserve(200);
  
}

void loop() {
  if(input_done){
   
   Serial.println(cli_input);

   if(cli_input == "status\n")
      showConnections();
      
   cli_input = "";
   input_done = false; 

  
   
  }
}


void serialEvent(){

    while(Serial.available()){
        char inp = (char)Serial.read();
        cli_input += inp;

        if(inp == '\n')
          input_done = true;
          
    }
    
}
