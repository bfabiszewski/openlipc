/*  openlipc-get.c
 *  replacement for lipc-prop-get
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
   printf("Usage: %s [-is] <publisher> <property-name>\n", title);
   printf("        -i           - int property\n");
   printf("        -s           - string property\n");
   exit(1);
}

int main(int argc, char **argv) {
  char publisher[255] ;
  char property[255];
  char *svalue;
  int ivalue;
  int lipc_handle, lipc_status;
  int is_int = 0;
  
  if (argc < 4) {
    usage(argv[0]);
  }
   
  if (strcmp(argv[1],"-i") == 0) {
    is_int = 1;
  } else if (strcmp(argv[1],"-s") != 0) {
    usage(argv[0]);
  }
    
  snprintf(publisher, sizeof(publisher), "%s", argv[2]);
  snprintf(property, sizeof(property), "%s", argv[3]);
  
  lipc_handle = LipcOpenNoName();
  if (!lipc_handle) {
    printf("Failed to open LIPC\n");
    return 1;
  }
  
  if (is_int) {
    lipc_status = LipcGetIntProperty(lipc_handle, publisher, property, &ivalue);
    if (!lipc_status) printf("%d\n", ivalue);
  } else {
    lipc_status = LipcGetStringProperty(lipc_handle, publisher, property, &svalue);
    if (!lipc_status) {
      printf("%s\n", svalue);
      LipcFreeString(svalue);
    }
  }

  LipcClose(lipc_handle);

  if (!lipc_status) {
    return 0;
  } else {
    printf("%s failed to get value for property %s (0x%x %s)\n", publisher, property, lipc_status, LipcGetErrorString(lipc_status));
    return 0;
  }
}
