//
// Simulator.cpp - Version 1.0
//
// This file is created by Tsz-Chiu Au on 10/23/17.
//
// You are *not* allowed to modify this file, and
// you do *not* submit this file.
//

#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <list>
#include "Simulator.h"
#include "HeapPriorityQueue.h"
#include "HashMap.h"

using namespace std;


ostream& operator<<(ostream &out, const Event& event) {
  out << event.toString();
  return out;
}


ostream& operator<<(ostream &out, const Simulator::Job& job) {
  out << std::fixed << std::setprecision(2);
  out << "Job " << job.job_id << " (duration = " << job.duration << ")";
  // no need to print job.request_time;
  return out;
}


bool operator<(const Simulator::Job& job1, const Simulator::Job& job2) {
  if (job1.request_time < job2.request_time) {
    return true;
  } else if (job1.request_time == job2.request_time) {
    if (job1.job_id == job2.job_id) throw runtime_error("Cannot have two jobs with the same request time and the same Job id.");
    return job1.job_id < job2.job_id;
  } else {
    return false;
  }
}


void Simulator::requestAddJob(float request_time, int job_id, float duration) {
  if (request_time < current_time) throw runtime_error("Cannot add job request before the current time.");
  event_queue.insert(new AddJobEvent(request_time, job_id, duration));
}


void Simulator::requestRemoveJob(float request_time, int job_id) {
  if (request_time < current_time) throw runtime_error("Cannot add job request before the current time.");
  event_queue.insert(new RemoveJobEvent(request_time, job_id));
}


Event Simulator::run_next_event() {
  if (machine_num <= 0) throw runtime_error("There is no machine.");
  if (event_queue.empty()) throw runtime_error("There is no next event.");

  Event* evt = event_queue.min();
  event_queue.removeMin();

  current_time = evt->getTime();    // update the current time
  eventHandler(evt);                // process the event

  Event tmp_evt = *evt;  // make a copy of the event
  delete evt;            // must delete the original event

  return tmp_evt;        // return the copy of the event
}


void Simulator::eventHandler(const Event *evt) {
  switch(evt->getType()) {
    case Event::JOB_START:{
      jobStartEventHandler(*dynamic_cast<const JobStartEvent*>(evt));
      break;
    }
    case Event::JOB_END:{
      jobEndEventHandler(*dynamic_cast<const JobEndEvent*>(evt));
      break;
    }
    case Event::JOB_ADDITION: {
      addJobEventHandler(*dynamic_cast<const AddJobEvent*>(evt));
      break;
    }
    case Event::JOB_REMOVAL:{
      removeJobEventHandler(*dynamic_cast<const RemoveJobEvent*>(evt));
      break;
    }
  }
}


void Simulator::jobStartEventHandler(const JobStartEvent& evt) {
  busy_machine_num++;
  if (busy_machine_num > machine_num) {
    throw runtime_error(" Error: assigned more jobs than the number of machines.");
  }
  job_status_record[evt.getJobId()].status = JobStatus::STARTED;
}


void Simulator::jobEndEventHandler(const JobEndEvent& evt) {
  job_status_record[evt.getJobId()].status = JobStatus::ENDED;
  freeMachine();
}


void Simulator::addJobEventHandler(const AddJobEvent& evt) {
  JobStatusRecord::Iterator iter = job_status_record.find(evt.getJobId());

  if (!(iter == job_status_record.end() || (*iter).value().status == JobStatus::UNQUEUED)) {
    throw runtime_error("Cannot add a job that has already been added previously.");
  }

  // decide what to do with the new job
  if (busy_machine_num < machine_num) {
    // some machine is free, we can schedule the job immediately
    assignJobToMachine(evt.getJobId(), evt.getDuration());
  } else {
    // no free machine, we put the job on the job queue
    assignJobToJobQueue(evt.getTime(), evt.getJobId(), evt.getDuration());
  }
}


void Simulator::removeJobEventHandler(const RemoveJobEvent& evt) {
  JobStatusRecord::Iterator iter = job_status_record.find(evt.getJobId());
  if (iter == job_status_record.end()) {
    throw runtime_error("Cannot remove job which does not exist.");
  }

  JobStatus job_status = job_status_record[evt.getJobId()];

  switch(job_status.status) {
    case JobStatus::QUEUED: {
      job_queue.remove(job_status.job_queue_pos);
      break;
    }
    case JobStatus::UNQUEUED: {
      event_queue.remove(job_status.event_queue_add_pos);
      break;
    }
    case JobStatus::SCHEDULED: {
      event_queue.remove(job_status.event_queue_start_pos);
      event_queue.remove(job_status.event_queue_end_pos);
      freeMachine();
      break;
    }
    case JobStatus::STARTED: {
      event_queue.remove(job_status.event_queue_end_pos);
      freeMachine();
      break;
    }
    case JobStatus::ENDED: {
      // do nothing
      break;
    }
    case JobStatus::REMOVED: {
      throw runtime_error("Should not remove the same job twice.");
    }
  }

  job_status_record[evt.getJobId()].status = JobStatus::REMOVED;
}


void Simulator::assignJobToMachine(int job_id, float duration) {
  job_status_record[job_id] = JobStatus(JobStatus::SCHEDULED);
  EventQueue::Position p1 = event_queue.insert(new JobStartEvent(current_time, job_id));
  EventQueue::Position p2 = event_queue.insert(new JobEndEvent(current_time + duration, job_id));
  job_status_record[job_id].event_queue_start_pos = p1;   // remember the position of the start event in the event queue
  job_status_record[job_id].event_queue_end_pos = p2;     // remember the position of the end event in the event queue
}


void Simulator::assignJobToJobQueue(float request_time, int job_id, float duration) {
  JobQueue::Position p = job_queue.insert(Job(request_time, job_id, duration));
  job_status_record[job_id] = JobStatus(JobStatus::QUEUED);
  job_status_record[job_id].job_queue_pos = p;   // remember the position of the job in the job queue
}


void Simulator::printJobQueue() {
  cout << "Job Queue:" << endl;

  JobQueue tmp_job_queue(job_queue);
  while(!tmp_job_queue.empty()) {
    Job job = tmp_job_queue.min();
    tmp_job_queue.removeMin();
    cout << "  " << job << endl;
  }
}


void Simulator::printEventQueue() {
  cout << "Event Queue:" << endl;

  EventQueue tmp_event_queue(event_queue);
  while(!tmp_event_queue.empty()) {
    Event* event_ptr = tmp_event_queue.min();
    tmp_event_queue.removeMin();
    cout << "  " << *event_ptr << endl;
  }
}


void Simulator::printJobStatusRecord() {
  cout << "Job Status:" << endl;
  for(JobStatusRecord::Iterator iter = job_status_record.begin(); !(iter == job_status_record.end()); ++iter) {
    JobStatusRecord::Entry entry = *iter;
    cout << "  Job " << entry.key() << ": " << entry.value() << endl;
  }
}


void Simulator::freeMachine() {
  busy_machine_num--;

  // if there is a free machine, push a job out of the job queue and schedule it.
  if (busy_machine_num == machine_num-1 && !job_queue.empty()) {
    Job job = job_queue.min();
    job_queue.removeMin();
    job_status_record[job.job_id] = JobStatus::UNQUEUED;
    EventQueue::Position p = event_queue.insert(new AddJobEvent(current_time, job.job_id, job.duration));
    job_status_record[job.job_id].event_queue_add_pos = p;     // remember the position of the add job event in the event queue
  }
}


ostream& operator<<(ostream &out, const Simulator::JobStatus& js) {
  switch(js.status) {
    case Simulator::JobStatus::QUEUED:
      out << "QUEUED";
      break;
    case Simulator::JobStatus::UNQUEUED:
      out << "UNQUEUED";
      break;
    case Simulator::JobStatus::SCHEDULED:
      out << "SCHEDULED";
      break;
    case Simulator::JobStatus::STARTED:
      out << "STARTED";
      break;
    case Simulator::JobStatus::ENDED:
      out << "ENDED";
      break;
    case Simulator::JobStatus::REMOVED:
      out << "REMOVED";
      break;
  }
  return out;
}

