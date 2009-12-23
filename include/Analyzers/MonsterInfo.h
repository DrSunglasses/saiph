#ifndef ANALYZER_MONSTERINFO_H
#define ANALYZER_MONSTERINFO_H

#include <map>
#include <string>
#include "Analyzer.h"
#include "../Point.h"
#include "../Monster.h"

namespace analyzer {

	class MonsterInfo : public Analyzer {
	public:
		MonsterInfo();

		void analyze();
		void parseMessages(const std::string& messages);
		void actionCompleted();

	private:
		std::map<Point, Monster>::const_iterator _look_at;
		std::map<Point, unsigned int> _checked;
	};
}
#endif