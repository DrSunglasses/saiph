#ifndef SAIPH_H
/* defines */
#define SAIPH_H
/* general defines */
#define MAX_BRANCHES 6
#define MAX_DUNGEON_DEPTH 64
/* branches */
#define BRANCH_MAIN 0
#define BRANCH_MINES 1
#define BRANCH_SOKOBAN 2
#define BRANCH_VLAD 3
#define BRANCH_WIZARD 4
#define BRANCH_ASTRAL 5
/* pathing */
#define COST_CARDINAL 2
#define COST_DIAGONAL 3
#define COST_ICE 8 // slippery and risky, try to find a way around (don't try very hard, though)
#define COST_LAVA 512 // lava, hot!
#define COST_PET 16 // try not to move onto pets
#define COST_TRAP 128 // avoid traps
#define COST_WATER 256 // avoid water if possible
#define PATHING_QUEUE_SIZE 4096 // max amount of nodes in pathing_queue
/* movement */
#define MOVE_NW 'y'
#define MOVE_N 'k'
#define MOVE_NE 'u'
#define MOVE_W 'h'
#define MOVE_E 'l'
#define MOVE_SW 'b'
#define MOVE_S 'j'
#define MOVE_SE 'n'
#define MOVE_UP '<'
#define MOVE_DOWN '>'
#define ILLEGAL_MOVE 0
/* actions */
#define REST '.'
#define ILLEGAL_ACTION 0
/* actions that will be moved somewhere else */
#define ELBERETH "Elbereth\n"
#define ENGRAVE 'E'
#define PRAY "#pray\n"
#define SEARCH 's'
/* common answers to questions */
#define HANDS '-'
#define NO 'n'
#define YES 'y'

/* forward declare */
class Saiph;

/* includes */
#include <list>
#include <string>
#include <vector>
#include "Analyzer.h"
#include "Connection.h"
#include "Globals.h"
#include "Map.h"
#include "MonsterTracker.h"
#include "Player.h"
#include "Point.h"
#include "Request.h"
#include "World.h"
/* analyzers */
#include "Analyzers/Door.h"
#include "Analyzers/Explore.h"
#include "Analyzers/Fight.h"
#include "Analyzers/Health.h"

/* namespace */
using namespace std;

/* struct used for pathing */
struct PathNode {
	PathNode *nextnode;
	unsigned int cost;
	unsigned char move;
};

/* this is our AI */
class Saiph {
	public:
		/* variables */
		MonsterTracker *monstertracker;
		World *world;
		Map map[MAX_BRANCHES][MAX_DUNGEON_DEPTH];
		int current_branch;
		int current_level;
		string command;
		string messages;
		bool engulfed;

		/* constructors */
		Saiph(bool remote);

		/* destructor */
		~Saiph();

		/* methods */
		void farlook(const Point &target);
		void registerAnalyzerSymbols(Analyzer *analyzer, const vector<unsigned char> &symbols);
		bool requestAction(const Request &request);
		bool run();
		unsigned char shortestPath(const Point &target, bool allow_illegal_last_move, int *distance, bool *straight_line);

	private:
		/* variables */
		vector<Analyzer *> analyzers;
		vector<Analyzer *> analyzer_symbols[UCHAR_MAX + 1];
		Connection *connection;
		PathNode pathmap[MAP_ROW_END + 1][MAP_COL_END + 1];
		Point pathing_queue[PATHING_QUEUE_SIZE];
		int pathcost[UCHAR_MAX + 1];
		bool item[UCHAR_MAX + 1];
		bool monster[UCHAR_MAX + 1];
		bool passable[UCHAR_MAX + 1];
		bool static_dungeon_symbol[UCHAR_MAX + 1];
		unsigned char uniquemap[UCHAR_MAX + 1][UCHAR_MAX + 1];

		/* methods */
		void dumpMaps();
		void inspect();
		void updateMaps();
		void updatePathMap();
		bool updatePathMapHelper(const Point &to, const Point &from);
};
#endif
