#include "../include/Dependencies.h"

// L(D) = (a^nb^n, n>=1)

std::vector<LGraph> _graphs = { LGraph(
	"_main", 0, {1}, {2}, { Vertex(
		"A", 1, {
			Edge(1, "a", Mark(OPEN,""), {
				Direct("a", Mark(OPEN,""))
			}),
			Edge(2, "b", Mark(CLOSE,""), {
				Direct("b", Mark(CLOSE,""))
			})
		}), Vertex(
		"B", 2, {
			Edge(2, "b", Mark(CLOSE,""), {
				Direct("b", Mark(CLOSE,""))
			})
		})
	})
};


 