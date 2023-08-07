#include "ConnectServer.h"


void update_progress(int cur, int total) {
  Debug::LOG_PROGRESS_UPDATE(cur,total);
}

enum CONNECT_SERVER{
    CONNECT_FAIL,
    CONNECT_SUCCESSFULL
};

static ConnectInternet cni;
RestClient client = RestClient(BASE_URL);

ConnectServer::ConnectServer(){}

ConnectServer::~ConnectServer(){}

bool ConnectServer::isServerConnected(){
    while(!cni.isConnected()){
        cni.connect();
        Debug::LOG_TO_SCREEN(0,0,"Waiting for connect...");
        delay(100);
    }
    Debug::LOG_TO_SCREEN(0,0,"Start connect...");
    String response="";
    int status = client.get(URI_CHECK_COMMUNICATION, &response);
    if(status==200 && response.equalsIgnoreCase("CONNECTED")){
        return CONNECT_SUCCESSFULL;
    }
    String txt =status+"  "+response;
    Debug::LOG_TO_SCREEN(0,0,txt);
    return CONNECT_FAIL;
    
}
int ConnectServer::getVersion(){
  String currentVersion = "";
  int status = client.get(URI_CHECK_COMMUNICATION, &currentVersion);
  if(status == STATUS_CODE_OKE){
    return STATUS_CODE_OKE;
  }
  return status;
}
String ConnectServer::getBoardId(){
  String boardID = "";
  int status = client.get(URI_GET_BOARD_ID, &boardID);
  if(status == STATUS_CODE_OKE){
    return boardID;
  }
  return "";
  
}

/*
int ConnectServer::pushData(){
    WiFiClient client;
    HTTPClient http;

    Serial.print("[HTTP] begin...\n");
    // configure traged server and url
    http.begin(client, URL_TEMP); //HTTP
    http.addHeader("Content-Type", "application/json");
    http.addHeader("Authorization", KEY);

    Serial.print("[HTTP] POST...\n");
    // start connection and send HTTP header and body
    int httpCode = http.POST("{\"value\":\""+String(random(19,24))+"\"}");

    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] POST... code: %d\n", httpCode);

      // file found at server
      if (httpCode == HTTP_CODE_OK) {
        const String& payload = http.getString();
        Serial.println("received payload:\n<<");
        Serial.println(payload);
        Serial.println(">>");
      }
    } else {
      Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
}
*/
int ConnectServer::communicationSever(String URI, String value, String& response,int method){
    WiFiClient client;
    HTTPClient http;
    Serial.print("[HTTP] begin...\n");
    // configure traged server and url
    http.begin(client, URI); //HTTP
    http.addHeader("Content-Type",CONTENT_TYPE );
    http.addHeader("Platform-Version",Platform);
    http.addHeader("Authorization", KEY);
    // Serial.print("[HTTP] POST...\n");
    // start connection and send HTTP header and body
    int httpCode = -1;
    switch (method)
    {
    case GET:{
      httpCode =http.GET();
      break;
    }
    case POST:
    {
      String body ="{\"value\":\""+value+"\"}"; 
      httpCode = http.POST(body);
      break;
    }
    case UPDATE:
      break;
    case PUT:
      break;
    case DELETE:
      break;
    default:
      Debug::LOG_TO_SCREEN(0,0,"METHOD NOT CORRECT");
      break;
    }
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] POST... code: %d\n", httpCode);
      // file found at server
      if (httpCode == HTTP_CODE_OK) {
        const String& payload = http.getString();
        Serial.println("received payload:\n<<");
        response = payload;
        Serial.println(payload);
        // this->updateFirmware(Platform);
        Serial.println(">>");
      }
    } else {
      Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
    http.end();
}
