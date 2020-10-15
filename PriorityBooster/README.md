# PriorityBooster Driver

Code for the PriorityBooster driver. Build using Visual Studio 2019, make sure you set the right architecture.  
Before installing make sure the system is in test signing mode through:  
`bcdedit /set testsigning on`  

After that just install the driver using sc.exe  
`sc.exe create PriorityBooster type= kernel binPath= C:\Absolute\Path\To\Driver.sys`  
Make sure you actually put a space character between after `type=` and `binPath=`  

Start the driver using sc.exe  
`sc.exe start PriorityBooster`  