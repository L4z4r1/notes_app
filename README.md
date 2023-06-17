# notes app
Simple notes app made in c++ in 2 days as an learning challenge

# installing
you can either download the compiled binaries or compile it yourself with this command:
### Linux:
`g++ -Wall -std=c++17 notes.cpp -o notes -lboost_filesystem -lstdc++fs`

### Windows:
`clang -Wall -std=c++17 notes.cpp -o notes.exe -lboost_filesystem -lstdc++fs`
or 
`g++ -Wall -std=c++17 notes.cpp -o notes.exe -lboost_filesystem -lstdc++fs`

(Untested)

After compiling, you need to put the app in a seperate folder and in that folder, you need to create another folder called d_not (standing for Data_NOTes)
```
[Folder]
 |
 --> notes.exe (Linux: notes)
 |
 --> d_not (Folder)
```
# usage
After you've setup everything, go into the folder where the app is located and type (Windows)`notes.exe help` or (Linux)`./notes help`
it should output help and you can see commands from there

### output of ./notes help command:
```
notepad app v0.1
commands:

CMD  ARG1   ARG2   ARG3  :: ACTION
::::::::::::::::::::::::::::::::::::::::::::
new [NAME]               :: creates a new file for writing notes
 ls [FILE]               :: lists the contents of an file
wrt [DATA] [FILE]        :: writes into a file
chl [FILE] [LINE] [DATA] :: creates a new file for writing notes
lsn                      :: lists all notes
del [FILE]               :: delete a notes file (do * instead of [FILE] to delete all notes files)
help                     :: lists all commands and other stuff
::::::::::::::::::::::::::::::::::::::::::::

to write more than just one word to the notes, put what you want to write under ""
eg. >> notes wrt "I love ducks" [FILE]
```
disclaimer: some features won't work!
Features that are known to not work: 1 command(del *)

------------------------------------------------------

To create a new notes file, do `./notes new [name]` or `notes.exe new [name]` this will create a new notes file in the `d_not` directory
To write into the newly created notes file, do `./notes wrt [data] [file]` this will write [data] into [file]. If this command succseeds, you will recieve an message saying:
```
wrote [data] into [file]
```
and that's it for the startup, everything you need to know can be learned using the help command

# user errors
If the application fails to detect the existance of `d_not` file, it will attempt to create it, in some cases it will fail so that's why you should do it manually
If the application fails to read the user input or the necessary arguments aren't provided, it will `seg fault`
If the command isn't recognized, it will output `no command recognized!`

# advanced compilation

### $PATH support (tested in Linux)
If you like the application, and want to add it to $PATH, you will need to setup everything manually.
(this tutorial is assuming you don't already have a folder with $PATH setup)
1. create a new folder and name it whatever you want, I will name mine `custom_cmd`
2. open that folder and create a new file inside of it called `d_not`
3. go to the app source code and download it
4. install boost filesystem with `brew install boost` (assuming you have homeBrew installed)
5. compile the app with (Linux)`g++ -Wall -std=c++17 -Dsupport_i_dir -DI_DIR='"~/custom_cmd"' notes.cpp -o notes -lboost_filesystem -lstdc++fs` OR (Windows)`g++ -Wall -std=c++17 -Dsupport_i_dir -DI_DIR='"~/custom_cmd"' notes.cpp -o notes.exe -lboost_filesystem -lstdc++fs` where the -DI_DIR argument is supposed to have the full path where you will place your app (the path you will add to $PATH later)
6. copy the compiled binary to the desired path (in my case "~/custom_cmd")
7. add the path to $PATH, in my case, I will add `export PATH="$HOME/custom_cmd:$PATH"` into .bash_rc
8. try it out!
