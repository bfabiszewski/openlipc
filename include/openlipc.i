 %module OpenLipc
 %{
 /* Includes the header in the wrapper code */
 #include "openlipc.h"
 %}
 
 /* Parse the header file to generate wrappers */
 %include "openlipc.h"
