#include "FSERestAPI.h"
#include <WiFiClientSecureBearSSL.h>
#include <ESP8266HTTPClient.h>

FSERestAPI::FSERestAPI() {

}

FSERestAPI::FSERestAPI(String host) {
	setHost(_host);
}

void FSERestAPI::setHost(String host) {
	_host = host;
}

String FSERestAPI::getReq(String path) {
	return do_request(_host + path, "GET");
}

String FSERestAPI::postReq(String path, String body) {
	return do_request(_host + path, "POST", body);
}

void FSERestAPI::putReq() {

}

void FSERestAPI::deleteReq() {

}

String FSERestAPI::do_request(String url, String method, String payload) {
	String response;
	int httpCode;
	std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
//	client->setFingerprint(_fingerprint.c_str());
	client->setInsecure();
	HTTPClient https;
	if (https.begin(*client, url)) {

		if (method == "GET") {
			int httpCode = https.GET();
		} else if (method == "POST"){
			https.addHeader("Content-Type","application/json");
			int httpCode = https.POST(payload.c_str());
		} else {
			Serial.printf("Not a valid method");
		}

		for(int i = 0; i< https.headers(); i++){
		  Serial.println(https.header(i));
		}

		// httpCode will be negative on error
		if (httpCode > 0) {
		  // HTTP header has been send and Server response header has been handled
		  Serial.printf("[HTTPS] %s... code: %d\n",method.c_str(), httpCode);
		  // file found at server?
		  if (httpCode == HTTP_CODE_OK) {
			response = https.getString();
		  }
		} else {
			response = https.getString();
			Serial.printf("[HTTPS] %s %s... failed, error: %s\n\r Code: %d \n\r Response: %s", method.c_str(), url.c_str(), https.errorToString(httpCode).c_str(), httpCode, response.c_str());
			Serial.println();
//			return "";
		}
		https.end();
	}
	return response;
}
