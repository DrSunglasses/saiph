#ifndef ANALYZER_EXPLORE_H
#define ANALYZER_EXPLORE_H

#include <map>
#include <string>
#include "Analyzer.h"
#include "../Coordinate.h"
#include "../Point.h"

/* search interval */
#define EXPLORE_SEARCH_INTERVAL 16
/* priorities */
#define PRIORITY_EXPLORE_ROGUE 100
#define PRIORITY_EXPLORE_STAIRS_UP 90
#define PRIORITY_EXPLORE_LEVEL 80
#define PRIORITY_EXPLORE_STAIRS_DOWN 90
#define PRIORITY_EXPLORE_MAGIC_PORTAL 90

namespace analyzer {

	class Explore : public Analyzer {
	public:
		Explore();

		void parseMessages(const std::string& messages);
		void analyze();
		void onEvent(event::Event * const event);

	private:
		std::map<Coordinate, int> _visit;
		std::map<int, int> _explore_levels;

		void explorePoint(Point p, unsigned int* min_cost, int* best_type, unsigned char* best_direction);
	};
}
#endif