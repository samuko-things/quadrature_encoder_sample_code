# quadrature encoder sample code
this arduino sample code shows how to use a geared DC motor with quadrature encoder
You are free to use the code in your preferred project.
(It uses the L298n driver)

## MOTOR POWER (M+ and M-) CONNECTION CHECK
Send positive PWM commands to the motor so it begins to rotate, if rotation is counterclockwise then the motor (M+ and M-) is properly connected. If not (i.e. it’s rotating clockwise), switch the M+ and M- connection and test it again you should see it now rotating counterclockwise.

## MOTOR ENCODER PIN (A and B) CONNECTION CHECK
Once the motor is connected properly as stated above
Check the printed angular pos during rotation. if postion is positive, then (A and B) is properly connected. If not switch the A and B connections and test it again.

> Check out my smc_L298N_pid_driver module [Click Here]()