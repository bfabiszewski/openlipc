/*  openlipc-send.c
 *  replacement for lipc-send-event
 *
 *  Copyright(C) 2013 Bartek Fabiszewski (www.fabiszewski.net)
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "include/openlipc.h"

void usage(char *title) {
   printf("Usage: %s <source> <event-name> [-is <value>]\n", title);
   printf("        -i           - int event_name\n");
   printf("        -s           - string event_name\n");
   exit(1);
}

int main(int argc, char **argv) {
  char source[255] ;
  char event_name[255];
  char value[255];
  int lipc_handle, event_handle;
  int lipc_status = 0;
  int is_int = 0;
  int is_value = 0;
  
  if (argc < 3) {
    usage(argv[0]);
  }
  snprintf(source, sizeof(source), "%s", argv[1]);
  snprintf(event_name, sizeof(event_name), "%s", argv[2]);
  
  if (argc >= 5) {
    is_value = 1;
    if (strcmp(argv[3],"-i") == 0) {
      is_int = 1;
    } else if (strcmp(argv[3],"-s") != 0) {
      usage(argv[0]);
    }
    
    snprintf(value, sizeof(value), "%s", argv[4]);
  }

  lipc_handle = LipcOpenEx(source, &lipc_status);
  if (!lipc_handle) {
    printf("Failed to open LIPC:lipc_status=%d\n", lipc_status);
    return lipc_status;
  }

  event_handle = LipcNewEvent(lipc_handle, event_name);
  if (!event_handle) {
    printf("Failed to create event\n");
    return 1;
  }
 
  if (is_value) { 
    if (is_int) {
      lipc_status = LipcAddIntParam(event_handle, atoi(value));
    } else {
      lipc_status = LipcAddStringParam(event_handle, value);
    }
    if (lipc_status != 0) {
      printf("Failed to add param\n");
      return lipc_status;
    }
  }

  lipc_status = LipcSendEvent(lipc_handle, event_handle);

  LipcClose(lipc_handle);

  if (lipc_status == 0) {
    return 0;
  } else {
    printf("Failed to send event %s from %s (0x%x %s)\n", event_name, source, lipc_status, LipcGetErrorString(lipc_status));
    return lipc_status;
  }
}
