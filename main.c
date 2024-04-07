#include <Windows.h>

#include <stdio.h>
#include <stdlib.h>



static const char USAGE_MSG[] = "USAGE: <KEYCODE>(0-255) [INTERVAL](Default: 1 (ms))";



static int keycode;
static int interval = 1;



static INPUT out[2] = {

	{

		.type = INPUT_KEYBOARD,

		.ki = {0, 0, KEYEVENTF_KEYUP, 0, 0}

	},

	{

		.type = INPUT_KEYBOARD,

		.ki = {0}

	}

};



int main(int argc, char* argv[]) {

	if (argc != 2 && argc != 3) { puts(USAGE_MSG); return 0; }



	keycode = atoi(argv[1]);
	if (keycode == 0) { puts("ERROR: argument 1 is not a valid number"); return 1; }
	if (keycode < 0 || keycode > 255) { puts("ERROR: argument 1 is not a valid keycode"); return 1; }

	out[0].ki.wVk = keycode;
	out[1].ki.wVk = keycode;



	if (argc == 3) {

		interval = atoi(argv[2]);
		if (interval == 0) { puts("ERROR: argument 2 is not a valid number"); return 1; }
		if (interval < 0) { puts("ERROR: given interval is negative"); return 1; }

	}



	for (;;) {

		if (GetAsyncKeyState(keycode) & 0x8000) { SendInput(2, out, sizeof(INPUT)); }

		Sleep(interval);

	}



	return 0;

}
