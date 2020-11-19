
/*


          Name:Spixa Command Handler
          Version ("Maj"."Min"."Bui" "Prototype") : 0.1.14 Undone


          Licensed under MIT

         Coded by: Spixa
         On GitHub: @Spixa



         Simple command handler for education purposes only :D
*/
#include <iostream>
#include <string>
bool isOn = true;

class Commands {
	public:

	enum HolderType { // Collection of holder type
		COMMAND, // 0
		DESCRIPTION, //1
		NAME, // 2
		USAGE, // 3
		MANUAL, // 4
		DUMMY // 5
	};

	enum CommandList {
		HELPCOMMAND,
		INFOCOMMAND,
		MANUALCOMMAND,
		EXITCOMMAND


	};

	unsigned int getCommandCount() { return commandCount;} //... getter for "command count"


	// pseudo hashmap sysyem. (similar to std::hashmap, f: cpp11)
	std::string access(int type,int index) {
	    std::string data;

	try {
		if (type == COMMAND)
		     data = command[index];
		if (type == DESCRIPTION)
		     data = description[index];
		if (type == NAME)
		     data = name[index];
		if (type == USAGE)
		     data = usage[index];
		if (type == MANUAL)
		     data = manual[index];
		if (type >= DUMMY)
		      throw -1;



	} catch (int caught_exception) {
		if (caught_exception == -1)
		    std::cout << "Error: Exception caught.\n";

	}
		return data;
	}





	const static unsigned int commandCount = 4;

	/*
	   Command error: (debug only)
	   help 1
	   info 2
	   man 3




	*/


    std::string command[commandCount] = {
		"help",
		"info",
		"man",
		"exit"






	};
	std::string description[commandCount] = {
		"Shows this page.", // help
		"Info of this->host", // info
		"Manual for all the commands",
		"Exits"


	};
	std::string name[commandCount] = {
		"Help",
		"Host Information",
		"Manual",
		"Exit"



	};

	std::string usage [commandCount] = {
		"",
		"<String: Detail>",
		"[String: commandName]",
		""



	};

	std::string manual[commandCount] = {
		"Helps you with the basic commands and gives a short description about the commands.",
		"Displays basic host information, such as version and build number.",
		"Opens a manual page giving in-depth explanation of each command.",
		"Exits"


	};




};

class CommandListener {
	public:
		void run(std::string str, std::string arg[])
	{
		std::string word = "";
		int i = 0;
		for (auto x : str)
		{
			if (x == ' ')
			{
				i++;
				arg[i] = word;

				word = "";
			}
			else
			{
				word = word += x;
			}

			arg[i] = word;
		}
	}
	    void input() {
	    	bool isRun = true;
	    	std::cout << "$process_command:  ";
	    	std::string data[200];
	    	std::string input;

	    	std::getline(std::cin,input);
	    	run(input,data);
	    	handleCommandRunnable(data,isRun);

	    	for (int i = 200; i > 0;i--) data[i] = "";


	    }


	protected:
	   Commands c;
	   void handleCommandRunnable(std::string arg[],bool arg1) {
	   	if (!arg1) return;

	   	if (arg[0] == c.access(c.COMMAND,c.HELPCOMMAND)) helpCommand();

	   	else if (arg[0] == c.access(c.COMMAND,c.EXITCOMMAND)) exitCommand();

	   	else if (arg[0] == c.access(c.COMMAND,c.INFOCOMMAND)) infoCommand();
	   	else if (arg[0] == c.access(c.COMMAND,c.MANUALCOMMAND)) manualCommand(arg[1]);
	   	else wrongCommand(arg[0]);



	   }

	   void handleCommandExecutable() {

	   }


	  private: // Command Funcions
	   void helpCommand() {
	   	for (int i =0; i < (int) c.commandCount;i++) {
	   		std::cout << c.command[i] << ": " << c.name[i] << " command\n\tUsage: \"" << c.command[i] << " " << c.usage[i] << "\"\n\t " << c.description[i] << "\n";

	   	}
	   }
	   void infoCommand() {
	   	std::cout << "Spixa's OpenSource CommandHandler -\nVersion: 0.1.14 Undone\n\n\t* Do \"help\" to get help\n\n";


	   }

	   void manualCommand(std:: string s) {

	   	bool d[2048]; // C99 feature i know. this warning is unfixable if you are using C98

	   	for ( int i = (int) c.commandCount;i > 0;i--) {
	   		if (s == c.command[i]) {
	   		   std::cout << "Manual for the \"" << c.name[i] << " command\"" << "\n\t" << c.manual[i] << "\n";
	   		   d[i] = true;
	   		}

	   	}
	   	for (int i = (int) c.commandCount; i > 0;i--) {
	   		if (d[i] == true ) return;

	   	}
	   	std::cout << "Can't load manual for that command.\n\tCommand does not exist\n\t\tDid you spell " << s << " correctly?\n\tCommand does not a manual node\n";
	   }
	   void exitCommand() {
	   	std::cout << "Throwing 0 as exit code\n";
	   	isOn = false;

	   }


	   void wrongCommand(std::string cmd) {
	   	std::cout << "Error: No instance of command " << cmd << " internally and/or externally.\n";
	   	std::cout << "\tCheck if you have spelt the command correctly\n\t\t" << cmd << " may be spelt wrong.\n\tCheck if you have enough permission to run this command.\n\t\tYou may not be permitted to run " << cmd << "\n";
	   }

};



class Host {

public:

   void run() {
   	construct();
   	virtualLoop();

   }

protected:

   CommandListener* cl;
   void construct() {
   	cl = new CommandListener;


   }


   void update() {
   	 cl->input();

   }


private:

   void virtualLoop() {
   	while (isOn) {
   		update();


   	}

   }




};


int main()
{
	std::cout << "Spixa's CommandHandler - 0.1.14 Undone\n\n\t* Do \"help\" to get help\n\n";
	Host h;
	h.run();


	return 0;

}
