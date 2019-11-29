// Copyright (c) 2015 Cesanta Software Limited
// All rights reserved

#include "../../../Libraries/mongoose.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream> 
#include <chrono>
#include <algorithm>    // std::random_shuffle
#include <vector>       // std::vector
#include <cstdlib>      // std::rand, std::srand
#define TAM_MAX 50000

using namespace std;
using namespace std::chrono;
struct device_settings {
  char setting1[100];
  char setting2[100];
};

static const char *s_http_port = "8000";
static struct mg_serve_http_opts s_http_server_opts;
static struct device_settings s_settings = {"0", "1"};

char libro[TAM_MAX];

struct mg_str upload_fname(struct mg_connection *nc, struct mg_str fname) {
  // Just return the same filename. Do not actually do this except in test!
  // fname is user-controlled and needs to be sanitized.
  return fname;
}

void guardar_libro(){
    int destino=open("libro.txt",O_WRONLY|O_TRUNC|O_CREAT,0666);
    
      write(destino,libro,TAM_MAX);
    
   close(destino);
}


static void handle_save(struct mg_connection *nc, struct http_message *hm) {
  // Get form variables and store settings values
  mg_get_http_var(&hm->body, "setting1", s_settings.setting1,
                  sizeof(s_settings.setting1));
  mg_get_http_var(&hm->body, "setting2", s_settings.setting2,
                  sizeof(s_settings.setting2));
   mg_get_http_var(&hm->body, "file", libro,
                  TAM_MAX);
   guardar_libro();
   cout<<"libro_guardado"<<endl;
 
   

  // Send response
  mg_http_send_redirect(nc, 302, mg_mk_str("/"), mg_mk_str(NULL));
}

static void handle_respuesta(struct mg_connection *nc) {
  // Generate random value, as an example of changing CPU usage
  // Getting real CPU usage depends on the OS.
  int cpu_usage = (double) rand() / RAND_MAX * 100.0;

  // Use chunked encoding in order to avoid calculating Content-Length
  mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");

  // Output JSON object which holds CPU usage data
  mg_printf_http_chunk(nc, "{ \"respuesta\": %d,\"tiempo\": %d }", 1,2);

  // Send empty chunk, the end of response
  mg_send_http_chunk(nc, "", 0);
}

static void handle_ssi_call(struct mg_connection *nc, const char *param) {
  if (strcmp(param, "respuesta") == 0) {
    mg_printf_html_escape(nc, "%s", s_settings.setting1);
  } else if (strcmp(param, "tiempo") == 0) {
    mg_printf_html_escape(nc, "%s", s_settings.setting2);
  }
}

static void ev_handler(struct mg_connection *nc, int ev, void *ev_data) {
  struct http_message *hm = (struct http_message *) ev_data;

  switch (ev) {
    case MG_EV_HTTP_REQUEST:
    if (mg_vcmp(&hm->uri, "/respuesta") == 0) {
        handle_respuesta(nc);
      } else {
       
        mg_serve_http(nc, hm, s_http_server_opts);  // Serve static content


      }
   
       // mg_serve_http(nc, hm, s_http_server_opts);  // Serve static content
        //hm=(struct http_message*)ev_data;

    
      break;
       case MG_EV_HTTP_PART_BEGIN:
        case MG_EV_HTTP_PART_DATA:
         case MG_EV_HTTP_PART_END:
        // cout<<"paso algo"<<endl;
          mg_file_upload_handler(nc, ev, ev_data, upload_fname);
            // Send response
          if(ev==MG_EV_HTTP_PART_END){
                           auto start = high_resolution_clock::now();
        //princiapl
                auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
         cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl; 
         mg_http_send_redirect(nc, 302, mg_mk_str("/respuesta"), mg_mk_str(NULL));

          } 
   
      break;  
    case MG_EV_SSI_CALL:
      handle_ssi_call(nc, (char*)ev_data);
      break;
    default:
      break;
  }
}

static void push_data_to_all_websocket_connections(struct mg_mgr *m) {
  struct mg_connection *c;
  int memory_usage = (double) rand() / RAND_MAX * 100.0;

  for (c = mg_next(m, NULL); c != NULL; c = mg_next(m, c)) {
    if (c->flags & MG_F_IS_WEBSOCKET) {
      mg_printf_websocket_frame(c, WEBSOCKET_OP_TEXT, "%d", memory_usage);
    }
  }
}

int main(void) {
  struct mg_mgr mgr;
  struct mg_connection *nc;
  cs_stat_t st;

  mg_mgr_init(&mgr, NULL);
  nc = mg_bind(&mgr, s_http_port, ev_handler);
  if (nc == NULL) {
    fprintf(stderr, "Cannot bind to %s\n", s_http_port);
    exit(1);
  }

  // Set up HTTP server parameters
  mg_set_protocol_http_websocket(nc);
  s_http_server_opts.document_root = "web_root";  // Set up web root directory

  if (mg_stat(s_http_server_opts.document_root, &st) != 0) {
    fprintf(stderr, "%s", "Cannot find web_root directory, exiting\n");
    exit(1);
  }

  printf("Starting web server on port %s\n", s_http_port);
  for (;;) {
    static time_t last_time;
    time_t now = time(NULL);
    mg_mgr_poll(&mgr, 1000);
    if (now - last_time > 0) {
      push_data_to_all_websocket_connections(&mgr);
      last_time = now;
    }
  }
  mg_mgr_free(&mgr);

  return 0;
}
