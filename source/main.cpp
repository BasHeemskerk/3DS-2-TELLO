#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <3ds.h>

#include <string>
using namespace std;

#include "included/network.hpp"
#include "included/tello_api.hpp"
#include "included/debug.hpp"
#include "included/renderer.hpp"
#include "included/app.hpp"

bool allowed_to_continue = false;

void initialize_app(){

	gfxInitDefault();

	// initialize block---------------------------
	DEBUG::initialize_debug();
	RENDERER::initialize_renderer();
	//---------------------------------------------

	//Load the launcher screen---------------------
	//LAUNCHER::load_launcher_background();
	//---------------------------------------------

	//Print to the bottom that it is debug console-
	DEBUG::print_to_Screen("\nDEBUG CONSOLE:\n\n", true, GFX_BOTTOM);
	//---------------------------------------------

	//Show some info in the debug screen-----------
	DEBUG::print_to_Screen(colored_text("red", "bold", "Initializing Tello API...\n"), false, GFX_BOTTOM);
	DEBUG::print_to_Screen(colored_text("green", "", "Tello API Initialized\n"), false, GFX_BOTTOM);
	DEBUG::print_to_Screen(colored_text("yellow", "", "--------------------------------\n"), false, GFX_BOTTOM);
	DEBUG::print_to_Screen(("Tello IP: " + string(tello_ip) + "\n").c_str(), false, GFX_BOTTOM);
	DEBUG::print_to_Screen(("Tello Port: " + string(tello_port) + "\n").c_str(), false, GFX_BOTTOM);
	DEBUG::print_to_Screen(colored_text("yellow", "", "--------------------------------\n"), false, GFX_BOTTOM);
	// Test connection block ----------------------
	NETWORK_FUNCTIONS::initialize_network();
	std::string system_ip_str = NETWORK_FUNCTIONS::retrieve_ip_address_alternative();
	const char* system_ip = system_ip_str.c_str();
	//---------------------------------------------
	DEBUG::print_to_Screen(("Local IP: " + string(system_ip) + "\n").c_str(), false, GFX_BOTTOM);
	DEBUG::print_to_Screen(("Local Port: " + string("8889") + "\n").c_str(), false, GFX_BOTTOM);
	DEBUG::print_to_Screen(colored_text("yellow", "", "--------------------------------\n"), false, GFX_BOTTOM);
	//---------------------------------------------

	//Load the launcher screen---------------------
	LAUNCHER::load_launcher_background();
	//---------------------------------------------

	//Set up a connection to the Tello-------------

	//---------------------------------------------

	
	//Setup complete-------------------------------
	if (initialized_network && ping_successfull && got_device_ip) {

		allowed_to_continue = true;

		DEBUG::print_to_Screen(colored_text("green", "", "Setup complete\n"), false, GFX_BOTTOM);
		DEBUG::print_to_Screen(colored_text("white", "", "Press A to start\n"), false, GFX_BOTTOM);
		DEBUG::print_to_Screen(colored_text("yellow", "", "--------------------------------\n"), false, GFX_BOTTOM);
	}
	else {
		DEBUG::print_to_Screen(colored_text("red", "", "Setup incomplete\n"), false, GFX_BOTTOM);
		DEBUG::print_to_Screen(colored_text("white", "", "Press START to exit\n"), false, GFX_BOTTOM);
		DEBUG::print_to_Screen(colored_text("yellow", "", "--------------------------------\n"), false, GFX_BOTTOM);
	}
	//---------------------------------------------
}

int main(int argc, char* argv[])
{

	initialize_app();

	// Main loop
	while (aptMainLoop())
	{
		//gspWaitForVBlank();
		//gfxSwapBuffers();
		hidScanInput();

		// Your code goes here
		u32 kDown = hidKeysDown();
		if (!allowed_to_continue){
			if (kDown & KEY_START)
				break; // break in order to return to hbmenu
		}
		else{
			if (kDown & KEY_A){
				DEBUG::print_to_Screen(colored_text("green", "bold", "Starting...\n"), false, GFX_BOTTOM);
				DEBUG::print_to_Screen(colored_text("yellow", "", "--------------------------------\n"), false, GFX_BOTTOM);
			}
		}
		

		LAUNCHER::render_launcher_background(GFX_TOP);
	}

	RENDERER::exit_renderer();

	gfxExit();
	return 0;
}
