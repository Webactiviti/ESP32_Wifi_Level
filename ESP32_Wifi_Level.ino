//-------------------------
//
// Gestion ddu niveau de puissance
// wifi avec connection UDP sur
// un mobile Android 
// 
//--------------------------

#include <WiFi.h>


//--------------------------------------------------
// WiFi network name and password hotspot mobile
char * ssid = "votrereseau";
char * pwd = "password";
IPAddress remote_IP(192, 168, 43, 1); //IP du mobile
unsigned int remote_port = 5555; // Port sur le mobile
unsigned int local_port = 10000; // Port local de la carte ESP32

WiFiUDP udp; //create UDP instance


void afficheLevelWifi(){

  wifi_power_t levelWifi = WiFi.getTxPower();
  String strLeveWifi="";

   switch (levelWifi){
    case  WIFI_POWER_19_5dBm : // 19.5dBm
      strLeveWifi ="19.5dBm";
      break;
      
    case  WIFI_POWER_19dBm :// 19dBm
      strLeveWifi ="19dBm";
      break;
    
    case WIFI_POWER_18_5dBm :// 18.5dBm
      strLeveWifi ="18.5dBm";
      break; 
         
    case WIFI_POWER_17dBm :// 17dBm
      strLeveWifi ="17dBm";
      break;
          
    case WIFI_POWER_15dBm :// 15dBm
      strLeveWifi ="15dBm";
      break;
          
    case WIFI_POWER_13dBm :// 13dBm
      strLeveWifi ="13dBm";
      break;
          
    case WIFI_POWER_11dBm :// 11dBm
      strLeveWifi ="11dBm";
      break;
          
    case WIFI_POWER_8_5dBm :// 8.5dBm
      strLeveWifi ="8.5dBm";
      break;
    case WIFI_POWER_7dBm : // 7dBm
      strLeveWifi ="7dBm";
      break;
          
    case WIFI_POWER_5dBm :// 5dBm
      strLeveWifi ="5dBm";
      break;
      
    case WIFI_POWER_2dBm :// 2dBm
      strLeveWifi ="2dBm ";
      break;
          
    case WIFI_POWER_MINUS_1dBm : // -1dBm
      strLeveWifi ="MINUS 1dBm";
      break;

    default :
      strLeveWifi ="Non défini";
    
   }

   
  Serial.print("\nLevel WIFI POWER  : ");
  Serial.println (strLeveWifi);
}


void setup() {
  // put your setup code here, to run once:

  
  delay(100);
  Serial.begin(115200);
  Serial.println(" *** ###  ---  ESP32 WIFI LEVEL  --- ### *** ");

  WiFi.begin(ssid, pwd);  // Connexion au hotspot

  Serial.print("\n --- Avant modification niveau wifi N°1 --- ");
  afficheLevelWifi();

  if (WiFi.setTxPower(WIFI_POWER_MINUS_1dBm)){
    delay(5);
  } else {
    Serial.println("Pas de changement du niveau Wifi");
  }

  Serial.print ("\n --- Après modification niveau wifi N°2 --- ");
  afficheLevelWifi();


  if (WiFi.setTxPower(WIFI_POWER_5dBm )){
    delay(5);
  } else {
    Serial.println("Pas de changement du niveau Wifi");
  }

  Serial.print ("\n --- Après modification niveau wifi --- ");
  afficheLevelWifi();

  

  while (WiFi.status() != WL_CONNECTED) { // Boucle d'attente de connexion au hotspot mobile
    delay(500);
    Serial.print(".");
  }

  Serial.print("Connexion à ");
  Serial.println(ssid);
  Serial.print("Adresse IP locale : ");
  Serial.println(WiFi.localIP());
}








void loop() {
  // put your main code here, to run repeatedly:

  uint8_t buff_ui[12]="Message UDP";// message de 11 caractères
  
  udp.beginPacket(remote_IP, remote_port);
  udp.write(buff_ui,11 );
  udp.endPacket();

  delay(2000);

}
