#include <SPI.h>
#include <WiFiNINA.h>

#define led 9

char ssid[] = "CenturyLink9360";        // your network SSID (name)
char pass[] = "jtn3exi5uwk43s";    // your network password
int status = WL_IDLE_STATUS;
WiFiServer server(80);           // Start the server on port 80

String mode = "No mode selected"; // Initialize the mode variable
String lightStatus = "lightoff"; //Initialize light status variable TODO do I need this? 
void setup() {
  pinMode(led, OUTPUT);
  Serial.begin(9600);

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // Check for the presence of the shield
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    while (true);
  }

  // Attempt to connect to WiFi network
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
    delay(10000);
  }

  Serial.println("Connected to WiFi");
  server.begin();
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  WiFiClient client = server.available();  // listen for incoming clients

  if (client) {  // if a new client connects,
    Serial.println("New Client.");          // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // HTML content - Initial page load
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
            client.println("<script>");
            client.println("function setMode(mode) {");
            client.println("var xhttp = new XMLHttpRequest();");
            client.println("xhttp.onreadystatechange = function() {");
            client.println("if (this.readyState == 4 && this.status == 200) {");
            client.println("document.getElementById('content').innerHTML = this.responseText;");
            client.println("}");
            client.println("};");
            client.println("xhttp.open('GET', '/?mode=' + mode, true);");
            client.println("xhttp.send();");
            client.println("}");
            client.println("</script>");
            client.println("</head>");
            client.println("<body>");
            client.println("<div id='content'>");
            client.println("<h1>Welcome to Light It Up!</h1>");
            client.print("<p><span id=\"mode\">"); //what is the span id? FIXME this had the words before mode in them 
            client.print(mode);
            client.println("</span></p>");
            client.println("<a href=\"webmode\" class=\"button\" onclick=\"setMode('webmode'); return true;\">Web Mode</a>");
            client.println("<a href=\"clapmode\" class=\"button\" onclick=\"setMode('clapmode'); return true;\">Clap Mode</a>");
            client.println("</div>");
            client.println("</body>");
            client.println("</html>");

            // The HTTP response ends with another blank line
            client.println();
            break;
          } else {    // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was for web mode or clap mode
        if (currentLine.endsWith("GET /?mode=webmode")) {
          //mode = "Web Mode";                // Set the mode to web mode isn't this repetitive though? FIXME I think it is set above 
          Serial.println("Web Mode selected");
          digitalWrite(led, High); 

          //stops working here...
          client.println("Web Mode Selected");
          // Send new content for Web Mode
          //client.println("HTTP/1.1 200 OK");
          //client.println("Content-type:text/html");

          //client.println("<!DOCTYPE HTML>");
          //client.println("<html>");
          //client.println("<head>");
          //client.println("<title>Web Mode</title>");
          //client.println("<style>");
          //client.println("body { font-family: Arial, sans-serif; background-color: #f4f4f4; text-align: center; padding: 50px; }");
          //client.println("h1 { color: #333; }");
          //client.println(".button { padding: 10px 20px; margin: 20px; text-decoration: none; color: white; background-color: #007BFF; border-radius: 5px; display: inline-block; }");
          //client.println(".button:hover { background-color: #0056b3; }");
          //client.println("</style>");
          client.println("<script>");
          //function to set status of the light 
          client.println("function setLight(lightStatus) {");
          client.println("var xhttp = new XMLHttpRequest();");
          client.println("xhttp.onreadystatechange = function() {");
          client.println("if (this.readyState == 4 && this.status == 200) {");
          client.println("document.getElementById('content').innerHTML = this.responseText;");
          client.println("}");
          client.println("};");
          client.println("</script>");
          client.println("</head>");
          client.println("<body>");
          client.println("<div id='content'>");
          client.println();
          client.println("<h1>Web Mode Activated</h1>");
          client.println("<p>You're now in Web Mode.</p>");

          
          client.println("<a href=\"lighton\" class=\"button\" onclick=\"setLight('lighton'); return true;\"> Turn On Light </a>"); //what does it mean for these to return true, or false? My thought is it should return true if its selected, but maybe I'm not thinking about it correctly 
          client.println("<a href=\"lightoff\" class=\"button\" onclick=\"setLight('lightoff'); return true;\"> Turn Off Light </a>");
          //client.println("<a href=\"/?lighton\">Turn On Light</a><br>"); using js above for more dynamic actions this is the old logic 
          //client.println("<a href=\"/?lightoff\">Turn Off Light</a><br>");

          //print option to switch modes (?) not sure if this is the right place to put this, or not....
          client.println("<a href=\"clapmode\" class=\"button\" onclick=\"setMode('clapmode'); return true;\">Switch to Clap Mode</a>");
          client.println("</html>");
          client.println("</div>");
          client.println("</body>");
          client.println("</html>");

           // Handle the request to turn the light on or off
          if (currentLine.endsWith("GET /?mode=lighton")) {
            digitalWrite(led, HIGH); // turn the LED on
            Serial.println("Light ON");
          } else if (currentLine.endsWith("GET /?mode=lightoff")) {
            digitalWrite(led, LOW); // turn the LED off
            Serial.println("Light OFF");
          }

          
          break;
        }else if (currentLine.endsWith("GET /?mode=clapmode")) {
          //mode = "Clap Mode";               // Set the mode to clap mode I believe mode was already set, so this is repetitive 
          Serial.println("Clap Mode selected");

          // Send new content for Clap Mode
          //client.println("HTTP/1.1 200 OK");
          //client.println("Content-type:text/html");
          //client.println();
          client.println("<h1>Clap Mode Activated</h1>");
          client.println("<p>You're now in Clap Mode.</p>");

          client.println("<a> You can now control your lights via claps! </a><br>");
          client.println("<a> You have the following options: </a><br>");
          client.println("<a> Clap once: turn lights on </a><br>");
          client.println("<a> Clap twice: switch to blinking lights (insert color once set TODO) </a><br>");
          client.println("<a> Clap three times: switch to blinking lights (insert different color once set TODO) </a><br>");
          client.println("<a> Clap four times: switch to dancing lights </a><br>");
          client.println("<a> Clap five times: turn lights off </a><br>");

          client.println("<a href=\"webmode\" class=\"button\" onclick=\"setMode('webmode'); return false;\">Switch to Web Mode</a>");
          break;
        }
      }
    }

    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
}