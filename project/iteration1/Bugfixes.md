# CSCI3081: Bugfixes

In my project, there are some small bugs still exist. 

First one is that while the arena_mobile_entity moving, the jitter problem is not fixed. 

Then sometimes after the arena_mobile_entity hitting the wall and obstacles (recharge station), the angle is not so perfect that 100% match the physics.

Thirdly, sometimes home_base will go out of view then come back in one moment.

Plus, I use a simply way to show the win and lose. I just print the result in terminal then assert out of the view and there is a "Abort" behind it. I think there are some better ways to solve this problem. I will fix it.

Addtionally, I think my sensor class is not adapted to the design pattern because I only put a destructor in there. 
There is one place I have question which is that I am not sure do I need to write another home_base_handler to handle the hoem_base's movement.

Except the rand or rand_r problem, I have another google test error which happened in graphics_arena_viewer.cc DrawRobot function, line148. It seems like casting stuff cause the problem. However, if I change '(int)' to '< int >', it cannot compile anylonger. Thus, I leave this google test error after all it does not affect the whole project so much.



<hr>
