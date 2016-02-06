# pasha_anc_co

```
#define FREE = 0
#define BUZY = 1
#define EXIT = 2
#define pointType unsigned char

class Point {
private:
	pointType type;
public:
	Point(pointType type);
};

class Pin {
private:
	int x, y, z;
public:
	Pin(int x,int y, int z);
};

class Map {
private:
	Point*** map; // std::vector;
public:
	void takePoint(int x, int y, int z);
	bool isTakenPoint(int x, int y, int z);
	void thin();

	void takePoint(int x, int y, int z) {
	
	}
	bool isTakenPoint(int x, int y, int z);
};
```
