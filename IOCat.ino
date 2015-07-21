#include <SPI.h>
#include <Ethernet.h>

#include <Twitter.h>

unsigned long my_time;
boolean triggered = false;
int count;

void setup(){
    pinMode(10, INPUT);
    Serial.begin(9600);
}

void loop(){

    if(triggered==true){
      if((millis()-my_time) >900000) //wait 15 min after last tweet avoid going faster and spamming the service
      {
        triggered = false; //reset triggers
        Serial.println("in wait");
      }
    }
    else
    {
        if(digitalRead(10)){ //button activated
            count = count +1;
            tweetMessage(); //send the tweet
            delay(1000);
            triggered = true;
            my_time = millis(); //set your timer
            Serial.println("triggered");
        }
     }
    
}

void tweetMessage(){
    Twitter twitter("3384059656-Fh8EjuIeoFRLTYLGCcruVbUedtsG3jsAeAeNEhq");// Place our key here.
    
    String stringMsg = "Meow! Watch me play at http://iocat.local:8080/ "; //Message to be sent, be sure to replace with the address of your streaming server add the milis to make the messge unique.
    stringMsg += count;
    stringMsg += " times";

    //Convert our message to a character array
    char msg[140];
    stringMsg.toCharArray(msg, 140);

    //Tweet that sucker!
    twitter.post(msg);
}
