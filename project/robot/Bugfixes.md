# CSCI3081: Bug List

In my project, there are some small bugs still exist.

1. I wrote Distress Sensor, DistressCall Event, TypeEmit Sensor and TypeEmit Event. However, I cannot find a right way to apply it to entities. When I want let entity in Arena Accept the EventDistressCall then all robot cannot accept collision event anymore. Thus, I comment those code.
2. The proximity event would affect all entities except player. It is correct but when the proximity sensor sensed the object, they would be jitter and stick together but not come to the opposite way.
3. I use the random number to reset the robot's position when user click Reset button. But it would lead more Google test errors.
4. I have not set the win and lose condition. I konw when all robots are frozen, then user wins. While user ran out of energy or all robots become to superbot, then user loses the game. I will implement the code after a few days.
5. I think my notifyObserver is useless. I still use the ent->Accept to update all entities. When I try to use the notifyObserver to update information, it would let all sensors useless. I cannot fix this problem at the last time.
6. I do not have enough time to write a fully worked test. My test can only test some getters and setters and cannot pass them all.


<hr>
