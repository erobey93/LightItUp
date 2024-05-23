#include <SPI.h>
#include <WiFiNINA.h>

#define led 9

//ssid and password located in .env file 
char ssid[] = "CenturyLink9360";
char pass[] = "jtn3exi5uwk43s";
int keyIndex = 0;

int status = WL_IDLE_STATUS;
WiFiServer server(80);

String readString;

void setup() {
  pinMode(led, OUTPUT);
  Serial.begin(9600);

  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
    delay(10000);
  }

  server.begin();

  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
}

void initialIntro()
{
   // HTML content - Intro
   //this should always be on the page - tells user what mode they are based on the mode variable 
            client.println("<!DOCTYPE HTML>");
            client.println("<html>");
            client.println("<head>");
            client.println("<title>Light It Up</title>");
            client.println("<style>");
            client.println("body { font-family: Arial, sans-serif; background-color: #f4f4f4; text-align: center; padding: 50px; }");
            client.println("h1 { color: #333; }");
            client.println(".button { padding: 10px 20px; margin: 20px; text-decoration: none; color: white; background-color: #007BFF; border-radius: 5px; display: inline-block; }");
            client.println(".button:hover { background-color: #0056b3; }");
            client.println("</style>");
            client.println("</head>");
            client.println("<body>");
            client.println("<h1>Welcome to Light It Up!</h1>");
            client.println("<h2>Created by Emily Robey </h2>");

            //Choose web mode, or clap mode 
            client.println("<a href=\"/?webmode\"> Web Mode </a><br>");
            client.println("<a href=\"/?clapmode\"> Clap Mode </a><br><br>");

            client.println("<a> Choose a mode to get started! </a><br>");
}

void mainPageOptionChosen()
{
   // HTML content - Intro
            //this should always be on the page - tells user what mode they are based on the mode variable 
            client.println("<!DOCTYPE HTML>");
            client.println("<html>");
            client.println("<head>");
            client.println("<title>Light It Up</title>");
            client.println("<style>");
            client.println("body { font-family: Arial, sans-serif; background-color: #f4f4f4; text-align: center; padding: 50px; }");
            client.println("h1 { color: #333; }");
            client.println(".button { padding: 10px 20px; margin: 20px; text-decoration: none; color: white; background-color: #007BFF; border-radius: 5px; display: inline-block; }");
            client.println(".button:hover { background-color: #0056b3; }");
            client.println("</style>");
            client.println("</head>");
            client.println("<body>");
            client.println("<h1>Welcome to Light It Up!</h1>");
            client.println("<h2>Created by Emily Robey </h2>");

            //Choose web mode, or clap mode 
            client.println("<a href=\"/?webmode\"> Web Mode </a><br>");
            client.println("<a href=\"/?clapmode\"> Clap Mode </a><br><br>");
}
void loop() {
  WiFiClient client = server.available();
  if (client) {
    Serial.println("new client");
    String currentLine = "";
    String readString = "";
    String mode = ""; //no mode to start, should prompt user to
    String intro = "";

    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        readString += c;
        Serial.write(c);

        if (c == '\n') {
          // if you get a newline, and the line is blank, the HTTP request has ended
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // HTML content - Intro
            //this should always be on the page - tells user what mode they are based on the mode variable 
            client.println("<!DOCTYPE HTML>");
            client.println("<html>");
            client.println("<head>");
            client.println("<title>Light It Up</title>");
            client.println("<style>");
            client.println("body { font-family: Arial, sans-serif; background-color: #f4f4f4; text-align: center; padding: 50px; }");
            client.println("h1 { color: #333; }");
            client.println(".button { padding: 10px 20px; margin: 20px; text-decoration: none; color: white; background-color: #007BFF; border-radius: 5px; display: inline-block; }");
            client.println(".button:hover { background-color: #0056b3; }");
            client.println("</style>");
            client.println("</head>");
            client.println("<body>");
            client.println("<h1>Welcome to Light It Up!</h1>");
            client.println("<h2>Created by Emily Robey </h2>");

            //Choose web mode, or clap mode 
            client.println("<a href=\"/?webmode\"> Web Mode </a><br>");
            client.println("<a href=\"/?clapmode\"> Clap Mode </a><br><br>");

            client.println("<a> Choose a mode to get started! </a><br>");

            client.println("</html>"); //end of main page 

            //check for change in mode
            //then perform logic based on change in mode
            //first check if it is in web mode -  Handle the request to turn the light on or off
            //if not check if in clapmode - wait for user's input until they switch out of webmode or the site closes? 
            if (readString.indexOf("GET /?webmode") >= 0) {
              //decide which buttons to display 
            //if in webmode show the Light On + Light Off buttons
            //else show them their options TODO would like them to be able to control the options
            //i.e. they can decide how to control the lights 
 
              client.println("<a href=\"/?lighton\">Turn On Light</a><br>");
              client.println("<a href=\"/?lightoff\">Turn Off Light</a><br>");

              //digitalWrite(led, HIGH); // turn the LED on for now remove shortly 
              //web mode logic 
              Serial.println("in Web Mode");

              // Handle the request to turn the light on or off
              if (readString.indexOf("GET /?lighton") >= 0) {
                digitalWrite(led, HIGH); // turn the LED on
                Serial.println("Light ON");
              } else if (readString.indexOf("GET /?lightoff") >= 0) {
                digitalWrite(led, LOW); // turn the LED off
                Serial.println("Light OFF");
              }
            } else if (readString.indexOf("GET /?clapmode") >= 0) {
              //digitalWrite(led, LOW); // turn the LED off
              
              //clap logic below 
              Serial.println("in Clap Mode");

              client.println("<a> You can now control your lights via claps! </a><br>");
              client.println("<a> You have the following options: </a><br>");
              client.println("<a> Clap once: turn lights on </a><br>");
              client.println("<a> Clap twice: switch to blinking lights (insert color once set TODO) </a><br>");
              client.println("<a> Clap three times: switch to blinking lights (insert different color once set TODO) </a><br>");
              client.println("<a> Clap four times: switch to dancing lights </a><br>");
              client.println("<a> Clap five times: turn lights off </a><br>");
            }
            // Break out of the while loop:
            break;
          } else {
            // clear the current line
            currentLine = "";
          }
        } else if (c != '\r') {
          // add character to the current line
          currentLine += c;
        }
      }
    }
    // Clear the readString for the next client
    readString = "";

    // Close the connection
    client.stop();
    Serial.println("client disconnected");
  }
}
  
