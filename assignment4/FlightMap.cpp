//
// FlightMap.cpp  (Version 1.0)
//
// This file is created by Tsz-Chiu Au on 10/30/17.
//
// You are *not* allowed to modify this file, and
// you do *not* submit this file.
//

#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <map>
#include <list>
#include "AdjacencyListDirectedGraph.h"
#include "FlightMap.h"
#include <queue>

FlightMap::FlightGraph::Vertex FlightMap::findOrCreateAirport(const string &airport) {
  try {
    return airport_db.at(airport);
  } catch (const out_of_range &e) {
    return (airport_db[airport] = flight_graph.insertVertex(airport));
  }
}

bool FlightMap::findAirport(FlightGraph::Vertex &vertex, const string &airport) {
  try {
    vertex = airport_db.at(airport);
    return true;
  } catch (const out_of_range &e) {
    return false;
  }
}

void FlightMap::printConnection(const FlightGraph::Edge &edge) {
  cout << *edge.origin() << " -> " << *edge.dest() << " (" << *edge << ")";
}

bool FlightMap::isAirportExist(const string &airport) {
  try {
    airport_db.at(airport);
    return true;
  } catch (const out_of_range &e) {
    return false;
  }
}

bool FlightMap::isConnectionExist(const string &airport1, const string &airport2) {
  FlightGraph::Vertex v1, v2;
  if (findAirport(v1, airport1) && findAirport(v2, airport2)) {
    return v1.isOutgoingTo(v2);
  } else {
    return false;
  }
}

void FlightMap::readFromFile(const string &filename) {
  ifstream infile(filename.c_str());

  if (!infile.is_open()) {
    throw runtime_error("Cannot open the file.");
  }

  // read all data first, make sure there is no data corruption
  int count = 0;
  list<string> airports1, airports2;
  list<double> distances;

  string a1, a2;
  double dist;
  while (infile.good()) {
    if (infile >> a1) {
      if (infile >> a2 >> dist) {
        airports1.push_back(a1);
        airports2.push_back(a2);
        distances.push_back(dist);
        if (isConnectionExist(a1, a2)) {
          throw runtime_error("Connection (" + a1 + " -> " + a2 + ") has already existed.");
        }
      } else {
        throw runtime_error("Data corrupted in the file.");
      }
    } else {
      break;  // no more data
    }
    count++;
  }
  infile.close();

  // store the data in flight_graph
  list<string>::const_iterator airport_iter1 = airports1.begin();
  list<string>::const_iterator airport_iter2 = airports2.begin();
  list<double>::const_iterator dist_iter = distances.begin();
  for (int i = 0; i < count; i++) {
    FlightGraph::Vertex v1 = findOrCreateAirport(*airport_iter1);
    FlightGraph::Vertex v2 = findOrCreateAirport(*airport_iter2);
    if (v1.isOutgoingTo(v2)) {
      throw runtime_error("Connection (" + *v1 + " -> " + *v2 + ") is duplicated.");
    } else {
      flight_graph.insertDirectedEdge(v1, v2, *dist_iter);
    }
    airport_iter1++;
    airport_iter2++;
    dist_iter++;
  }
}

void FlightMap::addAirport(const string &airport) {
  if (isAirportExist(airport)) {
    throw runtime_error(airport + "has already existed.");
  } else {
    airport_db[airport] = flight_graph.insertVertex(airport);
  }
}

void FlightMap::removeAirport(const string &airport) {
  FlightGraph::Vertex v;
  if (findAirport(v, airport)) {
    flight_graph.eraseVertex(v);
    airport_db.erase(airport);
  } else {
    throw runtime_error(airport + " do not exist.");
  }
}

void FlightMap::addConnection(const string &airport1, const string &airport2, double dist) {
  FlightGraph::Vertex v1, v2;
  if (!findAirport(v1, airport1)) {
    throw runtime_error(airport1 + " does not exist.");
  }
  if (!findAirport(v2, airport2)) {
    throw runtime_error(airport2 + " does not exist.");
  }
  if (dist <= 0.0) {
    throw runtime_error("Distance must be a positive number.");
  }
  if (v1.isOutgoingTo(v2)) {
    throw runtime_error("Connection (" + airport1 + " -> " + airport2 + ") has already existed.");
  }
  flight_graph.insertDirectedEdge(v1, v2, dist);
}

void FlightMap::addRoundTripConnection(const string &airport1, const string &airport2, double dist) {
  FlightGraph::Vertex v1, v2;
  if (!findAirport(v1, airport1)) {
    throw runtime_error(airport1 + " does not exist.");
  }
  if (!findAirport(v2, airport2)) {
    throw runtime_error(airport2 + " does not exist.");
  }
  if (dist <= 0.0) {
    throw runtime_error("Distance must be a positive number.");
  }
  if (v1.isOutgoingTo(v2) || v2.isOutgoingTo(v1)) {
    throw runtime_error("Connection between " + airport1 + " and " + airport2 + " exist.");
  }
  flight_graph.insertDirectedEdge(v1, v2, dist);
  flight_graph.insertDirectedEdge(v2, v1, dist);
}

void FlightMap::removeConnection(const string &airport1, const string &airport2) {
  FlightGraph::Vertex v1, v2;
  if (!findAirport(v1, airport1)) {
    throw runtime_error(airport1 + " does not exist.");
  }
  if (!findAirport(v2, airport2)) {
    throw runtime_error(airport2 + " does not exist.");
  }
  if (!v1.isOutgoingTo(v2)) {
    throw runtime_error(airport1 + " does not connect to " + airport2 + ".");
  }
  FlightGraph::Edge edge = v1.outgoingEdge(v2);
  flight_graph.eraseEdge(edge);
}

void FlightMap::printFlightMap() {
  cout << "Airports: " << endl;
  FlightGraph::VertexList vlist = flight_graph.vertices();
  for (FlightGraph::VertexItor iter = vlist.begin(); iter != vlist.end(); ++iter) {
    cout << "  " << **iter;
  }
  cout << endl;
  cout << "Flight Connections: " << endl;
  FlightGraph::EdgeList edge_list = flight_graph.edges();
  for (FlightGraph::EdgeItor iter = edge_list.begin(); iter != edge_list.end(); ++iter) {
    cout << "  " << *(iter->origin()) << " -> " << *(iter->dest()) << " (Distance = " << **iter << ")" << endl;
  }
  cout << "Outgoing Connections: " << endl;
  for (FlightGraph::VertexItor iter = vlist.begin(); iter != vlist.end(); ++iter) {
    cout << "  " << **iter << " ->";
    FlightGraph::EdgeList elist = iter->outgoingEdges();
    for (FlightGraph::EdgeItor iter = elist.begin(); iter != elist.end(); ++iter) {
      cout << " " << *(iter->dest()) << " (" << **iter << ") ";
    }
    cout << endl;
  }
}

void FlightMap::printAirportInfo(const string &airport) {
  FlightGraph::Vertex v;
  if (!findAirport(v, airport)) {
    throw runtime_error(airport + " do not exist.");
  }
  cout << "Airport Name: " << *v << endl;
  cout << "Incident Connections:" << endl;
  FlightGraph::EdgeList edge_list = v.incidentEdges();
  for(FlightGraph::EdgeItor iter = edge_list.begin(); iter != edge_list.end(); ++iter) {
    cout << "  ";
    printConnection(*iter);
    cout << endl;
  }
  cout << "Adjacent to these airports:" << endl;
  cout << " ";
  FlightGraph::VertexList all_vertex_list = flight_graph.vertices();
  for(FlightGraph::VertexItor iter = all_vertex_list.begin(); iter != all_vertex_list.end(); ++iter) {
    if (v.isAdjacentTo(*iter)) {
      cout << " " << **iter;
    }
  }
  cout << endl;
  cout << "Outgoing connections to these airports:" << endl;
  cout << " ";
  for(FlightGraph::VertexItor iter = all_vertex_list.begin(); iter != all_vertex_list.end(); ++iter) {
    if (v.isOutgoingTo(*iter)) {
      cout << " " << **iter;
    }
  }
  cout << endl;

  cout << "All outgoing connections:" << endl;
  FlightGraph::EdgeList elist = v.outgoingEdges();
  for(FlightGraph::EdgeItor iter = elist.begin(); iter != elist.end(); ++iter) {
    cout << "  ";
    printConnection(*iter);
  }
  cout << endl;

  int count = 0;
  for(FlightGraph::VertexItor iter = all_vertex_list.begin(); iter != all_vertex_list.end(); ++iter) {
    if (v == *iter) {
      count++;
    }
  }
  if (count != 1) {
    throw runtime_error("Cannot have more than one airport: " + airport + ".");
  }
}

void FlightMap::printConnectionInfo(const string &airport1, const string &airport2) {
  FlightGraph::Vertex v1, v2;
  if (!findAirport(v1, airport1)) {
    throw runtime_error(airport1 + " does not exist.");
  }
  if (!findAirport(v2, airport2)) {
    throw runtime_error(airport2 + " does not exist.");
  }
  if (!v1.isOutgoingTo(v2)) {
    throw runtime_error(airport1 + " does not connect to " + airport2 + ".");
  }
  FlightGraph::Edge edge = v1.outgoingEdge(v2);

  cout << "Connection: ";
  printConnection(edge);
  cout << (edge.isDirected()?" directed":" undirected") << endl;

  cout << "Incident airports: ";
  FlightGraph::VertexList end_vertices = edge.endVertices();
  cout << *(end_vertices.front()) << " and " << *(end_vertices.back()) << endl;
  if (end_vertices.size() != 2) {
    throw runtime_error("Cannot have more than two endpoints.");
  }
  if ( !( end_vertices.front() == edge.origin()) ) {
    throw runtime_error("Origin is different from the front endpoint.");
  }
  if ( !( end_vertices.back() == edge.dest()) ) {
    throw runtime_error("Destination is different from the back endpoint.");
  }
  if ( !( edge.origin() == edge.opposite(edge.dest()) ) ) {
    throw runtime_error("Origin is not the opposite of the destination.");
  }
  if ( !( edge.dest() == edge.opposite(edge.origin()) ) ) {
    throw runtime_error("Destination is not the opposite of the origin.");
  }
  cout << "All incident vertices:" << endl;
  cout << " ";
  FlightGraph::VertexList all_vertex_list = flight_graph.vertices();
  for(FlightGraph::VertexItor iter = all_vertex_list.begin(); iter != all_vertex_list.end(); ++iter) {
    if (edge.isIncidentOn(*iter)) {
      cout << " " << **iter;
    }
  }
  cout << endl;

  cout << "All adjacent connections:" << endl;
  FlightGraph::EdgeList all_edge_list = flight_graph.edges();
  for(FlightGraph::EdgeItor iter = all_edge_list.begin(); iter != all_edge_list.end(); ++iter) {
    if (edge.isAdjacentTo(*iter)) {
      cout << "  ";
      printConnection(*iter);
      cout << endl;
    }
  }

  int count = 0;
  for(FlightGraph::EdgeItor iter = all_edge_list.begin(); iter != all_edge_list.end(); ++iter) {
    if (edge == *iter) {
      count++;
    }
  }
  if (count != 1) {
    throw runtime_error("This connection appears more than one time.");
  }
}

void FlightMap::printRoute(const list<string> route) {
  bool isFirst = true;
  for(list<string>::const_iterator iter = route.begin(); iter != route.end(); ++iter) {
    if (isFirst) {
      isFirst = false;
    } else {
      cout << " -> ";
    }
    cout << *iter;
  }
}
/* -- */
double FlightMap::calcRouteDistance(const list<string> route){
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
list<string> FlightMap::findRoute(const string &airport1, const string &airport2){
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
list<string> FlightMap::findReachableAirports(const string &airport){
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
void FlightMap::printAllShortestRoutes(const string &airport){
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

list<string> FlightMap::findShortestRoute(const string &airport1, const string &airport2){
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
