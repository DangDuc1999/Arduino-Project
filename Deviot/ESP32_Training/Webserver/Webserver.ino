#include <WiFi.h>
#include "ESPAsyncWebServer.h"
AsyncWebServer server(80);
int cnt;

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1">
<style>
</style>
<body>
<h1>
<span id ="count">%COUNT%</span>
</h1>
</body>
<script>
setInterval(function(){
var xml = new XMLHttpRequest();
xml.onreadystatechange = function() {
document.getElementById("count").innerHTML = this.responseText;
};
xml.open("GET","/count",true);
xml.send();
}, 1000);
</script>
</head>

)rawliteral";

String process(const String& var){
if(var == COUNT){
return String(cnt);
}
return String();
}

void IRAM_ATTR irs() {
cnt++;
Serial.println("Interrupt Request!");
if (cnt % 2) digitalWrite(GPIO_NUM_2, 1);
else digitalWrite(GPIO_NUM_2, 0);
}

void setup() {
// put your setup code here, to run once:
Serial.begin(115200);
pinMode(0, INPUT_PULLUP);
attachInterrupt(GPIO_NUM_0, irs, FALLING);
WiFi.begin("T4N", "12345679");
while (WiFi.status() != WL_CONNECTED) {
}
Serial.println(WiFi.localIP());

 server.on("/",HTTP_GET, [](AsyncWebServerRequest *request){
request->send_P(200,"text/html",index_html,process);
});
server.on("/count",HTTP_GET, [](AsyncWebServerRequest *request){
request->send(200,"text/plain",String(cnt));
});
server.begin();
}

void loop() {
// put your main code here, to run repeatedly:
server.handleClient();
}
