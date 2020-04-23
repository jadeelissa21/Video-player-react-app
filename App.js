import React, { useCallback, useEffect, useState } from 'react';  
import PubNub from 'pubnub';   //import library for pubnub
import { PubNubProvider, usePubNub } from 'pubnub-react';//import library for pubnub
import './App.css'; //imports to CSS file for HTML syling
import ReactPlayer from "react-player"; //imports react player library
var videourl; // variable to store the location of the requested video
 
const pubnub = new PubNub({ //sets up a sequence of pubnub with pushlish and subscriber keys
  publishKey: 'YOUR PUBLISH KEY',
  subscribeKey: 'YOUR SUBSCRIBER KEY',
});
// tells pubnub to use VIDEOSELECTION chanel to hold values in pubnub
const channels = ['VIDEOSELECTION']; 
//sets up a sequence for a hook with pubnub variable required
const Hook = () => { 
const pubnub = usePubNub(); 
const [messages, setMessages] = useState([]);
const [input, setInput] = useState([]);

//sets up the pubnub listener to listen for published values in pubnub
// get relevant details from pubnub and stores in messages variable
useEffect(() => {
  pubnub.addListener({
    message: messageEvent => {
      setMessages([...messages, messageEvent.message]);
    },
  });
 
 //executes to pubnub listener
  pubnub.subscribe({ channels });
  }, [messages]);
// if statement to check if the value received from pubnub is VIDEO1,2 or 3
//if is VIDEO1 then sets vudeourl variable to location of video , same for 2 and 3
if (messages=="VIDEO1") {
    videourl=("videos\\Antarctica.mov");
    
  }
  if (messages=="VIDEO2") {
    videourl=("videos\\Australia.mov");
    
  }
  
  if (messages=="VIDEO3") {
    videourl=("videos\\Europe.mov");
    
  }

  //returns the below code to start the react player with the location of the video to play
  //and sets the player to loop the video indefinatly, location gained from above if statements
  return(
    <div className="App">
      <header className="App-header">
      <ReactPlayer playing url={videourl}
    loop={true} /> 
      </header>
    </div>
  );
  
 };


//blank functions to export hook
 const App = () => {
  return (
    <PubNubProvider client={pubnub}>
      <Hook />
    </PubNubProvider>
  );
};
 
export default App;
