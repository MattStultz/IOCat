#include <SPI.h>
#include <Ethernet.h>

#include <Twitter.h>

unsigned long my_time;
boolean triggered;

void setup(){
    pinMode(10, INPUT);
}

void loop(){

    if(triggered=true){
      if((millis()-my_time) >900000) //wait 15 min after last tweet avoid going faster and spamming the service
      {
        triggered = false; //reset triggers
      }
    }
    else
    {
        if(digitalRead(10)){ //button activated
            tweetMessage(); //send the tweet
            delay(1000);
            my_time = millis(); //set your timer
        }
     }
    
}

void tweetMessage(){
    Twitter twitter("3384059656-Fh8EjuIeoFRLTYLGCcruVbUedtsG3jsAeAeNEhq");// Place our key here.
    
    String stringMsg = "Meow! Watch me play at http://iocat.local:8080/"; //Message to be sent, be sure to replace with the address of your streaming server.
    

    //Convert our message to a character array
    char msg[140];
    stringMsg.toCharArray(msg, 140);

    //Tweet that sucker!
    twitter.post(msg);
}
