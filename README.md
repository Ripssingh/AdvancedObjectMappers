# AdvancedObjectMappers
Contains mapper Classes to actual objects in base controllers.

1. Command mapper- maps the command object in base controller to the one in the supervisory device. This command object can command other objects in the base controller

2. Global data Signal mapper - maps gds object in base controller  to the one in the supervisory device.  The gds objects contains a one master and a list of slaves. The master object value is also set to all the slaves when commanded so.

3. Signal Select mapper- maps sgsl object to supervisory device. The sgsl object and send signals to different objects on the determining varies condition like less than <, equal to =, or greater than >.
