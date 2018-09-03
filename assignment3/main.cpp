//
// main.cpp - Version 1.0
//
// This file is created by Tsz-Chiu Au on 10/23/17.
//
// You are *not* allowed to modify this file, and
// you do *not* submit this file.
//

#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include "Simulator.h"

using namespace std;


void printMenu() {
  cout << "Please select one of the following option:" << endl;
  cout << " a) Enter the number of machines." << endl;

  cout << " b) Schedule a request to add a new job." << endl;
  cout << " c) Schedule a request to remove a job." << endl;

  cout << " d) Run the simulation to the end." << endl;
  cout << " e) Run the simulation to the next event." << endl;

  cout << " f) Print the current state of the simulation." << endl;

  cout << " z) Quit this program." << endl;
}

int main(int argc, char *argv[]) {

  bool isVerbose = true;

  // the -q option turns off some outputs to help grading

  if (argc==2) {
    if (strcmp(argv[1], "-q")==0) {
      isVerbose = false;
    }
  }

  try {

    Simulator sim;

    bool isExit = false;

    while (!isExit) {  // loop until the user choose to quit

      if (isVerbose) printMenu();

      if (isVerbose) cout << "Your choice: ";
      char choice;
      cin >> choice;

      cin.get();  // get rid of the newline character

      if (isVerbose) cout << endl;

      switch (choice) {
        case 'a': {  // Enter the number of machines.
          if (sim.getMachineNum() > 0) {
            cout << "You have already entered the number of machines." << endl;
            break;
          }
          int machine_num;
          if (isVerbose) cout << "Please enter the number of machines: ";
          cin >> machine_num;
          if (machine_num <= 0) {
            cout << "The number of machines must be at least 1." << endl;
            break;
          }
          sim.setMachineNumber(machine_num);
          break;
        }
        case 'b': {  // Schedule a request to add a new job
          if (sim.getMachineNum() == 0) {
            cout << "You have not entered the number of machines first." << endl;
            break;
          }
          float request_time;
          int job_id;
          float duration;

          if (isVerbose) cout << "Please enter the request time: ";
          cin >> request_time;
          if (request_time < 0.0) {
            cout << "The request time must be at least 0." << endl;
            break;
          }

          if (isVerbose) cout << "Please enter the job ID: ";
          cin >> job_id;
          if (job_id < 0) {
            cout << "The jod ID must be at least 0." << endl;
            break;
          }

          if (isVerbose) cout << "Please enter the duration: ";
          cin >> duration;
          if (duration < 0.0) {
            cout << "The duration must be at least 0." << endl;
            break;
          }
          sim.requestAddJob(request_time, job_id, duration);
          break;
        }
        case 'c': {  // Schedule a request to remove a job
          if (sim.getMachineNum() == 0) {
            cout << "You have not entered the number of machines first." << endl;
            break;
          }
          float request_time;
          int job_id;

          if (isVerbose) cout << "Please enter the request time: ";
          cin >> request_time;
          if (request_time < 0.0) {
            cout << "The request time must be at least 0." << endl;
            break;
          }

          if (isVerbose) cout << "Please enter the job ID: ";
          cin >> job_id;
          if (job_id < 0) {
            cout << "The jod ID must be at least 0." << endl;
            break;
          }

          sim.requestRemoveJob(request_time, job_id);
          break;
        }
        case 'd': {  // Run the simulation to the end
          if (sim.getMachineNum() == 0) {
            cout << "You have not entered the number of machines first." << endl;
            break;
          }
          if (!sim.hasNextEvent()) {
            cout << "There is no event to simulate." << endl;
            break;
          }
          do {
            Event event = sim.run_next_event();
            cout << "Finished event: " << event << endl;
          } while(sim.hasNextEvent());
          cout << "Simulation End" << endl;
          break;
        }
        case 'e': {  // Run the simulation to the next event
          if (sim.getMachineNum() == 0) {
            cout << "You have not entered the number of machines first." << endl;
            break;
          }
          if (!sim.hasNextEvent()) {
            cout << "There is no event to simulate." << endl;
            break;
          }
          Event event = sim.run_next_event();
          cout << "Finished event: " << event << endl;
          break;
        }
        case 'f': {  // Print the current state of the simulation
          cout << std::fixed << std::setprecision(2);
          cout << "Current Time: " << sim.getCurrentTime() << "  ";
          cout << "The number of busy machines: " << sim.getBusyMachineNum() << "/" << sim.getMachineNum() << endl;

          sim.printJobStatusRecord();
          sim.printJobQueue();
          sim.printEventQueue();
          break;
        }

        case 'z':  // exit the program
          if (isVerbose) cout << "Bye!" << endl;
          isExit = true;
          break;
        default:
          cout << "Error: Unknown option." << endl;
      }
      if (isVerbose) cout << endl;
    }

    return 0;

  } catch(const exception& e) {
    // The error message should be printed to cerr,
    // but for grading purpose, we print it to cout.
    cout << "Error: " << e.what() << endl;
  }

  return 0;
}

