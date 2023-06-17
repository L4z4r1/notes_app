/*
Copyright (c) 2023 Lazar Vasilic. All rights reserved
This code is licenced under GNU General Public licence

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files to: distribute, copy, merge, modify, sell

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

Selling this software is allowed as far it's modified. Just straight up downloading software and reselling it is strictly prohibited.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.


By distributing and using this software, you agree with the licence.
*/
#include <iostream>
#include <iterator>
#include <string.h>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <libgen.h>
#include <fstream>
#include <filesystem>
#include <string>
//#include <boost/filesystem.hpp>
//#include <experimental/filesystem>

#ifndef I_DIR
  #define I_DIR "/home/lazar/Documents/CUSTOM_CMDS/"
#endif

using namespace std;

int main(int argc, char* argv[]) {
  #ifdef support_i_dir
  // Path to the desired working directory
  std::filesystem::path desiredPath = std::filesystem::path(I_DIR);

  // Set the current working directory
  std::filesystem::current_path(desiredPath);
  #endif

  #ifdef enable_debug
  const int DEBUG = 1;
  #else
  const int DEBUG = 0;
  #endif

  std::filesystem::path cP = std::filesystem::current_path();
  if (DEBUG==1) cout << "configured in: " << cP << endl;

  //configuring the default directory
  int f = chdir("d_not");
  if (DEBUG==1) cout << f << endl;
  if (f == -1){
    cout << "data folder not found, attempting to create new!" << endl;
    system("mkdir d_not");
  } if (f == 0) {
    (void)chdir("..");
  }


  // NEW NOTES FOLDER
  int cmd_new = (strcmp(argv[1], "new") == 0) || (strcmp(argv[1], "NEW") == 0);
  if (cmd_new) {
    ///////////////////////////
    // usage: app new [name] //
    ///////////////////////////
    // >> C/A1

    // going to the notes directory
    int e = chdir("d_not");
    string cmd = "touch " + string(argv[2]) + ".txt"; //creates the notes file
    int s = system(cmd.c_str());

    if (s == 0 && e == 0) {
      cout << "done.";
      (void)chdir(".."); //this is here and don't you dare fucking move it
      return 0;
    } else {
      cout << "something went wrong.";
      return 1;
    }
  }

  // write into the NOTES file
  int cmd_str = (strcmp(argv[1], "wrt") == 0) || (strcmp(argv[1], "WRT") == 0);
  if (cmd_str) {
    //////////////////////////////////
    // usage: app wrt [data] [file] //
    //////////////////////////////////
    // >> C/A1/A2

    // going to the notes directory
    int e = chdir("d_not");
    string o_file = argv[3] + string(".txt");
    ofstream file(o_file.c_str(), ios::app);

    if (e == 0 && file.is_open()) {
      file << argv[2] << endl;

      cout << "wrote " << argv[2] << " into " << argv[3] << endl;
      (void)chdir(".."); //this is here and don't you dare fucking move it

      file.close();

      return 0;

    } else {
      cout << "something went wrong.";
      return 1;
    }
  }

  // read from the NOTES file
  int cmd_ls = (strcmp(argv[1], "ls") == 0) || (strcmp(argv[1], "LS") == 0);
  if (cmd_ls) {
    //////////////////////////
    // usage: app ls [file] //
    //////////////////////////
    // >> C/A1

    // going to the notes directory
    int e = chdir("d_not");
    string o_file = argv[2] + string(".txt");
    ifstream file(o_file.c_str());

    if (e == 0 && file.is_open()) {

      string line;
      int lN = 1;
      // Read and print each line of the file
      while (getline(file, line)) {
        cout << lN << "| " << line << endl;
        lN++;
      }

      file.close();
      (void)chdir(".."); //this is here and don't you dare fucking move it
      return 0;

    } else {
      cout << "something went wrong.";
      return 1;
    }
  }

  // change line of the NOTES file with a new one
  int cmd_chl = (strcmp(argv[1], "chl") == 0) || (strcmp(argv[1], "CHL") == 0);
  if (cmd_chl) {
    /////////////////////////////////////////
    // usage: app chl [file] [line] [data] //
    /////////////////////////////////////////
    // >> C/A1/A2/A3

    int e = chdir("d_not");
    string inputFile = argv[2] + string(".txt");
    string temporaryFile = ".temp_file.tmp";
    int lineNumber = atoi(argv[3]); // Line number to replace
    string newLine = argv[4];

    ifstream file(inputFile);
    ofstream temp(temporaryFile);

    if (file.is_open() && temp.is_open() && e == 0) {
      string line;
      int currentLine = 1;

      // Read each line from the input file
      while (getline(file, line)) {
        if (currentLine == lineNumber) {
          // Replace the line with the new line
          temp << newLine << endl;
        } else {
          // Write the original line to the temporary file
          temp << line << endl;
        }
        currentLine++;
      }

      // Close both files
      file.close();
      temp.close();

      // Remove the original input file
      remove(inputFile.c_str());

      // Rename the temporary file to the original file name
      rename(temporaryFile.c_str(), inputFile.c_str());

      cout << "Line replaced successfully." << endl;
      (void)chdir("..");
    } else {
      cout << "Failed to open the files." << endl;
    }

    return 0;
  }

  // list all notes files created
  int cmd_lsn = (strcmp(argv[1], "lsn") == 0) || (strcmp(argv[1], "LSN") == 0);
  if (cmd_lsn) {
    ////////////////////
    // usage: app lsn //
    ////////////////////
    // >> C

    string directoryPath = "d_not"; // Replace with the actual directory path
//std::experimental::filesystem::directory_entry
    for (const auto& entry : std::filesystem::directory_iterator(directoryPath)) {
      if (entry.is_regular_file() && entry.path().extension() == ".txt") {
        string fileName = entry.path().filename().stem().string();
        cout << fileName << endl;
      }
    }

    return 0;
  }

  // delete a notes file
  int cmd_del = (strcmp(argv[1], "del") == 0) || (strcmp(argv[1], "DEL") == 0);
  if (cmd_del) {
    ///////////////////////////
    // usage: app del [FILE] //
    ///////////////////////////
    // >> C/A1
    int s = chdir("d_not");
    if (s == 0){
      if ((strcmp(argv[2], "*") == 0)) {
        try {
          (void)chdir("..");
          char* i;
          cout << "WARNING: You are about to PERMANETLY delete all your notes files\nAre you sure you want to perform this action?(Y/n) ";
          cin >> i;
          cout << endl;
          if (strcmp(i, "Y") == 0 || strcmp(i, "y") == 0) {
            std::filesystem::remove_all("d_not");
            system("mkdir d_not");
            return 0;
          } else if (strcmp(i, "N") == 0 || strcmp(i, "n") == 0) {
            cout << "user-triggered abortion!";
            return 0;
          } else {
            cout << "Uknown option, aborting!";
            return 1;
          }

        } catch (const std::filesystem::filesystem_error& error) {
          std::cout << "Uh, oh, something went wrong!\n > GENERATED ERROR: " << error.what() << std::endl;
          return 1;
        }
      } else {
        try {
          char* i;
          cout << "WARNING: You are about to PERMANETLY delete " << argv[2] << "\nAre you sure you want to perform this action?(Y/n) ";
          cin >> i;
          cout << endl;
          if (strcmp(i, "Y") == 0 || strcmp(i, "y") == 0) {
            std::filesystem::remove(argv[2] + string(".txt"));
            return 0;
          } else if (strcmp(i, "N") == 0 || strcmp(i, "n") == 0) {
            cout << "user-triggered abortion!";
            return 0;
          } else {
            cout << "Uknown option, aborting!";
            return 1;
          }

        } catch (const std::filesystem::filesystem_error& error) {
          std::cout << "Uh, oh, something went wrong!\n > GENERATED ERROR: " << error.what() << std::endl;
          return 1;
        }
      }
    } else {
      return 1;
    }
  }

  // print the licence
  int cmd_licence = (strcmp(argv[1], "licence") == 0) || (strcmp(argv[1], "LICENCE") == 0);
  if (cmd_licence) {
    ////////////////////////
    // usage: app licence //
    ////////////////////////
    // >> C
    string lines[] = {
        "Copyright (c) 2023 Lazar Vasilic. All rights reserved",
        "This code is licenced under GNU General Public licence",
        "Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files to: distribute, copy, merge, modify, sell\n"
        "\n"
        "The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.\n"
        "\n"
        "Selling this software is allowed as far it's modified. Just straight up downloading software and reselling it is strictly prohibited.\n"
        "\n"
        "THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.\n"
        "\n"
        "By distributing and using this software, you agree with the licence.\n"
    };

    for (const string& line : lines) {
      cout << line << endl;
    }

    return 0;
  }

  // help
  int cmd_hlp = (strcmp(argv[1], "help") == 0) || (strcmp(argv[1], "HELP") == 0) || (strcmp(argv[1], "") == 0);
  if (cmd_hlp) {
    cout << "notes  Copyright (C) 2023  Lazar Vasilic\nThis program comes with ABSOLUTELY NO WARRANTY. This is free software, and you are welcome to redistribute it under certain conditions; use the command `licence' for details." << endl;
    cout << endl;
    cout << "notepad app v0.1" << endl;
    cout << "commands:" << endl;
    cout << endl;
    cout << "CMD  ARG1   ARG2   ARG3  :: ACTION" << endl;
    cout << "::::::::::::::::::::::::::::::::::::::::::::" << endl;
    cout << "new [NAME]               :: creates a new file for writing notes" << endl;
    cout << " ls [FILE]               :: lists the contents of an file" << endl;
    cout << "wrt [DATA] [FILE]        :: writes into a file" << endl;
    cout << "chl [FILE] [LINE] [DATA] :: creates a new file for writing notes" << endl;
    cout << "lsn                      :: lists all notes" << endl;
    cout << "del [FILE]               :: delete a notes file (do * instead of [FILE] to delete all notes files)" << endl;
    cout << "help                     :: lists all commands and other stuff" << endl;
    cout << "::::::::::::::::::::::::::::::::::::::::::::" << endl;
    cout << endl;
    cout << "to write more than just one word to the notes, put what you want to write under \"\"" << endl;
    cout << "eg. >> " << argv[0] << " wrt \"I love ducks\" [FILE]" << endl;
  }
  cout << "no command recognized!";
  return 1;
}
