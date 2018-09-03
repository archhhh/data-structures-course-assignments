//
// assignment4.h  (Version 1.0)
//
// Please write your name, your student ID, and your email here.
// Moreover, please describe the implementation of your functions here.
// You will have to submit this file.
//
// Artyom Chen, 20162017, artychen13@unist.ac.kr
/*
  calcRouteDistance simply adds the values of the edges between the following vertices to the result and
  returns the result. throws all the necessary exceptions.
  findRoute uses DFS to find the route. findRouteUtil is implemented to be utilized in findRoute.
  findReachableAirports uses findRoute to find all the reachable airports.
  findShortestRoute implements Dijkstra Algorithm as described in the textbook.
  printAllShortestRoutes uses findShortestRouteto find all the shortest routes.

*/
#include <iostream>
#include <string>
#include <stdexcept>
#include <queue>
#include <list>
#include <vector>
#include <map>
#include <limits>
#include "AdjacencyListDirectedGraph.h"
#include "FlightMap.h"


double FlightMap::calcRouteDistance(const list<string> route) {
  double result = 0;
  for(list<string>::const_iterator iter = route.begin(), next = ++route.begin(); next != route.end(); ++iter, ++next){
    if(!isAirportExist(*iter))
      throw runtime_error("Airport does not exist.");
    if(!isConnectionExist(*iter, *next))
      throw runtime_error("No connection.");
    FlightGraph::Vertex v1, v2;
    findAirport(v1, *iter);
    findAirport(v2, *next);
    result += *(v1.outgoingEdge(v2));
  }
  return result;

}


list<string> FlightMap::findRoute(const string &airport1, const string &airport2) {
  if(!isAirportExist(airport1) || !isAirportExist(airport2))
    throw runtime_error("Airport does not exist.");
  list<string> ans;
  map <string, bool> visited;
  map<string, FlightGraph::Vertex>::iterator iter = airport_db.begin();
  while(iter != airport_db.end()){
    visited[iter->first] = false;
    iter++;
  }
  map <string, string> before;
  before[airport1] = "";
  findRouteUtil(ans, airport1, airport2, visited, before);
  return ans;

}


list<string> FlightMap::findReachableAirports(const string &airport) {
  if(!isAirportExist(airport))
    throw runtime_error("Airport does not exist.");
  map<string, FlightGraph::Vertex>::iterator iter = airport_db.begin();
  list <string> ans;
  while(iter != airport_db.end()){
    if(iter->first != airport)
    {
      list<string>route = findRoute(iter->first, airport);
      if(route.size() != 0)
        ans.push_back(iter->first);
    }
    iter++;
  }
  return ans;

}


list<string> FlightMap::findShortestRoute(const string &airport1, const string &airport2) {
  if(!isAirportExist(airport1) || !isAirportExist(airport2))
    throw runtime_error("Airport does not exist.");
  map <string, bool> visited;
  map <string, double> distance;
  map<string, FlightGraph::Vertex>::iterator iter = airport_db.begin();
  while(iter != airport_db.end()){
    visited[iter->first] = false;
    distance[iter->first] = 99999999;
    iter++;
  }
  map <string, string> before;
  before[airport1] = "";
  distance[airport1] = 0;
  priority_queue < pair<string, double>, vector< pair<string, double> >, greater > min_heap;
  iter = airport_db.begin();
  while(iter != airport_db.end())
  {
    min_heap.push(pair<string, double>(iter->first, distance[iter->first]));
    ++iter;
  }
  while(!min_heap.empty())
  {
    if(visited[(min_heap.top()).first])
    {
      min_heap.pop();
    }else{
      visited[(min_heap.top()).first] = true;
      string u = (min_heap.top()).first;
      min_heap.pop();
      iter = airport_db.begin();
      while(iter != airport_db.end()){
        if(u != iter->first && isConnectionExist(u, iter->first))
        {
          FlightGraph::Vertex v1, v2;
          findAirport(v1, u);
          findAirport(v2, iter->first);
          if(distance[u]+*(v1.outgoingEdge(v2)) < distance[iter->first])
          {
            distance[iter->first] = distance[u]+*(v1.outgoingEdge(v2));
            min_heap.push(pair<string, int>(iter->first, distance[iter->first]));
            before[iter->first] = u;
          }
        }
        iter++;
      }
    }
  }
  list <string> ans;
  if(distance[airport2] != 99999999)
  {
    string airport = airport2;
    while(airport != "")
    {
        ans.push_front(airport);
        airport = before[airport];
    }
  }
  return ans;

}


void FlightMap::printAllShortestRoutes(const string &airport) {
  if(!isAirportExist(airport))
    throw runtime_error("Airport does not exist.");
  map<string, FlightGraph::Vertex>::iterator iter = airport_db.begin();
  while(iter != airport_db.end()){
    if(iter->first != airport)
    {
      list<string>route = findShortestRoute(airport, iter->first);
      if(route.size() != 0)
      {
        printRoute(route);
        double distance = calcRouteDistance(route);
        cout << " (Distance = " << distance << ")\n";
      }
    }
    iter++;
  }

}
void FlightMap::findRouteUtil(list<string>& ans,const string &airport1, const string &airport2,  map <string, bool> &visited,   map <string, string> &before){
  visited[airport1] = true;
  if(airport1 == airport2)
  {
    string airport = airport1;
    while(airport != "")
    {
        ans.push_front(airport);
        airport = before[airport];
    }
  }else{
    map<string, FlightGraph::Vertex>::iterator iter = airport_db.begin();
    while(iter != airport_db.end()){
      if(airport1 != iter->first && isConnectionExist(airport1, iter->first) && !visited[iter->first])
      {
        before[iter->first] = airport1;
        findRouteUtil(ans, iter->first, airport2, visited, before);
      }
      iter++;
    }
  }
}
