#include <gpiod.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>

#ifndef	CONSUMER
#define	CONSUMER	"consumer"
#endif

using namespace std;

int main (int argc, char** argv) {
	const char* chipname = "gpiochip1";
	struct gpiod_chip* chip;
	struct gpiod_line* lineLed;
	struct gpiod_line* lineButton;

	// open GPIO chip
	chip = gpiod_chip_open_by_name(chipname);
	if (!chip) {
		cerr << "Open chip failed\n";
	       	exit (1);	
	}
	// open GPIO lines
	// P9_15
	lineLed = gpiod_chip_get_line(chip, 16);
	if (!lineLed) {
		cerr << "Get Led failed\n";
		exit (1);
	}
	// P9_23
	lineButton = gpiod_chip_get_line(chip, 17);
	if (!lineButton) {
		cerr << "Get button failed\n";
		exit (1);
	}
	// open LED line for output
	gpiod_line_request_output(lineLed, CONSUMER, 0);
	// open Button for input
	gpiod_line_request_input(lineButton, CONSUMER);	
	
	int timeSleep = 500000;
	int countButton = 0;
	int ButtonThresh = 100;
	while (true) {
		// read button
		int val = gpiod_line_get_value(lineButton);
		if (val == 1) {
			cout << "click recieved, current sleep time is: " << timeSleep << "\n";
			countButton++;
			if (countButton >= ButtonThresh) {
				// reset frequency
				timeSleep = 500000;
			} else {
				timeSleep /= 2;
			}
		} else {
			countButton = 0;
		}
		gpiod_line_set_value(lineLed, 1);
		usleep(timeSleep);
		gpiod_line_set_value(lineLed, 0);
		usleep(timeSleep);
	}
	gpiod_line_release(lineLed);
	gpiod_line_release(lineButton);
	gpiod_chip_close(chip);
	return 0;
}
