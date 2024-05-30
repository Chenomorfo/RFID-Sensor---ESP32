
//String hostURI = "http://192.168.137.1:3000";
String hostURI = "http://192.168.137.1:3001";

void GET_HW() {
  HTTPClient http;

  USE_SERIAL.print("[HTTP] begin...\n");
  // configure traged server and url
  //http.begin("https://www.howsmyssl.com/a/check", ca); //HTTPS
  http.begin(hostURI);  //HTTP

  USE_SERIAL.print("[HTTP] GET...\n");
  // start connection and send HTTP header
  int httpCode = http.GET();

  // httpCode will be negative on error
  if (httpCode > 0) {
    // HTTP header has been send and Server response header has been handled
    USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);

    // file found at server
    if (httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      USE_SERIAL.println(payload);
    }
  } else
    USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());


  http.end();
}
void POST_RFID(String data) {
  HTTPClient http;

  USE_SERIAL.print("[HTTP] begin...\n");
  // configure traged server and url
  //http.begin("https://www.howsmyssl.com/a/check", ca); //HTTPS
  http.begin(hostURI);  //HTTP
  http.addHeader("Content-Type", "text/plain");
  USE_SERIAL.print("[HTTP] POST...\n");
  // start connection and send HTTP header
  //int httpCode = http.POST("{\"rfid\":\"" + data + " \"}");
  int httpCode = http.POST(data);

  // httpCode will be negative on error
  if (httpCode > 0) {
    // HTTP header has been send and Server response header has been handled
    USE_SERIAL.printf("[HTTP] POST... code: %d\n", httpCode);

    // file found at server
    if (httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      USE_SERIAL.println(payload);
      if(payload == "Error") UnsuccessPass();
      else SuccessPass();
    }
  } else
    USE_SERIAL.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());


  http.end();
}