#ifndef DEFS
#include "defs.h"
#endif

void processPage() {
  // get arguments
  getArguments();
  
  // execute action ==> in main loop
  getRequestExec();

  // force execution loop
  requestExecution();
  print_shift_registers();
}

void mainPage() {

  processPage();  

  //test_shift();
  String out = "";
  out += "\
    <!DOCTYPE html><html>\
      <head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\
      <link rel=\"icon\" href=\"data:,\">\
      <style>\
      body { max-width : 364px; background-color : #aaaaaa}\
      html {  font-family: Helvetica; font-size: 10px;  display: inline-block;  margin: 0px auto 5px auto;  text-align: center;}\
      div {  float:left;  border: 1px solid #ddd;  background-color: #bbb; margin: 2px 2px 2px 2px;}  \
      .menu button { background-color: #ddd; border: none; color: #333; text-decoration: none; font-size: 12px; margin: 0px; cursor: pointer;  height: 48px;  width: 84px; }\
      .group button { background-color: #fff; border: none; color: #333; text-decoration: none; font-size: 14px; margin: 0px; cursor: pointer;  height: 84px;  width: 84px;}\
      .group a { display:block; }\
      .group img {margin : 0px; padding : 0px; border:0px;}\
      \
      button:hover { background-color: #ccc;}\
      button.on {   background-color: #fb1;}\
      button.on:hover {   background-color: #fc7;}\
      .shield { height : 96px; } \
      .shield button { background-repeat: no-repeat;  background-position: center; }\
      .shield button.up { background-image:url('icons/sbu.svg'); height: 32px; }\      
      .shield button.up_on { background-image:url('icons/sbu.svg?color=red'); height: 32px; }\ 
      .shield button.up_ok { background-image:url('icons/sbu.svg?color=green'); height: 32px; }\  
      .shield button.st { background-image:url('icons/sbst.svg'); height: 32px; } \
      .shield button.st_stop { background-image:url('icons/sbst.svg?color=red'); height: 32px; } \
      .shield button.dn { background-image:url('icons/sbd.svg'); height: 32px; }\
      .shield button.dn_on { background-image:url('icons/sbd.svg?color=red'); height: 32px; }\
      .shield button.dn_ok { background-image:url('icons/sbd.svg?color=green'); height: 32px; }\
</style>\
      <script type=\"application/javascript\">\
        function showGroup(group) {";
        
  for (uint8_t i = 1; i <= NUMBER_OF_GROUPS; i++){
    out += "document.getElementById(\"g";
    out += i;
    out += "\").style.display = (group == \"g";
    out += i;
    out += "\" ? \"block\" : \"none\");";
  }
  out += "     }\
      </script></head>\
      <body><div class=\"menu\">";
  for (uint8_t i = 1; i <= NUMBER_OF_GROUPS; i++) {
    out += "<div><button onClick=\"showGroup('g";
    out += i;
    out += "');\">";
    out += HomeGroups[i-1].group_name;
    out += "</button></div>";
  }
  out += "</div>";

  // print all groups
  for (uint8_t gid = 1; gid <= NUMBER_OF_GROUPS; gid++) {
    out += "<div class=\"group\" id=\"g";
    out += gid;
    out += "\"";
    String group_arg = getArgument("group");
    //Serial.println(group_arg);
    int sel_group_id = group_arg.toInt();
    if (sel_group_id == 0)
      sel_group_id = 1;
    out += (sel_group_id == gid ? "" : " style=\"display:none;\"");
    //out += (getArgument("group").toInt() == gid ? 
    out += ">";

    // get all items and status
    // print buttons / elements
    for (uint8_t i = 0; i < NUMBER_OF_ITEMS; i++) {
      if (HomeItems[i].group_id == gid) {
        if (HomeItems[i].type == LIGHT) {
            out += "\n<div><a href=\"?group=";
            out.concat(gid);
            out += "&item=";
            out.concat(HomeItems[i].id);
            out += "&value=";
            out += (HomeItems[i].current_state ==  OFF ? "ON" : "OFF");
            out += "\"><button";
            out += (HomeItems[i].current_state == ON ? " class=\"on\"" : "");  
            out += ">";
            out.concat(HomeItems[i].item_name);
            out += "</button></a></div>";
        }
        if (HomeItems[i].type == SHIELD) {
            out += "\n<div class=\"shield\"><a href=\"?group=";
            out.concat(gid);
            out += "&item=";
            out.concat(HomeItems[i].id);
            out += "&value=UP\"><button ";
            out += (HomeItems[i].current_state == UP ? " class=\"up_ok\"" : ((HomeItems[i].current_state == ON) && (HomeItems[i].set_state == UP) ? " class=\"up_on\"" : " class=\"up\"" ));  
            out += "> </button></a>";
            out += "<a href=\"?group=";
            out.concat(gid);
            out += "&item=";
            out.concat(HomeItems[i].id);
            out += "&value=STOP\"><button ";
            out += (HomeItems[i].current_state == OFF ? " class=\"st_stop\"" : " class=\"st\"");  
            out += ">";
            out.concat(HomeItems[i].item_name);
            out += "</button></a>";
            out += "<a href=\"?group=";
            out.concat(gid);
            out += "&item=";
            out.concat(HomeItems[i].id);
            out += "&value=DOWN\"><button ";
            out += (HomeItems[i].current_state == DOWN ? " class=\"dn_ok\"" : ((HomeItems[i].current_state == ON) && (HomeItems[i].set_state == DOWN) ? " class=\"dn_on\"" : " class=\"dn\"" ));  
            out += "> </button></a>";
            out += "</div>";
        }
      }
    }
    out += "</div>";
  }


  out += "</body></html>";
  server.send(200, "text/html", out);
  
}
