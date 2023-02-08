#include <A6lib.h>
#include <A6HTTP.h>
A6HTTP myA6("internet", "www.ptsv2.com", "/t/yp2hv-1575674386/post", 80, "application/x-www-form-urlencoded");

//Syntax: A6HTTP myA6("APN", "host", "path", port, "Content-Type");
//Find your APN for your provider online
//posttestserver.com lets you post anything for free and have a look at it afterwards.

void setup() {
  myA6.begin();
  //initialize HTTP library. 

  myA6.HttpPost("This is a Test");
  //Syntax: myA6.HttpPost("body");
  //body is the actual posted data matching your defined Content-Type
}

void loop() {

}
