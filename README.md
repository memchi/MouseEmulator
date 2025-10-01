# MouseEmulator

Play with MouseEmulator

<https://github.com/memchi/MouseEmulator>

## Use Sysinternals junction

* <https://learn.microsoft.com/en-us/sysinternals/downloads/junction>

### examples

* To determine if a file is a junction, specify the file name
  * `junction c:\test`
* To list junctions beneath a directory, include the -s switch
  * `junction -s c:\`
* To create a junction c:\Program-Files for "c:\Program Files"
  * `junction c:\Program-Files "c:\Program Files"`
* To delete a junction, use the -d switch
  * `junction -d c:\Program-Files`

### usage

* Rename Arduino in this repo for now
  * `Arduino` -> `Arduino_`
* Create a junction clone of the relevant Arduino folder into this repo
  * `.\Tools\Junction\junction.exe .\Arduino %USERPROFILE%\Documents\Arduino`
    * use `Map_C_Users_USERPROFILE_Documents_Arduino_here.bat`
