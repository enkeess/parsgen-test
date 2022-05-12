#include "../include/Parser.h"

#include <iostream>

Parser::Parser(
	const char* filename,
	std::vector<LGraph> graphs
): 
	scanner(filename),
	graphs(graphs) 
{
	for(auto& graph: graphs) {
		if(graph.getId() == DEFAULT_GRAPH_ID) {
			curGraph = graph;
			for(auto& v: graph.getVertices()) {
				if(v.getId() == DEFAULT_STATE_ID) {
					curVertex = v;
					break;
				}
			}
			break;
		}
	}
}

std::set<std::string> Parser::getLexeme(Vertex v) {
	return scanner.getLexeme(v.getPossibleStr());
}

bool Parser::run() {

	std::cout << "\n***** TRACE ROUTE *****\n\n";
	
	std::set<std::string> lexeme = {};
	std::vector<Edge> transition = {};

	for(lexeme = getLexeme(curVertex); lexeme.size() > 0; lexeme = getLexeme(curVertex)) {
		
		if(scanner.isEOF()) {
			break;
		}

		std::cout << curVertex.getName() << " -> ";

		std::string str = "";
		transition.clear();

		for(auto& edge: curVertex.getEdges()) {
			for(auto& dir: edge.getDirect()) {
				if(lexeme.count(dir.getLabel())) {
					transition.push_back(edge);
					break;
				}
			}
		}
		
		Edge edge;

		bool isNewEdge = false;

		if(transition.size() == 1) { 
			edge = transition[0];
			isNewEdge = true;
		} else { 
			if(!bracketTrace.empty()) { 
				Mark onTop = bracketTrace.top();

				for(auto& e: transition) {
					for(auto& dir: e.getDirect()) {
						if(dir.getMark().getType()  == CLOSE && 
						   dir.getMark().getLabel() == onTop.getLabel()) 
						{
							edge = e;

							isNewEdge = true;
							break;
						}
					}

					if(isNewEdge) {
						break;
					}
				}
			}

			if(!isNewEdge) {
				for(auto& e: transition) {
					for(auto& dir: e.getDirect()) {
						if(dir.getMark().getType() != CLOSE && 
						   dir.getLabel() != "") 
						{
							edge = e;
							isNewEdge = true;
							break;
						}
					}

					if(isNewEdge) {
						break;
					}
				}
			}

			if(!isNewEdge) {
				for(auto& e: transition) {
					for(auto& dir: e.getDirect()) {
						if(dir.getMark().getType() != CLOSE && 
						   dir.getLabel() == "") 
						{
							edge = e;
							isNewEdge = true;
							break;
						}
					}

					if(isNewEdge) {
						break;
					}
				}
			}		
		}

		if(!isNewEdge) {
			throw "NOT_FOUND_EDGE_FOR_TRANSFER";
		}

		scanner.updateFileShift(edge.getLabel());
		for(auto& v: curGraph.getVertices()) {
			if(v.getId() == edge.getTo()) {
				curVertex = v;
				std::cout << curVertex.getName() << ", by: '" << edge.getLabel() << "'; "; 
				std::cout << edge.getMark().print() << "\n";
				updateBracketTrace(edge.getMark());
				break;
			}
		}
	}

	while(!bracketTrace.empty() || !curGraph.getFinish().count(curVertex.getId())) {
		std::vector<Edge> transition = {};

		std::cout << curVertex.getName() << " -> ";

		transition.clear();

		for(auto& edge: curVertex.getEdges()) {
			if(edge.getLabel() == "") {
				transition.push_back(edge);
			}
		}
		
		Edge edge;

		bool isNewEdge = false;

		if(transition.size() == 0) {
			break;
		} 

		if(transition.size() == 1) {
			edge = transition[0];
			isNewEdge = true;
		} else {
			if(!bracketTrace.empty()) { 
				Mark onTop = bracketTrace.top();

				for(auto& e: transition) {
					if( e.getMark().getType()  == CLOSE && 
						e.getMark().getLabel() == onTop.getLabel()) 
					{
						edge = e;
						isNewEdge = true;
						break;
					}
		
					if(isNewEdge) {
						break;
					}
				}
			}

			if(!isNewEdge) {
				for(auto& e: transition) {
					if(e.getMark().getType() != CLOSE) {
						edge = e;
						isNewEdge = true;
						break;
					}
				}

				if(isNewEdge) {
					break;
				}
			}
		}

		for(auto& v: curGraph.getVertices()) {
			if(v.getId() == edge.getTo()) {
				curVertex = v;
				std::cout << curVertex.getName() << ", by: '" << edge.getLabel() << "'; "; 
				
				std::cout << edge.getMark().print() << "\n";
				updateBracketTrace(edge.getMark());
				break;
			}
		}
	}
	

	std::cout << "\n***** TRACE ROUTE *****\n";

	if(!curGraph.getFinish().count(curVertex.getId())) {
		throw "STATE_ERROR_NON_FINISH_STATE";
	}

	if(!scanner.isEOF()) { 
		throw "STATE_ERROR_EMPTY_SET_POSSIBLE_STR";
	}

	if(!bracketTrace.empty()) {
		throw "BRACKET_TRACE_ERROR_NON_EMPTY_STACK";
	}

	return true;
};

void Parser::updateBracketTrace(Mark m) {
	switch (m.getType()) {
		case(OPEN): 
			bracketTrace.push(m);
			break;
		case(CLOSE):
			if(!bracketTrace.empty()) { 
				Mark onTop = bracketTrace.top();
				if(onTop.getLabel() == m.getLabel()) {
					bracketTrace.pop();
				} else {
					std::cout << onTop.getLabel() << " vs " << m.getLabel() << '\n';
					throw "BRACKET_TRACE_ERROR_NON_PAIR_LABEL";
				}

			} else throw "BRACKET_TRACE_ERROR_PUSH_)_TO_EMPTY_STACK";

			break;
		default: 
			break;
	}
}