//
// Simulator.h - Version 1.0
//
// This file is created by Tsz-Chiu Au on 10/23/17.
//
// You are *not* allowed to modify this file, and
// you do *not* submit this file.
//

#ifndef ASSIGNMENT3_SIMULATOR_H
#define ASSIGNMENT3_SIMULATOR_H

#include <iostream>
#include <sstream>
#include <iomanip>
#include <list>
#include "HeapPriorityQueue.h"
#include "HashMap.h"

using namespace std;


/*
 * The forward declaration of the comparator of Event for ordering the events in the event_queue
 */
class EventLessThanComparator;


/*
 * Event
 */
class Event {
public:

  /*
   * The type of events
   */
  enum EventType { JOB_START, JOB_END, JOB_ADDITION, JOB_REMOVAL };

protected:

  float time;       // the time at which the event should happen
  int job_id;       // the job id associated with this event
  EventType type;   // the event type

public:

  /*
   * Default constructor
   */
  Event() {}

  /*
   * The basic constructor for all events.
   *
   * _time   - the time at which the event will happen
   * _job_id - the job id
   * _type   - the event type
   */
  Event(float _time, int _job_id, EventType _type) : time(_time), job_id(_job_id), type(_type) {}

  float getTime() const { return time; }       // get the time at which the event should happen
  int getJobId() const { return job_id; }      // get the job id associated with this event
  EventType getType() const { return type; }   // get the event type

  /*
   * Get the string describing this event.
   */
  virtual string toString() const {
    stringstream ss;
    ss << std::fixed << std::setprecision(2);
    ss << time << ": ";
    switch(type) {
      case JOB_START:
        ss << "START";
        break;
      case JOB_END:
        ss << "END";
        break;
      case JOB_ADDITION:
        ss << "ADD";
        break;
      case JOB_REMOVAL:
        ss << "REMOVE";
        break;
    }
    ss << " Job " << job_id;
    return ss.str();
  }

  friend class EventLessThanComparator;
  friend ostream& operator<<(ostream &out, const Event& event);
};

/*
 * The comparator of Event for ordering the events in the event_queue
 */
class EventLessThanComparator {
public:
  /*
   * Compare two events according to their time.
   * If they occur at the same time, order them according to their job IDs.
   *
   * event1 - the first event
   * event2 - the second event
   *
   * return true if the event1 should happen before event2
   */
  bool operator()(const Event* event1, const Event* event2) const {
    if (event1->time < event2->time) {
      return true;
    } else if (event1->time == event2->time) {
      if (event1->job_id == event2->job_id) throw runtime_error("Cannot have two events with the same time and the same Job id.");
      return event1->job_id < event2->job_id;
    } else {
      return false;
    }
  }
};


/*
 * The event for starting a job.
 */
class JobStartEvent : public Event {
public:
  /*
   * Constructor
   *
   * time   - the time at which the event will happen
   * job_id - the job id
   */
  JobStartEvent(float time, int job_id) : Event(time, job_id, JOB_START) {}
};


/*
 * The event for ending a job.
 */
class JobEndEvent : public Event {
public:
  /*
   * Constructor
   *
   * time   - the time at which the event will happen
   * job_id - the job id
   */
  JobEndEvent(float time, int job_id) : Event(time, job_id, JOB_END) {}
};


/*
 * The event for adding a new job.
 */
class AddJobEvent : public Event {
  float duration;   // the duration of the job
public:
  /*
   * Constructor
   *
   * _time     - the time at which the event will happen
   * _job_id   - the job id
   * _duration - the duration of the job
   */
  AddJobEvent(float _time, int _job_id, float _duration) :
      Event(_time, _job_id, JOB_ADDITION), duration(_duration) {}

  /*
   * Get the duration of the job.
   */
  float getDuration() const { return duration; }

  /*
   * Get the string describing this event.
   */
  virtual string toString() const {
    stringstream ss;
    ss << std::fixed << std::setprecision(2);
    ss << " (" << "duration=" << duration << ")";
    return Event::toString() + ss.str();
  }
};

/*
 * The event for removing a new job.
 */
class RemoveJobEvent : public Event {
public:
  /*
   * Constructor
   *
   * time   - the time at which the event will happen
   * job_id - the job id
   */
  RemoveJobEvent(float time, int job_id) : Event(time, job_id, JOB_REMOVAL) {}
};



/*
 * The simulator
 */
class Simulator {

  /*
   * A Job in the Job Queue.
   */
  class Job {
    float request_time;   // the request time
    int job_id;           // the job id
    float duration;       // the duration of the job
  public:

    /*
     * Default constructor
     */
    Job() {}

    /*
     * Constructor
     *
     * _request_time - the request time
     * _job_id       - the job id
     * _duration     - the duration of the job
     */
    Job(float _request_time, int _job_id, float _duration) :
        request_time(_request_time), job_id(_job_id), duration(_duration) {}

    friend bool operator<(const Job& lhs, const Job& rhs);
    friend ostream& operator<<(ostream &out, const Job& job);
    friend class Simulator;
  };

  // Need to friend these functions twice in order to expose the private inner class for
  // their definition in Simulator.h.
  // See https://stackoverflow.com/questions/8082190/overloading-operator-for-a-nested-private-class-possible
  friend ostream& operator<<(ostream &out, const Simulator::Job& job);
  friend bool operator<(const Simulator::Job& job1, const Simulator::Job& job2);


  /*
   * The forward declaration of JobStatus
   */
  class JobStatus;

  /*
   * Define the types of the job queue, the event queue, and the job status record
   */
  typedef HeapPriorityQueue<Job, LessThanComparator<Job> > JobQueue;
  typedef HeapPriorityQueue<Event*, EventLessThanComparator> EventQueue;
  typedef HashMap<int,JobStatus,IntHashComparator > JobStatusRecord;


  /*
   * The status of a job
   */
  class JobStatus {

    /*
     * The types of a job status
     */
    enum Type { QUEUED, UNQUEUED, SCHEDULED, STARTED, ENDED, REMOVED };

    Type status;                                  // the job status
    JobQueue::Position job_queue_pos;             // the position on the job queue
    EventQueue::Position event_queue_start_pos;   // the position of the start job event on the event queue
    EventQueue::Position event_queue_end_pos;     // the position of the end job event on the event queue
    EventQueue::Position event_queue_add_pos;     // the position of the add job event on the event queue

  public:

    /*
     * Default constructor
     */
    JobStatus() {}

    /*
     * Constructor
     *
     * _status - the type of the status
     */
    JobStatus(Type _status) : status(_status) {}


    friend class Simulator;
    friend ostream& operator<<(ostream &out, const JobStatus& js);
  };

  friend ostream& operator<<(ostream &out, const Simulator::JobStatus& js);

public:

  /*
   * Constructor
   */
  Simulator() : machine_num(0), busy_machine_num(0), current_time(0.0) {}

  /*
   * Set the machine number
   *
   * _machine_num - the number of machines
   */
  void setMachineNumber(int _machine_num) {
    if (_machine_num <= 0) throw runtime_error("The number of machines must be at least 1.");
    machine_num = _machine_num;
  }

  /*
   * Schedule a request to add a new job
   *
   * request_time - the request time
   * job_id       - the job id
   * duration     - the duration of the job
   */
  void requestAddJob(float request_time, int job_id, float duration);

  /*
   * Schedule a request to remove a job
   *
   * request_time - the request time
   * job_id       - the job id
   */
  void requestRemoveJob(float request_time, int job_id);

  /*
   * Is there a next event in the event queue?
   *
   * Return true if there is a next event in the event queue
   */
  bool hasNextEvent() const { return !event_queue.empty(); }

  /*
   * Run the simulation until the time of the next event,
   * and then simulate the event. The current time
   * will be advanced to the time of the event.
   *
   * Return the event that have been simulated
   */
  Event run_next_event();

  /*
   * Get the current time of the simulator
   */
  float getCurrentTime() const { return current_time; }

  /*
   * Get the number of machines
   */
  int getMachineNum() const { return machine_num; }

  /*
   * Get the number of machines that are currently working on some jobs.
   */
  int getBusyMachineNum() const { return busy_machine_num; }

  /*
   * Print the job queue
   */
  void printJobQueue();

  /*
   * Print the event queue
   */
  void printEventQueue();

  /*
   * Print the status of all jobs
   */
  void printJobStatusRecord();

private:

  /*
   * The event handler
   */
  void eventHandler(const Event *evt);

  /*
   * The event handler for JobStartEvent
   *
   * evt - the JobStartEvent
   */
  void jobStartEventHandler(const JobStartEvent& evt);

  /*
   * The event handler for JobEndEvent
   *
   * evt - the JobEndEvent
   */
  void jobEndEventHandler(const JobEndEvent& evt);

  /*
   * The event handler for AddJobEvent
   *
   * evt - the AddJobEvent
   */
  void addJobEventHandler(const AddJobEvent& evt);

  /*
   * The event handler for RemoveJobEvent
   *
   * evt - the RemoveJobEvent
   */
  void removeJobEventHandler(const RemoveJobEvent& evt);

  /*
   * Assign a job to a machine
   *
   * job_id   - the job id
   * duration - the duration of the job
   */
  void assignJobToMachine(int job_id, float duration);

  /*
   * Assign a job to the job queue
   *
   * request_time - the time at which the job is requested
   * job_id       - the job id
   * duration     - the duration of the job
   */
  void assignJobToJobQueue(float request_time, int job_id, float duration);

  /*
   * Free up a machine after it finishes a job.
   */
  void freeMachine();

private:
  JobQueue job_queue;                   // the job queue
  EventQueue event_queue;               // the event queue
  JobStatusRecord job_status_record;    // the status of all jobs

  int machine_num;          // the number of machines
  int busy_machine_num;     // the number of machines that are currently running some jobs
  float current_time;       // the current time of the simulation
};


#endif //ASSIGNMENT3_SIMULATOR_H
