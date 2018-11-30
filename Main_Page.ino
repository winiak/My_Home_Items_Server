#ifndef DEFS
#include "defs.h"
#endif

void mainPage() {

  // get arguments
  readArguments();
  
  // execute action ==> in main loop
  getRequestExec();

  // force execution loop
  requestExecution();
  
  // snprintf
  //test_shift();
  String out = "";
  out += "\
    <!DOCTYPE html><html>\
      <head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\
      <link rel=\"icon\" href=\"data:,\">\
      <style>html {  font-family: Helvetica; font-size: 10px;  display: inline-block;  margin: 0px auto 5px auto;  text-align: center;}\
      div {  float:left;  border: 1px solid #ddd;  background-color: #bbb;}\
      button { background-color: #aaaaaa; border: none; color: white; text-decoration: none; font-size: 20px; margin: 2px; cursor: pointer;  height: 96px;  width: 96px;}\
      button:hover { background-color: #ccc;}\
      .on {   background-color: #fb1;}\
      .button2 {background-color: #77878A;}</style></head>\
      <body><h1>Home Items Server</h1>";

  // get all items and status
  // print buttons / elements
  for (uint8_t i = 0; i < NUMBER_OF_ITEMS; i++) {
    if (HomeItems[i].type == LIGHT) {
        out += "<div><a href=\"?item=";
        out.concat(HomeItems[i].id);
        out += "&value=";
        out += (HomeItems[i].current_state ==  OFF ? "ON" : "OFF");
        out += "\"><button";
        out += (HomeItems[i].current_state == ON ? " class=\"on\"" : "");  
        out += ">";
        out.concat(HomeItems[i].item_name);
        out += "</button></a></div>";
    }  
  }
  out += "</body></html>";
  server.send(200, "text/html", out);
  
}

