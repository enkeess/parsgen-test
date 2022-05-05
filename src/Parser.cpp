#include "../include/Parser.h"

#include <iostream>

Parser::Parser(
	const char* filename,
	std::vector<LGraph> graphs // all graphs
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
	std::cout << "***** TRACE ROUTE *****\n";
	
	std::set<std::string> lexeme = {};
	std::vector<Edge> transition = {};

	// std::string str = "";

	for(lexeme = getLexeme(curVertex); lexeme.size() > 0; lexeme = getLexeme(curVertex)) {

		std::string str = "";
		// str = std::string(curVertex.getId());
		// std::cout << curVertex.getId() << " -> ";
		std::cout << curVertex.getName() << " -> ";
		transition.clear();
		for(auto& edge: curVertex.getEdges()) {
			if(lexeme.count(edge.getLabel())) {
				transition.push_back(edge);
			}
		}

		Edge edge;

		// будет как минимум одна альтернатина иначе мы не зайдем в цикл for вообще
		if(transition.size() == 1) { // единственная альтернатива осуществляется переход
			edge = transition[0];
		} else { // есть несколько альтернатив надо смотреть скобочный след
			Mark onTop = bracketTrace.top();
			bool wasFind = false;
			for(auto& e : transition) {
				std::vector<Mark> mark = e.getMark();
				Mark markFirst = mark[0];

				if(onTop.getType() == markFirst.getType()) { // переход найден
					wasFind = true;
					bracketTrace.push(onTop);
					edge = e;
					break;
				}
			}
		}

		scanner.updateFileShift(edge.getLabel());
		for(auto& v: curGraph.getVertices()) {
			if(v.getId() == edge.getTo()) {
				curVertex = v;
				for(auto& item: edge.getTrace()) {
					std::cout << item << ", by: ''\n" << item << " -> ";
				}
				std::cout << curVertex.getName() << ", by: '" << edge.getLabel() << "'\n";
				updateBracketTrace(edge.getMark());
				break;
			}
		}

		// std::cout << "NEW VERTEX: " << curVertex.getId() << "\n";
	} 

	std::cout << "***** TRACE ROUTE *****\n";

	// 0. не найдено ни одного токена для перехода


	// 1. Финальное состояние
	if(!curGraph.getFinish().count(curVertex.getId())) {
		throw "STATE_ERROR_non_finish_state";
	}

	// 2. Скобочный след пустой
	if(!bracketTrace.empty()) {
		throw "Bracket_Trace_Error_non_empty_stack";
	}

	// 3. Вложенность графов надо проверить
	// if(!graphsStack.empty()) {

	// }

	// 4. Файл закончился
	if(!scanner.isEOF()) { // файл не закончился
		throw "STATE_ERROR_empty_set_possible_str";
	}
	
	return true;
};

void Parser::updateBracketTrace(std::vector<Mark> mark) {
	for(auto& m: mark) {
		switch (m.getType()) {
			case(OPEN): 
				bracketTrace.push(m);
				break;
			case(CLOSE):
				if(!bracketTrace.empty()) { // стек не пуст 
					// 1. Взять элемент с вершины стека и посмотреть на него
					Mark onTop = bracketTrace.top();
					if(onTop.getLabel() == m.getLabel()) {
						bracketTrace.pop();
					} else throw "Bracket_Trace_Error_non_pair_label";

				} else throw "Bracket_Trace_Error_push_close_to_empty_stack";

				break;
			default: 
				break;
		}
	}
}


