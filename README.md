# Video-player-react-app

This repository hold the files required to recreate my Arduino / React player utilising Pubnub.
Place the App.css and vidoes into a public folder and execute the app.js within react.

The Arduino code was designed for use on a WeMOS D1 R1 board but can be modified to work on any Arduino.

The Ardiuno connect the board to the wifi, displays the IP address so checks can be made and then awating a keyboard input
Once the user presses 1,2 or 3 the code sends VIDEO1,VIDEO2 or VIDEO3 values to pubnub.

The React code sets up a subscribe listner from the pubnub channel VIDEOSELECTION and wait for an update.
Once upadate value is recieved checks against case statement to play relevent video.

please include follow these links and donalod the follow librabries to see application in full affect. 

https://www.npmjs.com/package/react-player

https://www.pubnub.com/docs/arduino/data-streams-publish-and-subscribe

