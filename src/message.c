/* IPwatchD - IP conflict detection in Linux systems
 * Copyright (C) 2007 Jaroslav Imrich <jariq@jariq.sk>
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *  
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *  
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA  02110-1301, USA.
 */  


#include "ipwatchd.h"


extern int debug_flag;
extern int syslog_flag;


/* message - handles output of messages generated by IPwatchD
 *
 * Parameters:
 *   - msg  - message to output
 *   - type - type of message
 *            Possible values: IPWATCHD_MESSAGE_INFO or IPWD_MSG_ERROR
 *            or IPWATCHD_MESSAGE_ALERT
 */
 
void ipwd_message(char *msg, int type) {

  /* IPwatchD running in debug mode prints all messages to STDOUT */
  if (debug_flag) {
  	
    fprintf(stdout, "%s", msg);
  
  /* IPwatchD running in normal mode */
  } else {
  	
  	/* In daemon mode - must record messages by syslog */
  	if (syslog_flag) {
  		
  	  switch (type) {
  	  	
  	    case IPWD_MSG_INFO:
  		  syslog(LOG_INFO, msg);
  		  break;
  		
        case IPWD_MSG_ERROR:
  		  syslog(LOG_ERR, msg);
  		  break;	
  		
  		case IPWD_MSG_ALERT:
  		  syslog(LOG_ALERT, msg);
  		  break;
  		    
  		default:	
  		  syslog(LOG_ERR, msg);
  		  break;
  	  
  	  }
  		
   	/* Not daemon yet - messages can be printed to terminal */	
  	} else {
  
  	  switch (type) {
  	  
  	    case IPWD_MSG_INFO:
  		  fprintf(stdout, "%s", msg);
  		  break;
  		
  		case IPWD_MSG_ERROR:
  		  fprintf(stderr, "%s", msg);
  		  break;	
  		
  		case IPWD_MSG_ALERT:
  		  fprintf(stderr, "%s", msg);
  		  break;
  		    
  		default:	
  		  fprintf(stderr, "%s", msg);
  		  break;
  		      		
      }

  	}
  	
  }  

}
