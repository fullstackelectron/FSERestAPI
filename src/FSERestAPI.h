/*
 * Created: 2021-090-14
 * Author: FullstackElectron
 *
 */

#ifndef LIB_FSERESTAPI_SRC_FSERESTAPI_H_
#define LIB_FSERESTAPI_SRC_FSERESTAPI_H_
#include <memory>
#include <Arduino.h>

class FSERestResponse {

};

class FSERestAPI {
public:
	FSERestAPI();
	FSERestAPI(String host);
	void setHost(String host);
	void deleteReq();
	String getReq(String path) ;
	String postReq(String path, String body);
	void putReq();
protected:
	String do_request(String url, String method, String payload= "");
	FSERestResponse _response;
private:
	String _host;
//	String _fingerprint = "49 24 E7 00 D5 12 B3 02 B7 E8 7B E2 C6 FF B3 5D 46 7F 1A CC";


};


#endif /* LIB_FSERESTAPI_SRC_FSERESTAPI_H_ */
