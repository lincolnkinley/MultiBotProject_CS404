# MultiBotProject_CS404
Multi Robot Communication, Distributed Computing, and Cooperation Project for CS404

This is the Final Project for CS 404, Autonomous Mobile Robots.
Included is a system for simulating multiple robots in a map that will work together to accomplish tasks as quickly as possible.
This software is designed to be deployed onto an arduino uno, so multiple design decisions were made around only having 2kB of RAM.
The software is almost capable of being depolyed onto an Arduino, the bluetooth send and recieve and run continuous still needs to be implemented.

In this system, robots will work together to accomplish missions as fast as possible.
Missions consist of a variable number of tasks in a list.
Tasks are represented by a space on a map that a robot must spend a specific amount of time at (simulating working).

Missions can be given to the robots at any point in time during operation.
Missions are completed in FIFO order, but the tasks in a mission are completed by robots finding which task is closest to them and doing it.
The robots communicate with each other by using a distance delay volunteering system to determine which robot is closer.

The system relies on a server to give out the missions, and allow the robots to communicate.
Originally, we wanted to use a Bluetooth mesh network for the robots to communicate, however mesh networks are already advanced topics.
Instead we decided to go with using the server for communicating.

Once of the benefits of this system is had we used a Mesh Network, the server would do ablsolutly no computation outside of sending tasks to the robots.
This allows the to scale to a large number of robots without the use of a powerful server.

The inspiration for this system was an Automated Distribution Warehouse (like Amazon).
The goal of the Distribution Center is to ship as many orders as possible in a single day.
In order to ship an order, all the items of that order must be collected and brought to the shipping dock.
Orders are simlar to missions, and the items in that order are similar to tasks.
Missions are done FIFO for two reasons,
    - We want to guarantee that an order will be shipped within a given time frame
    - Ending the day with multiple partially collected orders is bad, because we can't ship partial orders
Tasks on the other hand, should be done as quicky as possible.
