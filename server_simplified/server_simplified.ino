#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
const char* ssid = "....";
const char* password = "....";

ESP8266WebServer server(80);

//This form will be sent to your browser, when the device is locked
String form_closed =
   "<html>"
    "<head>"
    "</head>"
    "<body>"
  "<center>"
  "<img width='200px' src='http://www.endlessicons.com/wp-content/uploads/2012/12/lock-icon-614x460.png'>"
  "<form action='msg'> <p>Do you really need that chocolate?</p>"
  "<select name='msg'>"
  "<option value='open'>Yesssssss</option>"
  "<option value='close'>No, I continue my diet...</option>"
  "</select>"
  "<input type='submit' value='Open'></form>"
  "</center>"
  "</body>"
  "</html>";

 //this form will be sent to your browser, when the device is open
 //there is a redirect link in the html to the main page
String form_open = 
  "<html>"
    "<head>"
    "<meta http-equiv='refresh' content='3;url=/' />"
    "</head>"
    "<body>"
      "<center>"
      "<h1>Voillaaaa </h1>"
      "<img width='400px' src='http://www.clipartreview.com/_images_300/A_refrigerator_with_an_open_door_100429-171689-937009.jpg'>"
      "</center>"
     "</body>"
    "</html>";
    
void handleMessage(){
    String state= server.arg("msg");
    Serial.println(state);
    if(state=="close"){
      server.send(200, "text/html", form_closed);
    }    
    else{
        server.send(200, "text/html", form_open);
        //after 3 seconds closes back either way
        delay(3000);
        Serial.println("close");
    }
}


void setup(void){
  //open Serial port
  Serial.begin(115200);
  //open Wifi connection
  WiFi.begin(ssid, password);
  Serial.println("Serial started...");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Wifi connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  //handling the form itself
  server.on("/msg", handleMessage);

  //handling the main site
  server.on("/", [](){
    server.send(200, "text/html", form_closed);
    });

  //handling wrong url
  server.onNotFound([](){
    server.send(404, "text/plain", "File Not Found\n\n");
    });
  server.begin();
  Serial.println("HTTP server started");
}

void loop(void){
  server.handleClient();
}
