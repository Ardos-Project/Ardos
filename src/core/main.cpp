#include <iostream>

#include "notifier/Notify.h"

int main(int argc, char *argv[])
{
	Notify* notify = new Notify();
	notify->info("Test");
	return 0;
}
