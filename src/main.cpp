
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "SSD1306.h"

/* OLED PINS:
D3 -> SDA
D5 -> SCL
*/

int inPin = D0; //Input pin

int pin1 = D1;
int pin2 = D2;

int onFlag = 0;

int reading = 0;
int blinkCount = 0;

const char *ssid     = "www.amalshajan.me";
const char *password = "amalshajan.me";

ESP8266WebServer server(80);

SSD1306  display(0x3c, D3, D5);


void handleRoot() {
	server.send(200, "text/html",
		"<!DOCTYPE html>\n"
		"<html>\n"
		"\t<head>\n"
		"\t\t<title>Home | IoT Smart Energy Meter</title>\n"
		"\t\t\n"
		"\t\t<style>\n"
		"\t\t\t\n"
		"\t\t\t@charset \"UTF-8\";\n"
		"\t\t\t@import url(https://fonts.googleapis.com/css?family=Open+Sans:300,400,700);\n"
		"\t\t\t\n"
		"\t\t\tbody {\n"
		"\t\t\tfont-family: 'Open Sans', sans-serif;\n"
		"\t\t\tfont-weight: 300;\n"
		"\t\t\tline-height: 1.42em;\n"
		"\t\t\tcolor:#A7A1AE;\n"
		"\t\t\tbackground-color:#1F2739;\n"
		"\t\t\t}\n"
		"\t\t\t\n"
		"\t\t\th1 {\n"
		"\t\t\tfont-size:3em; \n"
		"\t\t\tfont-weight: 300;\n"
		"\t\t\tline-height:1em;\n"
		"\t\t\ttext-align: center;\n"
		"\t\t\tcolor: #4DC3FA;\n"
		"\t\t\t}\n"
		"\t\t\t\n"
		"\t\t\th2 {\n"
		"\t\t\tfont-size:1em; \n"
		"\t\t\tfont-weight: 300;\n"
		"\t\t\ttext-align: center;\n"
		"\t\t\tdisplay: block;\n"
		"\t\t\tline-height:1em;\n"
		"\t\t\tpadding-bottom: 2em;\n"
		"\t\t\tcolor: #FB667A;\n"
		"\t\t\t}\n"
		"\t\t\t\n"
		"\t\t\th2 a {\n"
		"\t\t\tfont-weight: 700;\n"
		"\t\t\ttext-transform: uppercase;\n"
		"\t\t\tcolor: #FB667A;\n"
		"\t\t\ttext-decoration: none;\n"
		"\t\t\t}\n"
		"\t\t\t\n"
		"\t\t\t.blue { color: #185875; }\n"
		"\t\t\t.yellow { color: #FFF842; }\n"
		"\t\t\t\n"
		"\t\t\t.container th h1 {\n"
		"\t\t\t\tfont-weight: bold;\n"
		"\t\t\t\tfont-size: 1em;\n"
		"\t\t\ttext-align: left;\n"
		"\t\t\tcolor: #185875;\n"
		"\t\t\t}\n"
		"\t\t\t\n"
		"\t\t\t.container td {\n"
		"\t\t\t\tfont-weight: normal;\n"
		"\t\t\t\tfont-size: 1em;\n"
		"\t\t\t-webkit-box-shadow: 0 2px 2px -2px #0E1119;\n"
		"\t\t\t\t-moz-box-shadow: 0 2px 2px -2px #0E1119;\n"
		"\t\t\t\t\t\tbox-shadow: 0 2px 2px -2px #0E1119;\n"
		"\t\t\t}\n"
		"\t\t\t\n"
		"\t\t\t.container {\n"
		"\t\t\t\ttext-align: left;\n"
		"\t\t\t\toverflow: hidden;\n"
		"\t\t\t\twidth: 80%;\n"
		"\t\t\t\tmargin: 0 auto;\n"
		"\t\t\tdisplay: table;\n"
		"\t\t\tpadding: 0 0 8em 0;\n"
		"\t\t\t}\n"
		"\t\t\t\n"
		"\t\t\t.container td, .container th {\n"
		"\t\t\t\tpadding-bottom: 2%;\n"
		"\t\t\t\tpadding-top: 2%;\n"
		"\t\t\tpadding-left:2%;  \n"
		"\t\t\t}\n"
		"\t\t\t\n"
		"\t\t\t.container tr:nth-child(odd) {\n"
		"\t\t\t\tbackground-color: #323C50;\n"
		"\t\t\t}\n"
		"\t\t\t\n"
		"\t\t\t.container tr:nth-child(even) {\n"
		"\t\t\t\tbackground-color: #2C3446;\n"
		"\t\t\t}\n"
		"\t\t\t\n"
		"\t\t\t.container th {\n"
		"\t\t\t\tbackground-color: #1F2739;\n"
		"\t\t\t}\n"
		"\t\t\t\n"
		"\t\t\t.container td:last-child { color: #FB667A; }\n"
		"\t\t\t\n"
		"\t\t\t.container tr:hover {\n"
		"\t\t\tbackground-color: #464A52;\n"
		"\t\t\t-webkit-box-shadow: 0 6px 6px -6px #0E1119;\n"
		"\t\t\t\t-moz-box-shadow: 0 6px 6px -6px #0E1119;\n"
		"\t\t\t\t\t\tbox-shadow: 0 6px 6px -6px #0E1119;\n"
		"\t\t\t}\n"
		"\t\t\t\n"
		"\t\t\t.container td:hover {\n"
		"\t\t\tbackground-color: #FFF842;\n"
		"\t\t\tcolor: #403E10;\n"
		"\t\t\tfont-weight: bold;\n"
		"\t\t\t\n"
		"\t\t\tbox-shadow: #7F7C21 -1px 1px, #7F7C21 -2px 2px, #7F7C21 -3px 3px, #7F7C21 -4px 4px, #7F7C21 -5px 5px, #7F7C21 -6px 6px;\n"
		"\t\t\ttransform: translate3d(6px, -6px, 0);\n"
		"\t\t\t\n"
		"\t\t\ttransition-delay: 0s;\n"
		"\t\t\t\ttransition-duration: 0.4s;\n"
		"\t\t\t\ttransition-property: all;\n"
		"\t\t\ttransition-timing-function: line;\n"
		"\t\t\t}\n"
		"\t\t\t\n"
		"\t\t\t@media (max-width: 800px) {\n"
		"\t\t\t.container td:nth-child(4),\n"
		"\t\t\t.container th:nth-child(4) { display: none; }\n"
		"\t\t\t}\n"
		"\t\t\t/*Switch*/\n"
		"\t\t\t.switch {\n"
		"\t\t\t\tmargin: 50px auto;\n"
		"\t\t\t\tposition: relative;\n"
		"\t\t\t}\n"
		"\n"
		"\t\t\t.switch label {\n"
		"\t\t\t\twidth: 100%;\n"
		"\t\t\t\theight: 100%;\n"
		"\t\t\t\tposition: relative;\n"
		"\t\t\t\tdisplay: block;\n"
		"\t\t\t}\n"
		"\n"
		"\t\t\t.switch input {\n"
		"\t\t\t\ttop: 0; \n"
		"\t\t\t\tright: 0; \n"
		"\t\t\t\tbottom: 0; \n"
		"\t\t\t\tleft: 0;\n"
		"\t\t\t\topacity: 0;\n"
		"\t\t\t\tz-index: 100;\n"
		"\t\t\t\tposition: absolute;\n"
		"\t\t\t\twidth: 100%;\n"
		"\t\t\t\theight: 100%;\n"
		"\t\t\t\tcursor: pointer;\n"
		"\t\t\t}\n"
		"\n"
		"\t\t\t.switch.btn-oval {\n"
		"\t\t\t\twidth: 180px;\n"
		"\t\t\t\theight: 50px;\n"
		"\t\t\t}\n"
		"\n"
		"\t\t\t.switch.btn-oval label {\n"
		"\t\t\t\tdisplay: block;\n"
		"\t\t\t\twidth: 100%;\n"
		"\t\t\t\theight: 100%;\n"
		"\t\t\t\tbackground: #a5a39d;\n"
		"\t\t\t\tborder-radius: 40px;\n"
		"\t\t\t\tbox-shadow:\n"
		"\t\t\t\t\t\tinset 0 3px 8px 1px rgba(0,0,0,0.2),\n"
		"\t\t\t\t\t\t0 1px 0 rgba(255,255,255,0.5);\n"
		"\t\t\t}\n"
		"\n"
		"\t\t\t.switch.btn-oval label:after {\n"
		"\t\t\t\tcontent: \"\";\n"
		"\t\t\t\tposition: absolute;\n"
		"\t\t\t\tz-index: -1;\n"
		"\t\t\t\ttop: -8px; right: -8px; bottom: -8px; left: -8px;\n"
		"\t\t\t\tborder-radius: inherit;\n"
		"\t\t\t\tbackground: #ababab;\n"
		"\t\t\t\tbackground: -moz-linear-gradient(#f2f2f2, #ababab);\n"
		"\t\t\t\tbackground: -ms-linear-gradient(#f2f2f2, #ababab);\n"
		"\t\t\t\tbackground: -o-linear-gradient(#f2f2f2, #ababab);\n"
		"\t\t\t\tbackground: -webkit-gradient(linear, 0 0, 0 100%, from(#f2f2f2), to(#ababab));\n"
		"\t\t\t\tbackground: -webkit-linear-gradient(#f2f2f2, #ababab);\n"
		"\t\t\t\tbackground: linear-gradient(#f2f2f2, #ababab);\n"
		"\t\t\t\tbox-shadow: 0 0 10px rgba(0,0,0,0.3),\n"
		"\t\t\t\t\t\t\t0 1px 1px rgba(0,0,0,0.25);\n"
		"\t\t\t}\n"
		"\n"
		"\t\t\t.switch.btn-oval label:before {\n"
		"\t\t\t\tcontent: \"\";\n"
		"\t\t\t\tposition: absolute;\n"
		"\t\t\t\tz-index: -1;\n"
		"\t\t\t\ttop: -18px; right: -18px; bottom: -18px; left: -18px;\n"
		"\t\t\t\tborder-radius: inherit;\n"
		"\t\t\t\tbackground: #eee;\n"
		"\t\t\t\tbackground: -moz-linear-gradient(#e5e7e6, #eee);\n"
		"\t\t\t\tbackground: -ms-linear-gradient(#e5e7e6, #eee);\n"
		"\t\t\t\tbackground: -o-linear-gradient(#e5e7e6, #eee);\n"
		"\t\t\t\tbackground: -webkit-gradient(linear, 0 0, 0 100%, from(#e5e7e6), to(#eee));\n"
		"\t\t\t\tbackground: -webkit-linear-gradient(#e5e7e6, #eee);\n"
		"\t\t\t\tbackground: linear-gradient(#e5e7e6, #eee);\n"
		"\t\t\t\tbox-shadow:\n"
		"\t\t\t\t\t\t0 1px 0 rgba(255,255,255,0.5);\n"
		"\t\t\t\t-webkit-filter: blur(1px);\n"
		"\t\t\t\t-moz-filter: blur(1px);\n"
		"\t\t\t\t-ms-filter: blur(1px);\n"
		"\t\t\t\t-o-filter: blur(1px);\n"
		"\t\t\t\tfilter: blur(1px);\n"
		"\t\t\t}\n"
		"\n"
		"\t\t\t.switch.btn-oval label i {\n"
		"\t\t\t\tdisplay: block;\n"
		"\t\t\t\theight: 100%;\n"
		"\t\t\t\twidth: 60%;\n"
		"\t\t\t\tborder-radius: inherit;\n"
		"\t\t\t\tbackground: silver;\n"
		"\t\t\t\tposition: absolute;\n"
		"\t\t\t\tz-index: 2;\n"
		"\t\t\t\tright: 40%;\n"
		"\t\t\t\ttop: 0;\n"
		"\t\t\t\tbackground: #b2ac9e;\n"
		"\t\t\t\tbackground: -moz-linear-gradient(#f7f2f6, #b2ac9e);\n"
		"\t\t\t\tbackground: -ms-linear-gradient(#f7f2f6, #b2ac9e);\n"
		"\t\t\t\tbackground: -o-linear-gradient(#f7f2f6, #b2ac9e);\n"
		"\t\t\t\tbackground: -webkit-gradient(linear, 0 0, 0 100%, from(#f7f2f6), to(#b2ac9e));\n"
		"\t\t\t\tbackground: -webkit-linear-gradient(#f7f2f6, #b2ac9e);\n"
		"\t\t\t\tbackground: linear-gradient(#f7f2f6, #b2ac9e);\n"
		"\t\t\t\tbox-shadow:\n"
		"\t\t\t\t\t\tinset 0 1px 0 white,\n"
		"\t\t\t\t\t\t0 0 8px rgba(0,0,0,0.3),\n"
		"\t\t\t\t\t\t0 5px 5px rgba(0,0,0,0.2);\n"
		"\t\t\t}\n"
		"\n"
		"\t\t\t.switch.btn-oval label i:after {\n"
		"\t\t\t\tcontent: \"\";\n"
		"\t\t\t\tposition: absolute;\n"
		"\t\t\t\tleft: 15%;\n"
		"\t\t\t\ttop: 25%;\n"
		"\t\t\t\twidth: 70%;\n"
		"\t\t\t\theight: 50%;\n"
		"\t\t\t\tbackground: #d2cbc3;\n"
		"\t\t\t\tbackground: -moz-linear-gradient(#cbc7bc, #d2cbc3);\n"
		"\t\t\t\tbackground: -ms-linear-gradient(#cbc7bc, #d2cbc3);\n"
		"\t\t\t\tbackground: -o-linear-gradient(#cbc7bc, #d2cbc3);\n"
		"\t\t\t\tbackground: -webkit-gradient(linear, 0 0, 0 100%, from(#cbc7bc), to(#d2cbc3));\n"
		"\t\t\t\tbackground: -webkit-linear-gradient(#cbc7bc, #d2cbc3);\n"
		"\t\t\t\tbackground: linear-gradient(#cbc7bc, #d2cbc3);\n"
		"\t\t\t\tborder-radius: inherit;\n"
		"\t\t\t}\n"
		"\n"
		"\t\t\t.switch.btn-oval label i:before {\n"
		"\t\t\t\tcontent: \"off\";\n"
		"\t\t\t\ttext-transform: uppercase;\n"
		"\t\t\t\tfont-style: normal;\n"
		"\t\t\t\tfont-weight: bold;\n"
		"\t\t\t\tcolor: rgba(0,0,0,0.4);\n"
		"\t\t\t\ttext-shadow: 0 1px 0 #bcb8ae, 0 -1px 0 #97958e;\n"
		"\t\t\t\tfont-family: Helvetica, Arial, sans-serif;\n"
		"\t\t\t\tfont-size: 24px;\n"
		"\t\t\t\tposition: absolute;\n"
		"\t\t\t\ttop: 50%;\n"
		"\t\t\t\tmargin-top: -12px;\n"
		"\t\t\t\tright: -50%;\n"
		"\t\t\t}\n"
		"\n"
		"\t\t\t.switch.btn-oval input:checked ~ label {\n"
		"\t\t\t\tbackground: #9abb82;\n"
		"\t\t\t}\n"
		"\n"
		"\t\t\t.switch.btn-oval input:checked ~ label i {\n"
		"\t\t\t\tright: -1%;\n"
		"\t\t\t}\n"
		"\n"
		"\t\t\t.switch.btn-oval input:checked ~ label i:before {\n"
		"\t\t\t\tcontent: \"on\";\n"
		"\t\t\t\tright: 115%;\n"
		"\t\t\t\tcolor: #82a06a;\n"
		"\t\t\t\ttext-shadow: \n"
		"\t\t\t\t\t0 1px 0 #afcb9b,\n"
		"\t\t\t\t\t0 -1px 0 #6b8659;\n"
		"\t\t\t}\n"
		"\n"
		"\t\t\t</style>\n"
		"\t</head>\n"
		"\t<body>\n"
		"\t\t<h1><span class=\"blue\">IoT </span>Smart <span class=\"blue\">Energy </span> <span class=\"yellow\">Meter </pan></h1>\n"
		"\t\t<h2>Usage: </h2>\n"
		"\t\t\t\n"
		"\t\t<div class=\"switch btn-oval\">\n"
		"\t\t\t<input type=\"checkbox\" name=\"pinOne\" onclick=\"handleClick(this)\";>\n"
		"\t\t\t<label><i></i></label>\n"
		"\t\t</div>\n"
		"\n"
		"\t\t<table class=\"container\" id=\"data-table\">\n"
		"\t\t\t<thead>\n"
		"\t\t\t\t<tr>\n"
		"\t\t\t\t\t<th><h1>Time</h1></th>\n"
		"\t\t\t\t\t<th><h1>Usage (Kwh)</h1></th>\n"
		"\t\t\t\t\t<th><h1>Rate (Rs.)</h1></th>\n"
		"\t\t\t\t</tr>\n"
		"\t\t\t</thead>\n"
		"\t\t\t<tbody>\n"
		"\t\t\t\t<tr>\n"
		"\t\t\t\t\t<td>&nbsp;</td>\n"
		"\t\t\t\t\t<td>&nbsp;</td>\n"
		"\t\t\t\t\t<td>&nbsp;</td>\n"
		"\t\t\t\t</tr>\n"
		"\t\t\t</tbody>\n"
		"\t\t</table>\n"
		"\n"
		"\t\t<script>\n"
		"\t\t\tvar oldVal = 0;\n"
		"\t\t\tfunction updateVals() {\n"
		"\t\t\t\tlet xhttp = new XMLHttpRequest();\n"
		"\t\t\t\txhttp.onreadystatechange = function() {\n"
		"\t\t\t\t\tif (this.readyState == 4 && this.status == 200) {\n"
		"\t\t\t\t\t\tvar reading = parseInt(this.responseText);\n"
		"\t\t\t\t\t\tif(oldVal == reading) {\n"
		"\t\t\t\t\t\t\treturn;\n"
		"\t\t\t\t\t\t}\n"
		"\t\t\t\t\t\toldVal = reading;\n"
		"\t\t\t\t\t\tvar table = document.getElementById(\"data-table\");    \n"
		"\t\t\t\t\t\tvar row = table.insertRow(1);\n"
		"\t\t\t\t\t\tvar timeCell = row.insertCell(0);\n"
		"\t\t\t\t\t\tvar usageCell = row.insertCell(1);\n"
		"\t\t\t\t\t\tvar rateCell = row.insertCell(2);\n"
		"\t\t\t\t\t\ttimeCell.innerHTML = new Date();\n"
		"\t\t\t\t\t\trateCell.innerHTML = reading;\n"
		"\t\t\t\t\t\tusageCell.innerHTML = reading/5;\n"
		"\t\t\t\t\t}\n"
		"\t\t\t\t}\n"
		"\t\t\t\txhttp.open(\"GET\", \"getReading\", true);\n"
		"\t\t\t\txhttp.send();\n"
		"\t\t\t}\n"
		"\n"
		"\n"
		"\t\t\tfunction handleClick(cb) {\n"
		"\t\t\t\tif(cb.checked) {\n"
		"\t\t\t\t\tthis.path = cb.name + \"On\";\n"
		"\t\t\t\t\tloadInterval = setInterval(updateVals, 1000)\n"
		"\t\t\t\t}\n"
		"\t\t\t\telse {\n"
		"\t\t\t\t\tthis.path = cb.name + \"Off\";\n"
		"\t\t\t\t\tclearInterval(loadInterval);\n"
		"\t\t\t\t}\n"
		"\t\t\t\tlet xhttp = new XMLHttpRequest();\n"
		"\t\t\t\txhttp.open(\"GET\", path, true);\n"
		"\t\t\t\txhttp.send();\n"
		"\t\t\t}\n"
		"\t\t</script>\n"
		"\t</body>\n"
		"</html>"
	);
}

void handelePinOneOn() {
	digitalWrite(pin1, HIGH);
	onFlag = 1;
	server.send(200, "text/html", "Pin one turned on");
}

void handelePinOneOff() {
	digitalWrite(pin1, LOW);
	onFlag = 0;
	server.send(200, "text/html", "Pin one turned off");
}

void handeleGetReading() {
	server.send(200, "text/html", String(reading));
}

void drawValue() {
		display.clear();
		display.setTextAlignment(TEXT_ALIGN_LEFT);
		display.setFont(ArialMT_Plain_16);
		display.drawString(0, 10, "Reading: ");
		display.setFont(ArialMT_Plain_24);
		display.drawString(0, 30, String(reading));
		display.display();
}

void drawString(String str) {
		display.clear();
		display.setTextAlignment(TEXT_ALIGN_LEFT);
		display.setFont(ArialMT_Plain_16);
		display.drawString(0, 10, str);
		display.display();
		delay(5000);
}

void setupWiFi(){
	Serial.print("Connecting to ");
	Serial.println(ssid);
	WiFi.begin(ssid, password);
	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}
	Serial.println("");
	Serial.println("WiFi connected");
}

int calCurrent() {
	if(!onFlag) {
		return 0;
	}
	int val = digitalRead(inPin);
	if(val == HIGH) {
		blinkCount++;
	}
	Serial.print("Blink count: ");
	Serial.print(blinkCount);
	Serial.print("Reading: ");
	Serial.print(reading);
	if(blinkCount == 10) {
		reading++;
		blinkCount = 0;
	}
}

void setup() {

	pinMode(inPin, INPUT);

	pinMode(pin1, OUTPUT);
	pinMode(pin2, OUTPUT);

	Serial.begin(115200);
	display.init();
	display.flipScreenVertically();

	delay(1000);

	//Serial.print("Configuring access point...");
	//drawString("Configuring access point...");
	//WiFi.softAP(ssid);
	//WiFi.softAP(ssid, password);
	setupWiFi();
	IPAddress myIP = WiFi.localIP();
	Serial.println(myIP);
	drawString("IP address: "+String(myIP));

	server.on("/", handleRoot);
	server.on("/pinOneOn", handelePinOneOn);
	server.on("/pinOneOff", handelePinOneOff);
	server.on("/getReading", handeleGetReading);

	server.begin();
	Serial.println("HTTP server started");
	drawString("HTTP server started");

}

void loop() {
	reading += calCurrent();
	drawValue();
	server.handleClient();
}
