//---------- COLORS
typedef struct color_s {
	unsigned int red;
	unsigned int green;
	unsigned int blue;
} Color;



//---------- NODES/PATH
typedef struct node_s {
	float x;
	float y;
	struct node_s* next;
} Node;
typedef Node* Path;



//---------- MAP
typedef struct map_s {
	char* fichierPPM;
	unsigned int energie; 	// Nb unité d'énergie produit par les centrales (wtf?!) 
	Color path;
	Color nodes;
	Color buildingAreas;
	Color in;
	Color out;
	unsigned int nbNodes;
	Node* listNodes;
} Map;



//---------- MONSTERS
typedef enum MonsterType_s {
	SLOW_MONSTER, FAST_MONSTER
} MonsterType;

typedef struct monster_s {
	MonsterType type; 		// Dépend de la vitesse du monstre et d'autres caractéristiques
	unsigned int lifePoints;
	unsigned int resistance;
	float speed;
} Monster;



//---------- TOWERS
typedef enum TowerType_s {
	ROCKET, LASER, MITRAILLETTE, HYBRIDE
} TowerType;

typedef struct tower_s {
	TowerType type;
	Puissance; 				// dégâts infligés par la tour
	unsigned int reach; 	// Portée : distance de tir en pixels
	float cadence;			// Intervalle entre deux tirs (1/10s.)
	float price;
} Tower;



//---------- PLAYER
typedef struct player_s {
	Budget initial
	Argent dépensé
	Argent gagné
} Player;
